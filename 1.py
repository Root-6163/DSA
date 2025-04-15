class Record:
    def __init__(self):
        self._name = None
        self._number = None

    def get_name(self):
        return self._name

    def get_number(self):
        return self._number

    def set_name(self, name):
        self._name = name

    def set_number(self, number):
        self._number = number

    def __str__(self):
        return f"Name: {self.get_name()}\tNumber: {self.get_number()}"


class HashTable:
    def __init__(self):
        self.size = int(input("Enter the Size of the hash table: "))
        self.table = [None for _ in range(self.size)]
        self.elementCount = 0
        self.comparisons = 0

    def isFull(self):
        return self.elementCount == self.size

    def hashFunction(self, element):
        return element % self.size

    def insert(self, record):
        if self.isFull():
            print("Hash Table Full")
            return False

        isStored = False
        position = self.hashFunction(record.get_number())

        if self.table[position] is None:
            self.table[position] = record
            print(f"Phone number of {record.get_name()} is at position {position}")
            isStored = True
            self.elementCount += 1
        else:
            print(f"Collision occurred for {record.get_name()}'s phone number at position {position}, finding new position.")
            while self.table[position] is not None:
                position = (position + 1) % self.size
            self.table[position] = record
            print(f"Phone number of {record.get_name()} is at position {position}")
            isStored = True
            self.elementCount += 1
        return isStored

    def search(self, record):
        position = self.hashFunction(record.get_number())
        comparisons = 1

        if self.table[position] is not None and \
           self.table[position].get_name() == record.get_name() and \
           self.table[position].get_number() == record.get_number():
            print(f"Phone number found at position {position} with {comparisons} comparison(s)")
            return position

        start = position
        while True:
            position = (position + 1) % self.size
            comparisons += 1
            if self.table[position] is None or comparisons > self.size:
                break
            if self.table[position].get_name() == record.get_name() and \
               self.table[position].get_number() == record.get_number():
                print(f"Phone number found at position {position} with {comparisons} comparison(s)")
                return position

        print("Record not found")
        return False

    def display(self):
        print("\nHash Table Contents:")
        for i in range(self.size):
            print(f"Hash Value: {i}\t\t{self.table[i]}")
        print(f"Number of records: {self.elementCount}")


class DoubleHashTable:
    def __init__(self):
        self.size = int(input("Enter the Size of the hash table: "))
        self.table = [None for _ in range(self.size)]
        self.elementCount = 0
        self.comparisons = 0

    def isFull(self):
        return self.elementCount == self.size

    def h1(self, element):
        return element % self.size

    def h2(self, element):
        return 5 - (element % 5)

    def doubleHashing(self, record):
        i = 1
        while i <= self.size:
            newPosition = (self.h1(record.get_number()) + i * self.h2(record.get_number())) % self.size
            if self.table[newPosition] is None:
                return True, newPosition
            i += 1
        return False, -1

    def insert(self, record):
        if self.isFull():
            print("Hash Table Full")
            return False

        position = self.h1(record.get_number())

        if self.table[position] is None:
            self.table[position] = record
            print(f"Phone number of {record.get_name()} is at position {position}")
            self.elementCount += 1
        else:
            print(f"Collision occurred for {record.get_name()}'s phone number at position {position}, finding new position.")
            found, newPosition = self.doubleHashing(record)
            if found:
                self.table[newPosition] = record
                print(f"Phone number of {record.get_name()} is at position {newPosition}")
                self.elementCount += 1
            else:
                print("Could not insert the record after double hashing")
        return True

    def search(self, record):
        position = self.h1(record.get_number())
        comparisons = 1

        if self.table[position] is not None and self.table[position].get_name() == record.get_name():
            print(f"Phone number found at position {position} with {comparisons} comparison(s)")
            return position

        i = 1
        while i <= self.size:
            position = (self.h1(record.get_number()) + i * self.h2(record.get_number())) % self.size
            comparisons += 1
            if self.table[position] is None:
                break
            if self.table[position].get_name() == record.get_name():
                print(f"Phone number found at position {position} with {comparisons} comparison(s)")
                return position
            i += 1

        print("Record not found")
        return False

    def display(self):
        print("\nHash Table Contents:")
        for i in range(self.size):
            print(f"Hash Value: {i}\t\t{self.table[i]}")
        print(f"Number of records: {self.elementCount}")


def input_record():
    record = Record()
    name = input("Enter Name: ")
    number = int(input("Enter Number: "))
    record.set_name(name)
    record.set_number(number)
    return record


# Menu-driven program
def main():
    while True:
        print("\nMain Menu:")
        print("1. Linear Probing")
        print("2. Double Hashing")
        print("3. Exit")
        choice1 = int(input("Enter Choice: "))

        if choice1 == 1:
            h1 = HashTable()
            while True:
                print("\nLinear Probing Menu:")
                print("1. Insert")
                print("2. Search")
                print("3. Display")
                print("4. Back")
                choice2 = int(input("Enter Choice: "))
                if choice2 == 1:
                    record = input_record()
                    h1.insert(record)
                elif choice2 == 2:
                    record = input_record()
                    h1.search(record)
                elif choice2 == 3:
                    h1.display()
                elif choice2 == 4:
                    break
                else:
                    print("Invalid Choice")

        elif choice1 == 2:
            h2 = DoubleHashTable()
            while True:
                print("\nDouble Hashing Menu:")
                print("1. Insert")
                print("2. Search")
                print("3. Display")
                print("4. Back")
                choice2 = int(input("Enter Choice: "))
                if choice2 == 1:
                    record = input_record()
                    h2.insert(record)
                elif choice2 == 2:
                    record = input_record()
                    h2.search(record)
                elif choice2 == 3:
                    h2.display()
                elif choice2 == 4:
                    break
                else:
                    print("Invalid Choice")
        elif choice1 == 3:
            print("Exiting...")
            break
        else:
            print("Please Enter Valid Choice")


if __name__ == "__main__":
    main()
