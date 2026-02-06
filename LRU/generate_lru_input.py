#!/usr/bin/python3

import random
import string

def generate_key():
    # Generate a random user ID like "User_42"
    return f"User_{random.randint(1, 20)}"

def generate_value():
    # Generate a random 4-letter string
    return ''.join(random.choices(string.ascii_uppercase, k=4))

def main():
    # We will generate 100 operations
    # Since our C++ Cache will have capacity 5 (example),
    # requesting 20 different users ensures massive eviction/thrashing.
    
    with open("lru_input.txt", "w") as f:
        # First line: Set Capacity
        f.write("CAPACITY 5\n")
        
        for _ in range(100):
            # 70% chance to PUT (Write), 30% chance to GET (Read)
            if random.random() < 0.7:
                cmd = "PUT"
                key = generate_key()
                val = generate_value()
                f.write(f"{cmd} {key} {val}\n")
            else:
                cmd = "GET"
                key = generate_key()
                f.write(f"{cmd} {key}\n")

if __name__ == "__main__":
    main()
