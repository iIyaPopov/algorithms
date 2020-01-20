#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int parlament(int** parts, int* people, int* choice_part, int m, int n, int k, int* min, int* min_people){
	if(k == m){
		for(int l = 0; l < n; l++)
			if(choice_part[l] == 0)
				return 0;
		int counter = 0;
		for(int i = 0; i < m; i++)
			if(people[i] == 1)
				counter++;
		if(counter < *min){
			*min = counter;
			for(int i = 0; i < m; i++)
				min_people[i] = people[i];
		}
	}
	else{
		for(int p = 0; p < 2; p++){
			people[k] = p;
			if(p == 1){//берем человека
				for(int j = 0; j < n; j++){
					if(parts[j][k] == 1)
						choice_part[j]++;
				}
				parlament(parts, people, choice_part, m, n, k + 1, min, min_people);
				people[k] = 0;
				for(int j = 0; j < n; j++){
					if(parts[j][k] == 1)
						choice_part[j]--;
				}
			}
			else{//не берем человека
				parlament(parts, people, choice_part, m, n, k + 1, min, min_people);
			}
		}
	}
}
void main(){
	int** parts;
	int* people;
	int* choice_part;
	int* min;
	int* min_people;
	char c;
	int n = 0, m = 0, i, j, min_count;
	FILE* file = fopen("parts.txt", "r");

	//определение размерности матрицы
	while(!feof(file)){
		c = fgetc(file);
		if(c == ' ')
			m++;
		else
			if(c == '\n'){
				n++;
			}
	}
	m = m / n + 1;
	fclose(file);
	min_count = m;
	min = &min_count;

	//выделение памяти
	people = new int[m];
	min_people = new int[m];
	for(i = 0; i < m; i++)
		people[i] = 0;
	choice_part = new int[n];
	for(i = 0; i < n; i++)
		choice_part[i] = 0;
	parts = new int*[n];
	for(i = 0; i < n; i++)
		parts[i] = new int[m];
	
	//считывание матрицы
	file = fopen("parts.txt", "r");
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			fscanf(file, "%d", &parts[i][j]);
	fclose(file);

	//перебор
	parlament(parts, people, choice_part, m, n, 0, min, min_people);
	for(i = 0; i < m; i++)
		if(min_people[i] != 0)
			cout << i << ' ';
	cout << endl;

	//вывод матрицы
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++)
			cout << parts[i][j] << ' ';
		cout << endl;
	}

	//освобождение памяти
	for(i = 0; i < n; i++)
		delete[] parts[i];
	delete parts;
	delete people;
	delete min_people;
	delete choice_part;
}