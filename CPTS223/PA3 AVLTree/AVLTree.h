#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include "AVLNode.h"

template <class T>

class AVLTree 
{
    private:
    AVLNode<T>* root;

    public:
    AVLTree() 
    {
        root = nullptr;
    }

    ~AVLTree() {}

    bool isEmpty()
    {
        return root == nullptr;
    }

    int height(AVLNode<T>* n, AVLNode<T>* base)
    {
        if(n == nullptr)
        {
            return -1;
        }
        AVLNode<T>* t = new AVLNode<T>;
        t = base;

        for(int i = 0; t != nullptr; ++i)
        {
            if(n == t)
            {
                return i;
            }
            if(*n > *t)
            {
                t = t->left();
            }
            else if(*n < *t)
            {
                t = t->right();
            }
        }

        return -2;
    }

    int insert(AVLNode<T>* n)
    {
        if(isEmpty())
        {
            root = n;
            return 0;
        }
        insertHelper(n, root);
        return 1;
    }

    /*
    bool rotate(AVLNode<T>* n, int direction)
    {
        if(direction == 0)
        {
            if(n->left()->left()->left() != nullptr && n->left()->right() == nullptr)
            {
                AVLNode<T>* t = new AVLNode<T>;
                t = n->left()->left();
                n->left()->setLeft(nullptr);
                n->left()->setRight(nullptr);
                t->setRight(n->left());
                n->setLeft(t);
                return true;
            }

            if(n->left()->left()->right() != nullptr && n->left()->right() == nullptr)
            {
                AVLNode<T>* m = new AVLNode<T>;
                m = n->left()->left();
                n->left()->setLeft(m->right());
                m->setRight(nullptr);
                m->setLeft(m);

                AVLNode<T>* t = new AVLNode<T>;
                t = n->left()->left();
                n->left()->setRight(nullptr);
                n->left()->setLeft(nullptr);
                t->setRight(n->left());
                n->setLeft(t);
                return true;
            }

            if(n->left()->right()->right() != nullptr && n->left()->left() == nullptr)
            {
                AVLNode<T>* t = new AVLNode<T>;
                t = n->left()->right();
                n->left()->setLeft(nullptr);
                n->left()->setRight(nullptr);
                t->setLeft(n->left());
                n->setLeft(t);
                return true;
            }

            if(n->left()->right()->left() != nullptr && n->left()->left() == nullptr)
            {
                AVLNode<T>* m = new AVLNode<T>;
                m = n->left()->right();
                n->left()->setRight(m->left());
                m->setLeft(nullptr);
                m->setRight(m);

                AVLNode<T>* t = new AVLNode<T>;
                t = n->left()->right();
                n->left()->setRight(nullptr);
                n->left()->setLeft(nullptr);
                t->setLeft(n->left());
                n->setLeft(t);
                return true;
            }
        }

        if(direction == 1)
        {
            if(n->right()->left()->left() != nullptr && n->right()->right() == nullptr)
            {
                AVLNode<T>* t = new AVLNode<T>;
                t = n->right()->left();
                n->right()->setLeft(nullptr);
                n->right()->setRight(nullptr);
                t->setRight(n->right());
                n->setRight(t);
                return true;
            }

            if(n->right()->left()->right() != nullptr && n->right()->right() == nullptr)
            {
                AVLNode<T>* m = new AVLNode<T>;
                m = n->right()->left();
                n->right()->setLeft(m->right());
                m->setRight(nullptr);
                m->setLeft(m);

                AVLNode<T>* t = new AVLNode<T>;
                t = n->right()->left();
                n->right()->setRight(nullptr);
                n->right()->setLeft(nullptr);
                t->setRight(n->right());
                n->setRight(t);
                return true;
            }

            if(n->right()->right()->right() != nullptr && n->right()->left() == nullptr)
            {
                AVLNode<T>* t = new AVLNode<T>;
                t = n->right()->right();
                n->right()->setLeft(nullptr);
                n->right()->setRight(nullptr);
                t->setLeft(n->right());
                n->setRight(t);
                return true;
            }

            if(n->right()->right()->left() != nullptr && n->right()->left() == nullptr)
            {
                AVLNode<T>* m = new AVLNode<T>;
                m = n->right()->right();
                n->right()->setRight(m->left());
                m->setLeft(nullptr);
                m->setRight(m);

                AVLNode<T>* t = new AVLNode<T>;
                t = n->right()->right();
                n->right()->setRight(nullptr);
                n->right()->setLeft(nullptr);
                t->setLeft(n->right());
                n->setRight(t);
                return true;
            }
        }
        return false;
    } */

    bool rotate(AVLNode<T>* n)
    {
        AVLNode<T>* t = new AVLNode<T>(root);

        for(int i = 0; t != nullptr; ++i)
        {
            if(t->left() == n)
            {
                if(n->right() == nullptr)
                {
                    if(n->left()->left() == nullptr)
                    {
                        AVLNode<T>* m = new AVLNode<T>(t->left()->left());
                        t->left()->setLeft(m->right());
                        m->right()->setLeft(m);
                        m->setLeft(nullptr);
                    }

                    AVLNode<T>* o = new AVLNode<T>(t->left()->left());
                    n->setLeft(nullptr);
                    o->setRight(n);
                    t->setLeft(o);
                    return true;
                }

                if(n->left() == nullptr)
                {
                    if(n->right()->right() == nullptr)
                    {
                        AVLNode<T>* m = new AVLNode<T>(t->left()->right());
                        t->left()->setRight(m->left());
                        m->left()->setRight(m);
                        m->setLeft(nullptr);
                    }

                    AVLNode<T>* o = new AVLNode<T>(t->left()->right());
                    n->setRight(nullptr);
                    o->setLeft(n);
                    t->setRight(o);
                    return true;
                }   
                break;
            }

            if(t->right() == n)
            {
                if(n->right() == nullptr)
                {
                    if(n->left()->left() == nullptr)
                    {
                        AVLNode<T>* m = new AVLNode<T>(t->right()->left());
                        t->right()->setLeft(m->right());
                        m->right()->setLeft(m);
                        m->setLeft(nullptr);
                    }

                    AVLNode<T>* o = new AVLNode<T>(t->right()->left());
                    n->setLeft(nullptr);
                    o->setRight(n);
                    t->setRight(o);
                    return true;
                }

                if(n->left() == nullptr)
                {
                    if(n->right()->right() == nullptr)
                    {
                        AVLNode<T>* m = new AVLNode<T>(t->right()->right());
                        t->right()->setRight(m->left());
                        m->left()->setRight(m);
                        m->setLeft(nullptr);
                    }

                    AVLNode<T>* o = new AVLNode<T>(t->right()->right());
                    n->setRight(nullptr);
                    o->setLeft(n);
                    t->setRight(o);
                    return true;
                }   
                break;
            }

            if(*n > *t)
            {
                t = t->left();
            }

            if(*n < *t)
            {
                t = t->right();
            }
            return false;
        }
    }

    int insertHelper(AVLNode<T>* n, AVLNode<T>* current)
    {
        if(n < current)
        {
            if(current->left() == nullptr)
            {
                current->setLeft(n);
                rotationCheck(root);
                return 1;
            }
            insertHelper(n, current->left());
        }

        if (n > current)
        {
            if(current->right() == nullptr)
            {
                current->setRight(n);
                rotationCheck(root);
                return 1;
            }
            insertHelper(n, current->right());
        }
        return 0;
    }

    void printInOrder()
    {
        if(!isEmpty())
        {
            printInOrderHelper(root);
        }
        return;
    }

    void printInOrderHelper(AVLNode<T>* current)
    {
        if(current == nullptr)
        {
            return;
        }

        if(current->left() == nullptr && current->right() == nullptr)
        {
            std::cout << *current->data() << std::endl;
            return;
        }

        printInOrderHelper(current->left());
        std::cout << *current->data() << std::endl;
        printInOrderHelper(current->right());
        return;
    }

    void printPreOrder()
    {
        if(!isEmpty())
        {
            printPreOrderHelper(root);
        }
        return;
    }

    void printPreOrderHelper(AVLNode<T>* current)
    {
        if(current == nullptr)
        {
            return;
        }

        if(current->left() == nullptr && current->right() == nullptr)
        {
            std::cout << *current->data() << std::endl;
            return;
        }

        std::cout << *current->data() << std::endl;
        printPreOrderHelper(current->left());
        printPreOrderHelper(current->right());
        return;
    }

    AVLNode<T>* rotationCheck(AVLNode<T>* n)
    {
        if(n == nullptr)
        {
            return nullptr;
        }

        if(n->left() == nullptr && n->right() == nullptr)
        {
            return n;
        }
    
        AVLNode<T>* t = new AVLNode<T>;
        t = rotationCheck(n->left());
        if(t == nullptr)
        {
            t = rotationCheck(n->right());
            if(t == nullptr)
            {
                return nullptr;
            }
            if(height(t,n) > 2)
            {
            return t;
            }

            if(height(t, n) == 2 && n->left() == nullptr)
            {
            return t;
            }
            return nullptr;
        }

        if(height(t,n) > 2)
        {
            return t;
        }

        if(height(t, n) == 2 && n->right() == nullptr)
        {
            return t;
        }
        return nullptr;
    }

    AVLNode<T>* findMin()
    {
        if(isEmpty())
        {
            return nullptr;
        }
        AVLNode<T>* t = new AVLNode<T>(root);

        while(t->left() != nullptr && t->right() != nullptr)
        {
            t = t->left();
        }
        return t;
    }

    AVLNode<T>* findMax()
    {
        if(isEmpty())
        {
            return nullptr;
        }
        AVLNode<T>* t = new AVLNode<T>(root);

        while(t->left() != nullptr && t->right() != nullptr)
        {
            t = t->right();
        }
        return t;
    }



};


#endif