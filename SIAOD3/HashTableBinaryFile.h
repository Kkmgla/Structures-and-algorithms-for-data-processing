#ifndef HASH_TABLE_BINARY_FILE_H
#define HASH_TABLE_BINARY_FILE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HashTable.h"
#include "BinaryFile.h"

using namespace std;
class HashTableBinaryFile : public BinaryFile, public HashTable
{

public:

	//��������� ������ �� ����� � �������� ������� � �������
	HashTableStruct readRecordsFromBinaryFileWriteToHash(FlightRecordStruct flightRecordStruct1, HashTableStruct* hashTableStruct1, int Filesize, int Tablesize);

	//������� ������ �� ������� ��� �������� �������� ����� � �������������� �� �����.
	void delHashBin(int key, HashTableStruct* hashtable, int tablesize, int filesize);

	/*����� ������ � ����� �� �������� �����(����� ���� � ��� - �������,
	�������� ����� ������ � ���� ������ � �����, ��������� ������ ������ � ������ �� �� ������).*/
	void findHashBin(int key, HashTableStruct* hashtable, int tablesize, int filesize);


};
#endif