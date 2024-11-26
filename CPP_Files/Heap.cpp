#include "Heap.h"

template<typename T>
void MaxHeap<T>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!(heap[index] > heap[parent])) {
            return; // Exit the function if the heap property is satisfied
        }
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

// Restore the heap property starting from the root
template<typename T>
void MaxHeap<T>::heapifyDown(int index) {
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
template<typename T>
void MaxHeap<T>::insert(const T& value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

// Get the maximum element
template<typename T>
T MaxHeap<T>::getMax() const {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap[0];
}

// Remove the maximum element
template<typename T>
void MaxHeap<T>::removeMax() {
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
template<typename T>
bool MaxHeap<T>::isEmpty() const {
    return heap.empty();
}

// Get the size of the heap
template<typename T>
int MaxHeap<T>::size() const {
    return heap.size();
}

// Display the heap
template<typename T>
void MaxHeap<T>::displayHeap() const {
    for (const T& value : heap) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}
