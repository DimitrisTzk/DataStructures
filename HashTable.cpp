#include "HashTable.h"

// Constructor
HashTable::HashTable(const string &txt, int limit, int initialSize) : DataStructure(limit, initialSize)
{
    cout << endl << "    HashTable" << endl;
    Collisions=0;
    Table = new Pairs*[MaxSize];

    for (int i=0; i < MaxSize; i++)
        Table[i] = nullptr;

    makeStructure(txt);

    cout << "UniquePairs: " << UniquePairs << " MaxSize: " << MaxSize << " Collisions: " << Collisions << endl;
}

// Destructor
HashTable::~HashTable()
{
    for (int i=0; i < MaxSize; i++)
    {
        if (Table[i] != nullptr)
            delete Table[i];
    }
    delete[] Table;
}

// Function that adds a pair to the table
void HashTable::addPair(const string& word1, const string& word2)
{
    if (UniquePairs >= MaxSize * LoadFactor)                                                                            // Check if the load factor is reached
        resizeTable();

    int index = hash(word1 + word2);

    if (Table[index] != nullptr && Table[index]->wordPair == make_pair(word1, word2))                             // Check if the pair already exists
    {
        Table[index]->count++;
        return;
    }

    int probeCount = 0;                                                                                                 //Use double hashing to find an empty slot
    int probeIndex = index;
    while (Table[probeIndex] != nullptr && Table[probeIndex]->wordPair != make_pair(word1, word2))
    {
        probeCount++;
        probeIndex = abs(index + probeCount * hash2(word1 + word2)) % MaxSize;                                 // Use the second hash function to find the next slot. Added abs() to avoid negative numbers
    }

    if (Table[probeIndex] == nullptr)                                                                                   // If the slot is empty, add the pair
    {
        Table[probeIndex] = new Pairs;
        Table[probeIndex]->wordPair = make_pair(word1, word2);
        Table[probeIndex]->count = 1;
        UniquePairs++;
        Collisions += probeCount;
    } else if (Table[probeIndex]->wordPair == make_pair(word1, word2))                                            // If the pair already exists, increase the count
        Table[probeIndex]->count++;
}

// Function that resizes the table when the load factor is reached by doubling the size of the table
void HashTable::resizeTable()
{
    int oldSize = MaxSize;
    MaxSize = MaxSize * 2;
    Pairs** newTable = new Pairs*[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        newTable[i] = nullptr;

    for (int i = 0; i < oldSize; i++)                                                                                   // Rehash the pairs into the new table
    {
        if (Table[i] != nullptr)
        {
            int index = hash(Table[i]->wordPair.first + Table[i]->wordPair.second);
            int probeCount = 0;
            int probeIndex = index;
            while (newTable[probeIndex] != nullptr && probeCount < MaxSize)
            {
                probeIndex = (index + probeCount * hash2(Table[i]->wordPair.first + Table[i]->wordPair.second))
                             % MaxSize;
                probeCount++;
            }

            if (newTable[probeIndex] == nullptr)
            {
                newTable[probeIndex] = new Pairs;
                newTable[probeIndex]->wordPair = Table[i]->wordPair;
                newTable[probeIndex]->count = Table[i]->count;
            }
        }
    }
    for (int i = 0; i < oldSize; i++)
    {
        if (Table[i] != nullptr)
            delete Table[i];
    }
    delete[] Table;
    Table = newTable;
}

// Function that returns the hash value of a word using the djb2 algorithm
int HashTable::hash(const string& word) const
{
    unsigned long hash = 5381;
    for (char i : word)
        hash = ((hash << 5) + hash) + i;
    return hash % MaxSize;
}

// Function that returns the second hash value of a word using the sdbm algorithm
int HashTable::hash2(const string& word) const
{
    unsigned long hash = 0;
    for (char i : word)
        hash = i + (hash << 6) + (hash << 16) - hash;
    return hash % MaxSize;
}

// Function that finds the pairs in the table and appends them to a file
void HashTable::findPairs(pair<string, string> *q, int size, ofstream &outFile)
{
    for (int i = 0; i < size; i++)
    {
        int index = hash(q[i].first + q[i].second);
        int probeCount = 0;
        int probeIndex = index;

        while (Table[probeIndex] != nullptr && Table[probeIndex]->wordPair != q[i])                                     //Use double hashing to find the pair
        {
            probeCount++;
            probeIndex = abs(index + probeCount * hash2(q[i].first + q[i].second)) % MaxSize;
        }

        if (Table[probeIndex] != nullptr && Table[probeIndex]->wordPair == q[i])
            outFile << q[i].first << " " << q[i].second << " " << Table[probeIndex]->count << endl;
        else
            outFile << q[i].first << " " << q[i].second << " NOTFOUND" << endl;
    }
}
