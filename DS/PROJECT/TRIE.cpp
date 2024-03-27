#include<bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    bool isWord;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isWord = false;
    }
};

class Trie {
public:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                curr->children[ch] = new TrieNode();
            }
            curr = curr->children[ch];
        }
        curr->isWord = true;
    }

    bool search(string word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                return false;
            }
            curr = curr->children[ch];
        }
        return curr->isWord;
    }

    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            if (curr->children.find(ch) == curr->children.end()) {
                return false;
            }
            curr = curr->children[ch];
        }
        return true;
    }

    bool deleteWord(TrieNode* node, string word, int index) {
        if (index == word.length()) {
            if (!node->isWord) {
                return false;  // Word not found in the Trie
            }
            node->isWord = false;  // Mark the node as non-word
            return node->children.empty();  // Return true if the node has no children
        }

        char ch = word[index];
        if (node->children.find(ch) == node->children.end()) {
            return false;  // Word not found in the Trie
        }

        TrieNode* nextNode = node->children[ch];
        bool shouldDeleteCurrentNode = deleteWord(nextNode, word, index + 1);

        if (shouldDeleteCurrentNode) {
            node->children.erase(ch);
            return node->children.empty();
        }

        return false;
    }
};

int main() {
    Trie trie;

    int choice;
    string word;

    while (true) {
        cout << "\n--- Trie Options ---\n";
        cout << "1. Insert Word\n";
        cout << "2. Search Word\n";
        cout << "3. Check Prefix\n";
        cout << "4. Delete Word\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the word to insert: ";
                cin >> word;
                trie.insert(word);
                cout << "Word '" << word << "' inserted into the Trie.\n";
                break;
            case 2:
                cout << "Enter the word to search: ";
                cin >> word;
                cout << (trie.search(word) ? "Word '" + word + "' found in the Trie.\n" : "Word '" + word + "' not found in the Trie.\n");
                break;
            case 3:
                cout << "Enter the prefix to check: ";
                cin >> word;
                cout << (trie.startsWith(word) ? "Prefix '" + word + "' found in the Trie.\n" : "Prefix '" + word + "' not found in the Trie.\n");
                break;
            case 4:
                cout << "Enter the word to delete: ";
                cin >> word;
                if (trie.deleteWord(trie.root, word, 0)) {
                    cout << "Word '" << word << "' deleted from the Trie.\n";
                } else {
                    cout << "Word '" << word << "' not found in the Trie.\n";
                }
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

