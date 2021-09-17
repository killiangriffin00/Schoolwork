#ifndef AVLNODE_H
#define AVLNODE_H

#include <iostream>

template <class T>

class AVLNode
{
    private:
    T* Data;
    AVLNode* Left;
    AVLNode* Right;

    public:

    AVLNode()
    {
        Left = nullptr;
        Right = nullptr;
    }

    AVLNode(AVLNode* n) 
    {
        Data = n->data();
        Left = n->left();
        Right = n->right();
    }

    AVLNode(T* d)
    {
        Data = d;
        Left = nullptr;
        Right = nullptr;
    }

    ~AVLNode() {}

    T* data()
    {
        return Data;
    }

    AVLNode* left()
    {
        return Left;
    }

    AVLNode* right()
    {
        return Right;
    }

    void setLeft(AVLNode* n)
    {
        Left = n;
    }

    void setRight(AVLNode* n)
    {
        Right = n;
    }

    /*friend void operator=(AVLNode& rightNode)
    {
        data = rightNode.data;
        left = rightNode.left;
        right = rightNode.right;
    }*/

    friend bool operator==(AVLNode& leftNode, AVLNode& rightNode)
    {
        return leftNode.data() == rightNode.data();
    }

    friend bool operator<(AVLNode& leftNode, AVLNode& rightNode)
    {
        return leftNode.data() < rightNode.data();
    }    

    friend bool operator>(AVLNode& leftNode, AVLNode& rightNode)
    {
        return leftNode.data() > rightNode.data();
    }    
};

#endif