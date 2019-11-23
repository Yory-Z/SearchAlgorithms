#include <iostream>
#include <ctime>
#include "util/FileWordsExtract.h"
#include "search/Binary.h"
#include "search/BinarySearchTree.h"
#include "search/SequenceSearchTree.h"
#include "search/RedBlackTree.h"
using namespace std;

void testBST();

void testRBT();

void testSearchingPerformance();

void BSTvsRBT();


int main() {

    // testSearchingPerformance();

//    testRBT();

    BSTvsRBT();

    return 0;
}

void BSTvsRBT() {
    time_t buildBegin, buildEnd;
    int end = 10000000;
    srand(time(NULL));

    for (int i = 10000; i < end; i *= 2) {
        vector<int> vec = ArrayHelper::GenerateNearlyOrderVec(i, i / 10);
//        vector<int> vec = ArrayHelper::GenerateUnorderVec(i, 1, i);

        int tar = rand() % end + 1;
        cout << "size: " << i <<endl;

        buildBegin = clock();

        RedBlackTree<int> rbt;
        for (int j : vec) {
            rbt.insert(j);
        }
        rbt.midOrder();
//        rbt.find(tar);
//        rbt.remove(tar);

        buildEnd = clock();

        cout << "RedBlackTree cause time: " << double(buildEnd - buildBegin) / CLOCKS_PER_SEC<<" S"<<endl;

        buildBegin = clock();

        BinarySearchTree<int, int> bst;
        for (int j : vec) {
            bst.insert(j, j);
        }
        bst.inOrderIterate();
//        bst.search(tar);
//        bst.remove(tar);

        buildEnd = clock();

        cout << "BinarySearchTree cause time: " << double(buildEnd - buildBegin) / CLOCKS_PER_SEC<<" S"<<endl;

        cout << endl;
    }
}

void testSearchingPerformance(){
    vector<string> words;
    string fileName = "E:\\CPPProject\\SearchAlgorithms\\search\\Diary.txt";

    //the words will be convert to lowercase letters
    FileWordsExtract::ExtractWords(fileName, words);

    time_t buildBegin, buildEnd;

    cout<<"Build Time cause analysis:"<<endl;
    buildBegin = clock();
    BinarySearchTree<string, int> binarySearchTree;
    for (vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        int *res = binarySearchTree.search(*it);
        if (res == nullptr){
            binarySearchTree.insert(*it, 1);
        } else {
            ++(*res);
        }
    }
    buildEnd = clock();
    cout<<"binary tree build cause time: "<<double(buildEnd - buildBegin) / CLOCKS_PER_SEC<<" S"<<endl;

    buildBegin = clock();
    SequenceSearchTree<string, int> sequenceSearchTree;
    for (vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        int *res = sequenceSearchTree.search(*it);
        if (res == nullptr){
            sequenceSearchTree.insert(*it, 1);
        } else {
            ++(*res);
        }
    }
    buildEnd = clock();
    cout<<"sequence build cause time: "<<double(buildEnd - buildBegin) / CLOCKS_PER_SEC<<" S"<<endl;

    cout<<"all words: "<<words.size()<<", binary tree's words(no duplicate): "<<sequenceSearchTree.size()<<endl;
    cout<<endl;


    cout<<"Search time cause analysis: "<<endl;
    string find;

    time_t start, end;

    srand(time(NULL));
    int testTime = 10;
    for (int i = 0; i < testTime; ++i) {
        find = words.at(rand() % words.size());

        cout<<"find: "<<find<<endl;
        int occurTimes = 0;

        start = clock();
        occurTimes = *binarySearchTree.search(find);
        end = clock();
        cout<<"binary tree search cause time: "<<double(end - start) / CLOCKS_PER_SEC<<" S"<<endl;

        start = clock();
        occurTimes = *sequenceSearchTree.search(find);
        end = clock();
        cout<<"sequence search cause time: "<<double(end - start) / CLOCKS_PER_SEC<<" S"<<endl;

        cout<<"occur "<<occurTimes<<endl;
        cout<<endl;
    }

}

void testRBT() {
    RedBlackTree<int> rbt;
//    vector<int> vec{10, 5, 4, 2, 15, 13, 8, 11, 9};
//    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    vector<int> vec{13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    vector<int> vec = ArrayHelper::GenerateUnorderVec(50, 1, 1000);

    ArrayHelper::PrintVec(vec);

    for (int i : vec) {
        rbt.insert(i);
    }

    for (int i : vec) {
        rbt.midOrder();
        cout << endl;

        rbt.remove(i);
    }

}

void testBST(){
    BinarySearchTree<int, int> bst;
//    vector<int> vec{1, 2, 3, 4, 5, 6};
//    vector<int> vec{6, 5, 4, 3, 2, 1};
    vector<int> vec{9, 3, 13, 1, 8, 10, 19, 12, 15, 14, 17};
    for (int i = 0; i < vec.size(); ++i) {
        bst.insert(vec.at(i), i);
    }

    bst.levelOrder();
    cout<<endl;
}