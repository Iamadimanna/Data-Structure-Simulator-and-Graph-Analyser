#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class BinaryIndexedTree {
private:
    vector<int> BIT;
    int size;

public:
    BinaryIndexedTree(int n) {
        size = n;
        BIT.resize(n + 1, 0);
    }

    void update(int index, int value) {
        if (index <= 0 || index > size) {
            cout << "Invalid index!\n";
            return;
        }

        int diff = value - get(index);
        while (index <= size) {
            BIT[index] += diff;
            index += index & -index;
        }
    }

    int query(int index) {
        if (index <= 0 || index > size) {
            cout << "Invalid index!\n";
            return 0;
        }

        int sum = 0;
        while (index > 0) {
            sum += BIT[index];
            index -= index & -index;
        }
        return sum;
    }

    int get(int index) {
        if (index <= 0 || index > size) {
            cout << "Invalid index!\n";
            return 0;
        }
        return BIT[index];
    }

    void printTree() {
        int levels = log2(size) + 1;
        int currentLevel = 0;
        int nodesToPrint = 1;
        int nodeCounter = 0;

        for (int i = 1; i <= size; i++) {
            if (nodeCounter == nodesToPrint) {
                cout << endl;
                nodeCounter = 0;
                nodesToPrint *= 2;
                currentLevel++;
            }

            for (int j = 0; j < pow(2, levels - currentLevel) - 1; j++) {
                cout << " ";
            }

            cout << BIT[i];

            for (int j = 0; j < pow(2, levels - currentLevel + 1) - 1; j++) {
                cout << " ";
            }

            nodeCounter++;
        }

        cout << endl;
    }
};

int main() {
    int size;
    cout << "Enter the size of the Binary Indexed Tree: ";
    cin >> size;

    BinaryIndexedTree bit(size);

    int choice, index, value;

    while (true) {
        cout << "\n--- Binary Indexed Tree Options ---\n";
        cout << "1. Update\n";
        cout << "2. Query\n";
        cout << "3. Print Tree\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the index and value to update: ";
                cin >> index >> value;
                bit.update(index, value);
                cout << "Updated BIT.\n";
                break;
            case 2:
                cout << "Enter the index to query: ";
                cin >> index;
                cout << "Query Result: " << bit.query(index) << endl;
                break;
            case 3:
                cout << "Binary Indexed Tree (BIT) Structure:\n";
                bit.printTree();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

