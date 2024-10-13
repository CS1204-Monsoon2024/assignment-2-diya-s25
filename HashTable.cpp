#include <iostream>
#include <vector>

class HashTable {
public:
    HashTable(int size);
    void insert(int key);
    int search(int key);
    void remove(int key);
    void printTable() const;

private:
    int hashFunction(int key) const;
    void resize();
    bool isPrime(int n) const;
    int nextPrime(int n) const;

    std::vector<int> table;
    std::vector<bool> occupied; // Keeps track of whether an index is occupied
    int size;
    int count;
    double loadFactorThreshold;
};

// Constructor
HashTable::HashTable(int size) {
    this->size = nextPrime(size);
    count = 0;
    table.resize(this->size, -1);
    occupied.resize(this->size, false);
    this->loadFactorThreshold = 0.8;
}

// Hash Function
int HashTable::hashFunction(int key) const {
    return key % size;
}

// Insert Function
void HashTable::insert(int key) {
    // Check for duplicate key
    if (search(key) != -1) {
        std::cout << "Duplicate key insertion is not allowed" << std::endl;
        return;
    }

    // Resize if load factor exceeds threshold
    if ((double)count / size >= loadFactorThreshold) {
        resize();
    }

    int index = hashFunction(key);
    int i = 0;
    const int maxProbes = size; // Set maximum probing limit

    while (i < maxProbes && occupied[(index + i * i) % size]) {
        i++;
    }

    // Check if we reached the maximum probing limit
    if (i == maxProbes) {
        std::cout << "Max probing limit reached!" << std::endl;
        return;
    }

    // Insert the key
    index = (index + i * i) % size;
    table[index] = key;
    occupied[index] = true;
    count++;
}

// Search Function
int HashTable::search(int key) {
    int index = hashFunction(key);
    int i = 0;

    while (occupied[(index + i * i) % size]) {
        int probeIndex = (index + i * i) % size;
        if (table[probeIndex] == key) {
            return probeIndex;  // Return the index where the key is found
        }
        i++;
    }

    return -1;  // Return -1 if the key is not found
}

// Remove Function
void HashTable::remove(int key) {
    int index = hashFunction(key);
    int i = 0;
    const int maxProbes = size; // Set maximum probing limit

    while (i < maxProbes && occupied[(index + i * i) % size]) {
        if (table[(index + i * i) % size] == key) {
            occupied[(index + i * i) % size] = false;
            table[(index + i * i) % size] = -1; // Mark as empty
            count--;
            return;
        }
        i++;
    }

    // If the loop ends and the key wasn't found
    std::cout << "Element not found" << std::endl;
}

// Print Table Function
void HashTable::printTable() const {
    for (int i = 0; i < size; i++) {
        if (occupied[i]) {
            std::cout << table[i] << " ";
        } else {
            std::cout << "- ";
        }
    }
    std::cout << std::endl; // End the line after printing the table
}

// Resizing the table
void HashTable::resize() {
    int newSize = nextPrime(size * 2);
    std::vector<int> oldTable = table;
    std::vector<bool> oldOccupied = occupied;

    table = std::vector<int>(newSize, -1);
    occupied = std::vector<bool>(newSize, false);
    size = newSize;
    count = 0;

    for (int i = 0; i < oldTable.size(); i++) {
        if (oldOccupied[i]) {
            insert(oldTable[i]);
        }
    }
}

// Helper to check if a number is prime
bool HashTable::isPrime(int n) const {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Helper to find the next prime number greater than or equal to n
int HashTable::nextPrime(int n) const {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

int main_temp() {
    HashTable ht(7);  // Initialize with a prime size
    
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(40);

    std::cout << "Table after insertions:\n";
    ht.printTable();
    
    std::cout << "Searching for 30: " << (ht.search(30) ? "Found" : "Not Found") << "\n";
    std::cout << "Removing 30.\n";
    ht.remove(30);

    std::cout << "Table after deletion:\n";
    ht.printTable();

    return 0;
}
