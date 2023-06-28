#ifndef SIMPLEBINARYTREE_H
#define SIMPLEBINARYTREE_H

#include "DataStructure.h"

using namespace std;


class BinarySearchTree : public DataStructure{
    private:
        struct Node {
            Pairs Pair;
            Node *left;
            Node *right;
            int height;
        };
        Node *Root;
    public:
        BinarySearchTree(const string& txt, int limit);
        ~BinarySearchTree();
        void destroyTree(Node* node);
        void makeTree(const string& filename);
        void addNode(BinarySearchTree::Node *&node, const string &word1, const string &word2);
        void findPairs(pair<string, string> *q, int size, const string &file)  override;
        void findPair(Node *node, const pair<string, string>& q, ofstream &file);
        static int getHeight(Node *node);
};

#endif //SIMPLEBINARYTREE_H
