#include "HashTableBinaryFile.h"
#include "HashTable.h"
#include "BinaryFile.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// Функция для чтения записей из двоичного файла и преобразования их в структуры
HashTableStruct HashTableBinaryFile::readRecordsFromBinaryFileWriteToHash(FlightRecordStruct flightRecordStruct1, HashTableStruct* hashTableStruct1, int FILESIZE, int TABLESIZE) {
	BinaryFile BF;
	HashTable HT;
	
	BF.FromTextToBin();
	fstream fs1("MyBinFile.bin", ios::in | ios::binary);
	if (!fs1.is_open()) {
		cerr << "Failed to open file." << endl;
		exit(1); // Возврат с ошибкой
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


	//create hash table
	fstream fs2("MyBinFile.bin", ios::in | ios::binary);
	if (!fs2.is_open()) {
		cerr << "Failed to open file." << endl;
		exit(1); // Возврат с ошибкой
	}
	fs2.seekg(0);
	for (int i = 0; i < FILESIZE; i++) {
		fs2.read((char*)&flightRecordStruct1, sizeof(FlightRecordStruct));
		int hash = HT.HASH(flightRecordStruct1.flightNumber, TABLESIZE);
		cout << "key:" << flightRecordStruct1.flightNumber << " hash:" << hash << endl;
		while (hashTableStruct1[hash].key != -1) {
			cout << hash << " is busy, rehash: ";
			hash = HT.reHASH(hash, TABLESIZE);
			cout << hash << endl;
		}
		hashTableStruct1[hash].key = flightRecordStruct1.flightNumber;
		hashTableStruct1[hash].filepos = i * sizeof(FlightRecordStruct); //filepos
		hashTableStruct1[hash].insert = 1;
	}
	fs2.close();

	cout << "\nhash table:\n" <<
		"[hash]:\t     key|\t filepos|\n" <<
		"=================================\n";
	for (int i = 0; i < TABLESIZE; i++) {
		if (hashTableStruct1[i].key == -1)
			printf("[%4d]:\n", i);
		else
			printf("[%4d]:\t%8d|\t%8d|\n", i, hashTableStruct1[i].key, hashTableStruct1[i].filepos);
	}
	return *hashTableStruct1;
}

//Удалить запись из таблицы при заданном значении ключа и соответственно из файла.
void HashTableBinaryFile::delHashBin(int key, HashTableStruct* hashtable, int tablesize, int filesize) {
	BinaryFile BF;
	HashTable HT;
	cout << "\nsearching " << key << " in table...\n";
	int hash = HT.HASH(key, tablesize);
	while (hashtable[hash].key != key) {
		if (hashtable[hash].insert == 0) exit (404); //в этой ячейке никогда ничего не было, значит, искать дальше бесполезно, ключа в таблице нет

		hash = reHASH(hash, tablesize); //в противном случае можем продолжить поиск
	}
	int removeposition = hashtable[hash].filepos; //для HashTableBinaryFile
	hashtable[hash].key = -1;
	hashtable[hash].filepos = -1;
	hashtable[hash].insert = 0;
	for (int i = 0; i < tablesize; i++)
		if (hashtable[i].filepos > removeposition)
			hashtable[i].filepos -= sizeof(FlightRecordStruct);

	fstream fs("MyBinFile.bin", ios::in | ios::out | ios::binary);
	FlightRecordStruct tempstruct;
	fs.seekg(0, ios_base::end);
	int size = fs.tellg();
	if (size != removeposition + sizeof(FlightRecordStruct))
		while (removeposition < size) {
			fs.seekp(removeposition + sizeof(FlightRecordStruct));
			fs.read((char*)&tempstruct, sizeof(FlightRecordStruct));
			fs.seekg(-2 * sizeof(FlightRecordStruct), ios_base::cur);
			fs.write((char*)&tempstruct, sizeof(FlightRecordStruct));
			removeposition += sizeof(FlightRecordStruct);
			int y = 0;
		}
	fs.close();
	// Теперь изменяем размер файла
	fs.open("MyBinFile.bin", ios::in | ios::out | ios::binary);
	if (fs.is_open()) {
		try {
			// Вычисляем размер файла после записи записей
			fs.seekg(0, ios_base::end);
			int size = fs.tellg();
			fs.close();
			filesystem::resize_file("MyBinFile.bin", size);
		}
		catch (const filesystem::filesystem_error& e) {
			cerr << "Ошибка при изменении размера файла: " << e.what() << endl;
		}
	}
	else {
		cerr << "Ошибка открытия файла для изменения размера: " << "MyBinFile.bin" << endl;
	}



	FlightRecordStruct flightRecordStruct1;
	filesize--;
	fstream fs1("MyBinFile.bin", ios::in | ios::binary);
	if (!fs1.is_open()) {
		cerr << "Failed to open file." << endl;
		exit(1); // Возврат с ошибкой
	}
	//check file
	cout << "file:\n" <<
		"[flightNumber]:\t   departureLocation|\t  arrivalDate|\t  arrivalTime|\t     delayHours|\n" <<
		"========================================================================================\n";

	for (int i = 0; i < filesize; i++) {
		(fs1.read(reinterpret_cast<char*>(&flightRecordStruct1), sizeof(FlightRecordStruct)));
		printf("[%3d]:\t\t%20s|\t%13s|\t%13s|\t\t%7.1f|\n", flightRecordStruct1.flightNumber, flightRecordStruct1.departureLocation, flightRecordStruct1.arrivalDate, flightRecordStruct1.arrivalTime, flightRecordStruct1.delayHours);
	}
	cout << "========================================================================================\n";
	fs1.close();

	cout << "\nhash table:\n" <<
		"[hash]:\t     key|\t filepos|\n" <<
		"=================================\n";
	for (int i = 0; i < tablesize; i++) {
		if (hashtable[i].key == -1)
			printf("[%4d]:\n", i);
		else
			printf("[%4d]:\t%8d|\t%8d|\n", i, hashtable[i].key, hashtable[i].filepos);
	}
};

/*Найти запись в файле по значению ключа(найти ключ в хеш - таблице,
	получить номер записи с этим ключом в файле, выполнить прямой доступ к записи по ее номеру).*/
void HashTableBinaryFile::findHashBin(int key, HashTableStruct* hashtable, int TABLESIZE, int FILESIZE) {
	BinaryFile BF;
	HashTable HT;
	if (key > TABLESIZE - 1 || key < 0)
	{
		cerr << "Key not found." << endl;
		exit(404);
	}
	int keytofind = key;
	cout << "\nsearching " << keytofind << " in table...\n";
	const auto start{ std::chrono::steady_clock::now() }; //начало замера времени
	int hash = HT.HASH(keytofind, TABLESIZE);
	while (hashtable[hash].key != keytofind) {
		cout << hash << " is wrong, rehash: ";
		hash = reHASH(hash, TABLESIZE);
		cout << hash << endl;
	}
	fstream fs("MyBinFile.bin", ios::in | ios::binary);
	if (!fs.is_open()) {
		cerr << "Failed to open file." << endl;
		exit(1); // Возврат с ошибкой
	}
	FlightRecordStruct flightRecordStruct1;

	// Проверяем, что ключ был найден
	if (hashtable[hash].key == keytofind) {
		fs.seekg(hashtable[hash].filepos);
		fs.read(reinterpret_cast<char*>(&flightRecordStruct1), sizeof(FlightRecordStruct));
	}
	else {
		cerr << "Key not found." << endl;
		exit(404);
		// Можно возвращать какой-то специальный флаг или бросать исключение, в зависимости от вашей логики.
	}
	const auto end{ std::chrono::steady_clock::now() }; //конец замера времени (вычисление хеш-функции, рехеширование, чтение из файла)
	const std::chrono::duration<double> elapsed_seconds{ end - start };
	fs.close(); // Не забываем закрыть файл
	//check file
	cout << "Время сортировки: " << elapsed_seconds << endl;
	cout << "file:\n" <<
		"[flightNumber]:\t   departureLocation|\t  arrivalDate|\t  arrivalTime|\t     delayHours|\n" <<
		"========================================================================================\n";

	printf("[%3d]:\t\t%20s|\t%13s|\t%13s|\t\t%7.1f|\n", flightRecordStruct1.flightNumber, flightRecordStruct1.departureLocation, flightRecordStruct1.arrivalDate, flightRecordStruct1.arrivalTime, flightRecordStruct1.delayHours);
}