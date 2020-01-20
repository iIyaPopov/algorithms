#ifndef CODING	//защита от повторного подключения библиотек
#define CODING	//защита от повторного подключения библиотек

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std; //cout, cin
const int SIZE = 56;
void FrequencyCounting(FILE* file, int* countSymbols);	//функция подсчета частоты встречаемости букв в файле
struct Tree{
	Tree* left;
	Tree* right;
	char symbol;
	int weight;
};
void bubbleSort(Tree* mas, int* counting, int size);	//сортировка "пузырьком" по убыванию(наиболее простой вариант)
void createTree(Tree* mas, int* countSymbols, int size, int countIndex);	//функция создания дерева, по которому будем кодировать символы
void coding(Tree* root, int* code, int i, char* symbols, int** symbolCode, int* index);	//вывод символа и его кода
void printCode(char* symbols, int** symbolCode, int index);
void writingCode(FILE* inFile, FILE* outFile, char* symbols, int** symbolCode, int index, int* countSymbols);	//запись закодированного текста в файл
void decoding(FILE* inFile, FILE* outFile, Tree* root, int* countSymbols);	//разархивирование
//int endByte(int* countSymbols, 
#endif			//защита от повторного подключения библиотек