#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <chrono>
#include <iomanip>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include "BTree.h"
#include "BST.h"
#include "BinaryFile.h"
using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Staff StaffRecordStruct1;
    int FILESIZE = 500;
    BinaryFile BF;
    BF.FromTextToBin();

    BST bst;
    //тест функции CreateBST
    node* ROOT = bst.CreateBST();

    BTree* tree = new BTree(3, -1);
    tree->CreateBTree();


    while (true) {
        cout << "1. Manipulate the file directly"
            << "\n2. Interact with the file via a BST (binary search tree)"
            << "\n3. Interact with the file via a B-Tree"
            << "\n4. Exit\n";

        char opt1;
        cout << "Enter your choice: ";
        cin >> opt1;
        while (true)
        {
            cout << "1. Find function"
                << "\n2. Add function"
                << "\n3. Del function"
                << "\n4. Return\n";

            char opt2;
            cout << "Enter your choice: ";
            cin >> opt2;
            switch (opt2) {
                case '1': {
                    if (opt1 == '1') {
                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;

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

                        //Тест функции findBin
                        StaffRecordStruct1 = BF.findBin(opt3);

                        //check file
                        cout << "file:\n" <<
                            "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
                            "======================================\n";

                        printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
                        cout << "======================================\n\n";
                        break;
                    }
                    else if (opt1 == '2')
                    {
                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;
                        cout << "Binary search tree\n The tree may not be displayed correctly due to the excessively large file size\n";
                        bst.treeBST(ROOT, 0);

                        const auto start2{ std::chrono::steady_clock::now() }; //начало замера времени

                        //тест функции findBST + findBinDir
                        int adr = bst.findBST(ROOT, opt3);
                        StaffRecordStruct1 = BF.findBinDir(adr);
                        const auto end2{ std::chrono::steady_clock::now() }; //конец замера времени (вычисление хеш-функции, рехеширование, чтение из файла)
                        const std::chrono::duration<double> elapsed_seconds{ end2 - start2 };
                        //check file
                        cout << "Время линейного поиска: " << elapsed_seconds << endl;
                        //check file
                        cout << "file:\n" <<
                            "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
                            "======================================\n";

                        printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
                        cout << "======================================\n\n";
                        break;
                    }
                    else if (opt1 == '3')
                    {
                        tree->display();
                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;
                        const auto start1{ std::chrono::steady_clock::now() }; //начало замера времени

                        int foundFilePos = tree->searchNode(opt3);

                        if (foundFilePos != -1) {
                            cout << "Node with key " << opt3 << " found. Filepos: " << foundFilePos << endl;
                        }
                        else {
                            cout << "Node with key " << opt3 << " not found." << endl;
                        }

                        //Тест функции findBinDir
                        StaffRecordStruct1 = BF.findBinDir(foundFilePos);
                        const auto end1{ std::chrono::steady_clock::now() }; //конец замера времени (вычисление хеш-функции, рехеширование, чтение из файла)
                        const std::chrono::duration<double> elapsed_seconds{ end1 - start1 };
                        //check file
                        cout << "Время линейного поиска: " << elapsed_seconds << endl;
                        //check file
                        cout << "file:\n" <<
                            "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
                            "======================================\n";

                        printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
                        cout << "======================================\n\n";
                        break;
                    }
                    else
                    {
                        cout << "No such option\n";
                        break;
                    }
                }
                case '2': {
                    if (opt1 == '1') {
                        int opt3;
                        string input;
                        bool edu;
                        cout << "Enter name of the person and his level of education (1-Yes/0-No):\n" <<
                            "Example: Mike_Thompson 1\n";
                        cin >> input >> edu;

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

                        //Тест функции addBin
                        BF.addBin(input, edu);
                        FILESIZE++;
                        fstream fs2("MyBinFile.bin", ios::in | ios::binary);
                        if (!fs2.is_open()) {
                            cerr << "Failed to open file." << endl;
                            exit(1); // Возврат с ошибкой
                        }

                        //check file
                        cout << "file:\n" <<
                            "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
                            "======================================\n";

                        for (int i = 0; i < FILESIZE; i++) {
                            (fs2.read(reinterpret_cast<char*>(&StaffRecordStruct1), sizeof(Staff)));
                            printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
                        }
                        cout << "======================================\n\n";
                        fs2.close();

                        break;
                    }
                    else if (opt1 == '2')
                    {
                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;
                        cout << "Binary search tree\n The tree may not be displayed correctly due to the excessively large file size\n";
                        bst.treeBST(ROOT, 0);
                        //тест функции addBST
                        ROOT = bst.addBST(ROOT, opt3, FILESIZE * 105);
                        //теперь по FILESIZE * 105 можно добавить соответствующую запись в бинарный файл
                        cout << "Binary search tree\n The tree may not be displayed correctly due to the excessively large file size\n";
                        bst.treeBST(ROOT, 0);
                        break;
                    }
                    else if (opt1 == '3')
                    {
                        tree->display();
                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;
                        tree->insert(opt3, 1555);
                        tree->display();
                        break;
                    }
                    else
                    {
                        cout << "No such option\n";
                        break;
                    }
                }
                case '3': {
                    if (opt1 == '1') {
                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;

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

                        //Тест функции delBin
                        BF.delBinIndex(opt3);
                        BF.FILESIZE--;
                        FILESIZE--;
                        fstream fs3("MyBinFile.bin", ios::in | ios::binary);
                        if (!fs3.is_open()) {
                            cerr << "Failed to open file." << endl;
                            exit(1); // Возврат с ошибкой
                        }

                        //check file
                        cout << "file:\n" <<
                            "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
                            "======================================\n";

                        for (int i = 0; i < FILESIZE; i++) {
                            (fs3.read(reinterpret_cast<char*>(&StaffRecordStruct1), sizeof(Staff)));
                            printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
                        }
                        cout << "======================================\n\n";
                        fs3.close();

                        break;
                    }
                    else if (opt1 == '2')
                    {
                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;
                        cout << "Binary search tree\n The tree may not be displayed correctly due to the excessively large file size\n";
                        bst.treeBST(ROOT, 0);
                        //тест функции delBSt
                        ROOT = bst.delBST(ROOT, opt3);
                        cout << "Binary search tree\n The tree may not be displayed correctly due to the excessively large file size\n";
                        bst.treeBST(ROOT, 0);
                        break;
                    }
                    else if (opt1 == '3')
                    {
                        tree->display();

                        int opt3;
                        cout << "Enter your key: ";
                        cin >> opt3;
                        //Тест функции delBin
                        BF.delBinIndex(opt3);
                        FILESIZE--;
                        fstream fs3("MyBinFile.bin", ios::in | ios::binary);
                        if (!fs3.is_open()) {
                            cerr << "Failed to open file." << endl;
                            exit(1); // Возврат с ошибкой
                        }
                        delete tree;
                        BTree* tree = new BTree(3, -1);
                        tree->CreateBTree();
                        tree->display();
                        break;
                    }
                    else
                    {
                        cout << "No such option\n";
                        break;
                    }
                }
                case '4': {
                    exit(1);
                }
                default: {
                    cout << "Invalid choice. Please try again.\n";
                }
            }
        }
    }
}