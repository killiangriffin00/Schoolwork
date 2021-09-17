/*
	NAME: Killian Griffin
    DATE: 11/9/20
    ASSIGNMENT: MA4
    DESCRIPTION: We are designing functions for a BankData class used with an unordered map data structure.

	1. The worst case Big-O is O(n), because a bad hash function will put all the values in one node, making what is more like a linked list, which has insertion
	   complexity O(n).
	
	2. Assuming that we, once again, have a bad hash function that tries to insert all values into one node, the search algorythm will have to iterate through all 
	   the values inserted, thus making the search complexity O(n)

	3. Assuming all values are inserted into one node, we will have a deletion complexity of O(n) due to the function having to iterate through n values.

	4. Assuming all values are inserted into one node, iteration will have a complexity of O(n) due to it being nessisary to iterate through the list-like node

	5. Unordered maps should be used for their low average search complexity, O(n), for sets of data that do not require any specific ordering.

	6. unordered_map is a robust choice for storing, removing, and searching, because the data for these accounts can be found in constant time and the data does
	   not need to be in any specific order.

*/


#include <unordered_map>
#include "BankData.hpp"
#include <fstream>

void readFile(std::ifstream *infile, std::unordered_map<int, BankData>* m);
void printMap(std::unordered_map<int, BankData> m);

int main(int argc, char* argv[])
{
	// we need a unordered map to store our key and mapped values
	// std::unordered_map<keyType, ValueType>; What should the key be? What about the value?

	std::unordered_map<int, BankData> m;
	std::ifstream infile("BankAccounts.csv");

	readFile(&infile, &m);

	printMap(m);

	m.erase(11111111);

	printMap(m);
	
	return 0;
}

void printMap(std::unordered_map<int, BankData> m)
{
	for(std::unordered_map<int, BankData>::iterator i = m.begin(); i != m.end(); ++i)
	{
		std::cout << "Account number: " << i->second.getAcctNum() << " Savings: $" << i->second.getSavingsAmount() << " Checking: $"
		<< i->second.getCheckingAmount() << " Bucket Number: " << m.bucket(i->second.getAcctNum()) << std::endl;
	}
	std::cout << std::endl << "Number of buckets: " << m.bucket_count() << std::endl << "Maximum elements: " << m.max_size() << std::endl << std::endl;
}

void readFile(std::ifstream *infile, std::unordered_map<int, BankData>* m)
{
	int aNum = 0;
	double savings = 0, checking = 0;

	infile->ignore(100, '\n');

	while(!infile->eof())
	{
		*infile >> aNum;
		infile->ignore(1, ',');
		*infile >> savings;
		infile->ignore(1, ',');
		*infile >> checking;
		BankData newValue(aNum, savings, checking);
		std::pair<int, BankData> newData(newValue.getAcctNum(), newValue);
		m->insert(newData);
	}
}