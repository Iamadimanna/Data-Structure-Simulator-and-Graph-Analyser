#include <bits/stdc++.h>
class XORNode {
public:
    int data;
    XORNode* npx; // XOR of prev and next nodes' addresses

    XORNode(int data) : data(data), npx(nullptr) {}
};

XORNode* XOR(XORNode* a, XORNode* b) {
    return reinterpret_cast<XORNode*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
}

XORNode* createNode(int data) {
    XORNode* newNode = new XORNode(data);
    return newNode;
}

void insertNode(XORNode** head, int data) {
    XORNode* newNode = createNode(data);
    newNode->npx = *head;

    if (*head != nullptr) {
        (*head)->npx = XOR(newNode, (*head)->npx);
    }

    *head = newNode;
}

void printList(XORNode* head) {
    XORNode* curr = head;
    XORNode* prev = nullptr;
    XORNode* next;

    std::cout << "XOR Linked List: ";
    while (curr != nullptr) {
        std::cout << curr->data << " ";

        next = XOR(prev, curr->npx);

        prev = curr;
        curr = next;
    }
    std::cout << std::endl;
}

int main() {
    XORNode* head = nullptr;
    int choice, data;

    while (true) {
        std::cout << "XOR Linked List Menu:\n";
        std::cout << "1. Insert Node\n";
        std::cout << "2. Print List\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter data to insert: ";
                std::cin >> data;
                insertNode(&head, data);
                std::cout << "Node inserted successfully.\n";
                break;

            case 2:
                printList(head);
                break;

            case 3:
                std::cout << "Exiting...\n";
                exit(0);

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        std::cout << std::endl;
    }

    return 0;
}

