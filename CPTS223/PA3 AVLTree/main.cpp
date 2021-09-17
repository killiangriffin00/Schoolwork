/*
    NAME: Killian Griffin
    DATE: 10/5/20
    ASSIGNMENT: PA3
    DESCRIPTION: We are making an AVL tree and using it to organise cancer data for the top 50 countries.

    1. O(nlogn), where n is the number of nodes in the tree.

    2. O(n), where n is the number of nodes in the tree.

    3. O(n), where n is the height of the tree.
*/
#include "AVLTree.h"
#include "AVLNode.h"
#include "CancerData.h"
#include <fstream>

void readFile(std::istream* infile, AVLTree<CancerData>* t);

int main()
{
    AVLTree<CancerData> both;   
    std::ifstream infile1;
    infile1.open("bothcancerdata2018.csv");
    readFile(&infile1, &both);
    infile1.close();

    AVLTree<CancerData> men;
    std::ifstream infile2;
    infile2.open("mencancerdata2018.csv");
    readFile(&infile2, &men);
    infile2.close();

    AVLTree<CancerData> women;
    std::ifstream infile3;
    infile3.open("womencancerdata2018.csv");
    readFile(&infile3, &women);
    infile3.close();

    std::cout << "Men and Women:" << std::endl;
    both.printInOrder();
    std::cout << std::endl;

    std::cout << "Men:" << std::endl;
    men.printInOrder();
    std::cout << std::endl;

    std::cout << "Women:" << std::endl;
    women.printInOrder();
    std::cout << std::endl;

    std::cout << "Total maximum: " << *both.findMax()->data() << std::endl;
    std::cout << "Men maximum: " << *men.findMax()->data() << std::endl;
    std::cout << "Women maximum: " << *women.findMax()->data() << std::endl << std::endl;

    std::cout << "Total minimum: " << *both.findMin()->data() << std::endl;
    std::cout << "Men minimum: " << *men.findMin()->data() << std::endl;
    std::cout << "Women minimum: " << *women.findMax()->data() << std::endl;


    /*
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .26)));
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .25)));
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .27)));
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .28)));
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .29)));
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .3)));
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .24)));
    t.insert(new AVLNode<CancerData>(new CancerData("Country", .23)));

    t.printPreOrder();

    std::cout << *t.findMax()->data() << std::endl;
    */


    return 0;
}

void readFile(std::istream* infile, AVLTree<CancerData>* t)
{
    float rate;
    std::string country;

    while(!infile->eof())
    {
        getline(*infile, country, ',');
        *infile >> rate;
        t->insert(new AVLNode<CancerData>(new CancerData(country, rate)));
    }
}