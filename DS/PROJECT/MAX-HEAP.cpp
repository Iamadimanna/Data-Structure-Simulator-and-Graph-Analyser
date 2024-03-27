#include<bits/stdc++.h>
using namespace std;

void swap(int& x, int& y) {
  int temp = x;
  x = y;
  y = temp;
}

class MaxHeap {
public:
  int* harr;
  int capacity;
  int heap_size;

  MaxHeap(int cap) {
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
  }

  int parent(int i) {
    return (i - 1) / 2;
  }

  int left(int i) {
    return (2 * i + 1);
  }

  int right(int i) {
    return (2 * i + 2);
  }

  int getMax() {
    return harr[0];
  }

  void insertKey(int k) {
    if (heap_size == capacity) {
      cout << "\nOverflow: Could not insert Key\n";
      return;
    }

    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    while (i != 0 && harr[parent(i)] < harr[i]) {
      swap(harr[i], harr[parent(i)]);
      i = parent(i);
    }
  }

  void increaseKey(int i, int new_val) {
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] < harr[i]) {
      swap(harr[i], harr[parent(i)]);
      i = parent(i);
    }
  }

  void deleteKey(int i) {
    increaseKey(i, INT_MAX);
    extractMax();
  }

  void linearSearch(int val) {
    for (int i = 0; i < heap_size; i++) {
      if (harr[i] == val) {
        cout << "Value Found!";
        return;
      }
    }
    cout << "Value NOT Found!";
  }

  int extractMax() {
    if (heap_size <= 0)
      return INT_MIN;
    if (heap_size == 1) {
      heap_size--;
      return harr[0];
    }

    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    maxHeapify(0);

    return root;
  }

  void maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < heap_size && harr[l] > harr[i])
      largest = l;
    if (r < heap_size && harr[r] > harr[largest])
      largest = r;
    if (largest != i) {
      swap(harr[i], harr[largest]);
      maxHeapify(largest);
    }
  }

  void printArray() {
    for (int i = 0; i < heap_size; i++)
      cout << harr[i] << " ";
    cout << endl;
  }

  int height() {
    return ceil(log2(heap_size + 1)) - 1;
  }
};

int main() {
  int s;
  cout << "Enter Size of Max Heap" << endl;
  cin >> s;
  MaxHeap obj(s);
  cout << "Max Heap Created" << endl;

  int option, val;

  do {
    cout << "What operation do you want to perform? " <<
      "Select Option number. Enter 0 to exit." << endl;
    cout << "1. Insert Key/Node" << endl;
    cout << "2. Search Key/Node" << endl;
    cout << "3. Delete Key/Node" << endl;
    cout << "4. Get Max" << endl;
    cout << "5. Extract Max" << endl;
    cout << "6. Height of Heap" << endl;
    cout << "7. Print/Traversal Heap values" << endl;
    cout << "8. Clear Screen" << endl;
    cout << "0. Exit Program" << endl;

    cin >> option;

    switch (option) {
    case 0:
      break;
    case 1:
      cout << "INSERT Operation -" << endl;
      cout << "Enter VALUE to INSERT in HEAP: ";
      cin >> val;
      obj.insertKey(val);
      cout << endl;
      break;
    case 2:
      cout << "SEARCH Operation -" << endl;
      cout << "Enter VALUE to SEARCH in HEAP: ";
      cin >> val;
      obj.linearSearch(val);
      break;
    case 3:
      cout << "DELETE Operation -" << endl;
      cout << "Enter INDEX of Heap Array to DELETE: ";
      cin >> val;
      obj.deleteKey(val);
      break;
    case 4:
      cout << "GET Max value : " << obj.getMax();
      cout << endl;
      break;
    case 5:
      cout << "EXTRACT Max value : " << obj.extractMax();
      cout << endl;
      break;
    case 6:
      cout << "HEAP TREE HEIGHT: " << obj.height() << endl;
      break;
    case 7:
      cout << "PRINT Heap Array: " << endl;
      obj.printArray();
      cout << endl;
      break;
    case 8:
      system("cls");
      break;
    default:
      cout << "Enter Proper Option number " << endl;
    }

  } while (option != 0);

  return 0;
}


