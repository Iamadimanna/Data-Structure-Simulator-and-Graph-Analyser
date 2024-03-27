#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 10;

class Node {
public:
    string key;
    int value;
    Node* next;

    Node(const string& k, int v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    Node** table;

public:
    HashTable() {
        table = new Node*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    int hashFunction(const string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % TABLE_SIZE;
    }

    void insert(const string& key, int value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr) {
                if (current->key == key) {
                    current->value = value; // Update value if key already exists
                    delete newNode;
                    return;
                }
                current = current->next;
            }
            current->next = newNode;
        }
    }

    int search(const string& key) {
        int index = hashFunction(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return -1; // Key not found
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};

int main() {
    HashTable hashTable;

    int choice;
    string key;
    int value;
    int searchResult; // Move declaration here

    while (true) {
        cout << "\n--- Hash Table Options ---\n";
        cout << "1. Insert/Update Key-Value\n";
        cout << "2. Search Key\n";
        cout << "3. Delete Key\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the key and value: ";
                cin >> key >> value;
                hashTable.insert(key, value);
                cout << "Key-Value pair inserted/updated.\n";
                break;
            case 2:
                cout << "Enter the key to search: ";
                cin >> key;
                searchResult = hashTable.search(key); // Assign value here
                if (searchResult != -1) {
                    cout << "Value: " << searchResult << endl;
                } else {
                    cout << "Key not found in the Hash Table.\n";
                }
                break;
            case 3:
                cout << "Enter the key to delete: ";
                cin >> key;
                hashTable.remove(key);
                cout << "Key deleted from the Hash Table.\n";
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    }

    return 0;
}

