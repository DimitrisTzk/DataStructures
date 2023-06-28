//Hash Table class implemented using open addressing and the hash function djb2

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "DataStructure.h"

#define LoadFactor 0.75

using namespace std;


class HashTable : public DataStructure{
    private:
        Pairs **Table;
        int Collisions;
    public:
        HashTable(const string& txt, int limit);
        ~HashTable();
        void addPair(const std::string &word1, const std::string &word2) override;
        void resizeTable();
        int hash(const string& word1) const;
        int hash2(const string &word) const;
        void findPairs(pair<string, string> *q, int size, const string &file) override;
};


#endif //HASHTABLE_H
