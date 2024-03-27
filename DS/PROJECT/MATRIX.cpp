#include<bits/stdc++.h>
using namespace std;

class Matrix {
private:
  vector<vector<int>> matrix;
  int rows;
  int cols;

public:
  Matrix(int numRows, int numCols) {
    rows = numRows;
    cols = numCols;
    matrix.resize(rows, vector<int>(cols, 0));
  }

  void set(int row, int col, int value) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
      matrix[row][col] = value;
    } else {
      cout << "Invalid row or column index!" << endl;
    }
  }

  int get(int row, int col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
      return matrix[row][col];
    } else {
      cout << "Invalid row or column index!" << endl;
      return 0;
    }
  }

  int getNumRows() {
    return rows;
  }

  int getNumCols() {
    return cols;
  }

  void print() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
  }

  void transpose() {
    vector<vector<int>> transposed(cols, vector<int>(rows, 0));
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        transposed[j][i] = matrix[i][j];
      }
    }
    matrix = transposed;
    swap(rows, cols);
  }

  void printSpiral() {
    int topRow = 0, bottomRow = rows - 1;
    int leftCol = 0, rightCol = cols - 1;

    while (topRow <= bottomRow && leftCol <= rightCol) {
      // Print top row
      for (int col = leftCol; col <= rightCol; col++) {
        cout << matrix[topRow][col] << " ";
      }
      topRow++;

      // Print right column
      for (int row = topRow; row <= bottomRow; row++) {
        cout << matrix[row][rightCol] << " ";
      }
      rightCol--;

      // Print bottom row
      if (topRow <= bottomRow) {
        for (int col = rightCol; col >= leftCol; col--) {
          cout << matrix[bottomRow][col] << " ";
        }
        bottomRow--;
      }

      // Print left column
      if (leftCol <= rightCol) {
        for (int row = bottomRow; row >= topRow; row--) {
          cout << matrix[row][leftCol] << " ";
        }
        leftCol++;
      }
    }

    cout << endl;
  }
};

int main() {
  int numRows, numCols;
  cout << "Enter the number of rows: ";
  cin >> numRows;
  cout << "Enter the number of columns: ";
  cin >> numCols;

  Matrix mat(numRows, numCols);

  cout << "Matrix of size " << mat.getNumRows() << "x" << mat.getNumCols() << " created." << endl;

  // Testing the matrix operations
  int option, row, col, value;

  do {
    cout << "What operation do you want to perform? " <<
      "Select option number. Enter 0 to exit." << endl;
    cout << "1. Set element at position" << endl;
    cout << "2. Get element at position" << endl;
    cout << "3. Print matrix" << endl;
    cout << "4. Transpose matrix" << endl;
    cout << "5. Print matrix in spiral form" << endl;
    cout << "0. Exit" << endl;

    cin >> option;

    switch (option) {
    case 0:
      break;
    case 1:
      cout << "Enter row: ";
      cin >> row;
      cout << "Enter column: ";
      cin >> col;
      cout << "Enter value: ";
      cin >> value;
      mat.set(row, col, value);
      cout << endl;
      break;
    case 2:
      cout << "Enter row: ";
      cin >> row;
      cout << "Enter column: ";
      cin >> col;
      cout << "Value at position (" << row << ", " << col << "): " << mat.get(row, col) << endl;
      break;
    case 3:
      cout << "Matrix:" << endl;
      mat.print();
      cout << endl;
      break;
    case 4:
      cout << "Transposing matrix..." << endl;
      mat.transpose();
      cout << "Matrix transposed." << endl;
      cout << endl;
      break;
    case 5:
      cout << "Printing matrix in spiral form:" << endl;
      mat.printSpiral();
      cout << endl;
      break;
    default:
      cout << "Enter a valid option number" << endl;
    }

  } while (option != 0);

  return 0;
}


