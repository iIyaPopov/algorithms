#ifndef CODING	//������ �� ���������� ����������� ���������
#define CODING	//������ �� ���������� ����������� ���������

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std; //cout, cin
const int SIZE = 56;
void FrequencyCounting(FILE* file, int* countSymbols);	//������� �������� ������� ������������� ���� � �����
struct Tree{
	Tree* left;
	Tree* right;
	char symbol;
	int weight;
};
void bubbleSort(Tree* mas, int* counting, int size);	//���������� "���������" �� ��������(�������� ������� �������)
void createTree(Tree* mas, int* countSymbols, int size, int countIndex);	//������� �������� ������, �� �������� ����� ���������� �������
void coding(Tree* root, int* code, int i, char* symbols, int** symbolCode, int* index);	//����� ������� � ��� ����
void printCode(char* symbols, int** symbolCode, int index);
void writingCode(FILE* inFile, FILE* outFile, char* symbols, int** symbolCode, int index, int* countSymbols);	//������ ��������������� ������ � ����
void decoding(FILE* inFile, FILE* outFile, Tree* root, int* countSymbols);	//����������������
//int endByte(int* countSymbols, 
#endif			//������ �� ���������� ����������� ���������