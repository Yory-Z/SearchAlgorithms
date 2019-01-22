//
// Created by Yory on 2019/1/20.
//

#ifndef SEARCHALGORITHMS_SEQUENCESEARCHTREE_H
#define SEARCHALGORITHMS_SEQUENCESEARCHTREE_H


#include<vector>
#include <string>
#include "../util/FileWordsExtract.h"
using std::vector;
using std::string;

template <typename Key, typename Value>
class SequenceSearchTree {
private:
    struct Node {
        Key key;
        Value value;
        Node *next;

        Node(Key key, Value value){
            this->key = key;
            this->value = value;
            this->next = nullptr;
        }
    };

    Node *head;
    int count;

public:
    static void testSequenceSearchTree(){

        vector<string> words;
        string fileName = "E:\\CPPProject\\Algorithm\\search\\TestFile.txt";
        FileWordsExtract::ExtractWords(fileName, words);

        string find = "and";
        int count = 0;

        SequenceSearchTree<string, int> sst;
        for (vector<string>::iterator it = words.begin(); it != words.end(); ++it){
            string temp = *it;
            if (temp == find){
                ++count;
            }

            int *res = sst.search(temp);
            if (res == nullptr){
                sst.insert(*it, 1);
            } else {
                ++(*res);
            }
        }

        cout<<"all words: "<<words.size()<<", bst words(no duplicate): "<<sst.size()<<endl;
        cout<<find<<" : "<<count<<endl;
        if (sst.contain(find)){
            cout<<find<<" : "<<*sst.search(find)<<endl;
        } else{
            cout<<"no "<<find<<" in "<<fileName<<endl;
        }

    }

    SequenceSearchTree(): head(nullptr), count(0){};
    ~SequenceSearchTree(){}

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    void insert(Key key, Value value){
        Node *node = head;
        while (node != nullptr){
            if (key == node->key){
                node->value = value;
                return;
            }
            node = node->next;
        }

        Node *temp = new Node(key, value);
        temp->next = head;
        head = temp;
        ++count;
    }

    bool contain(Key key){
        Node *node = head;
        while (node != nullptr){
            if (key == node->key){
                return true;
            }
            node = node->next;
        }
        return false;
    }

    Value* search(Key key){
        Node *node = head;
        while (node != nullptr){
            if (key == node->key){
                return &(node->value);
            }
            node = node->next;
        }
        return nullptr;
    }

};


#endif //SEARCHALGORITHMS_SEQUENCESEARCHTREE_H
