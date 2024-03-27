#include <iostream>
#include <string>

class RopeNode {
public:
    char val;
    int weight;
    RopeNode* left;
    RopeNode* right;

    RopeNode(char c) : val(c), weight(1), left(nullptr), right(nullptr) {}
};

class Rope {
private:
    RopeNode* root;

    // Helper function to calculate the weight of a rope node
    int calculateWeight(RopeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->weight;
    }

    // Helper function to perform a split operation on the rope
    void split(RopeNode* node, int index, RopeNode*& left, RopeNode*& right) {
        if (node == nullptr) {
            left = nullptr;
            right = nullptr;
            return;
        }

        int nodeWeight = calculateWeight(node->left);
        if (index <= nodeWeight) {
            split(node->left, index, left, node->left);
            right = node;
        } else {
            split(node->right, index - nodeWeight, node->right, right);
            left = node;
        }

        node->weight = calculateWeight(node->left) + calculateWeight(node->right);
    }

    // Helper function to concatenate two rope nodes
    RopeNode* concatenate(RopeNode* left, RopeNode* right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        RopeNode* newRoot = new RopeNode(' ');
        newRoot->left = left;
        newRoot->right = right;
        newRoot->weight = calculateWeight(left);

        return newRoot;
    }

    // Helper function to perform an inorder traversal of the rope and print the characters
    void printInorder(RopeNode* node) {
        if (node == nullptr) {
            return;
        }

        printInorder(node->left);
        std::cout << node->val;
        printInorder(node->right);
    }

public:
    Rope() : root(nullptr) {}

    // Function to insert a string at the given index in the rope
    void insert(const std::string& str, int index) {
        RopeNode* left;
        RopeNode* right;
        split(root, index, left, right);

        RopeNode* newNode = new RopeNode(str[0]);

        RopeNode* temp = newNode;
        for (int i = 1; i < str.length(); i++) {
            temp->right = new RopeNode(str[i]);
            temp->weight = 1;
            temp = temp->right;
        }

        root = concatenate(concatenate(left, newNode), right);
    }

    // Function to delete characters from the rope at the given index range
    void erase(int start, int end) {
        RopeNode* left1;
        RopeNode* right1;
        split(root, start, left1, right1);

        RopeNode* left2;
        RopeNode* right2;
        split(right1, end - start, left2, right2);

        root = concatenate(left1, right2);
    }

    // Function to print the characters in the rope
    void print() {
        printInorder(root);
        std::cout << std::endl;
    }
};

int main() {
    Rope rope;

    int choice;
    while (true) {
        std::cout << "\nRope Functionality Menu:\n";
        std::cout << "1. Insert string\n";
        std::cout << "2. Delete characters\n";
        std::cout << "3. Print rope\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string str;
                int index;
                std::cout << "Enter the string to insert: ";
                std::cin >> str;
                std::cout << "Enter the index to insert at: ";
                std::cin >> index;
                rope.insert(str, index);
                break;
            }
            case 2: {
                int start, end;
                std::cout << "Enter the start index: ";
                std::cin >> start;
                std::cout << "Enter the end index: ";
                std::cin >> end;
                rope.erase(start, end);
                break;
            }
            case 3:
                rope.print();
                break;
            case 4:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}

