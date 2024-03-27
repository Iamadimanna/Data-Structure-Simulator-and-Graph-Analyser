#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

// Define the Node structure for the Binomial Heap
struct Node {
    int key;
    int degree;
    std::vector<Node*> children;
    Node* parent;

    Node(int _key) : key(_key), degree(0), parent(nullptr) {}

    // Function to add a child to the node
    void addChild(Node* child) {
        children.push_back(child);
        child->parent = this;
        degree++;
    }
};

// Define the Binomial Heap class
class BinomialHeap {
public:
    std::vector<Node*> heap;

    // Function to merge two binomial trees of the same degree
    Node* mergeTrees(Node* tree1, Node* tree2) {
        if (tree1->key > tree2->key)
            std::swap(tree1, tree2);

        tree2->parent = tree1;
        tree1->addChild(tree2);

        return tree1;
    }

    // Function to merge two binomial heaps
    void mergeHeaps(BinomialHeap& otherHeap) {
        size_t maxSize = std::max(heap.size(), otherHeap.heap.size());
        heap.resize(maxSize, nullptr);

        Node* carry = nullptr;

        for (size_t i = 0; i < maxSize; ++i) {
            Node* tree1 = heap[i];
            Node* tree2 = (i < otherHeap.heap.size()) ? otherHeap.heap[i] : nullptr;

            if (carry) {
                if (tree1 && tree2) {
                    heap[i] = carry;
                    carry = mergeTrees(tree1, tree2);
                } else if (tree1) {
                    carry = mergeTrees(tree1, carry);
                } else {
                    carry = mergeTrees(tree2, carry);
                }
            } else {
                if (tree1 && tree2) {
                    heap[i] = nullptr;
                    carry = mergeTrees(tree1, tree2);
                } else if (tree1) {
                    heap[i] = tree1;
                } else {
                    heap[i] = tree2;
                }
            }
        }

        otherHeap.heap.clear();
    }

    // Function to find the index of the tree with the minimum key
    size_t findMinIndex() {
        size_t minIndex = 0;
        int minValue = heap[0]->key;

        for (size_t i = 1; i < heap.size(); ++i) {
            if (heap[i] && heap[i]->key < minValue) {
                minIndex = i;
                minValue = heap[i]->key;
            }
        }

        return minIndex;
    }

    // Function to consolidate the heap by merging trees of the same degree
    void consolidate() {
        size_t maxSize = std::log2(heap.size()) + 1;
        std::vector<Node*> tempHeap(maxSize, nullptr);

        while (!heap.empty()) {
            Node* tree = heap.back();
            heap.pop_back();

            size_t degree = tree->degree;

            while (tempHeap[degree]) {
                tree = mergeTrees(tree, tempHeap[degree]);
                tempHeap[degree] = nullptr;
                degree++;
            }

            tempHeap[degree] = tree;
        }

        heap = tempHeap;
    }

    // Function to perform the cascading cut operation
    void cascadingCut(Node* node) {
        Node* parent = node->parent;
        if (parent) {
            if (node != parent->children.back()) {
                std::swap(node, parent->children.back());
            }
            parent->children.pop_back();
            parent->degree--;
            node->parent = nullptr;
            heap.push_back(node);

            if (!parent->parent)
                return;

            if (parent->parent->children.size() > 1)
                return;

            if (parent->parent->children.size() == 1) {
                Node* sibling = parent->parent->children[0];
                parent->parent->children.clear();
                parent->parent->degree = 0;
                parent->parent = nullptr;
                heap.push_back(sibling);
            }

            cascadingCut(parent);
        }
    }

public:
    // Function to insert a new key into the heap
    void insert(int key) {
        BinomialHeap newHeap;
        Node* newNode = new Node(key);
        newHeap.heap.push_back(newNode);
        mergeHeaps(newHeap);
    }

    // Function to get the minimum key in the heap
    int getMinimum() {
        size_t minIndex = findMinIndex();
        return heap[minIndex]->key;
    }

    // Function to extract the minimum key from the heap
    int extractMin() {
        size_t minIndex = findMinIndex();
        Node* minNode = heap[minIndex];
        heap[minIndex] = nullptr;

        BinomialHeap newHeap;
        newHeap.heap.resize(minNode->degree);
        std::copy(minNode->children.begin(), minNode->children.end(), newHeap.heap.begin());
        mergeHeaps(newHeap);

        int minValue = minNode->key;
        delete minNode;

        consolidate();
        return minValue;
    }

    // Function to decrease the key of a node
    void decreaseKey(Node* node, int newKey) {
        node->key = newKey;

        Node* parent = node->parent;
        if (parent && node->key < parent->key) {
            cascadingCut(node);
        }
    }

    // Function to display the binomial heap
    void displayHeap() {
        std::cout << "Binomial Heap:\n";
        for (size_t i = 0; i < heap.size(); ++i) {
            if (heap[i]) {
                std::cout << "Tree of degree " << i << ": ";
                displayTree(heap[i]);
                std::cout << "\n";
            }
        }
    }

    // Function to display a tree
    void displayTree(Node* node) {
        std::cout << node->key << " ";

        for (Node* child : node->children) {
            displayTree(child);
        }
    }
};

int main() {
    BinomialHeap binomialHeap;

    int choice;
    do {
        std::cout << "\nBinomial Heap Menu\n";
        std::cout << "1. Insert a key\n";
        std::cout << "2. Get the minimum key\n";
        std::cout << "3. Extract the minimum key\n";
        std::cout << "4. Decrease the key of a node\n";
        std::cout << "5. Display the heap\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int key;
                std::cout << "Enter the key to insert: ";
                std::cin >> key;
                binomialHeap.insert(key);
                std::cout << "Key inserted successfully.\n";
                break;
            }
            case 2: {
                int minKey = binomialHeap.getMinimum();
                std::cout << "Minimum key: " << minKey << std::endl;
                break;
            }
            case 3: {
                int minKey = binomialHeap.extractMin();
                std::cout << "Minimum key extracted: " << minKey << std::endl;
                break;
            }
            case 4: {
                int nodeIndex, newKey;
                std::cout << "Enter the index of the node: ";
                std::cin >> nodeIndex;
                std::cout << "Enter the new key: ";
                std::cin >> newKey;
                binomialHeap.decreaseKey(binomialHeap.heap[nodeIndex], newKey);
                std::cout << "Key decreased successfully.\n";
                break;
            }
            case 5:
                binomialHeap.displayHeap();
                break;
            case 6:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

