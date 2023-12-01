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

	//Прочитать запись из файла и вставить элемент в таблицу
	HashTableStruct readRecordsFromBinaryFileWriteToHash(FlightRecordStruct flightRecordStruct1, HashTableStruct* hashTableStruct1, int Filesize, int Tablesize);

	//Удалить запись из таблицы при заданном значении ключа и соответственно из файла.
	void delHashBin(int key, HashTableStruct* hashtable, int tablesize, int filesize);

	/*Найти запись в файле по значению ключа(найти ключ в хеш - таблице,
	получить номер записи с этим ключом в файле, выполнить прямой доступ к записи по ее номеру).*/
	void findHashBin(int key, HashTableStruct* hashtable, int tablesize, int filesize);


};
#endif