#include "HashTable.h"

// Constructor
HashTable::HashTable(const string& txt, int limit) : DataStructure(limit)
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
    // Check if the table needs to be resized
    if (UniquePairs >= MaxSize * LoadFactor)
        resizeTable();

    int index = hash(word1 + word2);

    if (Table[index] != nullptr && Table[index]->wordPair == make_pair(word1, word2))
    {
        Table[index]->count++;
        return;
    }

    // Find the next available slot using double hashing
    int probeCount = 0;
    int probeIndex = index;
    while (Table[probeIndex] != nullptr && Table[probeIndex]->wordPair != make_pair(word1, word2))
    {
        probeCount++;
        probeIndex = abs(index + probeCount * hash2(word1 + word2)) % MaxSize;
    }

    // If a slot is found, add the pair or increment the count if the pair already exists
    if (Table[probeIndex] == nullptr)
    {
        Table[probeIndex] = new Pairs;
        Table[probeIndex]->wordPair = make_pair(word1, word2);
        Table[probeIndex]->count = 1;
        UniquePairs++;
        Collisions += probeCount;
    } else if (Table[probeIndex]->wordPair == make_pair(word1, word2))
    {
        Table[probeIndex]->count++;
    }
}

// Function that resizes the table when the load factor is reached by doubling the size of the table and finding the
// next prime number as the new size
void HashTable::resizeTable()
{
    int oldSize = MaxSize;
    MaxSize = MaxSize * 2;
    Pairs** newTable = new Pairs*[MaxSize];

    for (int i = 0; i < MaxSize; i++)
        newTable[i] = nullptr;

    // Rehash the pairs into the new table
    for (int i = 0; i < oldSize; i++)
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
void HashTable::findPairs(pair<string, string> *q, int size, const string &file)
{
    ofstream outfile(file, ios::app);

    for (int i = 0; i < size; i++)
    {
        int index = hash(q[i].first + q[i].second);
        int probeCount = 0;
        int probeIndex = index;

        while (Table[probeIndex] != nullptr && probeCount < MaxSize)
        {
            if (Table[probeIndex]->wordPair.first == q[i].first && Table[probeIndex]->wordPair.second == q[i].second)
            {
                outfile << Table[probeIndex]->wordPair.first << " " << Table[probeIndex]->wordPair.second << " "
                        << Table[probeIndex]->count << endl;
                break;
            }
            probeIndex = (probeIndex + 1) % MaxSize;
            probeCount++;
        }
    }
    outfile.close();
}
