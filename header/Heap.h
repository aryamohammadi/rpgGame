#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>  // For std::swap
#include <functional>
#include "../header/character.h"
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
        void heapifyUp(std::vector<Character*>&array, int index);
        void heapifyDown(std::vector<Character*>&array, int index);
        void heapsort(std::vector<Character*>& array);
};
