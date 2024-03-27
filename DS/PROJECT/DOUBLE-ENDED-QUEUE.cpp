#include <bits/stdc++.h>
using namespace std;

class Deque {
private:
    vector<int> arr;
    int front;
    int rear;
    int capacity;

public:
    Deque(int size) {
        arr.resize(size);
        capacity = size;
        front = -1;
        rear = 0;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (front == 0 && rear == capacity - 1) || (front == rear + 1);
    }

    void insertFront(int value) {
        if (isFull()) {
            cout << "Deque is full. Unable to insert element at the front.\n";
            return;
        }

        if (front == -1) {
            front = 0;
            rear = 0;
        } else if (front == 0) {
            front = capacity - 1;
        } else {
            front--;
        }

        arr[front] = value;
        cout << "Inserted " << value << " at the front of the deque.\n";
    }

    void insertRear(int value) {
        if (isFull()) {
            cout << "Deque is full. Unable to insert element at the rear.\n";
            return;
        }

        if (front == -1) {
            front = 0;
            rear = 0;
        } else if (rear == capacity - 1) {
            rear = 0;
        } else {
            rear++;
        }

        arr[rear] = value;
        cout << "Inserted " << value << " at the rear of the deque.\n";
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty. Unable to delete element from the front.\n";
            return;
        }

        cout << "Deleted " << arr[front] << " from the front of the deque.\n";

        if (front == rear) {
            front = -1;
            rear = -1;
        } else if (front == capacity - 1) {
            front = 0;
        } else {
            front++;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty. Unable to delete element from the rear.\n";
            return;
        }

        cout << "Deleted " << arr[rear] << " from the rear of the deque.\n";

        if (front == rear) {
            front = -1;
            rear = -1;
        } else if (rear == 0) {
            rear = capacity - 1;
        } else {
            rear--;
        }
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Deque is empty. No front element to retrieve.\n";
            return -1;
        }

        return arr[front];
    }

    int getRear() {
        if (isEmpty()) {
            cout << "Deque is empty. No rear element to retrieve.\n";
            return -1;
        }

        return arr[rear];
    }
};

int main() {
    int size;
    cout << "Enter the size of the deque: ";
    cin >> size;

    Deque deque(size);

    int choice;
    int value;

    while (true) {
        cout << "\n--- Deque Operations ---\n";
        cout << "1. Insert at Front\n";
        cout << "2. Insert at Rear\n";
        cout << "3. Delete from Front\n";
        cout << "4. Delete from Rear\n";
        cout << "5. Get Front Element\n";
        cout << "6. Get Rear Element\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert at the front: ";
                cin >> value;
                deque.insertFront(value);
                break;
            case 2:
                cout << "Enter the value to insert at the rear: ";
                cin >> value;
                deque.insertRear(value);
                break;
            case 3:
                deque.deleteFront();
                break;
            case 4:
                deque.deleteRear();
                break;
            case 5:
                cout << "Front Element: " << deque.getFront() << endl;
                break;
            case 6:
                cout << "Rear Element: " << deque.getRear() << endl;
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

