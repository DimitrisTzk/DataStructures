#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H

#include "DataStructure.h"

using namespace std;


class SortedArray : public DataStructure{
    private:
        Pairs* PairsArray;
    public:
        SortedArray(const string& txt, int limit);
        ~SortedArray();
        void resizeArray();
        void addPair(const string& word1, const string& word2) override;
        void findPairs(pair<string, string> *q, int size, const string &file) override;
        void sortArray();
        int binarySearch(const string &word1, const string &word2);
};

#endif //SORTEDARRAY_H
