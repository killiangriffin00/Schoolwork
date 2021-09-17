/*
    NAME: Killian Griffin
    DATE: 10/25/20
    ASSIGNMENT: PA4
    DESCRIPTION: We are designing and implementing a Red-Black Tree to organize a set of inventory records.

    1. O(log(n)). Its a bianary tree, so the insertion of each node is logarithmic.

    2. O(log(n)). Similarly to insertion, deletion searches the tree using bianry search, which is logarithmic.

    3. O(nlog(n)). Is similar to deletion, except it needs to be used for each node in the tree.

*/

#include "InventoryRecord.h"
#include "RedBlackTree.h"
#include <fstream>

void readFile(RedBlackTree<InventoryRecord>* t, std::istream* f);

int main()
{
    int option = 0, id = 0, number = 0, id2 = 0, number2 = 0;
    std::string type = "", type2 = "";
    RedBlackTree<InventoryRecord> i;
    std::ifstream infile("Inventory.csv");

    readFile(&i, &infile);
    infile.close();

    while(true)
    {
            std::cout << std::endl << "INVENTORY RECORD" << std::endl << "1. Add an item" << std::endl << "2. Update an item" << std::endl << "3. Print all items" << std::endl
            << "4. Exit" << std::endl;
            std::cout << std::endl << "Choose an option: ";
            std::cin >> option;

        while(option < 1 || option > 4)
        {    
            std::cout << std::endl << "INVENTORY RECORD" << std::endl << "1. Add an item" << std::endl << "2. Update an item" << std::endl << "3. Print all items" << std::endl
            << "4. Exit" << std::endl;
            std::cout << std::endl << "Choose an option: ";
            std::cin >> option;
        }

        switch(option)
        {
            case 1:
            {
            std::cout << std::endl << "Enter ID: ";
            std::cin >> id2;

            std::cout << std::endl << "Enter Item: ";
            std::cin >> type2;

            std::cout << std::endl << "Enter Quantity: "; 
            std::cin >> number2;

            RedBlackNode<InventoryRecord>* newNode = new RedBlackNode<InventoryRecord>(new InventoryRecord(id2, type2, number2));
            i.insert(newNode);
            }
            break;

            case 2:
            {
            std::cout << std::endl << "Enter ID: ";
            std::cin >> id;

            std::cout << std::endl << "Enter Item: ";
            std::cin >> type;

            std::cout << std::endl << "Enter Quantity: "; 
            std::cin >> number;

            RedBlackNode<InventoryRecord>* c = new RedBlackNode<InventoryRecord>;
            InventoryRecord s(id, type, number);
            c = i.search(&s);

            if(c == nullptr)
            {
                std::cout << "Item not found.";
            }
            else
            {
                std::cout << std::endl << "Enter new ID: ";
                std::cin >> id;

                std::cout << std::endl << "Enter new Item: ";
                std::cin >> type;

                std::cout << std::endl << "Enter new Quantity: "; 
                std::cin >> number;

                std::cout << std::endl;
                InventoryRecord n(id, type, number);
                c->setData(n);
            }
            }
            break;

            case 3:
            i.printInOrder();
            std::cout << std::endl;
            break;

            case 4:
            i.clear();
            return 0;
            break;
        }
    }

    /*
    RedBlackNode<InventoryRecord>* n = new RedBlackNode<InventoryRecord>(new InventoryRecord(1111, "Books", 80));
    i.insert(n);

    RedBlackNode<InventoryRecord>* o = new RedBlackNode<InventoryRecord>(new InventoryRecord(123, "Sa", 4));
    i.insert(o);

    RedBlackNode<InventoryRecord>* p = new RedBlackNode<InventoryRecord>(new InventoryRecord(2342, "bo", 7));
    i.insert(p);

    RedBlackNode<InventoryRecord>* q = new RedBlackNode<InventoryRecord>(new InventoryRecord(4342, "oks", 3));
    i.insert(q);

    RedBlackNode<InventoryRecord>* r = new RedBlackNode<InventoryRecord>(new InventoryRecord(112, "ok", 90));
    i.insert(r);

    i.printInOrder();
    */

    //i.insert(new RedBlackNode<InventoryRecord>(new InventoryRecord(1111, "h", 7)));

    return 0;
}

void readFile(RedBlackTree<InventoryRecord>* t, std::istream* f)
{
    int id = 0, number = 0;
    std::string type = "";
    while(!f->eof())
    {
        *f >> id;
        f->ignore(1, ',');
        getline(*f, type, ',');
        *f >> number;
        RedBlackNode<InventoryRecord>* newNode = new RedBlackNode<InventoryRecord>(new InventoryRecord(id, type, number));
        t->insert(newNode);
    }
}