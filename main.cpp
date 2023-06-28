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

#define inFile "gutenberg.txt"                                                                                          //Define the input file for the program (small-file.txt or gutenberg.txt)
#define outFile "output.txt"                                                                                            //Define the output file for the program
#define NumOfRandomPairs 10000                                                                                          //Number of random pairs needed for the program
#define PairLimit (-1)                                                                                                  //Pair limit for testing purposes, -1 for no limit

using namespace std;


int main() {

    auto startProgram = chrono::high_resolution_clock::now();

    //Process the input file and pick random pairs of words from it
    pair<string, string> wordPairs[NumOfRandomPairs];
    auto start = chrono::high_resolution_clock::now();
    if (!processFile(inFile, wordPairs, NumOfRandomPairs))
    {
        cout << "Failed to open the file." << endl;
        return -1;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time to process file and choose random pairs: " << duration << " milliseconds." << endl << endl;

    //Open the output file and check if it opened correctly
    ofstream outputFile(outFile);
    if (!outputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return -1;
    }

    //------------------------------------------------------------------------------------------------------------------

    //Create the Unsorted Array and track how long it takes to be generated and print it into the output file
    start = chrono::high_resolution_clock::now();
    UnsortedArray unsortedArray("edited.txt", PairLimit);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "Unsorted Array" << endl;
    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;
    outputFile.close();

    cout << "Time to create: " << duration << " milliseconds." << endl;

    //Call the findPairs function of the Unsorted Array to find the number of appearances of each pair and print the
    //results into the output file
    start = chrono::high_resolution_clock::now();
    unsortedArray.findPairs(wordPairs, NumOfRandomPairs, outFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile.open(outFile, ios::app);
    if (!outputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return -1;
    }
    outputFile << endl << "Time to find pairs in the Unsorted Array: " << duration << " milliseconds." << endl <<
    "------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Time to find pairs in the Unsorted Array: " << duration << " milliseconds." << endl;

    //------------------------------------------------------------------------------------------------------------------

//    //Create the Sorted Array and track how long it takes to be generated and print it into the output file
//    start = chrono::high_resolution_clock::now();
//    SortedArray sortedArray("edited.txt", PairLimit);
//    end = chrono::high_resolution_clock::now();
//    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
//    outputFile << "Sorted Array" << endl;
//    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;
//    outputFile.close();
//
//    cout << "Time to create: " << duration << " milliseconds." << endl;
//
//    //Call the findPairs function of the Sorted Array to find the number of appearances of each pair and print the
//    //results into the output file
//    start = chrono::high_resolution_clock::now();
//    sortedArray.findPairs(wordPairs, NumOfRandomPairs, outFile);
//    end = chrono::high_resolution_clock::now();
//    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
//
//    outputFile.open(outFile, ios::app);
//    if (!outputFile.is_open())
//    {
//        cout << "Failed to open the file." << endl;
//        return -1;
//    }
//    outputFile << endl << "Time to find pairs in the Sorted Array: " << duration << " milliseconds." << endl <<
//    "------------------------------------------------------------------------------------------------------------------------" << endl;
//
//    cout << "Time to find pairs in the Sorted Array: " << duration << " milliseconds." << endl;

    //------------------------------------------------------------------------------------------------------------------

    //Create the Simple Tree and track how long it takes to be generated and print it into the output file
    start = chrono::high_resolution_clock::now();
    BinarySearchTree bst("edited.txt", PairLimit);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "Binary Search Tree" << endl;
    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;
    outputFile.close();

    cout << "Time to create: " << duration << " milliseconds." << endl;

    //Call the findPairs function of the Simple Tree to find the number of appearances of each pair and print the
    //results into the output file
    start = chrono::high_resolution_clock::now();
    bst.findPairs(wordPairs, NumOfRandomPairs, outFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile.open(outFile, ios::app);
    if (!outputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return -1;
    }
    outputFile <<endl << "Time to find pairs in the Binary Search Tree: " << duration << " milliseconds." << endl <<
    "------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Time to find pairs: " << duration << " milliseconds." << endl;

    //------------------------------------------------------------------------------------------------------------------

    //Create the AVL Tree and track how long it takes to be generated and print it into the output file
    start = chrono::high_resolution_clock::now();
    AVLTree avl("edited.txt", PairLimit);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "AVL Binary Tree" << endl;
    outputFile << "Time to create: " << duration << " milliseconds." << endl << endl;
    outputFile.close();

    cout << "Time to create: " << duration << " milliseconds." << endl;

    //Call the findPairs function of the AVL Tree to find the number of appearances of each pair and print the
    //results into the output file
    start = chrono::high_resolution_clock::now();
    avl.findPairs(wordPairs, NumOfRandomPairs, outFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile.open(outFile, ios::app);
    if (!outputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return -1;
    }
    outputFile << endl << "Time to find pairs in the AVL Tree: " << duration << " milliseconds." << endl <<
    "------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Time to find pairs: " << duration << " milliseconds." << endl;

    //------------------------------------------------------------------------------------------------------------------

    //Create the Hash Table and track how long it takes to be generated and print it into the output file
    start = chrono::high_resolution_clock::now();
    HashTable hashTable("edited.txt", PairLimit);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    outputFile << "Hash Table" << endl;
    outputFile << "Time to create: " << duration << " milliseconds. "<< endl << endl;
    outputFile.close();

    cout << "Time to create: " << duration << " milliseconds." << endl;

    //Call the findPairs function of the Hash Table to find the number of appearances of each pair and print the
    //results into the output file
    start = chrono::high_resolution_clock::now();
    hashTable.findPairs(wordPairs, NumOfRandomPairs, outFile);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    outputFile.open(outFile, ios::app);
    if (!outputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return -1;
    }
    outputFile << endl << "Time to find pairs in the Hash Table: " << duration << " milliseconds." << endl;
    outputFile.close();

    cout << "Time to find pairs in the Hash Table: " << duration << " milliseconds." << endl;

    auto endProgram = chrono::high_resolution_clock::now();
    auto durationProgram = chrono::duration_cast<chrono::milliseconds>(endProgram - startProgram).count();
    cout<<endl<<"Total time of the program: "<<durationProgram<<" milliseconds"<<endl;

    return 0;
}

/* 
 * TODO:
 *
 * utilities.h diafores xrisimes sinartiseis
 *      file editing                DONE
 *      choose random pairs         DONE
 *      function for main stuff     NOT DONE***
 *
 *
 * datastructure geniki klasi gia oles tis domes just in case (removed for now)
 *
 * 1.unsorted array
 *      constructor                 DONE
 *      findPairs                   DONE
 *
 * 2.sorted array
 *      constructor                 DONE
 *      findPairs                   DONE
 *
 * 3.aplo dentro
 *      constructor                 DONE
 *      findPairs                   DONE
 *
 * 4.avl dentro
 *      constructor                 DONE
 *      findPairs                   DONE
 *
 * 5.pinakas katakermatismou me anoixti diefthinsi
 *      constructor                 DONE
 *      findPairs                   DONE
 *
 *             *****ANAFORA*****
 *
 *end TODO
*/