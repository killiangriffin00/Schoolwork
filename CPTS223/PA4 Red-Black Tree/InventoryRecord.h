#ifndef INVENTORYRECORD_H
#define INVENTORYRECORD_H

#include <iostream>
#include <string>

class InventoryRecord 
{
    private: 
    int id;
    std::string type;
    int number;

    public:
    InventoryRecord() {} 

    InventoryRecord(int iid, std::string itype, int inumber);

    ~InventoryRecord() {}

    bool operator==(const InventoryRecord& a);

    bool operator<(const InventoryRecord& b);

    bool operator>(const InventoryRecord& b);
    
    bool operator>=(const InventoryRecord& b);

    friend std::ostream& operator<<(std::ostream& output, const InventoryRecord& n);
};

#endif