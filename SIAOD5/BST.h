#ifndef BST_H
#define BST_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
struct node {
	int key = -1;
	int filepos = -1;
	node* left = NULL;
	node* right = NULL;

	node(int value = -1, int filepos = -1, node* left = NULL, node* right = NULL)
		: key(value), filepos(filepos), left(left), right(right){}
};
class BST
{
	//��������������� ������
	void insert(int value, int filepos);
	//node* insertRec(node* root, int value, int filepos);
	node* findMinNode(node* n);
public:
	node* root = NULL;
	//���������� ������ �� ������������� �����
	node * CreateBST();

	//���������� �������� � ������
	node* addBST(node*root, int value, int filepos);

	//����� �� ����� � ������
	int findBST(node* root, int value);

	//�������� �������� �� ������
	node * delBST(node * root, int key);

	//����� ������ � ����� ������
	void treeBST(node* n, int indent = 0);

	void testBST();
};
#endif