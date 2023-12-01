#ifndef BTREENODE_H
#define BTREENODE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class BTreeNode {
public:

    // Minimum degree
    int t;

    int filepos;

    // Vector of child pointers
    vector<BTreeNode*> C;

    // Is true when node is leaf, else false
    bool leaf;

    vector<pair<int, int>> keyFileposPairs;  // Вектор пар ключ-файловая позиция

    // Vector of keys
    vector<int> keys;

    // Constructor
    BTreeNode(int t, bool leaf, int filepos);

    // Traversing the node and print its content
    // with tab number of tabs before
    void traverse(int tab);

    // Insert key into given node. If child is split, we
    // have to insert *val entry into keys vector and
    // newEntry pointer into C vector of this node
    void insert(int key, int* val, int filepos, BTreeNode*& newEntry);

    // Split this node and store the new parent value in
    // *val and new node pointer in newEntry
    void split(int* val, BTreeNode*& newEntry, int filepos);

    // Returns true if node is full
    bool isFull();

    // Makes new root, setting current root as its child
    BTreeNode* makeNewRoot(int val, BTreeNode* newEntry, int filepos);

    int searchNode(int key);

};
#endif