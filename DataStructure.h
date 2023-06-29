#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;


class DataStructure {
    protected:
        struct Pairs{
            pair<string, string> wordPair;
            int count=0;
        };
        int pairLimit;
        int UniquePairs;
        int MaxSize;
    public:
        DataStructure(int limit, int initialSize);
        ~DataStructure();
        void makeStructure(const string& filename);
        virtual void addPair(const string& word1, const string& word2) {};                                              //Virtual functions to be overridden by derived classes
        virtual void findPairs(pair<string, string> *q, int size, ofstream &outFile) {};
};


#endif //DATASTRUCTURE_H
