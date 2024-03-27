#include <iostream>
#include <vector>
#include <list>

// Hashed Array Tree Class
class HashedArrayTree {
private:
    std::vector<std::list<std::pair<int, std::string>>> array;
    size_t arraySize;

public:
    HashedArrayTree(size_t size) : arraySize(size) {
        array.resize(arraySize);
    }

    void insert(int key, const std::string& value);
    std::string lookup(int key);
    void remove(int key);
};

void HashedArrayTree::insert(int key, const std::string& value) {
    size_t index = key % arraySize;
    array[index].push_back(std::make_pair(key, value));
}

std::string HashedArrayTree::lookup(int key) {
    size_t index = key % arraySize;
    for (const auto& pair : array[index]) {
        if (pair.first == key)
            return pair.second;
    }
    return ""; // Key not found
}

void HashedArrayTree::remove(int key) {
    size_t index = key % arraySize;
    for (auto it = array[index].begin(); it != array[index].end(); ++it) {
        if (it->first == key) {
            array[index].erase(it);
            break;
        }
    }
}

// Main Function
int main() {
    size_t arraySize;
    int key;
    std::string value;

    std::cout << "Enter the size of the Hashed Array Tree: ";
    std::cin >> arraySize;

    HashedArrayTree hat(arraySize);

    int choice;
    do {
        std::cout << "\nHashed Array Tree Menu\n";
        std::cout << "1. Insert a key-value pair\n";
        std::cout << "2. Lookup a key\n";
        std::cout << "3. Remove a key\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter key: ";
                std::cin >> key;
                std::cout << "Enter value: ";
                std::cin >> value;
                hat.insert(key, value);
                std::cout << "Key-value pair inserted successfully.\n";
                break;
            case 2:
                std::cout << "Enter key: ";
                std::cin >> key;
                value = hat.lookup(key);
                if (value.empty())
                    std::cout << "Key not found.\n";
                else
                    std::cout << "Value: " << value << std::endl;
                break;
            case 3:
                std::cout << "Enter key: ";
                std::cin >> key;
                hat.remove(key);
                std::cout << "Key removed successfully.\n";
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

