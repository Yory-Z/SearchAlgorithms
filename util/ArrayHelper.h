//
// Created by Yory on 2019/1/20.
//

#ifndef SEARCHALGORITHMS_ARRAYHELPER_H
#define SEARCHALGORITHMS_ARRAYHELPER_H


#include <iostream>
#include <ctime>
#include <cassert>
#include <vector>

using namespace std;

namespace ArrayHelper{

    void PrintArray(int *arr, int n){
        for (int i = 0; i < n; ++i){
            cout<<arr[i]<<' ';
        }
        cout<<endl;
    }

    void PrintVec(vector<int> vec) {
        for (int i : vec) {
            cout << i << ' ';
        }
        cout<<endl;
    }

    int* GenerateUnorderArray(int sum, int begin, int end){
        int* arr = new int[sum];
        srand(time(NULL));
        for (int i = 0; i < sum; ++i) {
            arr[i] = rand() % (end - begin + 1) + begin;
        }
        return arr;
    }

    vector<int> GenerateUnorderVec(int sum, int begin, int end){
        vector<int> vec(sum);
        srand(time(NULL));
        for (int i = 0; i < sum; ++i) {
            vec[i] = rand() % (end - begin + 1) + begin;
        }
        return vec;
    }

    int* GenerateNearlyOrderArray(int n, int swapTimes){
        int* arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }

        srand(time(NULL));
        for (int j = 0; j < swapTimes; ++j) {
            int posX = rand()%n;
            int posY = rand()%n;
            swap(arr[posX], arr[posY]);
        }
        return arr;
    }

    vector<int> GenerateNearlyOrderVec(int n, int swapTimes){
        vector<int> vec(n);

        for (int i = 0; i < n; ++i) {
            vec[i] = i;
        }

        srand(time(NULL));
        for (int j = 0; j < swapTimes; ++j) {
            int posX = rand()%n;
            int posY = rand()%n;
            swap(vec[posX], vec[posY]);
        }
        return vec;
    }

    template <typename T>
    bool IsSorted(T *arr, int n){
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i+1]){
                return false;
            }
        }
        return true;
    }

    template <typename T>
    void TestSort(const string &sortName, void (*sort)(T[], int), T *arr, int n){
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(IsSorted(arr, n));
        cout<<sortName<<" : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S"<<endl;
    }

    int* CopyArray(const int *arr, int n){
        int *a = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = arr[i];
        }
        return a;
    }

}

#endif //SEARCHALGORITHMS_ARRAYHELPER_H
