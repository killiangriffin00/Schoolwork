/*
    NAME: Killian Griffin
    DATE: 10/9/20
    ASSIGNMENT: MA3
    DESCRIPTION: We are designing functions for a TwitterData class used with a map data structure.

    1. I used actual name for the key, because the actual names of everyone are unique for the most part, and can be sorted alphabetically.

    2. O(nlog2(n)), where n is the ammount of elements inserted.

    3. O(log2(n)), where n is the ammount of elements in the tree.

    4. O(log2(n)), where n is the ammount of elements in the tree.

    5. O(1) for the iterator-argument erase, and O(log2(n)) for key-argument erase.

    6. Maps should be used when we have a type of data that we want to search for that is unique.

    7. Maps are not optimal to use for category data, because multiple people will be interested in the same category. Instead, using a linked list of map structures
       categorized by the category data value, and using nmaes for the individual maps might be more optimal for searching based on category.
*/

#include <map>
#include "twitterData.h"
#include <fstream> // included for reading the .csv file

void readFile(std::ifstream* infile, std::map<std::string, TwitterData>* m);

int main(int argc, char* argv[])
{
	// we need a map to store our key-value pairs
	// std::map<keyType, ValueType>; What should the key be? What about the value?
    std::map<std::string, TwitterData> m;
    std::ifstream infile("TwitterAccounts.csv");
    readFile(&infile, &m);

    for(std::map<std::string, TwitterData>::iterator i = m.begin(); i != m.end(); ++i)
    {
        if(i->second.getUserName() == "savage1")
        {
            m.erase(i);
            break;
        }
    }

    m.erase("RickSmith");

    for(std::map<std::string, TwitterData>::iterator i = m.begin(); i != m.end() ; ++i)
    {
        std::cout << i->first << ", " << i->second.getUserName() << std::endl;
    }

	return 0;
}

void readFile(std::ifstream* infile, std::map<std::string, TwitterData>* m)
{
    std::string junk, newString, name;
    int newInt;
    getline(*infile, junk, '\n');
    while(!infile->eof())
    {
        TwitterData* newData = new TwitterData();
        
        getline(*infile, newString, ',');
        newData->setUserName(newString);

        getline(*infile, newString, ',');
        newString.erase(0, 1);

        getline(*infile, name, ',');
        name.append(newString);
        newData->setActualName(name);

        getline(*infile, newString, ',');
        newData->setEmail(newString);

        *infile >> newInt;
        newData->setNumTweets(newInt);

        getline(*infile, newString);
        newData->setCategory(newString);

        m->insert(std::pair<std::string, TwitterData>(newData->getActualName(), *newData));
    }
}