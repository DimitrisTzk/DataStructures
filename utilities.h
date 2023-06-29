#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>
#include <utility>

using namespace std;

//File with useful functions for the project that don't belong to any class

//Function that splits a string into a vector of strings based on a delimiter
vector<string> splitString(const string& input, char delimiter)
{
    vector<string> tokens;
    stringstream ss(input);
    string token;

    while (getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

//Function that picks random pairs of words from a vector of strings
void pickRandomPairs(const vector<string>& words, int numPairs, pair<string, string>* q)
{
    int numWords = words.size();

    random_device rd;                                                                                                   //Seed the random number generator
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, numWords - 2);                                                          // Selecting index from 0 to numWords-2

    for (int i = 0; i < numPairs; ++i)
    {
        int index = distrib(gen);
        q[i] = make_pair(words[index], words[index + 1]);
    }
}

//Function that processes the input file and picks random pairs of words from it
bool processFile(const string& file, pair<string, string>* q, int pairLimit, int numPairs)
{
    if (pairLimit != -1 && (pairLimit < numPairs))                                                                                           // Check if the number of pairs requested exceeds the limit
    {
        cerr << "Number of pairs requested exceeds the limit!" << endl;
        return false;
    }

    cout << "Processing file..." << endl;

    ifstream inFile(file);
    ofstream outFile("edited.txt");

    if (!inFile)
    {                                                                                                                   // Check to make sure the files open correctly.
        cerr << "Failed to open input file!" << endl;
        return false;
    }
    if (!outFile)
    {
        cerr << "Failed to create output file!" << endl;
        return false;
    }

    char c;
    char prevChar = '\0';
    string content;
    int wordCount = 0;

    while (inFile.get(c))                                                                                            // Convert to lowercase
    {
        if (pairLimit != -1 && (wordCount == pairLimit + 1))                                                                                 // Stop reading the file if the limit is reached
            break;

        if (isalnum(c))
        {
            outFile << static_cast<char>(tolower(c));
            prevChar = c;
            content += static_cast<char>(tolower(c));
        }
        else                                                                                                            // Replace all other characters with spaces only if the previous character is not a space
        {
            if (!isspace(prevChar))                                                                                  //This ensures that every word is separated by a single space
            {
                outFile << ' ';
                content += ' ';
                ++wordCount;
            }
            prevChar = ' ';
        }
    }

    inFile.close();
    outFile.close();

    vector<string> words = splitString(content, ' ');
    int numWords = words.size();

    if (numPairs > numWords - 1)                                                                                        // Check if the number of pairs requested exceeds the available number of pairs
    {
        cerr << "Not enough words to pick " << numPairs << " pairs!" << endl;
        return false;
    }

    pickRandomPairs(words, numPairs, q);

    cout << "File processed successfully. Number of words: " << numWords << endl;                                       //Just a way to see the size of the file
    return true;
}

#endif //UTILITIES_H
