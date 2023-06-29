#ifndef AVLTREE_H
#define AVLTREE_H

#include "DataStructure.h"

using namespace std;


class AVLTree : public DataStructure{
    private:
        struct Node {
            Pairs Pair;
            Node *left;
            Node *right;
            int height;
        };
        Node *Root;
    public:
        AVLTree(const string &txt, int limit, int initialSize);
        ~AVLTree();
        void destroyTree(Node* node);
        void makeTree(const string& filename);
        void addPair(AVLTree::Node *&node, const string &word1, const string &word2);
        static void rotateLeft(Node *&node);
        static void rotateRight(Node *&node);
        static void doubleRotateLeft(Node *&node);
        static void doubleRotateRight(Node *&node);
        void findPairs(pair<string, string> *q, int size, ofstream &outFile) override;
        void findPair(Node *node, const pair<string, string>& q, ofstream &file);
        static int getHeight(Node *node);
};


#endif //AVLTREE_H
