#include <iostream>
#include <unordered_map>

// Suffix Tree Node
struct Node {
    std::unordered_map<char, Node*> children;
};

// Suffix Tree Class
class SuffixTree {
private:
    Node* root;

public:
    SuffixTree() {
        root = new Node();
    }

    void insert(const std::string& word);
    bool search(const std::string& word);
};

void SuffixTree::insert(const std::string& word) {
    Node* curr = root;

    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new Node();
        }

        curr = curr->children[c];
    }
}

bool SuffixTree::search(const std::string& word) {
    Node* curr = root;

    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            return false;
        }

        curr = curr->children[c];
    }

    return true;
}

int main() {
    SuffixTree suffixTree;

    int choice;
    std::string word;

    do {
        std::cout << "\nSuffix Tree Operations\n";
        std::cout << "1. Insert a word\n";
        std::cout << "2. Search for a word\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter a word: ";
                std::cin >> word;
                suffixTree.insert(word);
                std::cout << "Word inserted into the Suffix Tree.\n";
                break;
            case 2:
                std::cout << "Enter a word to search: ";
                std::cin >> word;
                if (suffixTree.search(word))
                    std::cout << "Word found in the Suffix Tree.\n";
                else
                    std::cout << "Word not found in the Suffix Tree.\n";
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

