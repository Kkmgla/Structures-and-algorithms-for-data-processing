#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include "BinaryFile.h"

using namespace std;

/*�������� ��������� ����� �� ����������*/
void BinaryFile::FromTextToBin() {
    vector<Staff> records;
    ifstream inputfile("MyTextFile.txt");

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyTextFile.txt" << endl;
        exit(1);
    }

    Staff record;
    while (inputfile >> record.IDNumber >> record.FullName >> record.EDU) {
        records.push_back(record);
        inputfile.ignore();
    }

    inputfile.close();

    ofstream outputfile("MyBinFile.bin", ios::binary);

    if (!outputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }

    outputfile.close();
}

/*�������� ������ � �������� ����*/
void BinaryFile::addBin(const string& FullName, bool EDU) {
    ifstream inputfile("MyBinFile.bin", ios::binary | ios::in);
    vector<Staff> records;

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    cout << "��������� ������" << " � ����:\n";

    ifstream midlefile("MyBinFile.bin", ios::binary | ios::in);
    Staff record;
    while (midlefile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) { //���������� ��������� �� ������ record � ��������� �� ������ (char). 
        records.push_back(record);
    }
    midlefile.close();

    //���� ������ � ����� ������� �������
    int max = records[0].IDNumber; 
    for (int i = 1; i < FILESIZE; i++) {
        if (records[i].IDNumber > max) {
            max = records[i].IDNumber; 
        }
    }

    Staff newRecord;
    newRecord.IDNumber = max + 1;
    strncpy_s(newRecord.FullName, FullName.c_str(), sizeof(newRecord.FullName));
    newRecord.EDU = EDU;

    records.push_back(newRecord);
    inputfile.close();

    ofstream outputfile("MyBinFile.bin", ios::binary | ios::out);

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }

    outputfile.close();
}

//������� ������ � �������� ������ �� �����
void BinaryFile::delBinIndex(int index) {
    vector<Staff> records;
    fstream inputfile("MyBinFile.bin", ios::binary | ios::in);

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    cout << "������� ������ �� ������� " << index << " �� �����:\n";

    Staff record;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) {
        records.push_back(record);
    }
    inputfile.close();

    //��� ����� �������� �� �������(������� � �����), ���� �����������
    if (index < records.size() - 1)
    {
        for (index; index < records.size()-1; index++)
        {
            records[index] = records[index + 1];
        }
        records.pop_back();
    }
    else if(index > records.size() - 1)
    {
        cerr << "������ � ����� ������ �� ����������!" << endl;
        return;
    }

    // ������ ��������� ���� ��� ������ (� ��������� ios::out | ios::trunc)
    fstream outputfile("MyBinFile.bin", ios::binary | ios::out | ios::trunc);

    if (!outputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        return;
    }

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }
    outputfile.close();

    // ������ �������� ������ �����
    if (filesystem::exists("MyBinFile.bin")) {
        try {
            // ��������� ������ ����� ����� ������ �������
            int size = records.size() * sizeof(Staff);
            filesystem::resize_file("MyBinFile.bin", size);
        }
        catch (const filesystem::filesystem_error& e) {
            cerr << "������ ��� ��������� ������� �����: " << e.what() << endl;
        }
    }
    else {
        cerr << "���� �� ����������: " << "MyBinFile.bin" << endl;
    }
}

void BinaryFile::delBinIDNumber(int key){
    vector<Staff> records;
    fstream inputfile("MyBinFile.bin", ios::binary | ios::in);

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    cout << "������� ������ �� ����� " << key << " �� �����:\n";

    Staff record;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(Staff))) {
        records.push_back(record);
    }
    inputfile.close();

    //��� ����� �������� �� �����(IDNumber � �����), ���� �����������
    int counter = 0;
    for (int i = 0; i < FILESIZE; i++)
    {
        if (records[i].IDNumber == key)
        {
            counter = i;
            break;
        }
    }
    for (counter; counter < records.size() - 1; counter++)
    {
        records[counter] = records[counter + 1];
    }
    records.pop_back();

    // ������ ��������� ���� ��� ������ (� ��������� ios::out | ios::trunc)
    fstream outputfile("MyBinFile.bin", ios::binary | ios::out);

    if (!outputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        return;
    }

    for (const Staff& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(Staff));
    }
    outputfile.close();

    // ������ �������� ������ �����
    if (filesystem::exists("MyBinFile.bin")) {
        try {
            // ��������� ������ ����� ����� ������ �������
            int size = records.size() * sizeof(Staff);
            filesystem::resize_file("MyBinFile.bin", size);
        }
        catch (const filesystem::filesystem_error& e) {
            cerr << "������ ��� ��������� ������� �����: " << e.what() << endl;
        }
    }
    else {
        cerr << "���� �� ����������: " << "MyBinFile.bin" << endl;
    }
}

/*��������� ������ ����� �� ��������� ������ ������*/
Staff BinaryFile::findBin(int index) {
    vector<Staff> records;
    ifstream file("MyBinFile.bin", ios::binary);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        return Staff();
    }
    cout << "���� ������ " << index << " � �����:\n";

    Staff record;
    int x = 0;
    const auto start{ std::chrono::steady_clock::now() }; //������ ������ �������
    while (file.read(reinterpret_cast<char*>(&record), sizeof(Staff))) { //���������� ��������� �� ������ record � ��������� �� ������ (char). 
        records.push_back(record); x++;
    }

    file.close();
    for (int i = 0; i < x; i++)
    {
        if (records[i].IDNumber == index)
        {
            const auto end{ std::chrono::steady_clock::now() }; //����� ������ ������� (���������� ���-�������, �������������, ������ �� �����)
            const std::chrono::duration<double> elapsed_seconds{ end - start };
            //check file
                cout << "����� ��������� ������: " << elapsed_seconds << endl;
            return records[i];
        }
    }
    cerr << "������ � ����� ������ �� ����������!" << endl;
    return Staff();
}

/*����� ������ �� ���������� ������ � �����*/
Staff BinaryFile::findBinDir(int address)
{
    vector<Staff> records;
    Staff record;
    ifstream file("MyBinFile.bin", ios::binary);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        return Staff();
    }
    cout << "���� ������ �� ������ " << address << " � �����:\n";

    /*�������� �� �������� ������
    ������ �������� (����� ������ � �����) ����� 105
    ������� ���� ����� �� ������� ��� ������� �� 105 ��� ������ ����� ����� ������������ �� ���-�� ��������,
    �� ����� ����� ������� ��������*/
    if (address % 105 != 0 || address > FILESIZE * 105)
    {
        return record;
    }
    file.seekg(address, ios::beg);

    // ��������� ������
    file.read(reinterpret_cast<char*>(&record), sizeof(Staff)); 
    file.close();
    return record;
}

void BinaryFile::testBinF()
{
    setlocale(LC_ALL, "Russian");
    BinaryFile BF;
    int FILESIZE = 10;
    Staff StaffRecordStruct1;
    //���� ������� FromTextToBin
    BF.FromTextToBin();
    fstream fs1("MyBinFile.bin", ios::in | ios::binary);
    if (!fs1.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // ������� � �������
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

    //���� ������� findBin
    StaffRecordStruct1 = BF.findBin(5);

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    cout << "======================================\n\n";

    //���� ������� addBin
    BF.addBin("Mike_Thompson", 1);
    FILESIZE++;
    fstream fs2("MyBinFile.bin", ios::in | ios::binary);
    if (!fs2.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // ������� � �������
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

    //���� ������� delBin
    BF.delBinIndex(1);
    FILESIZE--;
    fstream fs3("MyBinFile.bin", ios::in | ios::binary);
    if (!fs3.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // ������� � �������
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

    //���� ������� findBinDir
    StaffRecordStruct1 = BF.findBinDir(420);

    //check file
    cout << "file:\n" <<
        "[IDN]:\t\t    FullName|\t  EDU|\t\n" <<
        "======================================\n";

    printf("[%3d]:\t%20s|\t%5d|\n", StaffRecordStruct1.IDNumber, StaffRecordStruct1.FullName, StaffRecordStruct1.EDU);
    cout << "======================================\n\n";
    cout << sizeof(StaffRecordStruct1);
}