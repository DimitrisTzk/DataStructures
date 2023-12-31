#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "DataStructure.h"

#define LoadFactor 0.75                                                                                                 // The load factor of the table that triggers the resize

using namespace std;


class HashTable : public DataStructure{
    private:
        Pairs **Table;
        int Collisions;
    public:
        HashTable(const string &txt, int limit, int initialSize);
        ~HashTable();
        void addPair(const std::string &word1, const std::string &word2) override;
        void resizeTable();
        int hash1(const string &word) const;
        int hash2(const string &word) const;
        void findPairs(pair<string, string> *q, int size, ofstream &outFile) override;
};


#endif //HASHTABLE_H
