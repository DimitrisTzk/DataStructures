#include "AVLTree.h"

//Constructor
AVLTree::AVLTree(const string &txt, int limit, int initialSize) : DataStructure(limit, initialSize)
{
    cout << endl << "    AVLTree" << endl;

    Root = nullptr;

    makeTree(txt);

    cout << "UniquePairs: " << UniquePairs << " Height: " << getHeight(Root) << endl;
}

//Destructor
AVLTree::~AVLTree()
{
    destroyTree(Root);
}

//Recursively delete every node in the tree
void AVLTree::destroyTree(Node* node)
{
    if (node != nullptr)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

//Function that reads the words from the file and creates the tree
void AVLTree::makeTree(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
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

            addPair(Root, word1, word2);

            word1 = word2;                                                                                              // Swap word2 to word1 for the next iteration
        }
    }
    file.close();
}

//Function to add a node to the tree and balance it if necessary
void AVLTree::addPair(AVLTree::Node *&node, const string& word1, const string& word2)
{
    if (node == nullptr)                                                                                                //If the node is empty, create a new node
    {
        node = new Node;
        node->Pair.wordPair.first = word1;
        node->Pair.wordPair.second = word2;
        node->Pair.count = 1;
        node->left = nullptr;
        node->right = nullptr;
        UniquePairs++;
    }
    else if (word1 < node->Pair.wordPair.first ||                                                                       //Find the right place to add the node and check if the tree needs to be balanced
             (word1 == node->Pair.wordPair.first && word2 < node->Pair.wordPair.second))
    {
        addPair(node->left, word1, word2);
        if (getHeight(node->left) - getHeight(node->right) == 2)
        {
            if (word1 < node->left->Pair.wordPair.first ||
                 (word1 == node->left->Pair.wordPair.first && word2 < node->left->Pair.wordPair.second))
                rotateLeft(node);
            else
                doubleRotateLeft(node);
        }
    }
    else if (word1 > node->Pair.wordPair.first ||
             (word1 == node->Pair.wordPair.first && word2 > node->Pair.wordPair.second))
    {
        addPair(node->right, word1, word2);
        if (getHeight(node->right) - getHeight(node->left) == 2)
        {
            if (word1 > node->right->Pair.wordPair.first ||
                 (word1 == node->right->Pair.wordPair.first && word2 > node->right->Pair.wordPair.second))
                rotateRight(node);
            else
                doubleRotateRight(node);
        }
    }
    else                                                                                                                //The only other case is if the pair already exists, in which case we just increment the count
        node->Pair.count++;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;                                   //Update the height of the node by taking the max height of its children and adding 1
}

//Function to rotate the tree to the left
void AVLTree::rotateLeft(Node*& node)
{
    if (node == nullptr)
        return;
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->left), node->height) + 1;
    node = temp;
}

//Function to rotate the tree to the right
void AVLTree::rotateRight(Node*& node)
{
    if (node == nullptr)
        return;
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    temp->height = max(getHeight(temp->right), node->height) + 1;
    node = temp;
}

//Function to double rotate the tree to the left
void AVLTree::doubleRotateLeft(Node*& node)
{
    rotateRight(node->left);
    rotateLeft(node);
}

//Function to double rotate the tree to the right
void AVLTree::doubleRotateRight(Node*& node)
{
    rotateLeft(node->right);
    rotateRight(node);
}

//Function to find the pairs in the tree and append them to the file
void AVLTree::findPairs(pair<string, string> *q, int size, ofstream &outFile)
{
    for (int i = 0; i < size; ++i)
    {
        findPair(Root, q[i], outFile);
    }
}

//Function to find a pair in the tree
void AVLTree::findPair(Node* node, const pair<string, string>& q, ofstream& file)
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

//Function to find the height of a node
int AVLTree::getHeight(Node* node)
{
    if (node == nullptr)
        return -1;
    else
        return node->height;
}