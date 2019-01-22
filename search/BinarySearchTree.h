//
// Created by Yory on 2019/1/20.
//

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
        destroyRecur(root);
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
    void midOrder(){
        midOrderRecur(root);
    }
    void midOrderIterate(){
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
                cout<<node->key<<' ';
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
            if (tagNode.flag == 1){
                tagNode.flag = 2;
                st.push(tagNode);
                node = tagNode.node->right;
            } else {
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
        Node *node = findMaximumIterate();
        return node->key;
    }
    void removeMinimum(){
        assert(count != 0);
        root = removeMinimumRecur(root);
//        removeMinimumIterate();
    }
    void removeMaximum(){
        assert(count != 0);
        root = removeMaximumRecur(root);
//        removeMaximumIterate();
    }
    void remove(Key key){
        assert(count != 0);
        root = removeRecur(root, key);
    }

private:
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
    void insertIterate(Key key, Value value) {
        Node *node = root;
        Node *preNode = root;

        while (node != nullptr){
            if (key == node->key){
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
        if (preNode != nullptr){
            if (key < preNode->key){
                preNode->left = temp;
            } else {
                preNode->right = temp;
            }
        } else {
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
    Node* insertRecur(Node *node, Key key, Value value){
        if (node == nullptr){
            ++count;
            return new Node(key, value);
        }

        if (key == node->key){
            node->value = value;
        } else if (key < node->key){
            node->left = insertRecur(node->left, key, value);
        } else if (key > node->key){
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

    void preOrderRecur(Node *node){
        if (node != nullptr){
            cout<<node->key<<' ';
            preOrderRecur(node->left);
            preOrderRecur(node->right);
        }
    }
    void midOrderRecur(Node *node){
        if (node != nullptr){
            midOrderRecur(node->left);
            cout<<node->key<<' ';
            midOrderRecur(node->right);
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

    void removeMinimumIterate(Node *beginRoot){
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
            return;
        }

        //the node need to delete is the root node
        removeRootNode(node);
    }
    void removeMaximumIterate(Node *beginRoot){
        assert( count != 0);
        Node *node = beginRoot;
        Node *preNode = beginRoot;
        while (node->right != nullptr){
            preNode = node;
            node = node->right;
        }

        if (preNode != node){
            preNode->right = node->left;
            delete node;
            --count;
            return;
        }

        //the node need to delete is the root node
        removeRootNode(node);
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

    void removeRootNode(Node *rootNode){
        Node *node = rootNode;
        Node *preNode = rootNode;
        //the node need to delete is the root node
        if (node->left != nullptr){
            while (node->left != nullptr){
                preNode = node;
                node = node->left;
            }
            *rootNode = *node;
            preNode->left = nullptr;
            delete node;
        } else if (node->right != nullptr){
            while (node->right != nullptr){
                preNode = node;
                node = node->right;
            }
            *rootNode = *node;
            preNode->right = nullptr;
            delete node;
        }
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
            if (node->left == nullptr){
                Node *rightNode = node->right;
                delete node;
                --count;
                return rightNode;
            }
            if (node->right == nullptr){
                Node *leftNode = node->left;
                delete node;
                --count;
                return leftNode;
            }

            //get the successor from the right tree
/*            Node *candidateNode = new Node(findMinimumIterate(node->right));
            ++count;
//            node->right = removeMinimumRecur(node->right);
            removeMinimumIterate(node->right);*/

            //get the successor from the left tree
            Node *candidateNode = new Node(findMaximumIterate(node->left));
            ++count;
//            node->left = removeMaximumRecur(node->left);
            removeMaximumIterate(node->left);

            candidateNode->left = node->left;
            candidateNode->right = node->right;
            delete node;
            --count;
            return candidateNode;
        }
    }

};

#endif //SEARCHALGORITHMS_BINARYSEARCHTREE_H