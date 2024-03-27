#include <bits/stdc++.h>
using namespace std;

class Array {
private:
  int* arr;
  int size;

public:
  Array(int s) {
    size = s;
    arr = new int[size];
  }

  ~Array() {
    delete[] arr;
  }

  void set(int index, int value) {
    if (index >= 0 && index < size) {
      arr[index] = value;
    } else {
      cout << "Index out of bounds!" << endl;
    }
  }

  int get(int index) {
    if (index >= 0 && index < size) {
      return arr[index];
    } else {
      cout << "Index out of bounds!" << endl;
      return 0;
    }
  }

  int getSize() {
    return size;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
};

int main() {
  int size;
  cout << "Enter the size of the array: ";
  cin >> size;

  Array arr(size);

  cout << "Array of size " << arr.getSize() << " created." << endl;

  // Testing the array operations
  int option, index, value;

  do {
    cout << "What operation do you want to perform? " <<
      "Select option number. Enter 0 to exit." << endl;
    cout << "1. Set element at index" << endl;
    cout << "2. Get element at index" << endl;
    cout << "3. Print array" << endl;
    cout << "0. Exit" << endl;

    cin >> option;

    switch (option) {
    case 0:
      break;
    case 1:
      cout << "Enter index: ";
      cin >> index;
      cout << "Enter value: ";
      cin >> value;
      arr.set(index, value);
      cout << endl;
      break;
    case 2:
      cout << "Enter index: ";
      cin >> index;
      cout << "Value at index " << index << ": " << arr.get(index) << endl;
      break;
    case 3:
      cout << "Array: ";
      arr.print();
      cout << endl;
      break;
    default:
      cout << "Enter a valid option number" << endl;
    }

  } while (option != 0);

  return 0;
}


