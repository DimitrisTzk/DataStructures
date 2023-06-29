#include "BinarySearchTree.h"

//Constructor
BinarySearchTree::BinarySearchTree(const string &txt, int limit, int initialSize) : DataStructure(limit, initialSize)
{
    cout << endl << "    BinarySearchTree" << endl;

    Root = nullptr;

    makeTree(txt);

    cout << "UniquePairs: " << UniquePairs << " Height: " << getHeight(Root) << endl;
}

//Destructor
BinarySearchTree::~BinarySearchTree()
{
    destroyTree(Root);
}

//Recursively delete every node in the tree
void BinarySearchTree::destroyTree(Node* node)
{
    if (node != nullptr)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

//Function that reads the words from the file and creates the tree
void BinarySearchTree::makeTree(const string &filename)
{
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

            addNode(Root, word1, word2);

            // Swap word2 to word1 for the next iteration
            word1 = word2;
        }
    }
    file.close();
}

//Function that adds a pair to the tree
void BinarySearchTree::addNode(BinarySearchTree::Node *&node, const string &word1, const string &word2)
{
    if (node == nullptr)                                                                                                //If the node is empty, create a new node
    {
        node = new Node;
        node->Pair.wordPair.first = word1;
        node->Pair.wordPair.second = word2;
        node->Pair.count = 1;
        node->left = nullptr;
        node->right = nullptr;
        ++UniquePairs;
    }
    else if (node->Pair.wordPair.first == word1 && node->Pair.wordPair.second == word2)                                 //If the pair already exists, increment the count
    {
        ++node->Pair.count;
        return;
    }
    else if (word1 < node->Pair.wordPair.first ||                                                                       //If the pair doesn't exist, find the correct place to insert it
             (word1 == node->Pair.wordPair.first && word2 < node->Pair.wordPair.second))
        addNode(node->left, word1, word2);
    else if (word1 > node->Pair.wordPair.first ||
             (word1 == node->Pair.wordPair.first && word2 > node->Pair.wordPair.second))
        addNode(node->right, word1, word2);
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

//Function that calls the findPair function for each pair in the array
void BinarySearchTree::findPairs(pair<string, string> *q, int size, ofstream &outFile)
{
    for (int i = 0; i < size; ++i)
    {
        findPair(Root, q[i], outFile);
    }
}

//Function that finds the pair in the tree and appends it to the file
void BinarySearchTree::findPair(Node *node, const pair<string, string>& q, ofstream &file)
{
    if (node == nullptr)                                                                                                //Edge case of the pair not being in the tree
    {
        file << q.first << " " << q.second << " NOTFOUND" << endl;
        return;
    }
    else if (node->Pair.wordPair.first == q.first && node->Pair.wordPair.second == q.second)
    {
        file << q.first << " " << q.second << " " << node->Pair.count << endl;
        return;
    }
    else if (q.first < node->Pair.wordPair.first ||
             (q.first == node->Pair.wordPair.first && q.second < node->Pair.wordPair.second))
        findPair(node->left, q, file);
    else if (q.first > node->Pair.wordPair.first ||
             (q.first == node->Pair.wordPair.first && q.second > node->Pair.wordPair.second))
        findPair(node->right, q, file);
}

//Function that returns the height of the tree
int BinarySearchTree::getHeight(Node *node)
{
    if (node == nullptr)
        return -1;
    else
        return node->height;
}