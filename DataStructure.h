#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#define InitialSize 1000000

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
        DataStructure(int limit);
        ~DataStructure();
        void makeStructure(const string& filename);
        virtual void addPair(const string& word1, const string& word2) {};
        virtual void findPairs(pair<string, string> *q, int size, const string &file) = 0;
};


#endif //DATASTRUCTURE_H
