#include<bits/stdc++.h>

class BTreeNode {
private:
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool leaf;

public:
    BTreeNode(bool isLeaf);

    std::vector<int>& getKeys();
    std::vector<BTreeNode*>& getChildren();
    bool isLeaf();
};

class BTree {
private:
    BTreeNode* root;
    int t;

public:
    BTree(int degree);

    void insert(int key);
    void remove(int key);
    void search(int key);

    void printTree();
    void printNode(BTreeNode* node);

    void menu();
    void insertNonFull(BTreeNode* node, int key);
    void splitChild(BTreeNode* parent, int index, BTreeNode* child);
    void removeKey(BTreeNode* node, int key);
    void removeFromLeaf(BTreeNode* node, int index);
    void removeFromInternalNode(BTreeNode* node, int index);
    int getPredecessor(BTreeNode* node, int index);
    int getSuccessor(BTreeNode* node, int index);
    void mergeChildren(BTreeNode* node, int index);
    void fillChild(BTreeNode* node, int index);
    void borrowFromPrevious(BTreeNode* node, int index);
    void borrowFromNext(BTreeNode* node, int index);
};

BTreeNode::BTreeNode(bool isLeaf) : leaf(isLeaf) {}

std::vector<int>& BTreeNode::getKeys() {
    return keys;
}

std::vector<BTreeNode*>& BTreeNode::getChildren() {
    return children;
}

bool BTreeNode::isLeaf() {
    return leaf;
}

BTree::BTree(int degree) : root(nullptr), t(degree) {}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->getKeys().push_back(key);
    } else {
        if (root->getKeys().size() == (2 * t) - 1) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->getChildren().push_back(root);
            splitChild(newRoot, 0, root);
            insertNonFull(newRoot, key);
            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }
}

void BTree::splitChild(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* newNode = new BTreeNode(child->isLeaf());
    parent->getKeys().insert(parent->getKeys().begin() + index, child->getKeys()[t - 1]);
    parent->getChildren().insert(parent->getChildren().begin() + index + 1, newNode);

    newNode->getKeys().assign(child->getKeys().begin() + t, child->getKeys().end());
    child->getKeys().erase(child->getKeys().begin() + t - 1, child->getKeys().end());

    if (!child->isLeaf()) {
        newNode->getChildren().assign(child->getChildren().begin() + t, child->getChildren().end());
        child->getChildren().erase(child->getChildren().begin() + t, child->getChildren().end());
    }
}

void BTree::insertNonFull(BTreeNode* node, int key) {
    int index = node->getKeys().size() - 1;

    if (node->isLeaf()) {
        node->getKeys().push_back(0);
        while (index >= 0 && key < node->getKeys()[index]) {
            node->getKeys()[index + 1] = node->getKeys()[index];
            index--;
        }
        node->getKeys()[index + 1] = key;
    } else {
        while (index >= 0 && key < node->getKeys()[index]) {
            index--;
        }
        index++;

        if (node->getChildren()[index]->getKeys().size() == (2 * t) - 1) {
            splitChild(node, index, node->getChildren()[index]);
            if (key > node->getKeys()[index]) {
                index++;
            }
        }
        insertNonFull(node->getChildren()[index], key);
    }
}

void BTree::remove(int key) {
    if (root == nullptr) {
        std::cout << "The tree is empty. Cannot remove key.\n";
        return;
    }

    removeKey(root, key);
}

void BTree::removeKey(BTreeNode* node, int key) {
    int index = 0;
    while (index < node->getKeys().size() && key > node->getKeys()[index]) {
        index++;
    }

    if (index < node->getKeys().size() && key == node->getKeys()[index]) {
        if (node->isLeaf()) {
            removeFromLeaf(node, index);
        } else {
            removeFromInternalNode(node, index);
        }
    } else {
        if (node->isLeaf()) {
            std::cout << "Key not found in the tree.\n";
            return;
        }

        bool flag = (index == node->getKeys().size());
        if (node->getChildren()[index]->getKeys().size() < t) {
            fillChild(node, index);
        }
        if (flag && index > node->getKeys().size()) {
            removeKey(node->getChildren()[index - 1], key);
        } else {
            removeKey(node->getChildren()[index], key);
        }
    }
}

void BTree::removeFromLeaf(BTreeNode* node, int index) {
    node->getKeys().erase(node->getKeys().begin() + index);
}

void BTree::removeFromInternalNode(BTreeNode* node, int index) {
    int key = node->getKeys()[index];

    if (node->getChildren()[index]->getKeys().size() >= t) {
        int predecessor = getPredecessor(node, index);
        node->getKeys()[index] = predecessor;
        removeKey(node->getChildren()[index], predecessor);
    } else if (node->getChildren()[index + 1]->getKeys().size() >= t) {
        int successor = getSuccessor(node, index);
        node->getKeys()[index] = successor;
        removeKey(node->getChildren()[index + 1], successor);
    } else {
        mergeChildren(node, index);
        removeFromInternalNode(node->getChildren()[index], t - 1);
    }
}

int BTree::getPredecessor(BTreeNode* node, int index) {
    BTreeNode* current = node->getChildren()[index];
    while (!current->isLeaf()) {
        current = current->getChildren().back();
    }
    return current->getKeys().back();
}

int BTree::getSuccessor(BTreeNode* node, int index) {
    BTreeNode* current = node->getChildren()[index + 1];
    while (!current->isLeaf()) {
        current = current->getChildren()[0];
    }
    return current->getKeys()[0];
}

void BTree::mergeChildren(BTreeNode* node, int index) {
    BTreeNode* child = node->getChildren()[index];
    BTreeNode* sibling = node->getChildren()[index + 1];

    child->getKeys().push_back(node->getKeys()[index]);
    child->getKeys().insert(child->getKeys().end(), sibling->getKeys().begin(), sibling->getKeys().end());

    if (!child->isLeaf()) {
        child->getChildren().insert(child->getChildren().end(), sibling->getChildren().begin(), sibling->getChildren().end());
    }

    node->getKeys().erase(node->getKeys().begin() + index);
    node->getChildren().erase(node->getChildren().begin() + index + 1);

    delete sibling;
}

void BTree::fillChild(BTreeNode* node, int index) {
    if (index != 0 && node->getChildren()[index - 1]->getKeys().size() >= t) {
        borrowFromPrevious(node, index);
    } else if (index != node->getKeys().size() && node->getChildren()[index + 1]->getKeys().size() >= t) {
        borrowFromNext(node, index);
    } else {
        if (index != node->getKeys().size()) {
            mergeChildren(node, index);
        } else {
            mergeChildren(node, index - 1);
        }
    }
}

void BTree::borrowFromPrevious(BTreeNode* node, int index) {
    BTreeNode* child = node->getChildren()[index];
    BTreeNode* sibling = node->getChildren()[index - 1];

    child->getKeys().insert(child->getKeys().begin(), node->getKeys()[index - 1]);

    if (!child->isLeaf()) {
        child->getChildren().insert(child->getChildren().begin(), sibling->getChildren().back());
        sibling->getChildren().pop_back();
    }

    node->getKeys()[index - 1] = sibling->getKeys().back();
    sibling->getKeys().pop_back();
}

void BTree::borrowFromNext(BTreeNode* node, int index) {
    BTreeNode* child = node->getChildren()[index];
    BTreeNode* sibling = node->getChildren()[index + 1];

    child->getKeys().push_back(node->getKeys()[index]);

    if (!child->isLeaf()) {
        child->getChildren().push_back(sibling->getChildren().front());
        sibling->getChildren().erase(sibling->getChildren().begin());
    }

    node->getKeys()[index] = sibling->getKeys()[0];
    sibling->getKeys().erase(sibling->getKeys().begin());
}

void BTree::search(int key) {
    BTreeNode* current = root;
    while (current != nullptr) {
        int index = 0;
        while (index < current->getKeys().size() && key > current->getKeys()[index]) {
            index++;
        }
        if (index < current->getKeys().size() && key == current->getKeys()[index]) {
            std::cout << "Key " << key << " found in the tree.\n";
            return;
        }
        if (current->isLeaf()) {
            break;
        }
        current = current->getChildren()[index];
    }
    std::cout << "Key " << key << " not found in the tree.\n";
}

void BTree::printTree() {
    if (root != nullptr) {
        printNode(root);
    }
}

void BTree::printNode(BTreeNode* node) {
    std::cout << "[";
    for (int i = 0; i < node->getKeys().size(); i++) {
        std::cout << node->getKeys()[i];
        if (i != node->getKeys().size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "] ";

    if (!node->isLeaf()) {
        for (int i = 0; i < node->getChildren().size(); i++) {
            printNode(node->getChildren()[i]);
        }
    }
}

void BTree::menu() {
    int choice;
    int key;

    do {
        std::cout << "1. Insert key\n";
        std::cout << "2. Remove key\n";
        std::cout << "3. Search key\n";
        std::cout << "4. Print tree\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter key to insert: ";
                std::cin >> key;
                insert(key);
                break;
            case 2:
                std::cout << "Enter key to remove: ";
                std::cin >> key;
                remove(key);
                break;
            case 3:
                std::cout << "Enter key to search: ";
                std::cin >> key;
                search(key);
                break;
            case 4:
                std::cout << "B-Tree: ";
                printTree();
                std::cout << "\n";
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
        std::cout << "\n";
    } while (choice != 5);
}

int main() {
    int degree;
    std::cout << "Enter the degree of the B-tree: ";
    std::cin >> degree;

    BTree btree(degree);
    btree.menu();

    return 0;
}

