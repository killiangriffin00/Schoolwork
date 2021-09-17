#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H

#include <iostream>

enum color {RED, BLACK, DOUBLEBLACK};

template <class T>

class RedBlackNode
{
    private:
    T data;
    RedBlackNode<T>* left;
    RedBlackNode<T>* right;
    RedBlackNode<T>* parent;
    color rb;

    public:
    RedBlackNode() 
    { 
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        rb = RED;
    }
    
    ~RedBlackNode() {}

    RedBlackNode(RedBlackNode* copy)
    {
        data = copy->getData();
        left = copy->getLeft();
        right = copy->getRight();
        parent = copy->getParent();
        rb = copy->getColor();
    }

    RedBlackNode(T* d)
    {
        data = *d;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        rb = RED;
    }

    T getData() { return data; }

    RedBlackNode* getRight() { return right; }

    RedBlackNode* getLeft() { return left; }

    RedBlackNode* getParent() { return parent; }

    color getColor() { return rb; }

    void setData(T nData) { data = nData; }

    void setLeft(RedBlackNode* nLeft) { left = nLeft; }

    void setRight(RedBlackNode* nRight) { right = nRight; }

    void setParent(RedBlackNode* nParent) { parent = nParent; }

    void setColor(color c) { rb = c; }

    void recolor() 
    {
        if(rb == RED)
        { rb = BLACK; }
        else 
        rb = RED;
    }

    friend bool operator==(RedBlackNode& leftNode, RedBlackNode& rightNode) { return leftNode.getData() == rightNode.getData(); }

    friend bool operator<(RedBlackNode& leftNode, RedBlackNode& rightNode) { return leftNode.getData() < rightNode.getData(); }    

    friend bool operator>(RedBlackNode& leftNode, RedBlackNode& rightNode) { return leftNode.getData() > rightNode.getData(); }   
};





#endif