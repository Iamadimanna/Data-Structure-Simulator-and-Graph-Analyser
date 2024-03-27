#include<bits/stdc++.h>
const int ALPHABET_SIZE = 26;

class TrieNode {
public:
    std::vector<TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        children.resize(ALPHABET_SIZE, nullptr);
    }
};

class MultiwayTrie {
private:
    TrieNode* root;

public:
    MultiwayTrie() : root(new TrieNode()) {}

    void insert(const std::string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index])
                curr->children[index] = new TrieNode();
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index])
                return false;
            curr = curr->children[index];
        }
        return curr && curr->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!curr->children[index])
                return false;
            curr = curr->children[index];
        }
        return curr != nullptr;
    }
};

int main() {
    MultiwayTrie trie;

    int choice;
    std::string word;
    do {
        std::cout << "\nMultiway Trie Menu\n";
        std::cout << "1. Insert a word\n";
        std::cout << "2. Search for a word\n";
        std::cout << "3. Check if trie starts with a prefix\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter word to insert: ";
                std::cin >> word;
                trie.insert(word);
                std::cout << "Word inserted successfully.\n";
                break;
            }
            case 2: {
                std::cout << "Enter word to search: ";
                std::cin >> word;
                if (trie.search(word))
                    std::cout << "Word found.\n";
                else
                    std::cout << "Word not found.\n";
                break;
            }
            case 3: {
                std::cout << "Enter prefix to check: ";
                std::cin >> word;
                if (trie.startsWith(word))
                    std::cout << "Trie starts with the prefix.\n";
                else
                    std::cout << "Trie does not start with the prefix.\n";
                break;
            }
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

