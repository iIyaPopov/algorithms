#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;	//��� cin � cout
			//matr - ��������� �� ������� ���������
			//source - ��������� �����
			//distance - ������� ���������� ���������� (��� way)
			//min_distance - ����������� ��������� ���������� (��� min_way)
			//n - ���-�� ����� (�������)
			//m - ���-�� ���������� ����� (���������� n = m)
			//current - ������� ����� (�����)
			//visited - ��������� �� ������, ��� �������, �������� ����� (�����) ��� ���
			//way - ������� ����
			//min_way - ����������� ���� (���, ������� ��� ����������)
void solve(int** matr, int source, int distance, int* min_distance, int n, int m, int current, int* visited, int* way, int* min_way){		//������� ������� ������ (���������� ������ ��� ����� ���������� �����) - ��������
	if(m == 0){									//���� �� �������� ������������ �����
		distance += matr[current][source];		//��������� �� ������ ������ �������
		if(distance < *min_distance){			//�������� ������� ���������� � �����������
			*min_distance = distance;			//�������� �������
			min_way[0] = min_way[n] = source;	//������ ����, ���� ������
			for(int i = 1; i < n; i++)			//����������� ����������� ����
				min_way[i] = way[i];
		}
	}
	else{
		for(int i = 0; i < n; i++){					//������� ���� �����
			if(!visited[i] && matr[current][i]){	//���� �� �������� � ���� ����
				visited[i] = 1;						//��������, ��� ��������
				distance += matr[current][i];		//��������� ����
				way[n-m] = i;						//��������� � ��������
				solve(matr, source, distance, min_distance, n, m-1, i, visited, way, min_way);	//���� ������ ����� ��������� �����
				way[n-m] = -1;						//������� �� ������ �����
				distance -= matr[current][i];		//������� ���������� ��� ������������ ������������
				visited[i] = 0;						//�������� ��� ������������
			}
		}
	}
}
void main(){
	int source;							//��������� ����� (�����)
	int** matr;							//������� ��������� ��� �����, ��� ������� ���������� �/� ��������
	int n = 0;							//���-�� �������
	char c;								//���������� ����������
	int i, j, tmp = -1;					//����������
	int min_dist;						//����������� ����������
	int* p_min_dist;					//��������� �� min_dist
	int* min_way;						//������������������ ����� ������������ ���������� (����, ������� ��� ����������)
	int* way;							//����
	int* visited;						//��� "���������" �����
	char str[] = "matr.txt";			//�������� �����, ��� ���-�� ������� ���������
	FILE* out_file = fopen("graphviz.txt", "w"); //������� ���� ��� ��������� graphviz
	FILE* in_file = fopen(str, "r");	//�������� ����� ��� ������ (in_file - ��������� �� ���������, �.�. ����)
	while(!feof(in_file)){				//���� �� ����� �����
		c = getc(in_file);				//������ ������� � �����
		if(c == '\n')					//���� ������ - Enter
			n++;						//����������� ������� ���-�� �������
	}
	n++;								//���������� ��������� ���, �.�. � ����� ����� ��� Enter
	fclose(in_file);					//�������� �����

	//��������� ������
	visited = new int[n];				//������ �� n ��������� ��� visited
	matr = new int*[n];					//��������� n ����������
	for(i = 0; i < n; i++){				//������ �� ������� �� n ���������� �� n ��������� (���������� ������� n*n)
		matr[i] = new int[n];
		visited[i] = 0;
	}
	min_way = new int[n+1];				//������ ��� ����������� ����
	way = new int[n+1];					//������ ��� ����
	
	in_file = fopen(str, "r");					//����� ��������� ���� (����� ���� �� � �� ��������� � ������� ���, �� ��� �������� �������)
	for(i = 0; i < n; i++){						//������ n (��������� ����)
		for(j = 0; j < n; j++){					//������ n (���� ��������)
			fscanf(in_file, "%d", &matr[i][j]);	//��������� �� ����� ������� ��������� n*n (�������������� ����� �\� ����� ��������)
			if(tmp < matr[i][j])				//���������� ������������� ���������� �/� ����� �������
				tmp = matr[i][j];
		}
	}
	
	min_dist = tmp * n + 1;						//���-�� � ���� ������������� (������ ����� ����� ���� �� ����� �����)
	p_min_dist = &min_dist;						//p_min_dist ��������� �� min_dist
	cout << "Enter a source: ";
	cin >> source;								//���� ��������� �����
	visited[source] = 1;						//��������, ��� � source ��������
	solve(matr, source, 0, p_min_dist, n, n-1, source, visited, way, min_way);	//������ �������� (������ �������)
				//matr - ������� ���������
				//source - ����� �����������
				//0 - �.�. ������ ��������, �� ��� ������ �� ������, � ��������� ����� ����
				//p_min_dist - ��������� �� min_dist, ������� ����� tmp * n + 1 (� ����� ������ �������� ����, ������ �����)
				//n - ���-�� �����
				//n-1 - �.�. �������� � source, �� ��� �� ���� ����� ������
				//source - ������� �����, �.�. � ��� ��������

	//����� ���������� � �������
	for(i = 0; i <= n; i++)
		cout << min_way[i] << ' ';
	cout << endl;

	//���� ��� graphviz (���� ��������� �������� ������, ��������� - ��������� �����)
	int cur, next;
	fprintf(out_file, "digraph G{\n");	//���� �������� � ����� ��� ����
	for(i = 0; i < n; i++){				//n ������ �� ����� �������
		cur = min_way[i];				
		next = min_way[i+1];
		for(j = 0; j < n; j++){
			if(next == j)
				fprintf(out_file, "\t%d->%d;\n", cur, j);
			else
				fprintf(out_file, "\t%d->%d [style=dotted];\n", cur, j);	//���������� �����
		}
	}
	fprintf(out_file, "}");				//��� ���� ����
	fclose(out_file); //������� ����

	//������������ ������
	for(i = 0; i < n; i++)
		delete[] matr[i];
	delete matr;
	delete visited;
	delete min_way;
	delete way;
}