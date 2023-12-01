#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include "HashTable.h"
#include "BinaryFile.h"
#include "HashTableBinaryFile.h"

using namespace std;

void SimpleSearch(FlightRecordStruct flightRecordStruct1, int index) {
    fstream inputfile("MyBinFile.bin", ios::binary | ios::in);

    if (!inputfile.is_open()) {
        cerr << "������ �������� �����: " << "MyBinFile.bin" << endl;
        exit(1);
    }
    const auto start{ std::chrono::steady_clock::now() }; //������ ������ �������
    while (inputfile.read(reinterpret_cast<char*>(&flightRecordStruct1), sizeof(FlightRecordStruct))) {
        if (flightRecordStruct1.flightNumber == index) {
            break;
        }
    }
    const auto end{ std::chrono::steady_clock::now() }; //����� ������ ������� (���������� ���-�������, �������������, ������ �� �����)
    const std::chrono::duration<double> elapsed_seconds{ end - start };
    //check file
    cout << "����� ��������� ������: " << elapsed_seconds << endl;
    cout << "file:\n" <<
        "[flightNumber]:\t   departureLocation|\t  arrivalDate|\t  arrivalTime|\t     delayHours|\n" <<
        "========================================================================================\n";

    printf("[%3d]:\t\t%20s|\t%13s|\t%13s|\t\t%7.1f|\n", flightRecordStruct1.flightNumber, flightRecordStruct1.departureLocation, flightRecordStruct1.arrivalDate, flightRecordStruct1.arrivalTime, flightRecordStruct1.delayHours);
    cout << "========================================================================================\n";
    inputfile.close();
}

int main() {
	setlocale(LC_ALL, "Russian");
	BinaryFile BF;
	HashTable HT;
	HashTableBinaryFile HTBF;
	int FILESIZE = 501;
	FlightRecordStruct flightRecordStruct1;
	int TABLESIZE = 501;
	HashTableStruct* hashTableStruct1 = new HashTableStruct[TABLESIZE];

    //��������� ������ �� ����� � �������� ������� � �������
    *hashTableStruct1 = HTBF.readRecordsFromBinaryFileWriteToHash(flightRecordStruct1, hashTableStruct1, FILESIZE, TABLESIZE);

    SimpleSearch(flightRecordStruct1, 500);
    while (1) {
        cout << "����:\n" <<
            "1. ������� ������ �� ������� ��� �������� �������� ����� � �������������� �� �����.\n" <<
            "2. ����� ������ � ����� �� �������� �����(����� ���� � ��� - �������, �������� ����� ������ � ���� ������ � �����, ��������� ������ ������ � ������ �� �� ������).\n";
        int var;
        string input;
        int opt;
        bool isValid = true;
        cin >> var;
        switch (var) {

        case 1:
            cout << "������� ����, �� �������� ����� ������� ������ �� ��������� ����� � ���-�������: ";
            cin >> input;
            // �������� ������� ������ ����
            for (char c : input) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                opt = stoi(input); // �������������� ������ � �����
                if (opt > TABLESIZE - 1 || opt <= 0) {
                    cerr << "������������ ����. ����������, ������� ���������� ����." << endl;
                    continue; // ���������� ���� while � ��������� ���� �����
                }
            }
            else {
                cout << "������������ ����. ������� ������ �����." << endl;
                break;
            }

			//������� ������ �� ������� ��� �������� �������� ����� � �������������� �� �����.
			HTBF.delHashBin(opt, hashTableStruct1, TABLESIZE, FILESIZE);
            break;

        case 2:
            cout << "������� ����, �� �������� ����� �������� ������: ";
            cin >> input;
            for (char c : input) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                opt = stoi(input); // �������������� ������ � �����
                if (opt > TABLESIZE - 1 || opt <= 0) {
                    cerr << "������������ ����. ����������, ������� ���������� ����." << endl;
                    continue; // ���������� ���� while � ��������� ���� �����
                }
            }
            else {
                cout << "������������ ����. ������� ������ �����." << endl;
                break;
            }

            /*����� ������ � ����� �� �������� �����(����� ���� � ��� - �������,
            �������� ����� ������ � ���� ������ � �����, ��������� ������ ������ � ������ �� �� ������).*/
            HTBF.findHashBin(opt, hashTableStruct1, TABLESIZE, FILESIZE);
            break;

        default:
            break;
        }
    }
}