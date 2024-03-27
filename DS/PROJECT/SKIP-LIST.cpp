#include <bits/stdc++.h>

// Node class for Skip List
class SkipNode {
public:
    int value;
    SkipNode** forward;

    SkipNode(int level, int value) : value(value) {
        forward = new SkipNode*[level + 1];
        memset(forward, 0, sizeof(SkipNode*) * (level + 1));
    }

    ~SkipNode() {
        delete[] forward;
    }
};

// Skip List class
class SkipList {
private:
    int maxLevel;
    float probability;
    int level;
    SkipNode* header;

public:
    SkipList(int maxLevel, float probability) : maxLevel(maxLevel), probability(probability), level(0) {
        header = new SkipNode(maxLevel, 0);
        srand(time(NULL));
    }

    ~SkipList() {
        SkipNode* current = header->forward[0];
        while (current != nullptr) {
            SkipNode* next = current->forward[0];
            delete current;
            current = next;
        }
        delete header;
    }

    // Generate a random level for a new node
    int randomLevel() {
        int newLevel = 0;
        while (static_cast<float>(rand()) / RAND_MAX < probability && newLevel < maxLevel) {
            newLevel++;
        }
        return newLevel;
    }

    // Insert a value into the Skip List
    void insert(int value) {
        SkipNode* update[maxLevel + 1];
        memset(update, 0, sizeof(SkipNode*) * (maxLevel + 1));

        SkipNode* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();
            if (newLevel > level) {
                for (int i = level + 1; i <= newLevel; i++) {
                    update[i] = header;
                }
                level = newLevel;
            }

            SkipNode* newNode = new SkipNode(newLevel, value);
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
            std::cout << "Inserted value: " << value << std::endl;
        } else {
            std::cout << "Value " << value << " already exists in the Skip List." << std::endl;
        }
    }

    // Search for a value in the Skip List
    void search(int value) {
        SkipNode* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];

        if (current != nullptr && current->value == value) {
            std::cout << "Value " << value << " found in the Skip List." << std::endl;
        } else {
            std::cout << "Value " << value << " not found in the Skip List." << std::endl;
        }
    }

    // Print the elements of the Skip List
    void print() {
        for (int i = level; i >= 0; i--) {
            SkipNode* current = header->forward[i];
            std::cout << "Level " << i << ": ";
            while (current != nullptr) {
                std::cout << current->value << " ";
                current = current->forward[i];
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int maxLevel, choice;
    float probability;
    std::cout << "Enter the maximum level of the Skip List: ";
    std::cin >> maxLevel;
    std::cout << "Enter the probability value (between 0 and 1): ";
    std::cin >> probability;

    SkipList skipList(maxLevel, probability);

    while (true) {
        std::cout << "\nSkip List Menu:\n";
        std::cout << "1. Insert a value\n";
        std::cout << "2. Search for a value\n";
        std::cout << "3. Print the Skip List\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter the value to insert: ";
                std::cin >> value;
                skipList.insert(value);
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter the value to search: ";
                std::cin >> value;
                skipList.search(value);
                break;
            }
            case 3:
                skipList.print();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}

