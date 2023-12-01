#ifndef BINARY_FILE_H
#define BINARY_FILE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct FlightRecordStruct {
	char departureLocation[100] = "";
	int flightNumber = -1;
	char arrivalDate[100] = "";
	char arrivalTime[100] = "";
	float delayHours = -1;
};

class BinaryFile
{
	int FileSIZE = 15;
	vector<FlightRecordStruct> records;

public:

	/*создание двоичного файла из текстового*/
	void FromTextToBin();

	/*добавить запись в двоичный файл*/
	void addBin(const string& DepartureLocation, const string& ArrivalDate, const string& ArrivalTime, float DelayHours);

	/*удалить запись с заданным ключом из файла*/
	void delBin(int key);

	/*прочитать запись файла по заданному номеру записи*/
	FlightRecordStruct findBin(int key);

	/*Выполнить тестирование операций в main приложения,
	и содержание функции main переместить в соответствующую функцию заголовочного файла с именем testBinF.*/
	void testBinF();
};
#endif