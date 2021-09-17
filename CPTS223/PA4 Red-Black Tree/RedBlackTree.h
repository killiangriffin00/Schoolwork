#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include "RedBlackNode.h"

template <class T>

class RedBlackTree 
{
    private: 
    RedBlackNode<T>* root;

    public:
    RedBlackTree() { root = nullptr; }

    ~RedBlackTree() {}

    bool isEmpty() { return root == nullptr; }

    color getColor(RedBlackNode<T>* n)
    {
        if(n != nullptr)
        {
            return n->getColor();
        }
        return BLACK;
    }

    RedBlackNode<T>* search(T* d)
    {
        RedBlackNode<T>* current = new RedBlackNode<T>(root);

        while(current->getLeft() != nullptr || current->getRight() != nullptr)
        {
            if(current->getData() > *d)
            {
                current = current->getLeft();
            }

            else if(current->getData() < *d)
            {
                current = current->getRight();
            }

            else
            return current;
        }

        return nullptr;
    }

    void insert(RedBlackNode<T>* newNode)
    {
        if(isEmpty())
        {
            root = newNode;
            root->setColor(BLACK);
            return;
        }
        int end = 0;

        RedBlackNode<T>* current = new RedBlackNode<T>();

        current = root;

        while(end == 0)
        {
            if(current->getData() >= newNode->getData())
            {
                if(current->getLeft() == nullptr)
                {
                    newNode->setParent(current);
                    current->setLeft(newNode);
                    end = 1;
                }
                else
                current = current->getLeft();
                
            }

            else if(current->getData() < newNode->getData())
            {
                if(current->getRight() == nullptr)
                {
                    newNode->setParent(current);
                    current->setRight(newNode);
                    end = 1;
                }
                else
                current = current->getRight();
            }
        }
        balance(newNode);

        return;
    }

    RedBlackNode<T>* leftRotate(RedBlackNode<T>* n)
    {
        RedBlackNode<T>* r = new RedBlackNode<T>(n);
        RedBlackNode<T>* t = new RedBlackNode<T>(r->getRight());
        r->setRight(nullptr);
        t->setLeft(r);
        t->setParent(r->getParent());
        r->setParent(t);
        return t;
    }

    RedBlackNode<T>* rightRotate(RedBlackNode<T>* n)
    {
        RedBlackNode<T>* r = new RedBlackNode<T>(n);
        RedBlackNode<T>* t = new RedBlackNode<T>(r->getLeft());
        r->setLeft(nullptr);
        t->setRight(r);
        t->setParent(r->getParent());
        r->setParent(t);
        return t;
    }

    void balance(RedBlackNode<T>* n)
    {
        RedBlackNode<T>* current = new RedBlackNode<T>(n);
        RedBlackNode<T>* grand = new RedBlackNode<T>;
        RedBlackNode<T>* uncle = new RedBlackNode<T>;
        
        while(current->getParent()->getParent() != nullptr)
        {
            if(getColor(current->getParent()) == RED)
            {
                grand = current->getParent()->getParent();
                if(grand->getLeft() == current)
                {
                    uncle = grand->getRight();
                }
                else
                uncle = grand->getLeft();

                if(getColor(uncle) == RED)
                {
                    grand->recolor();
                    uncle->recolor();
                    current->getParent()->recolor();
                }

                else if(getColor(uncle) == BLACK)
                {
                    if(uncle == grand->getLeft())
                    {
                        if(current == grand->getRight()->getLeft())
                        {
                            rightRotate(current->getParent());
                        }

                        else if(current == grand->getRight()->getRight())
                        {
                            leftRotate(grand);
                            current->getParent()->recolor();
                            grand->recolor();
                        }   
                    }

                    else if(uncle == grand->getRight())
                    {
                        if(current == grand->getLeft()->getRight())
                        {
                            leftRotate(current->getParent());
                        }

                        else if(current == grand->getLeft()->getLeft())
                        {
                            rightRotate(grand);
                            current->getParent()->recolor();
                            grand->recolor();
                        }  
                    }
                }
            }
            current = current->getParent();
        }
        return;
    }

    RedBlackNode<T>* remove(T rmData)
    {
        return nullptr;
    }

    void clear()
    {
        if(isEmpty())
        {
            return;
        }
        clearHelper(root);
    }

    void clearHelper(RedBlackNode<T>* n)
    {
        if(n == nullptr)
        {
            return;
        }

        if(n->getLeft() == nullptr && n->getRight() == nullptr)
        {
            delete n;
            return;
        }

        clearHelper(n->getLeft());
        clearHelper(n->getRight());
        delete n;
        return;
    }

    void printInOrder()
    {
        if(isEmpty())
        {
            return;
        }

        printInOrderHelper(root);
        return;
    }

    void printInOrderHelper(RedBlackNode<T>* current)
    {
        if(current == nullptr)
        {
            return;
        }

        if(current->getLeft() == nullptr && current->getRight() == nullptr)
        {
            std::cout << current->getData() << std::endl;
            return;
        }
        
        printInOrderHelper(current->getLeft());
        std::cout << current->getData() << std::endl;
        printInOrderHelper(current->getRight());
        return;
    }
};

#endif