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
        cerr << "Ошибка открытия файла: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    Staff record;
    int i = 0;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) { //приведение указателя на объект record к указателю на символ (char). 
        record.IDNumber;
        BST::insert(record.IDNumber, i);
        i += sizeof(record);
    }
    inputfile.close();
    return root;
}


int BST::findBST(node* root, int value) {
    if (root == nullptr) {
        cout << "Элемент со значением " << value << " не был найден\n";
        return 0;
    }

    if (value == root->key) {
        cout << "Эллемент с номером " << value << " найден\n" << "Позиция в файле: " << root->filepos << endl;
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
        cout << "Узел с ключом " << value << " найден!" << endl;
        // Если у узла нет детей или только один
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

        // У узла есть двое детей
        node* tmp = findMinNode(root->right);

        // Заменяем значение удаляемого узла на значение наименьшего узла в правом поддереве
        root->key = tmp->key;

        // Удаляем наименьший узел в правом поддереве
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
    //тест функции CreateBST
    node* ROOT = bst.CreateBST();
    cout << "Бинарное дерево" << endl;
    bst.treeBST(ROOT, 0);

    //тест функции findBST + findBinDir
    int adr = bst.findBST(ROOT, 3);
    StaffRecordStruct1 = BF.findBinDir(adr);

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    cout << "======================================\n\n";

    //тест функции addBST
    ROOT = bst.addBST(ROOT, 11, FILESIZE * 105);
    //теперь по FILESIZE * 105 можно добавить соответствующую запись в бинарный файл
    bst.treeBST(ROOT, 0);

    //тест функции delBSt
    ROOT = bst.delBST(ROOT, 7);
    bst.treeBST(ROOT, 0);
}