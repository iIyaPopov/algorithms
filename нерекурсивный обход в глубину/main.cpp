#include <iostream>
#include <stdio.h>
#include <stack>
using namespace std;
void dfs_iterative(int v, int* visited, int** m, int n){
	stack <int> s;
	int i;
	visited[v] = 1;
    s.push(v);
    while (!s.empty()){
		v = s.top();
		for(i = 0; i < n; i++){
			if(m[v][i] && !visited[i]){
				cout << v << '-' << i << endl;
				visited[i] = 1;
				s.push(i);
				break;
			}
		}
		if(i == n)
			s.pop();
	}
}
void main(){
	const char matr[] = "matr1.txt";
	FILE* in_file = fopen(matr, "r");
	int** m;
	int* visited;
	char c;
	int n = 0, i, j;

	//определение количества вершин
	while(!feof(in_file)){
		c = fgetc(in_file);
		if(c == ' ')
			n++;
		if(c == '\n'){
			n++;
			break;
		}
	}
	fclose(in_file);
	
	//выделение памяти
	m = new int*[n];
	for(i = 0; i < n; i++)
		m[i] = new int[n];
	visited = new int[n];
	for(i = 0; i < n; i++)
		visited[i] = 0;

	//считывание матрицы смежности
	in_file = fopen(matr, "r");
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			fscanf(in_file, "%d", &m[i][j]);
	fclose(in_file);

	//вывод матрицы смежности
	cout << "m[]:" << endl;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++)
			cout << m[i][j] << ' ';
		cout << endl;
	}

	//работа алгоритма
	for(i = 0; i < n-1; i++){
		if(visited[i] == 0){
			cout << "From " << i  << ':' << endl;
			dfs_iterative(i, visited, m, n);
			cout << endl;
		}
	}

	//освобождение памяти
	for(i = 0; i < n; i++)
		delete[] m[i];
	delete m;
	delete visited;
}