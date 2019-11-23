//
// Created by Yory on 2019/11/21.
//

#ifndef SEARCHALGORITHMS_REDBLACKTREE_H
#define SEARCHALGORITHMS_REDBLACKTREE_H

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

template <typename Key>
class RedBlackTree {
private:

    struct Color {
        const int RED = 1;
        const int BLACK = 2;
    } Color;

    struct Node {
        Key key;
        Node* pre;
        Node* left;
        Node* right;
        int color;

        Node(Node* pre, Node* left, Node* right, int color) {
            this->color = color;
        }

        explicit Node(Key key) {
            this->key = key;
        }
    };

    Node* NIL;
    Node* root;

    Node* findMinimum(Node* start) {
        while (start->left != NIL) {
            start = start->left;
        }
        return start;
    }

    void leftRotate(Node* x);
    void rightRotate(Node* x);

    void insertFixUp(Node* z);
    void insert(Node* z);

    void transplant(Node* tar, Node* can);

    void removeFixUp(Node* x);
    void remove(Node* z);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(Key k);

    void remove(Key k);

    void midOrder();

    Node* find(Key key) {
        Node* cur = root;
        while (cur != NIL) {
            if (key == cur->key) {
                return cur;
            } else if (key < cur->key) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return cur;
    }
};

template<typename Key>
RedBlackTree<Key>::RedBlackTree(): NIL(new Node(NULL, NULL, NULL, Color.BLACK)), root(NIL) {
}

template<typename Key>
RedBlackTree<Key>::~RedBlackTree() {
}

template<typename Key>
void RedBlackTree<Key>::leftRotate(RedBlackTree::Node* x) {
    Node* y = x->right;

    x->right = y->left;
    if (y->left != NIL) {
        y->left->pre = x;
    }

    y->pre = x->pre;
    if (x->pre == NIL) {
        root = y;
    } else if (x == x->pre->left) {
        x->pre->left = y;
    } else {
        x->pre->right = y;
    }

    y->left = x;
    x->pre = y;
}

template<typename Key>
void RedBlackTree<Key>::rightRotate(RedBlackTree::Node* x) {
    Node* y = x->left;

    x->left = y->right;
    if (y->right != NIL) {
        y->right->pre = x;
    }

    y->pre = x->pre;
    if (x->pre == NIL) {
        root = y;
    } else if (x == x->pre->left) {
        x->pre->left = y;
    } else {
        x->pre->right = y;
    }

    y->right = x;
    x->pre = y;
}

template<typename Key>
void RedBlackTree<Key>::insertFixUp(RedBlackTree::Node* z) {

    while (z->pre->color == Color.RED) {

        // z->pre 结点是 z->pre 结点的父亲的 left son
        if (z->pre == z->pre->pre->left) {

            // 叔结点
            Node* y = z->pre->pre->right;

            // case 1
            // 叔结点颜色为 RED
            // 调整颜色后，z 上移两层，执行下一轮循环
            if (y->color == Color.RED) {
                z->pre->color = Color.BLACK;
                y->color = Color.BLACK;
                z->pre->pre->color = Color.RED;
                z = z->pre->pre;

            } else {
                // case 2
                // z 的叔结点颜色为 BLACK 并且 z 是其父亲结点的 right son
                // 需要进行左旋将 z 转换为 left son
                if (z == z->pre->right) {
                    z = z->pre;
                    leftRotate(z);
                }

                // case 3
                // z 的叔结点颜色为 BLACK 并且 z 是其父亲结点的 left son
                z->pre->color = Color.BLACK;
                z->pre->pre->color = Color.RED;
                rightRotate(z->pre->pre);
            }
        }

        // z->pre 的结点是 z->pre 结点的父亲的 right son
        // 此情况与上面是对称的
        // 将上面的处理方法中的 right and left 相互转化即可得出下面的处理方式
        else {

            // 叔结点
            Node* y = z->pre->pre->left;

            // case 1
            // 叔结点颜色为 RED
            // 调整颜色后，z 上移两层，执行下一轮循环
            if (y->color == Color.RED) {
                z->pre->color = Color.BLACK;
                y->color = Color.BLACK;
                z->pre->pre->color = Color.RED;
                z = z->pre->pre;

            } else {
                // case 2
                // z 的叔结点颜色为 BLACK 并且 z 是其父亲结点的 left son
                // 需要进行右旋将 z 转换为 right son
                if (z == z->pre->left) {
                    z = z->pre;
                    rightRotate(z);
                }

                // case 3
                // z 的叔结点颜色为 BLACK 并且 z 是其父亲结点的 right son
                z->pre->color = Color.BLACK;
                z->pre->pre->color = Color.RED;
                leftRotate(z->pre->pre);
            }
        }
    }

    root->color = Color.BLACK;
}

template<typename Key>
void RedBlackTree<Key>::insert(RedBlackTree::Node* z) {
    Node* pre = NIL;
    Node* cur = root;

    while (cur != NIL) {
        pre = cur;
        if (z->key < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    z->pre = pre;
    if (pre == NIL) {
        root = z;
    } else if (z->key < pre->key) {
        pre->left = z;
    } else {
        pre->right = z;
    }

    z->left = NIL;
    z->right = NIL;
    z->color = Color.RED;

    insertFixUp(z);
}

/*
 * 用 can 结点替换掉 tar 结点
 * */
template<typename Key>
void RedBlackTree<Key>::transplant(RedBlackTree::Node *tar, RedBlackTree::Node *can) {
    if (tar->pre == NIL) {
        root = can;
    } else if (tar == tar->pre->left) {
        tar->pre->left = can;
    } else {
        tar->pre->right = can;
    }
    can->pre = tar->pre;
}

/*
 * 此函数给 x 指针所指向的结点加上一层额外的 BLACK
 * 但是 x->color 依旧不变
 * 所以，x 的颜色为 RED + BLACK (x->color 为 RED)
 * 或者 BLACK + BLACK (x->color 为 BLACK)
 *
 * 之所以加上一层额外的颜色，是为了保证删除或移走了原来为 BLACK 的结点后
 * 能够维持红黑树的第5条性质
 * */
template<typename Key>
void RedBlackTree<Key>::removeFixUp(RedBlackTree::Node *x) {

    while (x != root && x->color == Color.BLACK) {

        // x 是 left son
        if (x == x->pre->left) {

            // 兄弟结点
            Node* bro = x->pre->right;

            // case 1
            // 兄弟结点颜色为 RED
            // 修改父结点和兄弟结点的颜色，然后左旋
            // 得以将兄弟结点的颜色修改为 BLACK
            if (bro->color == Color.RED) {
                bro->color = Color.BLACK;
                x->pre->color = Color.RED;
                leftRotate(x->pre);
                // 左旋后更新兄弟结点
                bro = x->pre->right;
            }

            // case 2
            // 兄弟结点的颜色为 BLACK
            // 兄弟结点的子节点的颜色都为 BLACK
            // 将兄弟结点的颜色修改为 RED
            // 并且将 x 指针上移一层
            if (bro->left->color == Color.BLACK && bro->right->color == Color.BLACK) {
                bro->color = Color.RED;
                x = x->pre;
            } else {
                // case 3
                // 兄弟结点的 right son 颜色为 BLACK (left son 颜色为 RED)
                // 需要修改兄弟结点的 right son 颜色为 RED
                if (bro->right->color == Color.BLACK) {
                    bro->left->color = Color.BLACK;
                    bro->color = Color.RED;
                    rightRotate(bro);
                    // 更新兄弟结点
                    bro = x->pre->right;
                }

                // case 4
                // 兄弟结点颜色为 BLACK
                // 兄弟结点 right son 颜色为 RED
                bro->color = x->pre->color;
                x->pre->color = Color.BLACK;
                bro->right->color = Color.BLACK;
                leftRotate(x->pre);

                x = root;
            }
        }

        // x 是 right son
        // 此情况和上面是对称的
        // 将上面处理方法中的 right and left 相互转化即可得出下面的处理方式
        else {

            // 兄弟结点
            Node* bro = x->pre->left;

            // case 1
            // 兄弟结点颜色为 RED
            if (bro->color == Color.RED) {
                bro->color = Color.BLACK;
                x->pre->color = Color.RED;
                rightRotate(x->pre);
                // 更新兄弟结点
                bro = x->pre->left;
            }

            // case 2
            // 兄弟结点的颜色为 BLACK
            // 兄弟结点的子结点颜色都为 BLACK
            if (bro->left->color == Color.BLACK && bro->right->color == Color.BLACK) {
                bro->color = Color.RED;
                x = x->pre;

            } else {
                // case 3
                // 兄弟结点的 left son 颜色为 BLACK (right son 颜色为 RED)
                if (bro->left->color == Color.BLACK) {
                    bro->right->color = Color.BLACK;
                    bro->color = Color.RED;
                    leftRotate(bro);
                    // 更新兄弟结点
                    bro = x->pre->left;
                }

                // case 4
                // 兄弟结点的颜色为 BLACK
                // 兄弟结点 left son 颜色为 RED
                bro->color = x->pre->color;
                x->pre->color = Color.BLACK;
                bro->left->color = Color.BLACK;
                rightRotate(x->pre);

                x = root;
            }

        }

    }

    x->color = Color.BLACK;
}

/*
 * y 指向的是即将被删除的结点或被移至树中 z 的位置的结点
 * 记录 y 的踪迹，是因为当 y 的颜色为 BLACK 时， y 的变化可能导致红黑性质的破坏
 * x 指向的是用来顶替 y 原来位置的结点，因为 x 也可能引起红黑性质的破坏。
 * */
template<typename Key>
void RedBlackTree<Key>::remove(RedBlackTree::Node *z) {

    Node* y = z;
    Node* x = NIL;

    // 记住 y 原来的颜色
    int yOrgColor = y->color;

    // z 的子节点个数 < 2
    // left zon 为 NIL, 由 right son 顶替 z 的位置
    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    }

    // z 的子节点个数 < 2
    // right zon 为 NIL, 由 left son 顶替 z 的位置
    else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    }

    // z 的子结点个数大于等于 2
    else {

        // 从 right son 这颗子树中寻找最小的结点来顶替 z 的位置
        y = findMinimum(z->right);

        // 记住 y 原来的颜色
        yOrgColor = y->color;
        x = y->right;

        if (y->pre == z) {
            // 因为 z 即将被删除
            // 所以不能将 x->pre 赋值为 y->pre
            // 而需要按照下面的方式赋值
            x->pre = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->pre = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->pre = y;
        y->color = z->color;
    }

    // 当 y 原来的颜色为 BLACK 时，移走 y 会破坏红黑性质
    if (yOrgColor == Color.BLACK) {
        removeFixUp(x);
    }
}

template<typename Key>
void RedBlackTree<Key>::midOrder() {
    if (root == NULL) {
        return;
    }

    stack<Node* > sta;
    Node* cur = root;
    while (!sta.empty() || cur != NIL) {
        while (cur != NIL) {
            sta.push(cur);
            cur = cur->left;
        }

        if (!sta.empty()) {
            cur = sta.top();
            sta.pop();
//            cout << cur->key << ' ';
            cur = cur->right;
        }
    }
}

template<typename Key>
void RedBlackTree<Key>::insert(Key k) {
    Node* n = new Node(k);
    insert(n);
}

template<typename Key>
void RedBlackTree<Key>::remove(Key k) {
    Node* n = find(k);
    if (n != NIL) {
        remove(n);
//        cout << k << " was removed!" << endl;
    } else {
//        cout << "Can not find " << k << "." << endl;
    }
}

#endif //SEARCHALGORITHMS_REDBLACKTREE_H
