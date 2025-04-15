#include <iostream>
using namespace std;

class Heap {
    int maxHeap[20], minHeap[20], numStudents, value;
public:
    Heap() { 
        maxHeap[0] = 0;  
        minHeap[0] = 0;  
    }
    
    void getData();
    void insertMaxHeap(int[], int);
    void upAdjustMaxHeap(int[], int);
    void insertMinHeap(int[], int);
    void upAdjustMinHeap(int[], int);
    void displayMinMax();
};

void Heap::getData() {  
    cout << "\nEnter the number of students: ";
    cin >> numStudents;
    
    cout << "\nEnter the marks: ";
    for (int i = 0; i < numStudents; i++) {   
        cin >> value;
        insertMaxHeap(maxHeap, value);
        insertMinHeap(minHeap, value);
    }
}

void Heap::insertMaxHeap(int heap[], int value) {
    int n = heap[0];  
    heap[n + 1] = value;
    heap[0] = n + 1;
    upAdjustMaxHeap(heap, n + 1);
}

void Heap::upAdjustMaxHeap(int heap[], int index) {
    int temp;
    while (index > 1 && heap[index] > heap[index / 2]) {
        temp = heap[index];
        heap[index] = heap[index / 2];
        heap[index / 2] = temp;
        index = index / 2;
    }
}

void Heap::insertMinHeap(int heap[], int value) {
    int n = heap[0];  
    heap[n + 1] = value;
    heap[0] = n + 1;
    upAdjustMinHeap(heap, n + 1);
}

void Heap::upAdjustMinHeap(int heap[], int index) {
    int temp;
    while (index > 1 && heap[index] < heap[index / 2]) {
        temp = heap[index];
        heap[index] = heap[index / 2];
        heap[index / 2] = temp;
        index = index / 2;
    }
}

void Heap::displayMinMax() {
    cout << "\nMaximum Marks: " << maxHeap[1] << "\nHeap structure (Max Heap): ";
    for (int i = 1; i <= numStudents; i++) {   
        cout << maxHeap[i] << " ";
    }

    cout << "\n\nMinimum Marks: " << minHeap[1] << "\nHeap structure (Min Heap): ";
    for (int i = 1; i <= numStudents; i++) {   
        cout << minHeap[i] << " ";
    }
    cout << endl;
}

int main() {  
    Heap heapObj;
    heapObj.getData();
    heapObj.displayMinMax();
    return 0;
}
