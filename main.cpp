#include <iostream>
#include <ctime>
#include "util/FileWordsExtract.h"
#include "search/Binary.h"
#include "search/BinarySearchTree.h"
#include "search/SequenceSearchTree.h"
using namespace std;

void testSearchingPerformance();

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

int main() {

    testSearchingPerformance();
    return 0;
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