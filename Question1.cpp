#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

// d-ary Heap class
class DHeap {
private:
    vector<int> heap;   // internal array storing heap elements
    int d;              // degree of the heap
    bool isMaxHeap;     // true if max-heap, false if min-heap

    // Compare function: returns true if a should be above b in the heap.
    bool compare(int a, int b) {
        return isMaxHeap ? (a > b) : (a < b);
    }

    // Bubble up (swim) operation.
    void bubbleUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / d;
            if (compare(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Bubble down (sink) operation.
    void bubbleDown(int index) {
        int n = heap.size();
        while (true) {
            int best = index;
            // check all d children
            for (int i = 1; i <= d; i++) {
                int child = d * index + i;
                if (child < n && compare(heap[child], heap[best])) {
                    best = child;
                }
            }
            if (best != index) {
                swap(heap[index], heap[best]);
                index = best;
            } else {
                break;
            }
        }
    }

public:
    // Constructor: set d and heap type ("min" or "max").
    DHeap(int degree, const string &heapType) : d(degree) {
        isMaxHeap = (heapType == "max");
    }

    // Insert an element into the heap.
    void insert(int key) {
        heap.push_back(key);
        bubbleUp(heap.size() - 1);
    }

    // Extract the root element (max or min, depending on type).
    // Returns the extracted element.
    int extract() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty!");
        }
        int root = heap[0];
        // Move last element to root and remove last element.
        heap[0] = heap.back();
        heap.pop_back();
        // Restore heap property.
        if (!heap.empty())
            bubbleDown(0);
        return root;
    }

    // Print the heap in level-wise format.
    void printHeap() {
        int n = heap.size();
        int level = 0;
        int index = 0;
        while (index < n) {
            // Number of nodes on current level is at most d^level.
            int nodesThisLevel = pow(d, level);
            // Print all nodes for this level.
            for (int i = 0; i < nodesThisLevel && index < n; i++, index++) {
                cout << heap[index] << " ";
            }
            cout << "\n";
            level++;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read the first line: d and heap type.
    int d;
    string heapType;
    cin >> d >> heapType;

    // Create our d-ary heap.
    DHeap dheap(d, heapType);

    string operation;
    // Process subsequent operations until end of file.
    while (cin >> operation) {
        if (operation == "ins") {
            // Read entire line of numbers (next line may contain several numbers).
            cin.ignore(); // consume newline before the numbers line
            string numsLine;
            getline(cin, numsLine);
            istringstream iss(numsLine);
            int num;
            while (iss >> num) {
                dheap.insert(num);
            }
        } else if (operation == "extract") {
            // For each extract, remove the root.
            try {
                int extracted = dheap.extract();
                // You can print the extracted value if desired; here we just perform the operation.
                // For example: cout << "Extracted: " << extracted << "\n";
            } catch (runtime_error &e) {
                cout << e.what() << "\n";
            }
        }
    }
    
    // Print the final heap level-wise.
    dheap.printHeap();
    return 0;
}
