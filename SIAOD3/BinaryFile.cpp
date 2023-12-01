#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "BinaryFile.h"
#include "HashTable.h"

using namespace std;

/*�������� ��������� ����� �� ����������*/
void BinaryFile::FromTextToBin() {
    vector<FlightRecordStruct> records;
    ifstream inputfile("MyTextFile.txt");

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyTextFile.txt" << endl;
        exit(1);
    }

    FlightRecordStruct record;
    while (inputfile >> record.departureLocation >> record.flightNumber >> record.arrivalDate >> record.arrivalTime >> record.delayHours) {
        records.push_back(record);
        inputfile.ignore();
    }

    inputfile.close();

    ofstream outputfile("MyBinFile.bin", ios::binary);

    if (!outputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }

    for (const FlightRecordStruct& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(FlightRecordStruct));
    }

    outputfile.close();
}

/*�������� ������ � �������� ����*/
void BinaryFile::addBin(const string& DepartureLocation, const string& ArrivalDate, const string& ArrivalTime, float DelayHours) {
    ifstream inputfile("MyBinFile.bin", ios::binary | ios::in);
    vector<FlightRecordStruct> records;

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    FlightRecordStruct lastRecord;

    // ���������� ��������� � ����� �����
    inputfile.seekg(0, ios::end);

    // ���������� ��������� � ������ ��������� ������
    inputfile.seekg(-static_cast<int>(sizeof(FlightRecordStruct)), ios::end);

    // ���������� ��������� ������
    inputfile.read(reinterpret_cast<char*>(&lastRecord), sizeof(FlightRecordStruct));

    ifstream midlefile("MyBinFile.bin", ios::binary | ios::in);
    FlightRecordStruct record;
    while (midlefile.read(reinterpret_cast<char*>(&record), sizeof(FlightRecordStruct))) { //���������� ��������� �� ������ record � ��������� �� ������ (char). 
        records.push_back(record);
    }
    midlefile.close();

    FlightRecordStruct newRecord;
    newRecord.flightNumber = lastRecord.flightNumber + 1;
    strncpy_s(newRecord.departureLocation, DepartureLocation.c_str(), sizeof(newRecord.departureLocation));
    strncpy_s(newRecord.arrivalDate, ArrivalDate.c_str(), sizeof(newRecord.arrivalDate));
    strncpy_s(newRecord.arrivalTime, ArrivalTime.c_str(), sizeof(newRecord.arrivalTime));
    newRecord.delayHours = DelayHours;

    records.push_back(newRecord);
    inputfile.close();

    ofstream outputfile("MyBinFile.bin", ios::binary | ios::out);

    for(const FlightRecordStruct & record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(FlightRecordStruct));
    }

    outputfile.close();
}

//������� ������ � �������� ������ �� �����
void BinaryFile::delBin(int index) {
    vector<FlightRecordStruct> records;
    fstream inputfile("MyBinFile.bin", ios::binary | ios::in);

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }

    FlightRecordStruct record;
    while (inputfile.read(reinterpret_cast<char*>(&record), sizeof(FlightRecordStruct))) {
        records.push_back(record);
    }

    inputfile.close();

    if (index < records.size() - 1) {
        records[index] = records[index + 1];
        index++;
    }
    else if(index > records.size() - 1) {
        cerr << "������ � ����� ������ �� ����������!" << endl;
        return;
    }
    records.pop_back();

    // ������ ��������� ���� ��� ������ (� ��������� ios::out | ios::trunc)
    fstream outputfile("MyBinFile.bin", ios::binary | ios::out | ios::trunc);

    if (!outputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        return;
    }

    for (const FlightRecordStruct& record : records) {
        outputfile.write(reinterpret_cast<const char*>(&record), sizeof(FlightRecordStruct));
    }
    outputfile.close();

    // ������ �������� ������ �����
    if (filesystem::exists("MyBinFile.bin")) {
        try {
            // ��������� ������ ����� ����� ������ �������
            int size = records.size() * sizeof(FlightRecordStruct);
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
FlightRecordStruct BinaryFile::findBin(int index) {
    vector<FlightRecordStruct> records;
    ifstream file("MyBinFile.bin", ios::binary);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        return FlightRecordStruct();
    }

    FlightRecordStruct record;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(FlightRecordStruct))) { //���������� ��������� �� ������ record � ��������� �� ������ (char). 
        records.push_back(record);
    }

    file.close();

    if (index < records.size()) {
        return records[index - 1];
    }
    else {
        cerr << "������ � ����� ������ �� ����������!" << endl;
        return FlightRecordStruct();
    }
}

/*��������� ������������ �������� � main ����������,
� ���������� ������� main ����������� � ��������������� ������� ������������� ����� � ������ testBinF.*/
void BinaryFile::testBinF() {
    setlocale(LC_ALL, "Russian");
    BinaryFile BF;
    HashTable HT;
    FlightRecordStruct flightRecordStruct1;
    int FILESIZE = 9;

    //���� ������� FromTextToBin
    BF.FromTextToBin();
    fstream fs1("MyBinFile.bin", ios::in | ios::binary);
    if (!fs1.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // ������� � �������
    }
    //check file
    cout << "file:\n" <<
        "[flightNumber]:\t   departureLocation|\t  arrivalDate|\t  arrivalTime|\t     delayHours|\n" <<
        "========================================================================================\n";

    for (int i = 0; i < FILESIZE; i++) {
        (fs1.read(reinterpret_cast<char*>(&flightRecordStruct1), sizeof(FlightRecordStruct)));
        printf("[%3d]:\t\t%20s|\t%13s|\t%13s|\t\t%7.1f|\n", flightRecordStruct1.flightNumber, flightRecordStruct1.departureLocation, flightRecordStruct1.arrivalDate, flightRecordStruct1.arrivalTime, flightRecordStruct1.delayHours);
    }
    cout << "========================================================================================\n";
    fs1.close();


    //���� ������� addBin
    BF.addBin("Colorado", "2023-12-30", "04:00", 1.2);
    FILESIZE++;
    fstream fs2("MyBinFile.bin", ios::in | ios::binary);
    if (!fs2.is_open()) {
        cerr << "Failed to open file." << endl;
        exit (1); // ������� � �������
    }

    //check file
    cout << "file:\n" <<
        "[flightNumber]:\t   departureLocation|\t  arrivalDate|\t  arrivalTime|\t     delayHours|\n" <<
        "========================================================================================\n";


    for (int i = 0; i < FILESIZE; i++) {
        (fs2.read(reinterpret_cast<char*>(&flightRecordStruct1), sizeof(FlightRecordStruct)));
        printf("[%3d]:\t\t%20s|\t%13s|\t%13s|\t\t%7.1f|\n", flightRecordStruct1.flightNumber, flightRecordStruct1.departureLocation, flightRecordStruct1.arrivalDate, flightRecordStruct1.arrivalTime, flightRecordStruct1.delayHours);
    }
    cout << "========================================================================================\n";
    fs2.close();

    //���� ������� delBin
    BF.delBin(9);
    FILESIZE--;
    fstream fs3("MyBinFile.bin", ios::in | ios::binary);
    if (!fs3.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1); // ������� � �������
    }

    //check file
    cout << "file:\n" <<
        "[flightNumber]:\t   departureLocation|\t  arrivalDate|\t  arrivalTime|\t     delayHours|\n" <<
        "========================================================================================\n";

    for (int i = 0; i < FILESIZE; i++) {
        (fs3.read(reinterpret_cast<char*>(&flightRecordStruct1), sizeof(FlightRecordStruct)));
        printf("[%3d]:\t%20s|\t\t%11s|\t%13s|\t\t%7.1f|\n", flightRecordStruct1.flightNumber, flightRecordStruct1.departureLocation, flightRecordStruct1.arrivalDate, flightRecordStruct1.arrivalTime, flightRecordStruct1.delayHours);
    }
    cout << "========================================================================================\n";
    fs3.close();

    //���� ������� delBin
    flightRecordStruct1 = BF.findBin(5);

    //check file
    cout << "file:\n" <<
        "[flightNumber]:\t   departureLocation|\t  arrivalDate|\t  arrivalTime|\t     delayHours|\n" <<
        "========================================================================================\n";

    printf("[%3d]:\t\t%20s|\t%13s|\t%13s|\t\t%7.1f|\n", flightRecordStruct1.flightNumber, flightRecordStruct1.departureLocation, flightRecordStruct1.arrivalDate, flightRecordStruct1.arrivalTime, flightRecordStruct1.delayHours);
};