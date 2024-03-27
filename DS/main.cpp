#include <iostream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <vector>
#include <iomanip>
std::string getExtension(const std::string& filename) {
    size_t dotIndex = filename.rfind('.');
    return (dotIndex != std::string::npos) ? filename.substr(dotIndex) : "";
}

void displayOptions(const std::vector<std::string>& options) {
    std::cout << "Welcome! Please choose a data structure:\n\n";
    std::cout << std::setw(10) << "No." << std::setw(20) << "Data Structure" << '\n';
    std::cout << "----------------------------------------\n";

    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << std::setw(10) << i + 1 << std::setw(50) << options[i] << '\n';
    }
}

int main() {
    std::vector<std::string> dataStructures = {

        "MULTIWAY-TREE",
        "HASH-LIST",
        "PATRICIA-TREE",
        "FIBONACCI-HEAP",
        "BINOMIAL-HEAP",
        "KD-TREE",
        "SUFFIX-TREE",
        "RADIX-TREE",
        "HASHED-ARRAY-TREE",
        "CUCKOO-HASH-TABLE",
        "B-TREE",
        "BLOOM-FILTER",
        "RED-BLACK-TREE",
        "SKIP-LIST",
        "ROPE",
        "UNION-FIND",
        "XOR-LINKED-LIST",
        "SPARSE-MATRIX",
        "SUFFIX-ARRAY",
        "HASH-TABLE",
        "BINARY-INDEXED-TREE",
        "TRIE",
        "DOUBLE-ENDED-QUEUE",
        "SEGMENT-TREE",
        "STACK",
        "QUEUE",
        "CIRCULAR-QUEUE",
        "SINGLE-LINKED-LIST",
        "DOUBLE-LINKED-LIST",
        "CIRCULAR-LINKED-LIST",
        "STACK-BY-LINKED-LIST",
        "QUEUE-BY-LINKED-LIST",
        "ALGORITHMIC-ANALYSIS-OF-GRAPH-DATA-STRUCTURE",
        "GRAPH-DATA-STRUCTURE-VISUALISATION",
        "BINARY-SEARCH-TREE",
        "AVL-TREE",
        "MIN-HEAP",
        "MAX-HEAP",
        "ARRAY",
        "MATRIX"
    };

    displayOptions(dataStructures);
    std::string input;
    std::cout << "ENTER NAME OF DATA STRUCTURE : ";
    std::getline(std::cin, input);

    std::string directoryPath = "C:\\Users\\HP\\Desktop\\DS\\PROJECT";

    DIR* dir = opendir(directoryPath.c_str());
    if (dir) {
        dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                std::string filename = entry->d_name;

                // Check if the input string matches the file name
                if (filename.find(input) != std::string::npos) {
                    // Execute the matching file on the console
                    std::string fullPath = directoryPath + "/" + filename;
                    std::string command = "g++ -o temp " + fullPath + " && temp.exe";

                    system(command.c_str());
                    break;  // Stop searching after finding the first match
                }
            }
        }
        closedir(dir);
    }

    return 0;
}
