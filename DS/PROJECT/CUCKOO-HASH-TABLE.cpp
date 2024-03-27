#include <iostream>
#include <vector>
#include <functional>
#include <string>

// Hash Function 1
  size_t hashFunction1 (const std::string & key, size_t tableSize)
{
  
std::hash < std::string > hashFunc;
  
return hashFunc (key) % tableSize;

}


 
// Hash Function 2
  size_t hashFunction2 (const std::string & key, size_t tableSize)
{
  
std::hash < std::string > hashFunc;
  
return (hashFunc (key) >> 16) % tableSize;

}


 
// Cuckoo Hash Table Class
  class CuckooHashTable
{

private:
std::vector < std::pair < std::string, int >>table1;
  
std::vector < std::pair < std::string, int >>table2;
  
size_t tableSize;
  
int maxDisplacements;

 
public:
CuckooHashTable (size_t size, int displacements):tableSize (size),
    maxDisplacements (displacements)
  {
    
table1.resize (tableSize);
    
table2.resize (tableSize);
  
} 
 
bool insert (const std::string & key, int value);
  
int lookup (const std::string & key);
  
bool remove (const std::string & key);
  
void displayTables ();

};


 
bool CuckooHashTable::insert (const std::string & key, int value)
{
  
size_t hash1 = hashFunction1 (key, tableSize);
  
size_t hash2 = hashFunction2 (key, tableSize);
  
 
    // Check if the first table slot is empty
    if (table1[hash1].first.empty ())
    {
      
table1[hash1].first = key;
      
table1[hash1].second = value;
      
return true;
    
}
  
 
    // Check if the second table slot is empty
    if (table2[hash2].first.empty ())
    {
      
table2[hash2].first = key;
      
table2[hash2].second = value;
      
return true;
    
}
  
 
    // Perform eviction and rehashing
    // ...
    
    // Swap the keys and values
    std::swap (const_cast < std::string & >(key), table1[hash1].first);
  
std::swap (value, table1[hash1].second);
  
return true;

}


 
int
CuckooHashTable::lookup (const std::string & key)
{
  
size_t hash1 = hashFunction1 (key, tableSize);
  
size_t hash2 = hashFunction2 (key, tableSize);
  
 
if (table1[hash1].first == key)
    
return table1[hash1].second;
  
if (table2[hash2].first == key)
    
return table2[hash2].second;
  
 
return -1;			// Key not found
}


 
bool CuckooHashTable::remove (const std::string & key)
{
  
size_t hash1 = hashFunction1 (key, tableSize);
  
size_t hash2 = hashFunction2 (key, tableSize);
  
 
if (table1[hash1].first == key)
    {
      
table1[hash1].first.clear ();
      
return true;
    
}
  
if (table2[hash2].first == key)
    {
      
table2[hash2].first.clear ();
      
return true;
    
}
  
 
return false;		// Key not found
}


 
void
CuckooHashTable::displayTables ()
{
  
std::cout << "Table 1: ";

for (const auto & entry:table1)
    {
      
if (!entry.first.empty ())
	
std::cout << "(" << entry.first << ", " << entry.second << ") ";
    
}
  
std::cout << std::endl;
  
 
std::cout << "Table 2: ";

for (const auto & entry:table2)
    {
      
if (!entry.first.empty ())
	
std::cout << "(" << entry.first << ", " << entry.second << ") ";
    
}
  
std::cout << std::endl;

}


 
// Main Function
  int
main ()
{
  
size_t tableSize;
  
int maxDisplacements;
  
std::string key;
  
int value;
  
 
std::cout << "Enter the size of the hash tables: ";
  
std::cin >> tableSize;
  
 
std::cout << "Enter the maximum displacements: ";
  
std::cin >> maxDisplacements;
  
 
CuckooHashTable hashTable (tableSize, maxDisplacements);
  
 
int choice;
  
  do
    {
      
std::cout << "\nCuckoo Hash Table Menu\n";
      
std::cout << "1. Insert a key-value pair\n";
      
std::cout << "2. Lookup a key\n";
      
std::cout << "3. Remove a key\n";
      
std::cout << "4. Display hash tables\n";
      
std::cout << "5. Exit\n";
      
std::cout << "Enter your choice: ";
      
std::cin >> choice;
      
 
switch (choice)
	{
	
case 1:
	  
std::cout << "Enter key: ";
	  
std::cin >> key;
	  
std::cout << "Enter value: ";
	  
std::cin >> value;
	  
if (hashTable.insert (key, value))
	    
std::cout << "Key-value pair inserted successfully.\n";
	  
	  else
	    
std::
	      cout <<
	      "Failed to insert key-value pair. Maximum displacements reached.\n";
	  
break;
	
case 2:
	  
std::cout << "Enter key: ";
	  
std::cin >> key;
	  
value = hashTable.lookup (key);
	  
if (value != -1)
	    
std::cout << "Value: " << value << std::endl;
	  
	  else
	    
std::cout << "Key not found.\n";
	  
break;
	
case 3:
	  
std::cout << "Enter key: ";
	  
std::cin >> key;
	  
if (hashTable.remove (key))
	    
std::cout << "Key removed successfully.\n";
	  
	  else
	    
std::cout << "Key not found.\n";
	  
break;
	
case 4:
	  
hashTable.displayTables ();
	  
break;
	
case 5:
	  
std::cout << "Exiting...\n";
	  
break;
	
default:
	  
std::cout << "Invalid choice. Please try again.\n";
	
}
    
}
  while (choice != 5);
  
 
return 0;

}



