#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "utilities.h"
#include "UnsortedArray.h"
#include "SortedArray.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "HashTable.h"

#define inFile "small-file.txt"                                                                                         //Define the input file for the program
#define outFile "output.txt"                                                                                            //Define the output file for the program
#define NumOfPairsToFind 10000                                                                                          //Number of random pairs needed for the program
#define PairLimit (-1)                                                                                                  //Pair limit for testing purposes, -1 for no limit. Must be bigger than NumOfPairsToFind
#define InitialSize 1000000                                                                                             //Initial size for the Arrays and the Hash Table

using namespace std;


int main()
{
    auto startProgram = chrono::high_resolution_clock::now();                                              //Timer for the program runtime

    pair<string, string> wordPairs[NumOfPairsToFind];
    auto start = chrono::high_resolution_clock::now();
    if (!processFile(inFile, wordPairs, PairLimit, NumOfPairsToFind))                           //Run the processFile function to process the input file and choose random pairs from it
    {
        cout << "Failed to open the file." << endl;
        return -1;                                                                                                      //If the file failed to open, return -1
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Time to process file and choose random pairs: " << duration << " milliseconds." << endl << endl;

    ofstream outputFile(outFile);
    if (!outputFile.is_open())                                                                                          //Open the output file and check if it opened correctly
    {
        cout << "Failed to open the file." << endl;
        return -1;
    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    start = chrono::high_resolution_clock::now();                                                                       //Create the Unsorted Array and track how long it takes to be generated
    UnsortedArray unsortedArray("edited.txt", PairLimit, InitialSize);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile << "Unsorted Array" << endl;
    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;

    cout << "Time to create: " << duration << " milliseconds." << endl;

    start = chrono::high_resolution_clock::now();                                                                       //Find the pairs in the Unsorted Array and track how long it takes
    unsortedArray.findPairs(wordPairs, NumOfPairsToFind, outputFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile << endl << "Time to find pairs in the Unsorted Array: " << duration << " milliseconds." << endl <<
    "------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Time to find pairs in the Unsorted Array: " << duration << " milliseconds." << endl;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    start = chrono::high_resolution_clock::now();                                                                       //Create the Sorted Array and track how long it takes to be generated
    SortedArray sortedArray("edited.txt", PairLimit, InitialSize);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "Sorted Array" << endl;
    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;

    cout << "Time to create: " << duration << " milliseconds." << endl;

    start = chrono::high_resolution_clock::now();                                                                       //Find the pairs in the Sorted Array and track how long it takes
    sortedArray.findPairs(wordPairs, NumOfPairsToFind, outputFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile << endl << "Time to find pairs in the Sorted Array: " << duration << " milliseconds." << endl <<
    "------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Time to find pairs in the Sorted Array: " << duration << " milliseconds." << endl;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    start = chrono::high_resolution_clock::now();                                                                       //Create the Binary Search Tree and track how long it takes to be generated
    BinarySearchTree bst("edited.txt", PairLimit, InitialSize);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "Binary Search Tree" << endl;
    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;

    cout << "Time to create: " << duration << " milliseconds." << endl;

    start = chrono::high_resolution_clock::now();                                                                       //Find the pairs in the Binary Search Tree and track how long it takes
    bst.findPairs(wordPairs, NumOfPairsToFind, outputFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile <<endl << "Time to find pairs in the Binary Search Tree: " << duration << " milliseconds." << endl <<
    "------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Time to find pairs: " << duration << " milliseconds." << endl;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    start = chrono::high_resolution_clock::now();                                                                       //Create the AVL Tree and track how long it takes to be generated
    AVLTree avl("edited.txt", PairLimit, InitialSize);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "AVL Binary Tree" << endl;
    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;

    cout << "Time to create: " << duration << " milliseconds." << endl;

    start = chrono::high_resolution_clock::now();                                                                       //Find the pairs in the AVL Tree and track how long it takes
    avl.findPairs(wordPairs, NumOfPairsToFind, outputFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile << endl << "Time to find pairs in the AVL Tree: " << duration << " milliseconds." << endl <<
    "------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Time to find pairs: " << duration << " milliseconds." << endl;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    start = chrono::high_resolution_clock::now();                                                                       //Create the Hash Table and track how long it takes to be generated
    HashTable hashTable("edited.txt", PairLimit, InitialSize);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "Hash Table" << endl;
    outputFile << "Time to create: " << duration << " milliseconds. "<< endl << endl;

    cout << "Time to create: " << duration << " milliseconds." << endl;

    start = chrono::high_resolution_clock::now();
    hashTable.findPairs(wordPairs, NumOfPairsToFind, outputFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile << endl << "Time to find pairs in the Hash Table: " << duration << " milliseconds." << endl;
    outputFile.close();

    cout << "Time to find pairs in the Hash Table: " << duration << " milliseconds." << endl;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    auto endProgram = chrono::high_resolution_clock::now();                                                //Display the total runtime of the program
    auto durationProgram = chrono::duration_cast<chrono::milliseconds>(endProgram - startProgram).count();
    cout<<endl<<"Total time of the program: "<<durationProgram<<" milliseconds"<<endl;

    return 0;
}
