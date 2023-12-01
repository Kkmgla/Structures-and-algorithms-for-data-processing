#ifndef BINARY_FILE_H
#define BINARY_FILE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#pragma pack(1)
struct Staff {
	int IDNumber = -1;
	char FullName[100] = "N/A";
	bool EDU = 0;
};

class BinaryFile
{
	vector<Staff> records;

public:
	int FILESIZE = 500;
	/* создание двоичного файла записей фиксированной длины
	из заранее подготовленных данных в текстовом файле*/
	void FromTextToBin();

	/*добавить запись в двоичный файл*/
	void addBin(const string& FullName, bool EDU);

	/*удалить запись с заданным индексом из файла*/
	void delBinIndex(int index);


	void delBinIDNumber(int key);

	/*поиск и вывод записи в файле с помощью линейного поиска*/
	Staff findBin(int key);

	/*вывод записи по известному адресу в файле*/
	Staff findBinDir(int address);
	
	void testBinF();
};
#endif