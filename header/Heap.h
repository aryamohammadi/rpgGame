#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

class MaxHeap {
private:
    std::vector<int> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MaxHeap() {}
    void insert(int value);
    int getMax() const;
    void removeMax();
    bool isEmpty() const;
    int size() const;
    void displayHeap() const;
};
