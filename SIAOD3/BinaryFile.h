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

	/*�������� ��������� ����� �� ����������*/
	void FromTextToBin();

	/*�������� ������ � �������� ����*/
	void addBin(const string& DepartureLocation, const string& ArrivalDate, const string& ArrivalTime, float DelayHours);

	/*������� ������ � �������� ������ �� �����*/
	void delBin(int key);

	/*��������� ������ ����� �� ��������� ������ ������*/
	FlightRecordStruct findBin(int key);

	/*��������� ������������ �������� � main ����������,
	� ���������� ������� main ����������� � ��������������� ������� ������������� ����� � ������ testBinF.*/
	void testBinF();
};
#endif