#pragma once
#include <vector>
#include "combat.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>  // For std::swap
#include <functional>

// Template for the MaxHeap class, allowing any type T
//template<typename T>

class MaxHeap {
    private:
        std::vector<Character*> heap; // Vector of generic type T

    public:
        MaxHeap() {}
        void insert(int value);
        int getMax() const;
        void removeMax();
        bool isEmpty() const;
        int size() const;
        void displayHeap() const;
        void heapsort(std::vector<Character*>& array);
        void heapifyDown(std::vector<Character*>&array, int index);
        void heapifyUp(std::vector<Character*>&array, int index);
};
