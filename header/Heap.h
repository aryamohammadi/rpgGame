#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>  // For std::swap
#include <functional>

// Template for the MaxHeap class, allowing any type T
template<typename T>

class MaxHeap {
    private:
        std::vector<T> heap; // Vector of generic type T

    public:
        MaxHeap() {}
        void insert(const T& value);
        T getMax() const;
        void removeMax();
        bool isEmpty() const;
        int size() const;
        void displayHeap() const;
        void heapifyUp(int index);
        void heapifyDown(int index);
};
