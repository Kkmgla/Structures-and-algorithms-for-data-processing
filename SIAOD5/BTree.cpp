#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include "BinaryFile.h"
#include "BTreeNode.h"
#include "BTree.h"
#include "BST.h"
using namespace std;

void BTree::CreateBTree()
{
    ifstream inputfile("MyBinFile.bin", ios::binary | ios::in);
    vector<Staff> records;
    if (!inputfile.is_open()) {
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    Staff record;
    int i = 0;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) { //приведение указателя на объект record к указателю на символ (char). 
        record.IDNumber;
        BTree::insert(record.IDNumber, i);
        i += sizeof(record);
    }
    inputfile.close();
}

// Function to create a new BTree with
// minimum degree t
BTree::BTree(int t, int filepos)
{
    root = new BTreeNode(t, true, filepos);
}

// Function to insert a node in the B-Tree
void BTree::insert(int key, int filepos)
{
    BTreeNode* newEntry = NULL;
    int val = 0;

    // Insert in B-Tree
    root->insert(key, &val, filepos, newEntry);

    // If newEntry is not Null then root needs to be
    // split. Create new root
    if (newEntry != NULL) {
        root = root->makeNewRoot(val, newEntry, filepos);
    }
}

// Prints BTree
void BTree::display()
{
    root->traverse(0);
}


// В классе BTree добавьте метод для поиска узла по ключу
int BTree::searchNode(int key) {
    return (root != nullptr) ? root->searchNode(key) : -1;
}

void BTree::testBTree() {
    setlocale(LC_ALL, "Russian");
    BinaryFile BF;
    BST bst;
    int FILESIZE = 10;
    Staff StaffRecordStruct1;
    //Тест функции FromTextToBin
    BF.FromTextToBin();
    fstream fs1("MyBinFile.bin", ios::in | ios::binary);
    if (!fs1.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // Возврат с ошибкой
    }
    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    for (int i = 0; i < FILESIZE; i++) {
        (fs1.read(reinterpret_cast<char*>(&StaffRecordStruct1), sizeof(Staff)));
        printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    }
    cout << "======================================\n\n";
    fs1.close();

    // Создаем B-дерево с тем же минимальным количеством ключей в узле, что и в вашем коде (2)
       // Create B-Tree
    int lev = 3;
    BTree* tree = new BTree(lev, -1);
    tree->CreateBTree();
    tree->display();

    tree->insert(100000, 1000000);
    tree->display();
    int searchKey = 3;
    int foundFilePos = tree->searchNode(searchKey);

    if (foundFilePos != -1) {
        cout << "Node with key " << searchKey << " found. Filepos: " << foundFilePos << endl;
    }
    else {
        cout << "Node with key " << searchKey << " not found." << endl;
    }
    //Тест функции findBinDir
    StaffRecordStruct1 = BF.findBinDir(foundFilePos);

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    cout << "======================================\n\n";
}