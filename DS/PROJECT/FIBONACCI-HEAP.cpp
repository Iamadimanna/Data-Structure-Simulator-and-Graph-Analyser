#include <iostream>
#include <cmath>
#include <limits>

// Fibonacci Node
struct FibonacciNode {
    int key;
    int degree;
    bool marked;
    FibonacciNode* parent;
    FibonacciNode* child;
    FibonacciNode* prev;
    FibonacciNode* next;

    explicit FibonacciNode(int k) : key(k), degree(0), marked(false),
                                    parent(nullptr), child(nullptr),
                                    prev(this), next(this) {}
};

// Fibonacci Heap
class FibonacciHeap {
private:
    FibonacciNode* minNode;
    int nodeCount;

public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

    bool isEmpty() const {
        return minNode == nullptr;
    }

    void insert(int key) {
        FibonacciNode* node = new FibonacciNode(key);
        if (minNode) {
            node->prev = minNode;
            node->next = minNode->next;
            minNode->next = node;
            node->next->prev = node;
            if (key < minNode->key) {
                minNode = node;
            }
        } else {
            minNode = node;
        }
        nodeCount++;
    }

    int getMinimum() const {
        if (minNode) {
            return minNode->key;
        }
        return std::numeric_limits<int>::max();
    }

    int extractMin() {
        FibonacciNode* extractedNode = minNode;
        if (extractedNode) {
            if (extractedNode->child) {
                FibonacciNode* child = extractedNode->child;
                FibonacciNode* temp = child;
                do {
                    temp->parent = nullptr;
                    temp = temp->next;
                } while (temp != child);
                extractedNode->prev->next = child;
                child->prev = extractedNode->prev;
                extractedNode->next->prev = child->prev;
                child->prev->next = extractedNode->next;
            }
            if (extractedNode == extractedNode->next) {
                minNode = nullptr;
            } else {
                minNode = extractedNode->next;
                consolidate();
            }
            nodeCount--;
            int extractedKey = extractedNode->key;
            delete extractedNode;
            return extractedKey;
        }
        return std::numeric_limits<int>::max();
    }

    void decreaseKey(FibonacciNode* node, int newKey) {
        if (newKey > node->key) {
            return;
        }
        node->key = newKey;
        FibonacciNode* parent = node->parent;
        if (parent && node->key < parent->key) {
            cut(node, parent);
            cascadingCut(parent);
        }
        if (node->key < minNode->key) {
            minNode = node;
        }
    }

private:
    void consolidate() {
        int maxDegree = static_cast<int>(log2(nodeCount)) + 1;
        FibonacciNode** degreeTable = new FibonacciNode*[maxDegree + 1]();
        FibonacciNode* current = minNode;
        FibonacciNode* endNode = minNode;

        do {
            FibonacciNode* nextNode = current->next;
            int degree = current->degree;

            while (degreeTable[degree]) {
                FibonacciNode* otherNode = degreeTable[degree];
                if (current->key > otherNode->key) {
                    std::swap(current, otherNode);
                }
                link(otherNode, current);
                degreeTable[degree] = nullptr;
                degree++;
            }
            degreeTable[degree] = current;
            current = nextNode;

            if (current->key < minNode->key) {
                minNode = current;
            }
        } while (current != endNode);

        delete[] degreeTable;
    }

    void link(FibonacciNode* node1, FibonacciNode* node2) {
        node1->prev->next = node1->next;
        node1->next->prev = node1->prev;

        if (node2->child) {
            node1->prev = node2->child;
            node1->next = node2->child->next;
            node2->child->next = node1;
            node1->next->prev = node1;
        } else {
            node1->prev = node1;
            node1->next = node1;
        }

        node1->parent = node2;
        node2->degree++;
        node1->marked = false;
    }

    void cut(FibonacciNode* node, FibonacciNode* parent) {
        if (node == node->next) {
            parent->child = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if (node == parent->child) {
                parent->child = node->next;
            }
        }
        parent->degree--;
        node->prev = minNode;
        node->next = minNode->next;
        minNode->next = node;
        node->next->prev = node;
        node->parent = nullptr;
        node->marked = false;
    }

    void cascadingCut(FibonacciNode* node) {
        FibonacciNode* parent = node->parent;
        if (parent) {
            if (!node->marked) {
                node->marked = true;
            } else {
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }
};

int main() {
    FibonacciHeap fibHeap;

    int choice;
    do {
        std::cout << "\nFibonacci Heap Menu\n";
        std::cout << "1. Insert key\n";
        std::cout << "2. Get minimum key\n";
        std::cout << "3. Extract minimum key\n";
        std::cout << "4. Decrease key\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int key;
                std::cout << "Enter key: ";
                std::cin >> key;
                fibHeap.insert(key);
                std::cout << "Key inserted successfully.\n";
                break;
            }
            case 2: {
                int minKey = fibHeap.getMinimum();
                if (minKey != std::numeric_limits<int>::max()) {
                    std::cout << "Minimum key: " << minKey << std::endl;
                } else {
                    std::cout << "Heap is empty.\n";
                }
                break;
            }
            case 3: {
                int minKey = fibHeap.extractMin();
                if (minKey != std::numeric_limits<int>::max()) {
                    std::cout << "Minimum key extracted: " << minKey << std::endl;
                } else {
                    std::cout << "Heap is empty.\n";
                }
                break;
            }
            case 4: {
                int nodeKey, newKey;
                std::cout << "Enter the key of the node to decrease: ";
                std::cin >> nodeKey;
                std::cout << "Enter the new key: ";
                std::cin >> newKey;
                // TODO: Call the decreaseKey function with nodeKey and newKey
                break;
            }
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}

