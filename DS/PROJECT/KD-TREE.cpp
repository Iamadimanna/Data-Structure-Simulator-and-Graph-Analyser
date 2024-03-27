#include <iostream>
#include <vector>
#include <algorithm>

// Define a Point structure to represent a point in K-D space
struct Point {
    std::vector<double> coordinates;

    Point(const std::vector<double>& _coordinates) : coordinates(_coordinates) {}
};

// Define the K-D Tree class
class KDTree {
private:
    struct Node {
        Point point;
        Node* left;
        Node* right;

        Node(const Point& _point) : point(_point), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t dimensions;

public:
    KDTree(size_t _dimensions) : root(nullptr), dimensions(_dimensions) {}

    ~KDTree() {
        deleteTree(root);
    }

    void insert(const Point& point) {
        root = insertNode(root, point, 0);
    }

    void search(const Point& target) {
        Node* result = searchNode(root, target, 0);
        if (result)
            std::cout << "Point found" << std::endl;
        else
            std::cout << "Point not found" << std::endl;
    }

private:
    Node* insertNode(Node* node, const Point& point, size_t depth) {
        if (!node)
            return new Node(point);

        size_t currentDimension = depth % dimensions;

        if (point.coordinates[currentDimension] < node->point.coordinates[currentDimension])
            node->left = insertNode(node->left, point, depth + 1);
        else
            node->right = insertNode(node->right, point, depth + 1);

        return node;
    }

    Node* searchNode(Node* node, const Point& target, size_t depth) {
        if (!node || node->point.coordinates == target.coordinates)
            return node;

        size_t currentDimension = depth % dimensions;

        if (target.coordinates[currentDimension] < node->point.coordinates[currentDimension])
            return searchNode(node->left, target, depth + 1);
        else
            return searchNode(node->right, target, depth + 1);
    }

    void deleteTree(Node* node) {
        if (!node)
            return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

// Main Function
int main() {
    size_t dimensions;
    std::cout << "Enter the number of dimensions: ";
    std::cin >> dimensions;

    KDTree kdTree(dimensions);

    int choice;
    std::vector<double> coordinates;

    do {
        std::cout << "\nK-D Tree Menu\n";
        std::cout << "1. Insert a point\n";
        std::cout << "2. Search for a point\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                coordinates.clear();
                for (size_t i = 0; i < dimensions; ++i) {
                    double coord;
                    std::cout << "Enter the coordinate for dimension " << (i + 1) << ": ";
                    std::cin >> coord;
                    coordinates.push_back(coord);
                }
                kdTree.insert(Point(coordinates));
                std::cout << "Point inserted successfully.\n";
                break;
            case 2:
                coordinates.clear();
                for (size_t i = 0; i < dimensions; ++i) {
                    double coord;
                    std::cout << "Enter the coordinate for dimension " << (i + 1) << ": ";
                    std::cin >> coord;
                    coordinates.push_back(coord);
                }
                kdTree.search(Point(coordinates));
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

