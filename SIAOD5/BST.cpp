#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include "BST.h"
#include "BinaryFile.h"
using namespace std;

void BST::insert(int value, int filepos)
{
    root = addBST(root, value, filepos);
}

node* BST::findMinNode(node* n)
{
    while (n->left != nullptr) {
        n = n->left;
    }
    return n;
}

node* BST::addBST(node* root, int value, int filepos)
{
    if (root == nullptr) {
        return new node(value, filepos, nullptr, nullptr);
    }

    if (value < root->key) {
        root->left = addBST(root->left, value, filepos);
    }
    else if (value > root->key) {
        root->right = addBST(root->right, value, filepos);
    }

    return root;
}

node* BST::CreateBST()
{
    ifstream inputfile("MyBinFile.bin", ios::binary | ios::in);
    vector<Staff> records;
    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    Staff record;
    int i = 0;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) { //���������� ��������� �� ������ record � ��������� �� ������ (char). 
        record.IDNumber;
        BST::insert(record.IDNumber, i);
        i += sizeof(record);
    }
    inputfile.close();
    return root;
}


int BST::findBST(node* root, int value) {
    if (root == nullptr) {
        cout << "������� �� ��������� " << value << " �� ��� ������\n";
        return 0;
    }

    if (value == root->key) {
        cout << "�������� � ������� " << value << " ������\n" << "������� � �����: " << root->filepos << endl;
        return root->filepos;
    }
    else if (value < root->key) {
        return findBST(root->left, value);
    }
    else {
        return findBST(root->right, value);
    }
}

node * BST::delBST(node * root, int value)
{
    if (root == nullptr) {
        return root;
    }

    if (value < root->key) {
        root->left = delBST(root->left, value);
    }
    else if (value > root->key) {
        root->right = delBST(root->right, value);
    }
    else if(value == root->key)
    {
        cout << "���� � ������ " << value << " ������!" << endl;
        // ���� � ���� ��� ����� ��� ������ ����
        if (root->left == nullptr) {
            node* tmp = root->right;
            delete root;
            return tmp;
        }
        else if (root->right == nullptr) {
            node* tmp = root->left;
            delete root;
            return tmp;
        }

        // � ���� ���� ���� �����
        node* tmp = findMinNode(root->right);

        // �������� �������� ���������� ���� �� �������� ����������� ���� � ������ ���������
        root->key = tmp->key;

        // ������� ���������� ���� � ������ ���������
        root->right = delBST(root->right, tmp->key);
    }
    return root;
}

void BST::treeBST(node* root, int indent) {
    if (root != nullptr) {
        treeBST(root->right, indent + 4);

        for (int i = 0; i < indent; i++) {
            std::cout << " ";
        }
        std::cout << root->key << "\n";

        treeBST(root->left, indent + 4);
    }
}

void BST::testBST()
{
    setlocale(LC_ALL, "Russian");
    BinaryFile BF;
    BST bst;
    int FILESIZE = 10;
    Staff StaffRecordStruct1;
    //���� ������� CreateBST
    node* ROOT = bst.CreateBST();
    cout << "�������� ������" << endl;
    bst.treeBST(ROOT, 0);

    //���� ������� findBST + findBinDir
    int adr = bst.findBST(ROOT, 3);
    StaffRecordStruct1 = BF.findBinDir(adr);

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    cout << "======================================\n\n";

    //���� ������� addBST
    ROOT = bst.addBST(ROOT, 11, FILESIZE * 105);
    //������ �� FILESIZE * 105 ����� �������� ��������������� ������ � �������� ����
    bst.treeBST(ROOT, 0);

    //���� ������� delBSt
    ROOT = bst.delBST(ROOT, 7);
    bst.treeBST(ROOT, 0);
}