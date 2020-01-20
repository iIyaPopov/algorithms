//���������� ����������� ��������� ������������ ������
#include <iostream>
#include <stdio.h>
using namespace std;
void main(){
	FILE* file = fopen("size of matr.txt", "r");
	int k = 0, i, j, t;
	char c;
	int* matr;
	int** n;

	//����������� ���������� ������
	while(!feof(file)){
		c = fgetc(file);
		if(c == ' ' || c == '\n')
			k++;
	}
	fclose(file);

	//��������� ������
	matr = new int[k+1];
	n = new int*[k];
	for(i = 0; i < k; i++){
		n[i] = new int[k];
		for(j = 0; j < k; j++)
			n[i][j] = 0;
	}

	//���������� �������� ������
	file = fopen("size of matr.txt", "r");
	for(i = 0; i < k + 1; i++)
		fscanf(file, "%d", &matr[i]);
	fclose(file);

	int num = 1;
	//���������� ������������ �������
	for(i = 1; i < k; i++){//����� ��������� "\"
		for(j = 0; j < k - i; j++){//����� �������� � ��������� i (k - i - ���������� ��������� � ��������� i)
			n[j][j+i] = INT_MAX;
			for(t = j; t < i + j; t++){
				int cur = n[j][t] + n[t+1][i+j] + matr[j] * matr[t+1] * matr[i+j+1];
				if(cur < n[j][i+j])
					n[j][i+j] = cur;
			}
		}
	}

	//����� �����������
	for(i = 0; i < k + 1; i++)
		cout << matr[i] << ' ';
	cout << endl;
	for(i = 0; i < k; i++){
		for(j = 0; j < k; j++){
			cout << n[i][j] << ' ';
		}
		cout << endl;
	}

	//������� ���������� ������
	for(i = 0; i < k; i++)
		delete[] n[i];
	delete n;
	delete matr;
}