#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <string>

using namespace std;

struct HashTableStruct {
	int key = -1;
	int filepos = -1;
	bool insert = 0;
};
class HashTable
{

public:

	/*����������� �������*/
	int HASH(int key, int size);

	/*������������ �������*/
	int reHASH(int key, int size);

	/*����� ������������ ���� ��������, ������� � ������������ ����� ������� � ������ testHeshT,
		����������� � ��� ���������� ������� main, ���������, ��� ���������� �����������. */
	void testHashT();	

		/*�������� ���� � �������*/
	void addHash(int key, HashTableStruct* hashtable, int tablesize);

	/*������� ���� �� �������*/
	int delHash(int key, HashTableStruct* hashtable, int tablesize);

	/*����� ���� � �������*/
	bool findHash(int key, HashTableStruct* hashtable, int tablesize);

};
#endif