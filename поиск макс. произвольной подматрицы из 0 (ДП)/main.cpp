#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
void submatrix(int** table, int n, int m){
	int i, j, left, right, k, max_s = 0, max_left_x, max_left_y, max_right_x, max_right_y, s;
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			left = j;
			right = j;
			if(table[i][j] != 0){
				for(k = j; k >= 0; k--){
					if(table[i][k] >= table[i][j])
						left = k;
					else
						break;
				}
				for(k = j; k < m; k++){
					if(table[i][k] >= table[i][j])
						right = k;
					else
						break;
				}
			}
			s = (right - left + 1) * table[i][j];
			cout << s << ' ';
			if(s > max_s){
				max_s = s;
				max_left_x = i;
				max_left_y = left;
				max_right_x = i - table[i][j] + 1;
				max_right_y = right;
			}
		}
		cout << endl;
	}
	cout << max_left_x << ' ' << max_left_y << endl << max_right_x << ' ' << max_right_y << endl;
}
int colunm(int** matrix, int x, int y){
	int i = x - 1, j = y, result = 1;
	while(1){
		if(i >= 0){
			if(matrix[i][j] == 0){
				result++;
				i--;
			}
			else
				break;
		}
		else
			break;
	}
	return result;
}
void main(){
	FILE* in_file = fopen("matrix.txt", "r");
	char c;
	int m = 0, n = 0, i, j, num;
	int** matrix;
	int** table;

	//определение размерности матрицы
	while(!feof(in_file)){
		c = fgetc(in_file);
		if(c == '\n'){
			n++;
		}
		if(c == ' '){
			m++;
		}
	}
	fclose(in_file);
	m = m / n + 1;

	//выделение памяти
	matrix = new int*[n];
	table = new int*[n];
	for(i = 0; i < n; i++){
		matrix[i] = new int[m];
		table[i] = new int[m];
		for(j = 0; j < m; j++)
			table[i][j] = 0;
	}

	//считывание матрицы
	in_file = fopen("matrix.txt", "r");
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			fscanf(in_file, "%d", &matrix[i][j]);
	fclose(in_file);

	//заполнение динамической таблицы
	//верхняя строка
	for(j = 0; j < m; j++)
		if(matrix[0][j] == 0)
			table[0][j] = 1;
	//остальные строки
	for(i = 1; i < n; i++){
		for(j = 0; j < m; j++){
			if(matrix[i][j] == 0){
				table[i][j] = colunm(matrix, i, j);
			}
		}
	}

	//вывод результатов
	cout << "matrix:" << endl;
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++)
			cout << matrix[i][j];
		cout << endl;
	}
	cout << endl << "table:" << endl;
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++)
			cout << table[i][j];
		cout << endl;
	}

	cout << endl;
	submatrix(table, n, m);

	//освобождение выделенной памяти
	for(i = 0; i < n; i++){
		delete[] matrix[i];
		delete[] table[i];
	}
	delete matrix;
	delete table;
}