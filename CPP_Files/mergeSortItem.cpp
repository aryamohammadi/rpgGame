#include "../header/mergeSort.h"

void MergeSort::merge(vector<ItemStack*>& array, SortOrder order, int left, int mid, int right){
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    vector<ItemStack*> Left(leftSize);
    vector<ItemStack*> Right(rightSize);

    for(unsigned i = 0; i < leftSize; i++){
        Left[i] = array[left + 1];
    }
    for(unsigned i = 0; i < rightSize; i++){ 
        Right[i] = array[mid + 1 + i];
    }
    int indexOfFirstSubArray = 0;
    int indexOfSecondSubArray = 0;
    int indexOfMergedSubArray = left;

    while(indexOfFirstSubArray < leftSize && indexOfSecondSubArray < rightSize){
        if(CompareItem::compare(Left[indexOfFirstSubArray]->getItem(), Right[indexOfSecondSubArray]->getItem(), sortConfig, order)){
            array[indexOfMergedSubArray] = Left[indexOfFirstSubArray];
            indexOfFirstSubArray ++;
        }
        else{
            array[indexOfMergedSubArray] = Right[indexOfSecondSubArray];
            indexOfSecondSubArray ++;
        }
        indexOfMergedSubArray ++;
    }

    while(indexOfFirstSubArray < leftSize){
        array[indexOfMergedSubArray] = Left[indexOfFirstSubArray];
        indexOfFirstSubArray ++;
        indexOfMergedSubArray ++;
    }   
    
    while(indexOfSecondSubArray < rightSize){
        array[indexOfMergedSubArray] = Left[indexOfSecondSubArray];
        indexOfSecondSubArray ++;
        indexOfMergedSubArray ++;
    }
}

void MergeSort::mergeSort(vector<ItemStack*>& array, SortOrder order, int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;

        mergeSort(array, order, left, mid);
        mergeSort(array, order, mid + 1, right);

        merge(array, order, left, mid, right);
    }
}