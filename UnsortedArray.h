#ifndef UNSORTEDARRAY_H
#define UNSORTEDARRAY_H

#include "DataStructure.h"

using namespace std;


class UnsortedArray : public DataStructure{
    private:
        Pairs* PairsArray;
    public:
        UnsortedArray(const string& txt, int limit);
        ~UnsortedArray();
        void addPair(const string& word1, const string& word2) override;
        void resizeArray();
        void findPairs(pair<string, string>* q, int size, const string &file) override;
};


#endif //UNSORTEDARRAY_H
