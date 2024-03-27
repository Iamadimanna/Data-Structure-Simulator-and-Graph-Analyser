#include <iostream>
#include <unordered_map>

// Radix Tree Node
class RadixTreeNode {
public:
    std::unordered_map<char, RadixTreeNode*> children;
    bool isEndOfWord;
    std::string value;

    RadixTreeNode() : isEndOfWord(false) {}
};

// Radix Tree Class
class RadixTree {
private:
    RadixTreeNode* root;

public:
    RadixTree() : root(new RadixTreeNode()) {}

    void insert(const std::string& key, const std::string& value);
    std::string lookup(const std::string& key);
    void remove(const std::string& key);
};

void RadixTree::insert(const std::string& key, const std::string& value) {
    RadixTreeNode* current = root;

    for (char c : key) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new RadixTreeNode();
        }
        current = current->children[c];
    }

    current->isEndOfWord = true;
    current->value = value;
}

std::string RadixTree::lookup(const std::string& key) {
    RadixTreeNode* current = root;

    for (char c : key) {
        if (current->children.find(c) == current->children.end()) {
            return ""; // Key not found
        }
        current = current->children[c];
    }

    if (current->isEndOfWord) {
        return current->value;
    } else {
        return ""; // Key not found
    }
}

void RadixTree::remove(const std::string& key) {
    RadixTreeNode* current = root;

    for (char c : key) {
        if (current->children.find(c) == current->children.end()) {
            return; // Key not found
        }
        current = current->children[c];
    }

    if (current->isEndOfWord) {
        current->isEndOfWord = false;
        current->value = "";
    }
}

// Main Function
int main() {
    RadixTree radixTree;

    int choice;
    std::string key, value;

    do {
        std::cout << "\nRadix Tree Menu\n";
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
                radixTree.insert(key, value);
                std::cout << "Key-value pair inserted successfully.\n";
                break;
            case 2:
                std::cout << "Enter key: ";
                std::cin >> key;
                value = radixTree.lookup(key);
                if (!value.empty()) {
                    std::cout << "Value: " << value << std::endl;
                } else {
                    std::cout << "Key not found.\n";
                }
                break;
            case 3:
                std::cout << "Enter key: ";
                std::cin >> key;
                radixTree.remove(key);
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

