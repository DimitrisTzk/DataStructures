#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>
#include <utility>

using namespace std;

vector<string> splitString(const string& input, char delimiter)
{
    vector<string> tokens;
    stringstream ss(input);
    string token;

    while (getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

void pickRandomPairs(const vector<string>& words, int numPairs, pair<string, string>* q)
{
    int numWords = words.size();

    // Seed the random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, numWords - 2);  // Selecting index from 0 to numWords-2

    for (int i = 0; i < numPairs; ++i)
    {
        int index = distrib(gen);
        q[i] = make_pair(words[index], words[index + 1]);
    }
}

bool processFile(const string& file, pair<string, string>* q, int numPairs)
{
    ifstream inFile(file);
    ofstream outFile("edited.txt");

    // Check to make sure the files open correctly.
    if (!inFile) {
        cerr << "Failed to open input file!" << endl;
        return false;
    }
    if (!outFile) {
        cerr << "Failed to create output file!" << endl;
        return false;
    }

    char c;
    char prevChar = '\0';
    string content;

    while (inFile.get(c)) {
        // Convert to lowercase
        if (isalnum(c)) {
            outFile << static_cast<char>(tolower(c));
            prevChar = c;
            content += static_cast<char>(tolower(c));
        }
            // Replace all other characters with spaces only if the previous character is not a space
        else {
            if (!isspace(prevChar)) {
                outFile << ' ';
                content += ' ';
            }
            prevChar = ' ';
        }
    }

    inFile.close();
    outFile.close();

    vector<string> words = splitString(content, ' ');
    int numWords = words.size();

    // Check if the number of pairs requested exceeds the available number of pairs
    if (numPairs > numWords - 1) {
        cerr << "Not enough words to pick " << numPairs << " pairs!" << endl;
        return false;
    }

    pickRandomPairs(words, numPairs, q);

    cout << "File processed successfully. Number of words: " << numWords << endl;
    return true;
}

#endif //UTILITIES_H
