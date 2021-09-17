#include "InventoryRecord.h"

InventoryRecord::InventoryRecord(int iid, std::string itype, int inumber)
{
    id = iid;
    type = itype;
    number = inumber;
}

bool InventoryRecord::operator<(const InventoryRecord& b)
{
    return this->id < b.id;
}

bool InventoryRecord::operator>(const InventoryRecord& b)
{
    return this->id > b.id;
}

bool InventoryRecord::operator>=(const InventoryRecord& b)
{
    return this->id > b.id;
}

std::ostream& operator<<(std::ostream &output, const InventoryRecord &n)
{
    output << n.id << ": " << n.type << ". Quantity: " << n.number;
    return output;
}

bool InventoryRecord::operator==(const InventoryRecord& a)
{
    return a.id == this->id && a.type == this->type && a.number == this->number;
}
