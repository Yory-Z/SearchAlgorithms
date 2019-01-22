//
// Created by Yory on 2019/1/20.
//

#ifndef SEARCHALGORITHMS_BINARY_H
#define SEARCHALGORITHMS_BINARY_H

#include <algorithm>
#include "../util/ArrayHelper.h"
#include<string>
using std::string;

template <typename T>
class Binary {
public:
    static void testBinarySearch();

private:
    static int BinarySearch(T *arr, int n, int target, const string &type);
    static int BinarySearchRecur(T *arr, int target, int left, int right);
    static int Floor(T *arr, int begin, int target);
    static int Ceil(T *arr, int n, int begin, int target);
};

template <typename T>
void Binary<T>::testBinarySearch() {
    int n = 12;
    int *arr = ArrayHelper::GenerateUnorderArray(n, 0, 20);
    int target = 5;
    string type = "floor";
//    string type = "ceil";

    sort(arr, arr + n);
    ArrayHelper::PrintArray(arr, n);

    int res = BinarySearch(arr, n, target, type);
    cout<<"res: "<<res<<endl;
}

template <typename T>
int Binary<T>::BinarySearch(T *arr, int n, int target, const string &type) {
    int left = 0, right = n - 1;
    while (left <= right){
        int mid = left + (right - left) / 2;
        if (arr[mid] == target){
            return type == "floor" ? Floor(arr, mid, target) : Ceil(arr, n, mid, target);
        } else if (arr[mid] > target){
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (left == 0)
        return 0;
    else if (right == n - 1)
        return n - 1;
    else
        return type == "floor" ? left - 1 : left;
}

template <typename T>
int Binary<T>::Floor(T *arr, int begin, int target) {
    while (begin >= 0 && arr[begin] == target) {
        --begin;
    }
    return begin + 1;
}

template <typename T>
int Binary<T>::Ceil(T *arr, int n, int begin, int target) {
    while (begin < n && arr[begin] == target){
        ++begin;
    }
    return begin - 1;
}

template <typename T>
int Binary<T>::BinarySearchRecur(T *arr, int target, int left, int right) {
    if (left <= right){
        int mid = left + (right - left) / 2;
        if (arr[mid] == target){
            return mid;
        }else if (arr[mid] > target) {
            return BinarySearchRecur(arr, target, left, mid - 1);
        } else {
            return BinarySearchRecur(arr, target, mid + 1, right);
        }
    }
    return -1;
}

#endif //SEARCHALGORITHMS_BINARY_H
