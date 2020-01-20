#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;
int min_3x(int x1, int x2, int x3){//минимум из трех чисел
	if(x1 < x2){
		if(x1 < x3)
			return x1;
		else
			return x3;
	}
	else{
		if(x2 < x3)
			return x2;
		else
			return x3;
	}
}
void main(){
	FILE* in_file = fopen("matrix.txt", "r");
	char c;
	int num;
	int m = 0, n = 0, i, j;
	int** matrix;
	int** table;

	//подсчет размера матрицы
	while(!feof(in_file)){
		c = fgetc(in_file);
		if(c == ' ')
			m++;
		else
			if(c == '\n'){
				n++;
			}
	}
	m = m / n + 1;
	fclose(in_file);
	cout << n << ' ' << m << endl;
	//выделение памяти
	matrix = new int*[n];
	for(i = 0; i < n; i++)
		matrix[i] = new int[m];
	table = new int*[n+1];
	for(i = 0; i < n + 1; i++){
		table[i] = new int[m+1];
		for(j = 0; j < m + 1; j++)
			table[i][j] = 0;
	}

	//считывание матрицы
	in_file = fopen("matrix.txt", "r");
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			fscanf(in_file, "%d", &matrix[i][j]);
	fclose(in_file);

	//вывод на экран
	cout << "matrix:" << endl;
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++)
			cout << matrix[i][j];
		cout << endl;
	}

	//изначальное заполнение динамической таблицы
	for(i = 0; i < m; i++)//нижняя строка
		table[n][i] = 0;
	for(i = 0; i < n + 1; i++)//правый столбец
		table[i][m] = 0;
	cout << endl << "table:" << endl;

	//заполнение динамической таблицы
	for(i = n - 1; i >= 0; i--){
		for(j = m - 1; j >= 0; j--){
			if(matrix[i][j] == 1)
				table[i][j] = 0;
			else
				table[i][j] = min_3x(table[i+1][j], table[i+1][j+1], table[i][j+1]) + 1; 
		}
	}

	//вывод динамической таблицы
	for(i = 0; i < n + 1; i++){
		for(j = 0; j < m + 1; j++)
			cout << table[i][j];
		cout << endl;
	}

	//очистка выделенной памяти
	for(i = 0; i < n; i++)
		delete[] matrix[i];
	delete matrix;
	for(i = 0; i < n + 1; i++)
		delete[] table[i];
	delete table;
}