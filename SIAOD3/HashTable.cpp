#include "HashTable.h"
#include "BinaryFile.h"
#include <string>
using namespace std;

	/*хеширование таблицы*/
	int HashTable::HASH(int key, int tableSize) {
		int hash = key;
		const double A = 0.71828182846; // дробная часть числа Эйлера
		double fractionalPart = A * hash - floor(A * hash); // Взятие дробной части
		hash = static_cast<int>(tableSize * fractionalPart);
		return hash;
	};

	/*рехешировать таблицу*/
	int HashTable::reHASH(int hashed, int tableSize) {
		return ((hashed + 1) % tableSize); // Смещение на 1
	};

	/*вставить ключ в таблицу*/
	void HashTable::addHash(int Key, HashTableStruct* hashtable, int tablesize) {
		cout << "\nadding " << Key << " in table...\n";
		int hash = HASH(Key, tablesize);
		while (hashtable[hash].insert != 0) {
			cout << hash << " is wrong, rehash: ";
			hash = reHASH(hash, tablesize);
			cout << hash << endl;
		}
		hashtable[hash].key = Key;
		hashtable[hash].insert = 1;
		hashtable[hash].filepos = Key * sizeof(FlightRecordStruct);
	};

	/*удалить ключ из таблицы*/
	int HashTable::delHash(int key, HashTableStruct* hashtable, int tablesize) {
		int hash = HASH(key, tablesize);
		while (hashtable[hash].key != key) {
			if (hashtable[hash].insert == 0) return 404; //в этой ячейке никогда ничего не было, значит, искать дальше бесполезно, ключа в таблице нет

			hash = reHASH(hash, tablesize); //в противном случае можем продолжить поиск
		}
		int removeposition = hashtable[hash].filepos; //для HashTableBinaryFile
		hashtable[hash].key = -1;
		hashtable[hash].filepos = -1;
		hashtable[hash].insert = 0;
		for (int i = 0; i < tablesize; i++)
			if (hashtable[i].filepos > removeposition)
				hashtable[i].filepos -= sizeof(FlightRecordStruct);
	};

	/*найти ключ в таблице*/
	bool HashTable::findHash(int key, HashTableStruct* hashtable, int tablesize) {
		cout << "\nsearching " << key << " in table...\n";
		if (key > tablesize-1)
		{
			cerr << "Элемента с таким ключом не существует" << endl; 
			exit(1);
		}
		int hash = HASH(key, tablesize);
		while (hashtable[hash].key != key) {
			cout << hash << " is wrong, rehash: ";
			hash = reHASH(hash, tablesize);
			cout << hash << endl;
		}
		cout << "\nhash table:\n" <<
			"[hash]:\t     key|\t filepos|\n" <<
			"=================================\n";
		printf("[%4d]:\t%8d|\t%8d|\n", hash, hashtable[hash].key, hashtable[hash].filepos);

		return 1;
	};

	/*После тестирования всех операций, создать в заголовочном файле функцию с именем testHeshT,
			переместить в нее содержание функции main, проверить, что приложение выполняется. */
	void HashTable::testHashT() {
		setlocale(LC_ALL, "Russian");
		BinaryFile BF;
		HashTable HT;
		FlightRecordStruct flightRecordStruct1;
		int TABLESIZE = 15;
		HashTableStruct* hashTableStruct1 = new HashTableStruct[TABLESIZE];
		int FILESIZE = 9;

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

		//Тест функции findHash
		HT.findHash(8, hashTableStruct1, TABLESIZE);

		//Тест функции addHash
		HT.addHash(11, hashTableStruct1, TABLESIZE);

		cout << "\nhash table:\n" <<
			"[hash]:\t     key|\t filepos|\n" <<
			"=================================\n";
		for (int i = 0; i < TABLESIZE; i++) {
			if (hashTableStruct1[i].key == -1)
				printf("[%4d]:\n", i);
			else
				printf("[%4d]:\t%8d|\t%8d|\n", i, hashTableStruct1[i].key, hashTableStruct1[i].filepos);
		}

		//Тест функции delHash
		HT.delHash(11, hashTableStruct1, TABLESIZE);

		cout << "\nhash table:\n" <<
			"[hash]:\t     key|\t filepos|\n" <<
			"=================================\n";
		for (int i = 0; i < TABLESIZE; i++) {
			if (hashTableStruct1[i].key == -1)
				printf("[%4d]:\n", i);
			else
				printf("[%4d]:\t%8d|\t%8d|\n", i, hashTableStruct1[i].key, hashTableStruct1[i].filepos);
		}
	};