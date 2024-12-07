#include "../header/Heap.h"
#include "../header/character.h"
#include <iostream>

using namespace std;

void MaxHeap::heapifyUp(std::vector<Character*>&array, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!(array[index]->getSpeed() > array[parent]->getSpeed())) {
            return; // Exit the function if the heap property is satisfied
        }
        std::swap(array[index], array[parent]);
        index = parent;
    }
}


void MaxHeap::heapifyDown(std::vector<Character*>&array, int index) {
    int size = array.size();
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    while (leftChild < size) {
        if (array[leftChild]->getSpeed() > array[largest]->getSpeed()) {
            largest = leftChild;
        }
        if (rightChild < size && array[rightChild]->getSpeed() > array[largest]->getSpeed()) {
            largest = rightChild;
        }

        // If the largest is still the current node, we're done
        if (largest == index) {
            return;
        }

        // Otherwise, swap and continue heapifying down
        std::swap(array[index], array[largest]);
        index = largest;

        // Update child indices for the new current node
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
    }
}

void MaxHeap::heapsort(std::vector<Character*>& array) {
    int n = array.size();

    // Step 1: Build the MaxHeap (heapify the entire array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(array, i);
    }

    // Step 2: Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move the current root (largest) to the end
        std::swap(array[0], array[i]);

        // Call heapifyDown on the reduced heap
        // Note: Pass size as i to ignore the sorted elements
        heapifyDown(array, 0);
    }
    std::cout << "\n";
}
