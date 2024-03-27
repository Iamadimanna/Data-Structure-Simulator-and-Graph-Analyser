#include <iostream>
#include <string>
#include <vector>

class PatriciaTrie {
private:
    struct TrieNode {
        std::string prefix;
        std::vector<TrieNode*> children;
        bool isEndOfWord;

        TrieNode(const std::string& prefix) : prefix(prefix), isEndOfWord(false) {}
    };

    TrieNode* root;

public:
    PatriciaTrie() {
        root = new TrieNode("");
    }

    void insert(const std::string& word) {
        TrieNode* current = root;
        TrieNode* parent = nullptr;
        int i = 0;

        while (i < word.length()) {
            // Find the child node with matching prefix
            int j = 0;
            while (j < current->children.size() && word[i + j] == current->children[j]->prefix[0]) {
                ++j;
            }

            if (j < current->children.size()) {
                // Found a matching child node
                parent = current;
                current = current->children[j];
                i += j;
            } else {
                // No matching child node, insert a new node
                TrieNode* newNode = new TrieNode(word.substr(i));
                current->children.push_back(newNode);
                current = newNode;
                i = word.length();
            }
        }

        // Mark the last node as end of word
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* current = root;
        int i = 0;

        while (i < word.length()) {
            // Find the child node with matching prefix
            int j = 0;
            while (j < current->children.size() && word[i + j] == current->children[j]->prefix[0]) {
                ++j;
            }

            if (j < current->children.size()) {
                // Found a matching child node
                current = current->children[j];
                i += j;
            } else {
                // No matching child node, word not found
                return false;
            }
        }

        // Check if the last node is marked as end of word
        return current->isEndOfWord;
    }

    void display() {
        std::cout << "Patricia Trie:\n";
        display(root, 0);
        std::cout << std::endl;
    }

private:
    void display(TrieNode* node, int level) {
        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }

        std::cout << node->prefix << " (" << (node->isEndOfWord ? "EOW" : "   ") << ")" << std::endl;

        for (TrieNode* child : node->children) {
            display(child, level + 1);
        }
    }
};

int main() {
    PatriciaTrie trie;

    int choice;
    std::string word;

    do {
        std::cout << "\nPatricia Trie Menu\n";
        std::cout << "1. Insert a word\n";
        std::cout << "2. Search for a word\n";
        std::cout << "3. Display the trie\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the word to insert: ";
                std::cin >> word;
                trie.insert(word);
                std::cout << "Word inserted successfully!\n";
                break;
            case 2:
                std::cout << "Enter the word to search: ";
                std::cin >> word;
                std::cout << (trie.search(word) ? "Word found!\n" : "Word not found.\n");
                break;
            case 3:
                trie.display();
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

