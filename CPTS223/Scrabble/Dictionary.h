#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <map>

using std::vector;
using std::string;
using std::pair;
using std::map;

enum Status
{
    EMPTY = 0,
    FILLED = 1,
    DELETED = 2
};

class Dictionary 
{
    private:
     //   vector<pair<Status, string>> table; // A HASH TABLE OF ALL THE VALID WORDS
        vector<pair<Status, map<string, string>>> table;
        int numItems;

        int hash(string);
        int findNextPrime(int);
        bool isPrime(int);
        float load_factor();
        void readWords();

    public:
        Dictionary();
        Dictionary(int);

        void insert(string);
        void emplace(pair<string, string>);
        void rehash();
        bool isWord(string);
        map<string, string> at(int);
        

        vector<pair<Status, map<string, string>>> getTable() { return table; };
};





#endif