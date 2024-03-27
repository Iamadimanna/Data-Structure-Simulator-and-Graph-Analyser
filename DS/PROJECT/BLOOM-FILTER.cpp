#include <bits/stdc++.h>

class BloomFilter {
private:
    std::bitset<10000> filter;
    std::vector<std::function<size_t(const std::string&)>> hashFunctions;

public:
    BloomFilter() {
        hashFunctions = {
            std::hash<std::string>(),
            std::hash<std::string_view>(),
            [](const std::string& str) {
                size_t hash = 0;
                for (char c : str) {
                    hash += c;
                }
                return hash;
            }
        };
    }

    void add(const std::string& str) {
        for (const auto& hashFunc : hashFunctions) {
            size_t index = hashFunc(str) % filter.size();
            filter.set(index);
        }
    }

    bool contains(const std::string& str) {
        for (const auto& hashFunc : hashFunctions) {
            size_t index = hashFunc(str) % filter.size();
            if (!filter.test(index)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    BloomFilter filter;

    std::cout << "Bloom Filter Menu:\n";
    std::cout << "1. Add an element\n";
    std::cout << "2. Check if an element exists\n";
    std::cout << "3. Exit\n";

    int choice;
    std::string element;

    while (true) {
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter an element to add: ";
                std::cin >> element;
                filter.add(element);
                std::cout << "Element added.\n";
                break;
            case 2:
                std::cout << "Enter an element to check: ";
                std::cin >> element;
                std::cout << "Element " << element << " ";
                if (filter.contains(element)) {
                    std::cout << "probably exists in the filter.\n";
                } else {
                    std::cout << "does not exist in the filter.\n";
                }
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

