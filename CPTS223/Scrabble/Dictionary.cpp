#include "Dictionary.h"

// ********************* PUBLIC *********************

Dictionary::Dictionary()
{
    table.resize(7001);
    readWords();
}

Dictionary::Dictionary(int n)
{
    table.resize(n);
}

void Dictionary::insert(string s)
{
    // use the first 3 letters to find the hash value, then put whole word into that map
    int hashV = hash(s.substr(0,2));

    table[hashV].first = FILLED;
    table[hashV].second.insert(pair<string, string>(s, s));
    ++numItems;

    if (load_factor() > 0.5)
    {
        rehash();
    }
}

void Dictionary::emplace(pair<string, string> p)
{
    int hashV = hash(p.first.substr(0,2));
    table[hashV].first = FILLED;
    table[hashV].second.insert(p);
    ++numItems;

    if (load_factor() > 0.5)
        rehash();
}

map<string, string> Dictionary::at(int i)
{
    if (i < table.size())
        return table[i].second;
    else 
        throw new std::out_of_range("at - i not in table range");
}

// ********************* PRIVATE *********************

int Dictionary::hash(string k)
{
    int sum = 0;
    for (int i = 0; i < k.length(); ++i)
        sum += (k[i] * (i + 1));
    return sum % table.size();
}

float Dictionary::load_factor()
{
    return numItems / (float)table.size();
}

/*
void Dictionary::rehash()
{
    int tSize = table.size();
    Dictionary* d = new Dictionary(findNextPrime(tSize * 2));

    for (int i = 0; i < tSize; ++i)
    {
        if (table[i].first == FILLED)
        {
            d->insert(table[i].second);
        }
    }
    table = d->getTable();
    delete d;
}
*/

void Dictionary::rehash()
{
    int tSize = table.size();
    Dictionary* d = new Dictionary(findNextPrime(tSize * 2));

    for (int i = 0; i < tSize; ++i)
    {
        if (table[i].first == FILLED)
        {
            while (!table[i].second.empty())
            {
                string s = table[i].second.begin()->second;
                d->insert(s);
                table[i].second.erase(s);
            }
        }
    }
    table = d->getTable();
    delete d;
}


int Dictionary::findNextPrime(int n)
{
    while (!isPrime(n))
        ++n;
    return n;
}

bool Dictionary::isPrime(int n)
{
    for (int i = 2; i < sqrt(n); ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}


void Dictionary::readWords()
{
    std::ifstream infile;
    string word;
    try 
    {
        infile.open("words.txt");
        while (getline(infile, word))
        {
            insert(word);
        }
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "\"words.txt\" does not exist" << std::endl;
    }
}

bool Dictionary::isWord(string s)
{
    int hashV = hash(s.substr(0,2));

    return table[hashV].second.count(s);
}