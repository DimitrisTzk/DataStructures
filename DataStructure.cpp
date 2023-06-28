#include "DataStructure.h"

DataStructure::DataStructure(int limit) {
    pairLimit = limit;
    UniquePairs = 0;
    MaxSize = InitialSize;
}

DataStructure::~DataStructure() = default;

void DataStructure::makeStructure(const string& filename) {
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    string word1, word2;

    // Read the first word
    if (file >> word1)
    {
        // Read the second word
        while (file >> word2)
        {
            //Stop reading the file when it reaches PairLimit pairs
            if (UniquePairs == pairLimit)
                return;

            addPair(word1, word2);

            // Swap word2 to word1 for the next iteration
            word1 = word2;
        }
    }
}