#include <bits/stdc++.h>
enum class Color { RED, BLACK };

// Node class for Red-Black Tree
class Node {
public:
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int key) : key(key), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    // Left rotation
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Right rotation
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    // Fix the tree after inserting a node
    void insertFixup(Node* z) {
        while (z->parent != nullptr && z->parent->color == Color::RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = Color::BLACK;
    }

    // Fix the tree after deleting a node
    void deleteFixup(Node* x) {
        while (x != root && (x == nullptr || x->color == Color::BLACK)) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == Color::BLACK) &&
                    (w->right == nullptr || w->right->color == Color::BLACK)) {
                    w->color = Color::RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == Color::BLACK) {
                        if (w->left != nullptr)
                            w->left->color = Color::BLACK;
                        w->color = Color::RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    if (w->right != nullptr)
                        w->right->color = Color::BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == Color::BLACK) &&
                    (w->left == nullptr || w->left->color == Color::BLACK)) {
                    w->color = Color::RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == Color::BLACK) {
                        if (w->right != nullptr)
                            w->right->color = Color::BLACK;
                        w->color = Color::RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    if (w->left != nullptr)
                        w->left->color = Color::BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr)
            x->color = Color::BLACK;
    }

    // Insert a node into the Red-Black Tree
    void insert(int key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;
        while (x != nullptr) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        insertFixup(z);
        std::cout << "Inserted value: " << key << std::endl;
    }

    // Delete a node from the Red-Black Tree
    void remove(int key) {
        Node* z = findNode(key);
        if (z == nullptr) {
            std::cout << "Value " << key << " does not exist in the Red-Black Tree." << std::endl;
            return;
        }

        Node* y = z;
        Node* x = nullptr;
        Color yOriginalColor = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimumNode(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == Color::BLACK)
            deleteFixup(x);

        std::cout << "Deleted value: " << key << std::endl;
    }

    // Transplant a subtree with another subtree
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    // Find the minimum node in the subtree rooted at a given node
    Node* minimumNode(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Find a node with a given key in the Red-Black Tree
    Node* findNode(int key) {
        Node* current = root;
        while (current != nullptr && current->key != key) {
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return current;
    }

    // Perform an in-order traversal and print the Red-Black Tree
    void inorderTraversal(Node* node, std::string indent, bool isLast) {
        if (node == nullptr)
            return;

        std::cout << indent;
        if (isLast) {
            std::cout << "└─";
            indent += "  ";
        } else {
            std::cout << "├─";
            indent += "| ";
        }

        std::string nodeColor = (node->color == Color::RED) ? "Red" : "Black";
        std::cout << node->key << " (" << nodeColor << ")" << std::endl;

        inorderTraversal(node->left, indent, (node->right == nullptr));
        inorderTraversal(node->right, indent, true);
    }

public:
    RedBlackTree() : root(nullptr) {}

    // Print the Red-Black Tree
    void print() {
        std::cout << "Red-Black Tree:" << std::endl;
        inorderTraversal(root, "", true);
        std::cout << std::endl;
    }

    // Menu to interact with the Red-Black Tree
    void menu() {
        int choice;
        int value;
        std::cout << "Red-Black Tree Menu:\n";
        std::cout << "1. Insert a value\n";
        std::cout << "2. Delete a value\n";
        std::cout << "3. Print the Red-Black Tree\n";
        std::cout << "4. Exit\n";

        while (true) {
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    std::cout << "Enter a value to insert: ";
                    std::cin >> value;
                    insert(value);
                    break;
                case 2:
                    std::cout << "Enter a value to delete: ";
                    std::cin >> value;
                    remove(value);
                    break;
                case 3:
                    print();
                    break;
                case 4:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }
};

int main() {
    RedBlackTree rbTree;
    rbTree.menu();

    return 0;
}

