#include "../header/mergeSort.h"

void MergeSort::merge(vector<unique_ptr<ItemStack>>& array, SortOrder order, int left, int mid, int right){
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    vector<unique_ptr<ItemStack>> Left(leftSize);
    vector<unique_ptr<ItemStack>> Right(rightSize);

    for(unsigned i = 0; i < leftSize; i++){
        Left[i] = move(array[left + i]);
    }
    for(unsigned i = 0; i < rightSize; i++){ 
        Right[i] = move(array[mid + 1 + i]);
    }
    int indexOfFirstSubArray = 0;
    int indexOfSecondSubArray = 0;
    int indexOfMergedSubArray = left;

    while(indexOfFirstSubArray < leftSize && indexOfSecondSubArray < rightSize){
        if(Left[indexOfFirstSubArray] == nullptr){
            array[indexOfMergedSubArray] = move(Right[indexOfSecondSubArray]);
            indexOfSecondSubArray++;
        }
        else if(Right[indexOfSecondSubArray] == nullptr){
            array[indexOfMergedSubArray] = move(Left[indexOfFirstSubArray]);
            indexOfFirstSubArray++;
        }
        else{
            if(CompareItem::compare(Left[indexOfFirstSubArray]->getItem(), Right[indexOfSecondSubArray]->getItem(), sortConfig, order)){
                array[indexOfMergedSubArray] = move(Left[indexOfFirstSubArray]);
                indexOfFirstSubArray ++;
            }
            else{
                array[indexOfMergedSubArray] = move(Right[indexOfSecondSubArray]);
                indexOfSecondSubArray ++;
            }
        }
        indexOfMergedSubArray ++;
    }

    while(indexOfFirstSubArray < leftSize){
        array[indexOfMergedSubArray] = move(Left[indexOfFirstSubArray]);
        indexOfFirstSubArray ++;
        indexOfMergedSubArray ++;
    }   
    
    while(indexOfSecondSubArray < rightSize){
        array[indexOfMergedSubArray] = move(Right[indexOfSecondSubArray]);
        indexOfSecondSubArray ++;
        indexOfMergedSubArray ++;
    }
}

void MergeSort::mergeSort(vector<unique_ptr<ItemStack>>& array, SortOrder order, int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;

        mergeSort(array, order, left, mid);
        mergeSort(array, order, mid + 1, right);

        merge(array, order, left, mid, right);
    }
}
