#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "BinaryFile.h"
#include "BTreeNode.h"
using namespace std;
bool BTreeNode::isFull()
{
    // returns true if node is full
    return (this->keys.size() == 2 * t - 1);
}

BTreeNode::BTreeNode(int t, bool leaf, int filepos)
{
    // Constructor to set value of t and leaf
    this->filepos = filepos;
    this->t = t;
    this->leaf = leaf;
}

// Function to print the nodes of B-Tree
void BTreeNode::traverse(int tab)
{
    int i;
    string s;

    // Print 'tab' number of tabs
    for (int j = 0; j < tab; j++) {
        s += '\t';
    }
    for (i = 0; i < keys.size(); i++) {

        // If this is not leaf, then before printing key[i]
        // traverse the subtree rooted with child C[i]
        if (leaf == false)
            C[i]->traverse(tab + 1);
        cout << s << keys[i] << endl;
    }

    // Print the subtree rooted with last child
    if (leaf == false) {
        C[i]->traverse(tab + 1);
    }
}

// Function to split the current node and store the new
// parent value is *val and new child pointer in &newEntry
// called only for splitting non-leaf node
void BTreeNode::split(int* val, BTreeNode*& newEntry, int filepos)
{

    // Create new non leaf node
    newEntry = new BTreeNode(t, false, filepos);

    //(t+1)th becomes parent
    *val = this->keys[t];

    // Last (t-1) entries will go to new node
    for (int i = t + 1; i < 2 * t; i++) {
        newEntry->keys.push_back(this->keys[i]);
    }

    // This node stores first t entries
    this->keys.resize(t);

    // Last t entries will go to new node
    for (int i = t + 1; i <= 2 * t; i++) {
        newEntry->C.push_back(this->C[i]);
    }

    // This node stores first (t+1) entries
    this->C.resize(t + 1);
}

// Function to insert a new key in given node.
// If child of this node is split, we have to insert *val
// into keys vector and newEntry pointer into C vector
void BTreeNode::insert(int new_key, int* val, int filepos, BTreeNode*& newEntry)
{
    keyFileposPairs.insert(lower_bound(keyFileposPairs.begin(), keyFileposPairs.end(), make_pair(new_key, filepos)),
        make_pair(new_key, filepos));
    // Non leaf node
    if (leaf == false) {
        int i = 0;

        // Find first key greater than new_key
        while (i < keys.size() && new_key > keys[i])
            i++;

        // We have to insert new_key into left child of
        // Node with index i
        C[i]->insert(new_key, val, filepos, newEntry);

        // No split was done
        if (newEntry == NULL)
            return;
        if (keys.size() < 2 * t - 1) {

            // This node can accommodate a new key
            // and child pointer entry
            // Insert *val into key vector
            keys.insert(keys.begin() + i, *val);

            // Insert newEntry into C vector
            C.insert(C.begin() + i + 1, newEntry);

            // As this node was not split, set newEntry
            // to NULL
            newEntry = NULL;
        }
        else {

            // Insert *val and newentry
            keys.insert(keys.begin() + i, *val);
            C.insert(C.begin() + i + 1, newEntry);

            // Current node has 2*t keys, so split it
            split(val, newEntry, filepos);
        }
    }
    else {

        // Insert new_key in this node
        vector<int>::iterator it;

        // Find correct position
        it = lower_bound(keys.begin(), keys.end(),
            new_key);

        // Insert in correct position
        keys.insert(it, new_key);

        // If node is full
        if (keys.size() == 2 * t) {

            // Create new node
            newEntry = new BTreeNode(t, true, filepos);

            // Set (t+1)th key as parent
            *val = this->keys[t];

            // Insert last (t-1) keys into new node
            for (int i = t + 1; i < 2 * t; i++) {
                newEntry->keys.push_back(this->keys[i]);
            }

            // This node stores first t keys
            this->keys.resize(t);
        }
    }
}

// Function to create a new root
// setting current node as its child
BTreeNode* BTreeNode::makeNewRoot(int val, BTreeNode* newEntry, int filepos)
{
    // Create new root
    BTreeNode* root = new BTreeNode(t, false, filepos);

    // Stores keys value
    root->keys.push_back(val);

    // Push child pointers
    root->C.push_back(this);
    root->C.push_back(newEntry);
    return root;
}

int BTreeNode::searchNode(int key) {
    int i = 0;
    while (i < keyFileposPairs.size() && key > keyFileposPairs[i].first) {
        i++;
    }

    if (i < keyFileposPairs.size() && key == keyFileposPairs[i].first) {
        // Ключ найден в этом узле
        return keyFileposPairs[i].second;  // Возвращаем файловую позицию
    }
    else if (leaf) {
        // Узел является листом, и ключ отсутствует
        return -1;  // Возвращаем -1, чтобы указать, что ключ не найден
    }
    else {
        // Рекурсивно переходим к дочернему узлу
        return C[i]->searchNode(key);
    }
}