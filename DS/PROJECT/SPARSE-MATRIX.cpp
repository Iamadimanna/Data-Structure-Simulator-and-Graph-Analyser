#include<bits/stdc++.h>
class SparseMatrix {
private:
    int rows;
    int cols;
    std::vector<int> values;
    std::vector<int> columnIndices;
    std::vector<int> rowPointers;

public:
    SparseMatrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
        rowPointers.resize(rows + 1, 0);
    }

    void insert(int row, int col, int value) {
        values.push_back(value);
        columnIndices.push_back(col);
        rowPointers[row + 1]++;
    }

    void compress() {
        for (int i = 1; i <= rows; i++) {
            rowPointers[i] += rowPointers[i - 1];
        }
    }

    int get(int row, int col) const {
        for (int i = rowPointers[row]; i < rowPointers[row + 1]; i++) {
            if (columnIndices[i] == col) {
                return values[i];
            }
        }
        return 0;
    }
};

int main() {
    int numRows, numCols;
    std::cout << "Enter the number of rows: ";
    std::cin >> numRows;
    std::cout << "Enter the number of columns: ";
    std::cin >> numCols;

    SparseMatrix matrix(numRows, numCols);

    int numNonZero;
    std::cout << "Enter the number of non-zero elements: ";
    std::cin >> numNonZero;

    std::cout << "Enter the non-zero elements in the format (row, column, value):\n";
    for (int i = 0; i < numNonZero; i++) {
        int row, col, value;
        std::cin >> row >> col >> value;
        matrix.insert(row, col, value);
    }

    matrix.compress();

    std::cout << "Sparse Matrix:\n";
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << matrix.get(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

