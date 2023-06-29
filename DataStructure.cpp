#include "DataStructure.h"

//Constructor
DataStructure::DataStructure(int limit, int initialSize)
{
    pairLimit = limit;
    UniquePairs = 0;
    MaxSize = initialSize;
}

//Default destructor
DataStructure::~DataStructure() = default;

//Function that reads the words from the file and creates the data structure
void DataStructure::makeStructure(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())                                                                                                //Check if the file opened correctly
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    string word1, word2;

    if (file >> word1)
    {
        while (file >> word2)
        {
            if (UniquePairs == pairLimit)                                                                               //Stop after reaching the set limit
                return;

            addPair(word1, word2);

            word1 = word2;                                                                                              // Swap word2 to word1 for the next iteration
        }
    }
}