#include <iostream>
#include <list>
#include <vector>

class HashList {
private:
    std::vector<std::list<std::pair<int, std::string>>> table;
    int capacity;

public:
    HashList(int size) : capacity(size) {
        table.resize(capacity);
    }

    void insert(int key, const std::string& value) {
        int index = hashFunction(key);
        table[index].push_back(std::make_pair(key, value));
    }

    bool remove(int key) {
        int index = hashFunction(key);
        std::list<std::pair<int, std::string>>& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return true;
            }
        }

        return false; // Key not found
    }

    std::string search(int key) {
        int index = hashFunction(key);
        std::list<std::pair<int, std::string>>& bucket = table[index];

        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }

        return ""; // Key not found
    }

    void display() {
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& entry : table[i]) {
                std::cout << "(" << entry.first << ", " << entry.second << ") ";
            }
            std::cout << std::endl;
        }
    }

private:
    int hashFunction(int key) {
        // A simple hash function that maps keys to indices
        return key % capacity;
    }
};

int main() {
    int capacity;
    std::cout << "Enter the capacity of the hash list: ";
    std::cin >> capacity;

    HashList hashList(capacity);

    int choice;
    do {
        std::cout << "\nHash List Menu\n";
        std::cout << "1. Insert a key-value pair\n";
        std::cout << "2. Remove a key\n";
        std::cout << "3. Search for a key\n";
        std::cout << "4. Display the hash list\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int key;
                std::string value;
                std::cout << "Enter key: ";
                std::cin >> key;
                std::cout << "Enter value: ";
                std::cin >> value;
                hashList.insert(key, value);
                std::cout << "Key-value pair inserted successfully.\n";
                break;
            }
            case 2: {
                int key;
                std::cout << "Enter key to remove: ";
                std::cin >> key;
                if (hashList.remove(key))
                    std::cout << "Key removed successfully.\n";
                else
                    std::cout << "Key not found.\n";
                break;
            }
            case 3: {
                int key;
                std::cout << "Enter key to search: ";
                std::cin >> key;
                std::string value = hashList.search(key);
                if (!value.empty())
                    std::cout << "Value: " << value << std::endl;
                else
                    std::cout << "Key not found.\n";
                break;
            }
            case 4:
                hashList.display();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

