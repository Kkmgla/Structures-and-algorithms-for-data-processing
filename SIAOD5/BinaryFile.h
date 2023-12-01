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
	/* �������� ��������� ����� ������� ������������� �����
	�� ������� �������������� ������ � ��������� �����*/
	void FromTextToBin();

	/*�������� ������ � �������� ����*/
	void addBin(const string& FullName, bool EDU);

	/*������� ������ � �������� �������� �� �����*/
	void delBinIndex(int index);


	void delBinIDNumber(int key);

	/*����� � ����� ������ � ����� � ������� ��������� ������*/
	Staff findBin(int key);

	/*����� ������ �� ���������� ������ � �����*/
	Staff findBinDir(int address);
	
	void testBinF();
};
#endif