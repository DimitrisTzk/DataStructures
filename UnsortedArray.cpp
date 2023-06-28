#include "UnsortedArray.h"

//Constructor
UnsortedArray::UnsortedArray(const string& txt, int limit) : DataStructure(limit)
{
    cout << endl << "    UnsortedArray" << endl;
    PairsArray = new Pairs[MaxSize];

    makeStructure(txt);

    cout << "AllPairs: " << UniquePairs << " MaxSize: " << MaxSize << endl;
}

//Destructor
UnsortedArray::~UnsortedArray()
{
    delete[] PairsArray;
}

//Function that adds the pairs to the array and requests more space when it's filled
void UnsortedArray::addPair(const string& word1, const string& word2)
{
    if (UniquePairs >= MaxSize)
    {
        resizeArray();
    }

//    //Check if the pair is already in the array, if so, increase the count, if not, add it to the array
//    for (int i = 0; i < UniquePairs; ++i)
//    {
//        if (PairsArray[i].wordPair == make_pair(word1, word2))
//        {
//            ++PairsArray[i].count;
//            return;
//        }
//    }

    PairsArray[UniquePairs].wordPair.first = word1;
    PairsArray[UniquePairs].wordPair.second = word2;
    //++PairsArray[UniquePairs].count;
    ++UniquePairs;
}

//Function to allocate more memory to the array by doubling the memory
void UnsortedArray::resizeArray()
{
    int newMaxSize = MaxSize * 2;
    Pairs* newPairs = new Pairs[newMaxSize];

    for (int i = 0; i < UniquePairs; ++i)
        newPairs[i] = PairsArray[i];

    delete[] PairsArray;                                                                                                //Delete the old array to save space

    MaxSize = newMaxSize;
    PairsArray = newPairs;
}

//Function that finds the pairs of the q array inside the PairsArray, counts them and writes them to the file
void UnsortedArray::findPairs(pair<string, string>* q, int size, const string &file)
{
    ofstream outFile(file, ios::app);
    if (!outFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    int count;

    for (int i = 0; i < size; ++i)
    {
        count = 0;
        for (int j = 0; j < UniquePairs; ++j)
        {
            if (q[i] == PairsArray[j].wordPair)
                count++;
        }
        outFile << q[i].first << " " << q[i].second << " " << count << endl;
    }
    outFile.close();
}
