#include "SortedArray.h"

//Construct array with initial size of InitialSize pairs
SortedArray::SortedArray(const string &txt, int limit, int initialSize) : DataStructure(limit, initialSize)
{
    cout << endl << "    SortedArray" << endl;

    PairsArray = new Pairs[MaxSize];

    makeStructure(txt);

    cout << "UniquePairs: " << UniquePairs << " MaxSize: " << MaxSize << endl;
}

//Destructor
SortedArray::~SortedArray()
{
    delete[] PairsArray;
}

//Function to allocate more memory to the array by doubling the memory
void SortedArray::resizeArray()
{
    int newMaxSize = MaxSize * 2;
    Pairs* newPairs = new Pairs[newMaxSize];

    for (int i = 0; i < UniquePairs; ++i)
    {
        newPairs[i] = PairsArray[i];
    }

    delete[] PairsArray;                                                                                                //Delete the old array to save space

    MaxSize = newMaxSize;
    PairsArray = newPairs;
}

//Function that adds the pairs to the array, counts the number of appearances of each pair, and requests more space when it's filled
void SortedArray::addPair(const string& word1, const string& word2)
{
    if (UniquePairs >= MaxSize)
    {
        resizeArray();
    }

    for (int i = 0; i < UniquePairs; ++i)                                                                               //Use binary search to check if the pair is already in the array
    {
        int temp = binarySearch(word1, word2);
        if (temp != -1)
        {
            ++PairsArray[temp].count;
            return;
        }
    }

    PairsArray[UniquePairs].wordPair.first = word1;
    PairsArray[UniquePairs].wordPair.second = word2;
    ++PairsArray[UniquePairs].count;
    ++UniquePairs;
    sortLastPair();
}

//Function that finds the correct position for the last pair added and moves pairs to the right to make space
void SortedArray::sortLastPair()
{
    int i = UniquePairs - 1;                                                                                            //Index of the last pair added to the array
    Pairs temp;

    while (i > 0 && PairsArray[i].wordPair.first < PairsArray[i - 1].wordPair.first)                                    //Find the correct position for the 1st word
    {
        temp = PairsArray[i];
        PairsArray[i] = PairsArray[i - 1];
        PairsArray[i - 1] = temp;
        --i;
    }
    while (i > 0 && PairsArray[i].wordPair.first == PairsArray[i - 1].wordPair.first && PairsArray[i].wordPair.second   //Find the correct position including the 2nd word
            < PairsArray[i - 1].wordPair.second)
    {
        temp = PairsArray[i];
        PairsArray[i] = PairsArray[i - 1];
        PairsArray[i - 1] = temp;
        --i;
    }
}

//Function to find the pairs in the array using binary search and write them to the output file
void SortedArray::findPairs(pair<string, string> *q, int size, ofstream &outFile)
{
    for (int i = 0; i < size; ++i)
    {
        int temp = binarySearch(q[i].first, q[i].second);
        if (temp != -1)
        {
            outFile << PairsArray[temp].wordPair.first << " " << PairsArray[temp].wordPair.second << " "
                   << PairsArray[temp].count << endl;
        }
        else
        {
            outFile << q[i].first << " " << q[i].second << " NOTFOUND" << endl;
        }
    }
}

//Binary search function used to find pairs in the array
int SortedArray::binarySearch(const string &word1, const string &word2)
{
    int left = 0;
    int right = UniquePairs - 1;
    int mid;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if (word1 < PairsArray[mid].wordPair.first)
            right = mid - 1;
        else if (word1 > PairsArray[mid].wordPair.first)
            left = mid + 1;
        else
        {
            if (word2 < PairsArray[mid].wordPair.second)
                right = mid - 1;
            else if (word2 > PairsArray[mid].wordPair.second)
                left = mid + 1;
            else
                return mid;
        }
    }
    return -1;                                                                                                          //If the pair is not in the array, return -1
}
