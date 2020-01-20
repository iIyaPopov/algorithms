#include <stdio.h>
#include <iostream>
using namespace std;
int num = 0;
struct visited{
	int vis;
	int number;
	int L_i;
	int* soon;
	int point;
};
int min_3x(int x1, int x2, int x3){
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
void dfs(int** matr, visited* vert, int v, int n){
	int k = 0;
	vert[v].vis = 1;
	vert[v].number = num;
	for(int i = 0; i < n; i++){
		if(matr[i][v] == 1 && vert[i].vis == 0){
			vert[v].soon[k++] = i;
			matr[v][i] = 0;//�������� ���������� ����� ��� ������
			num++;
			dfs(matr, vert, i, n);
		}
	}
	for(int i = 0; i < v; i++){//�������� ������ ������� �������� ������� ���������
		if(matr[i][v] == 1){
			vert[v].L_i = i;
			return;
		}
	}
	vert[v].L_i = vert[v].number;

}
void main(){
	FILE* file = fopen("matr.txt", "r");
	const int n = 10;
	int i, j;
	int** matr;
	visited* vert;
	vert = new visited[n];
	for(i = 0; i < n; i++)
		vert[i].soon = new int[n];
	matr = new int*[n];
	
	//���������� ������� ���������
	for(i = 0; i < n; i++){
		vert[i].vis = 0;
		matr[i] = new int[n];
		for(j = 0; j < n; j++)
			fscanf(file, "%d", &matr[i][j]);
	}

	//����� � �������
	for(i = 0; i < n; i++){
		if(vert[i].vis == 0){
			dfs(matr, vert, i, n);
		}
	}
	cout << endl;

	for(i = n - 1; i >= 0; i--){
		for(j = 0; j < n; j++){
			if(vert[i].soon[j] >= 0 && vert[i].soon[j] < n){
				vert[i].L_i = min(vert[i].L_i, vert[vert[i].soon[j]].L_i); 
				if(vert[vert[i].soon[j]].L_i >= vert[i].number)
					vert[i].point = 1;
			}
		}
	}

	//����� �����������
	for(i = 0; i < n; i++)
		cout << vert[i].number + 1 << ' ';
	cout << endl;
	for(i = 0; i < n; i++)
		cout << vert[i].L_i + 1 << ' ';
	cout << endl << endl;

	//����� ������� ���������
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++)
			cout << matr[i][j] << ' ';
		cout << endl;
	}

	cout << endl;

	//����� ������� ������ ������� ��������� ������
	for(i = 0; i < n; i++){
		cout << i+1 << ':' << ' ';
		for(j = 0; j < n; j++)
			if(vert[i].soon[j] >= 0 && vert[i].soon[j] < n)
				cout << vert[i].soon[j]+1 << ' ';
		if(vert[i].point == 1)
			cout << " - point of ..." << endl;
		else
			cout << endl;
	}
	cout << endl;

	//������� ������
	for(i = 0; i < n; i++)
		delete vert[i].soon;
	for(i = 0; i < n; i++)
		delete[] matr[i];
	delete matr;
	delete vert;
	fclose(file);
}