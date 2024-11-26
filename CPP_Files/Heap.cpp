#include "Heap.h"
#include "character.h"
#include <iostream>

using namespace std;

MaxHeap::~MaxHeap(){
    for (int i = 0; i < heap.size();i++){
        delete heap.at(i);
    }
}

//make a deep copy of the vector passed in and put it into heap


void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!(*heap[index] > *heap[parent])) {
            return; // Exit the function if the heap property is satisfied
        }
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

// Restore the heap property starting from the root
//template<typename T>
void MaxHeap::heapifyDown(int index) {
    int size = heap.size();
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    while (leftChild < size) {
        if (heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        // If the largest is still the current node, we're done
        if (largest == index) {
            return;
        }

        // Otherwise, swap and continue heapifying down
        std::swap(heap[index], heap[largest]);
        index = largest;

        // Update child indices for the new current node
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
    }
}

// Insert a new element into the heap
//template<typename T>
/* void MaxHeap::insert(const Character& value) {
    heap.push_back(new Character(value));
    heapifyUp(heap.size() - 1);
} */

// Get the maximum element
//template<typename T>
Character* MaxHeap::getMax() const {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}

// Remove the maximum element
//template<typename T>
void MaxHeap::removeMax() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    heap[0] = heap.back();  // Replace root with the last element
    heap.pop_back();        // Remove the last element
    if (!heap.empty()) {
        heapifyDown(0);     // Restore heap property starting from the root
    }
}

// Check if the heap is empty
//template<typename T>
bool MaxHeap::isEmpty() const {
    return heap.empty();
}

// Get the size of the heap
//template<typename T>
int MaxHeap::size() const {
    return heap.size();
}

// Display the heap
//template<typename T>
/* void MaxHeap::displayHeap() const {
    for (const Character& value : heap) {
        std::cout << value << " ";
    }
    std::cout << "\n";
} */
