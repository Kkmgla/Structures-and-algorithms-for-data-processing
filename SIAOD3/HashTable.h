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

	/*хеширование таблицы*/
	int HASH(int key, int size);

	/*рехешировать таблицу*/
	int reHASH(int key, int size);

	/*После тестирования всех операций, создать в заголовочном файле функцию с именем testHeshT,
		переместить в нее содержание функции main, проверить, что приложение выполняется. */
	void testHashT();	

		/*вставить ключ в таблицу*/
	void addHash(int key, HashTableStruct* hashtable, int tablesize);

	/*удалить ключ из таблицы*/
	int delHash(int key, HashTableStruct* hashtable, int tablesize);

	/*найти ключ в таблице*/
	bool findHash(int key, HashTableStruct* hashtable, int tablesize);

};
#endif