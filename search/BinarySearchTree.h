//
// Created by Yory on 2019/1/20.
//

/*
 * This Binary Searching Tree doesn't have duplicate key,
 * if the key gonna insert exists, then update it's value
 * Description: the very root nodes' value in the binary searching tree is bigger than it's left nodes,
 *              smaller than it's right nodes
 * */

#ifndef SEARCHALGORITHMS_BINARYSEARCHTREE_H
#define SEARCHALGORITHMS_BINARYSEARCHTREE_H


#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>

using namespace std;

#include "../util/FileWordsExtract.h"
using namespace FileWordsExtract;

template <typename Key, typename Value>
class BinarySearchTree {
private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value){
            this->key = key;
            this->value = value;
            this->left = nullptr;
            this->right = nullptr;
        }

        Node(Node *node){
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };

    //used for postOrderIterate
    typedef struct {
        Node *node;
        int flag;
    } TagNode;

    Node *root;
    int count;

public:
    static void testBinarySearchTree(){
        vector<string> words;
        string fileName = "E:\\CPPProject\\Algorithm\\search\\TestFile.txt";
        FileWordsExtract::ExtractWords(fileName, words);

        string find = "he";

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

    }
    BinarySearchTree(): root(nullptr), count(0){}
    ~BinarySearchTree(){
//        destroyRecur(root);
    }

    int size(){
        return count;
    }
    bool isEmpty(){
        return count == 0;
    }

    void insert(Key key, Value value){
//        root = insertRecur(root, key, value);
        insertIterate(key, value);
        ++count;
    }

    bool contain(Key key){
//        return containRecur(root, key);
        return containIterate(key);
    }

    Value* search(Key key) {
//        return searchRecur(root, key);
        return searchIterate(key);
    }

    void preOrder(){
        preOrderRecur(root);
    }
    void preOrderIterate(){
        Node *node = root;
        stack<Node *> st;
        while (!st.empty() || node != nullptr){
            while (node != nullptr){
                cout<<node->key<<' ';
                st.push(node);
                node = node->left;
            }
            if (!st.empty()){
                node = st.top();
                st.pop();
                node = node->right;
            }
        }
    }
    void inOrder(){
        inOrderRecur(root);
    }
    void inOrderIterate(){
        Node *node = root;
        stack<Node *> st;
        while (!st.empty() || node != nullptr) {
            while (node != nullptr){
                st.push(node);
                node = node->left;
            }
            if (!st.empty()){
                node = st.top();
                st.pop();
//                cout<<node->key<<' ';
                node = node->right;
            }
        }
    }
    void postOrder(){
        postOrderRecur(root);
    }
    void postOrderIterate(){
        Node *node = root;
        TagNode tagNode;
        stack<TagNode> st;
        while (!st.empty() || node != nullptr){
            while (node != nullptr){
                tagNode.node = node;
                tagNode.flag = 1;
                st.push(tagNode);
                node = node->left;
            }
            tagNode = st.top();
            st.pop();
            //has traversed the node a time
            if (tagNode.flag == 1){
                tagNode.flag = 2;
                st.push(tagNode);
                node = tagNode.node->right;
            } else {
                //the second time traverse the node
                cout<<tagNode.node->key<<' ';
                node = nullptr;
            }
        }
    }

    void levelOrder(){
        queue<Node *> q;
        q.push(root);
        while (!q.empty()){
            Node *node = q.front();
            q.pop();
            cout<<node->key<<' ';

            if (node->left != nullptr){
                q.push(node->left);
            }
            if (node->right != nullptr){
                q.push(node->right);
            }
        }
    }

    Key findMinimum(){
        assert( count != 0);
//        Node *node = findMinimumRecur(root);
        Node *node = findMinimumIterate(root);
        return node->key;
    }
    Key findMaximum(){
        assert( count != 0);
//        Node *node = findMaximumRecur(root);
        Node *node = findMaximumIterate(root);
        return node->key;
    }
    void removeMinimum(){
        assert(count != 0);
//        root = removeMinimumRecur(root);
        root = removeMinimumIterate(root);
    }
    void removeMaximum(){
        assert(count != 0);
//        root = removeMaximumRecur(root);
        root = removeMaximumIterate(root);
    }
    void remove(Key key){
        assert(count != 0);
//        root = removeRecur(root, key);
        root = removeIterate(root, key);
    }

private:
    void insertIterate(Key key, Value value) {
        Node *node = root;
        Node *preNode = root;

        //find the correct location
        while (node != nullptr){
            if (key == node->key){
                //the key already existed, update it's value
                node->value = value;
                return;
            } else if (key < node->key){
                preNode = node;
                node = node->left;
            } else {
                preNode = node;
                node = node->right;
            }
        }

        Node *temp = new Node(key, value);
        //if the preNode is not nullptr, it mean the location isn't the root
        if (preNode != nullptr){
            if (key < preNode->key){
                preNode->left = temp;
            } else {
                preNode->right = temp;
            }
        } else {
            //if the preNode is nullptr, it mean the binary tree doesn't have node
            //so the new created node will be the root node
            root = temp;
        }
    }
    bool containIterate(Key key){
        Node *node = root;
        while (node != nullptr){
            if (key == node->key){
                return true;
            } else if (key < node->key){
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }
    Value* searchIterate(Key key){
        Node *node = root;
        while (node != nullptr){
            if (key == node->key){
                return &(node->value);
            } else if (key < node->key){
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }

    Node* insertRecur(Node *node, Key key, Value value){
        //when the node is nullptr, it means the recursion is end
        //now just return the new created node, the preNode will point to it
        if (node == nullptr){
            ++count;
            return new Node(key, value);
        }

        if (key == node->key){
            //the key already existed, update it's value
            node->value = value;
        } else if (key < node->key){
            //the key is smaller the current root node's key, turn to the left tree
            node->left = insertRecur(node->left, key, value);
        } else if (key > node->key){
            //the key is bigger the current root node's key, turn to the right tree
            node->right = insertRecur(node->right, key, value);
        }
        return node;
    }
    bool containRecur(Node *node, Key key){
        if (node == nullptr){
            return false;
        }

        if (key == node->key){
            return true;
        } else if (key < node->key){
            return containRecur(node->left, key);
        } else {
            return containRecur(node->right, key);
        }
    }
    Value* searchRecur(Node *node, Key key){
        if (node == nullptr){
            return nullptr;
        }

        if (key == node->key){
            return &(node->value);
        } else if (key < node->key){
            return searchRecur(node->left, key);
        } else {
            return searchRecur(node->right, key);
        }
    }

    void preOrderRecur(Node *node){
        if (node != nullptr){
            cout<<node->key<<' ';
            preOrderRecur(node->left);
            preOrderRecur(node->right);
        }
    }
    void inOrderRecur(Node *node){
        if (node != nullptr){
            inOrderRecur(node->left);
            cout<<node->key<<' ';
            inOrderRecur(node->right);
        }
    }
    void postOrderRecur(Node *node){
        if (node != nullptr){
            postOrderRecur(node->left);
            postOrderRecur(node->right);
            cout<<node->key<<' ';
        }
    }
    void destroyRecur(Node *node){
        if (node != nullptr){
            destroyRecur(node->left);
            destroyRecur(node->right);

            delete node;
            --count;
        }
    }

    Node* findMinimumRecur(Node *node){
        if (node->left == nullptr){
            return node;
        }
        return findMinimumRecur(node->left);
    }
    Node* findMaximumRecur(Node *node){
        if (node->right == nullptr){
            return node;
        }
        return findMaximumRecur(node->right);
    }
    Node* findMinimumIterate(Node *beginRoot){
        assert(count != 0);
        Node *node = beginRoot;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* findMaximumIterate(Node *beginRoot){
        assert(count != 0);
        Node *node = beginRoot;
        while (node->right != nullptr){
            node = node->right;
        }
        return node;
    }

    Node* removeMinimumIterate(Node *beginRoot){
        assert( count != 0);
        Node *node = beginRoot;
        Node *preNode = beginRoot;
        while (node->left != nullptr){
            preNode = node;
            node = node->left;
        }

        //the node need to delete isn't the root node
        if (preNode != node){
            preNode->left = node->right;
            delete node;
            --count;
            return beginRoot;
        }

        //the node need to delete is the beginRoot
        //the binary tree from the beginRoot doesn't have left tree
        //find the minimum node from the right tree to replace the root node
        if (node->right != nullptr){
            node = node->right;
            while (node->left != nullptr){
                preNode = node;
                node = node->left;
            }
            preNode->left = nullptr;

            if(beginRoot->right != node) {
                //this node become the new root node
                node->left = beginRoot->left;
                node->right = beginRoot->right;
            }

            delete beginRoot;
            return node;
        }

        //here, the binary tree doesn't have left tree and right tree
        delete beginRoot;
        return nullptr;
    }
    Node* removeMaximumIterate(Node *beginRoot){
        assert( count != 0);
        Node *node = beginRoot;
        Node *preNode = beginRoot;
        while (node->right != nullptr){
            preNode = node;
            node = node->right;
        }

        //the node need to delete isn't the root node
        if (preNode != node){
            preNode->right = node->left;
            delete node;
            --count;
            return beginRoot;
        }

        //the node need to delete is the beginRoot
        //the binary tree from the beginRoot doesn't have right tree
        //find the maximum node from the left tree to replace the root node
        if (node->left != nullptr) {
            node = node->left;
            while (node->right != nullptr){
                preNode = node;
                node = node->right;
            }
            preNode->right = nullptr;

            if (beginRoot->left != node) {
                //this node become the new root node
                node->left = beginRoot->left;
                node->right = beginRoot->right;
            }

            delete beginRoot;
            return node;
        }

        //here, the binary tree from the beginRoot doesn't have left tree and right tree
        delete beginRoot;
        return nullptr;
    }
    Node* removeMinimumRecur(Node *node){
        if (node->left == nullptr){
            Node *rightNode = node->right;
            delete node;
            --count;
            return rightNode;
        }
        node->left = removeMinimumRecur(node->left);
        return node;
    }
    Node* removeMaximumRecur(Node *node){
        if(node->right == nullptr){
            Node *leftNode = node->left;
            delete node;
            --count;
            return leftNode;
        }
        node->right = removeMaximumRecur(node->right);
        return node;
    }

    Node* removeRecur(Node *node, Key key){
        if (node == nullptr){
            return nullptr;
        }

        if (key < node->key){
            node->left = removeRecur(node->left, key);
            return node;
        } else if (key > node->key){
            node->right = removeRecur(node->right, key);
            return node;
        } else {
            //the current node's left tree is nullptr
            //delete the current node, and return it's right node(nullptr is ok)
            if (node->left == nullptr){
                Node *rightNode = node->right;
                delete node;
                --count;
                return rightNode;
            }

            //the current node's right tree is nullptr
            //delete the current node, and return it's left node(nullptr is ok)
            if (node->right == nullptr){
                Node *leftNode = node->left;
                delete node;
                --count;
                return leftNode;
            }

            //In this case, the current node's have left tree and right tree
            //We have two solution
            //solution 1: get the successor from the right tree
            //solution 2:get the successor from the left tree
            Node *candidateNode = findCandidateNodeReplace(node);

            delete node;
            --count;
            return candidateNode;
        }
    }
    Node* removeIterate(Node *beginRoot, Key key) {
        Node* node = beginRoot;
        Node* preNode = beginRoot;

        while (node != nullptr && key != node->key) {
            preNode = node;
            if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        if (node == nullptr) {
            return beginRoot;
        }

        //the node need to delete isn't the beginRoot node
        if (preNode != node) {

            if (node->left == nullptr) {
                //if the current node doesn't have left tree
                //let the preNode point to it's right tree
                //delete the current node, and return the right tree(nullptr is ok)

                Node* rightNode = node->right;
                preNode->left == node ? preNode->left = rightNode : preNode->right = rightNode;
            } else if (node->right == nullptr) {
                //if the current node doesn't have right tree
                //let the preNode point to it's left tree
                //delete the current node, and return the left tree(nullptr is ok)

                Node* leftNode = node->left;
                preNode->left == node ? preNode->left = leftNode : preNode->right = leftNode;
            } else {
                //the current node have right tree and left tree
                Node* candidateNode = findCandidateNodeReplace(node);
                preNode->left == node ? preNode->left = candidateNode : preNode->right = candidateNode;
            }

            delete node;
            --count;
            return beginRoot;
        }

        //the node need to delete is the beginRoot node
        //or the current node's left tree and right tree isn't nullptr
        Node* candidateNode = findCandidateNodeReplace(node);
        delete node;
        return candidateNode;
    }

    Node* findCandidateNodeReplace(Node* node){
        assert(node->left != nullptr || node->right != nullptr);

        Node* candidateNode = nullptr;
        if (node->left != nullptr) {
            //solution 1: get the successor from the left tree

            candidateNode = new Node(findMaximumIterate(node->left));

//            node->left = removeMaximumRecur(node->left);
            node->left = removeMaximumIterate(node->left);

            candidateNode->left = node->left;
            candidateNode->right = node->right;
        } else {
            //solution 2:get the successor from the right tree

            candidateNode = new Node(findMinimumIterate(node->right));

            node->right = removeMinimumRecur(node->right);
//            node->right = removeMinimumIterate(node->right);

            candidateNode->left = node->left;
            candidateNode->right = node->right;
        }

        //because this function create a node
        ++count;
        return candidateNode;
    }

};

#endif //SEARCHALGORITHMS_BINARYSEARCHTREE_H
