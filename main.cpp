#include <iostream>
#include <ctime>
#include "util/FileWordsExtract.h"
#include "search/Binary.h"
#include "search/BinarySearchTree.h"
#include "search/SequenceSearchTree.h"
using namespace std;

void testSearchingPerformance();

int main() {

    testSearchingPerformance();
    return 0;
}

void testSearchingPerformance(){
    vector<string> words;
    string fileName = "E:\\CPPProject\\SearchAlgorithms\\search\\Diary.txt";
    FileWordsExtract::ExtractWords(fileName, words);
    string find = "he";

    time_t time1 = clock();

    BinarySearchTree<string, int> bst;
    for (vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        int *res = bst.search(*it);
        if (res == nullptr){
            bst.insert(*it, 1);
        } else {
            ++(*res);
        }
    }

    cout<<"all words: "<<words.size()<<", bst words(no duplicate): "<<bst.size()<<endl;
    if (bst.contain(find)){
        cout<<find<<" : "<<*bst.search(find)<<endl;
    } else{
        cout<<"no "<<find<<" in "<<fileName<<endl;
    }


    time_t time2 = clock();

    SequenceSearchTree<string, int> sst;
    for (vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        int *res = sst.search(*it);
        if (res == nullptr){
            sst.insert(*it, 1);
        } else {
            ++(*res);
        }
    }

    cout<<"all words: "<<words.size()<<", sst words(no duplicate): "<<sst.size()<<endl;
    if (sst.contain(find)){
        cout<<find<<" : "<<*sst.search(find)<<endl;
    } else{
        cout<<"no "<<find<<" in "<<fileName<<endl;
    }

    time_t time3 = clock();

    cout<<endl;
    cout<<"course time analysis:"<<endl;
    cout<<"binary tree search: "<<double(time2 - time1) / CLOCKS_PER_SEC<<" S"<<endl;
    cout<<"sequence search: "<<double(time3- time2) / CLOCKS_PER_SEC<<" S"<<endl;

}