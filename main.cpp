#include "HashTable.cpp"

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 
    ht.remove(28);  
    ht.printTable(); 
    ht.insert(29);  
    ht.printTable(); 

    ht.insert(5);
    ht.printTable();
    ht.remove(10);
    ht.printTable();
    ht.insert(26);  
    ht.printTable(); 
    ht.remove(31);  
    ht.printTable(); 
    ht.insert(2);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
