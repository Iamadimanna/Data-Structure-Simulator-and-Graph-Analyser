#include <iostream>
#include <vector>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);

        // Initialize each element as a separate subset
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        // Find the root of the subset
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        // Union two subsets based on rank
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    void printSets() {
        std::cout << "Set Representatives: ";
        for (int i = 0; i < parent.size(); ++i) {
            if (parent[i] == i) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    int size;
    std::cout << "Enter the size of the Union-Find data structure: ";
    std::cin >> size;

    UnionFind uf(size);

    int choice, x, y;
    int set;
    while (true) {
        std::cout << "Union-Find Menu:\n";
        std::cout << "1. Union Sets\n";
        std::cout << "2. Find Set\n";
        std::cout << "3. Print Sets\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter two elements to union: ";
                std::cin >> x >> y;
                uf.unionSets(x, y);
                std::cout << "Sets unioned successfully.\n";
                break;

            case 2:
                std::cout << "Enter an element to find its set: ";
                std::cin >> x;
                set = uf.find(x);
                std::cout << "Element " << x << " belongs to the set with representative " << set << std::endl;
                break;

            case 3:
                uf.printSets();
                break;

            case 4:
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

