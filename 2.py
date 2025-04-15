table = []
b = 0  # Table size
bucket = {}

def create():
    """Initialize the hash table and bucket."""
    global b, table, bucket
    b = int(input("Enter the table size: "))
    table = [[None, -1] for _ in range(b)]  # Reinitialize table
    bucket = {i: -1 for i in range(b)}  # Reinitialize bucket

def print_table():
    """Print the hash table."""
    print("\nHash Table:")
    for i in range(b):
        print(f"Index {i}: {table[i]}")
#        print("\n",table[i],end="->")
    print("")

def chain_insert(key):
    """Insert key using chaining method."""
    global b
    hash_index = key % b

    if table[hash_index][0] is None:
        table[hash_index][0] = key
        bucket[hash_index] = hash_index  # Store the chain starting point
        print(f"Inserted {key} at index {hash_index}")
    else:
        flag = False
        for i in range(b):
            new_index = (hash_index + i) % b
            if table[new_index][0] is None:  # Found an empty slot
                if bucket[hash_index] != -1:
                    table[bucket[hash_index]][1] = new_index  # Link previous chain
                bucket[hash_index] = new_index
                table[new_index][0] = key
                print(f"Inserted {key} at index {new_index} (chained from {hash_index})")
                flag = True
                break
        
        if not flag:
            print(f"Table full, key {key} not inserted.")

def chain_search(key):
    """Search for a key in the hash table."""
    global b
    hash_index = key % b

    if table[hash_index][0] == key:
        print(f"Key {key} found at index {hash_index}")
        return True
    else:
        chain = table[hash_index][1]
        while chain != -1:
            if table[chain][0] == key:
                print(f"Key {key} found at index {chain}")
                return True
            chain = table[chain][1]
    
    print(f"Key {key} not found.")
    return False

def chain_delete(key):
    """Delete a key from the hash table."""
    global b
    hash_index = key % b

    if table[hash_index][0] == key:
        table[hash_index] = [None, -1]
        print(f"Key {key} deleted from index {hash_index}")
    else:
        prev_chain = hash_index
        chain = table[hash_index][1]
        while chain != -1:
            if table[chain][0] == key:
                table[prev_chain][1] = table[chain][1]  # Remove from chain
                table[chain] = [None, -1]
                print(f"Key {key} deleted from index {chain}")
                return
            prev_chain = chain
            chain = table[chain][1]
        
        print(f"Key {key} not found.")

# Create the hash table
create()

while True:
    print("\n\t\t\t-----------**---------")
    print("\t\t\t| 0. Exit            |")
    print("\t\t\t| 1. Chaining        |")
    print("\t\t\t|____________________|")

    ch = int(input("Enter your choice: "))

    if ch == 1:
        while True:
            print("\n\t\t\t-----------**---------")
            print("\t\t\t| 0. BACK            |")
            print("\t\t\t| 1. INSERT          |")
            print("\t\t\t| 2. SEARCH          |")
            print("\t\t\t| 3. DELETE          |")
            print("\t\t\t|____________________|")

            ch2 = int(input("Enter your choice: "))

            if ch2 == 1:
                key = int(input("Enter the key to insert: "))
                chain_insert(key)
                print_table()
            
            elif ch2 == 2:
                key = int(input("Enter the key to search: "))
                chain_search(key)
                print_table()
            
            elif ch2 == 3:
                key = int(input("Enter the key to delete: "))
                chain_delete(key)
                print_table()
            
            elif ch2 == 0:
                print("Going back...")
                break
            
            else:
                print("Invalid choice. Try again.")
    
    elif ch == 0:
        print("Exiting...")
        print_table()
        break
    
    else:
        print("Invalid choice. Try again.")
