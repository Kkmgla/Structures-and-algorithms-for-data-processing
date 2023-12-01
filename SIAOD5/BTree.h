#ifndef BTREE_H
#define BTREE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "BTreeNode.h"
using namespace std;
class BTree {

    // Root of B-Tree
    BTreeNode* root;

    // Minimum degree
    int t;

public:
    // Constructor
    BTree(int t, int filepos);

    // Insert key
    void insert(int key, int filepos);

    // Display the tree
    void display();

    void CreateBTree();

    // Delete a key from the B-Tree
    void remove(int key);

    int searchNode(int key);

    void testBTree();
};
#endif