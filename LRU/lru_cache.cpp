/**
 * @file lru_cache.cpp
 * @brief Stream-Processing LRU Cache.
 * Reads commands from Standard Input (stdin) to allow pipeline testing.
 */

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

template <typename K, typename V>
class LRUCache {
private:
    std::list<std::pair<K, V>> data_list;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> map_index;
    size_t capacity;

public:
    LRUCache(size_t cap) : capacity(cap) {}

    V get(K key) {
        auto it = map_index.find(key);
        if (it == map_index.end()) {
            return "NULL";
        }
        // Move accessed item to the front (Most Recent)
        data_list.splice(data_list.begin(), data_list, it->second);
        return it->second->second;
    }

    void put(K key, V value) {
        auto it = map_index.find(key);
        
        // 1. Update existing key
        if (it != map_index.end()) {
            it->second->second = value;
            data_list.splice(data_list.begin(), data_list, it->second);
            return;
        }

        // 2. Evict if at capacity
        if (data_list.size() == capacity) {
            K last_key = data_list.back().first;
            map_index.erase(last_key);
            data_list.pop_back();
        }

        // 3. Insert new key
        data_list.push_front({key, value});
        map_index[key] = data_list.begin();
    }
};

int main() {
    // 1. SETUP: Read Capacity from the input stream (stdin)
    std::string cmd;
    size_t cap;
    
    // Check if input stream is valid
    if (!(std::cin >> cmd >> cap)) {
        std::cerr << "Error: No input provided. Did you pipe the file? (./lru_cache < lru_input.txt)" << std::endl;
        return 1;
    }
    
    if (cmd != "CAPACITY") {
        std::cerr << "Error: Input must start with 'CAPACITY [int]'" << std::endl;
        return 1;
    }

    LRUCache<std::string, std::string> cache(cap);
    std::cout << "Engine Initialized. Capacity: " << cap << std::endl;

    // 2. THE LOOP: Process the stream line-by-line
    std::string command, key, value;
    
    while (std::cin >> command) {
        if (command == "PUT") {
            std::cin >> key >> value;
            cache.put(key, value);
            std::cout << "[WRITE] " << key << ": " << value << std::endl;
        } 
        else if (command == "GET") {
            std::cin >> key;
            std::string result = cache.get(key);
            if (result == "NULL") {
                std::cout << "[MISS ] " << key << " not found." << std::endl;
            } else {
                std::cout << "[HIT  ] " << key << " -> " << result << std::endl;
            }
        }
    }

    return 0;
}
