#include <iostream>
#include <stdio.h>
using namespace std;
void main(){
	const int v = 15;//����������� �������
	const int k = 5;//���-�� ���������
	int w[k+1] = {0, 6, 4, 3, 2, 5};//���� ���������
	int p[k+1] = {0, 5, 3, 1, 3, 6};//��������� ���������
	int a[k+1][v+1];
	int i, s, j, n, tmp, tmp_v;
	
	//�������������
	for(i = 0; i <= v; i++)
	    a[0][i] = 0;

	//���������� ������������� �������
	for(s = 1; s <= k; s++){
		for(n = 0; n <= v; n++){
		    a[s][n] = a[s-1][n]; 
		    if(n >= w[s] && (a[s-1][n-w[s]] + p[s] > a[s][n]))
		        a[s][n] = a[s-1][n-w[s]] + p[s];
		}
	}

	//����� �����������
	for(i = 0; i <= k; i++){
		for(int j = 0; j <= v; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
	cout << "Things: ";
	tmp_v = v;
	int tmp_value = 0;

	//����������� ������ �����
	for(i = k; i > 0; i--){
		if(a[i][tmp_v] != a[i-1][tmp_v]){
			cout << i << " ";
			tmp_value += p[i];
			tmp_v -= w[i];
		}
	}
	cout << endl << "Value: " << tmp_value << endl;
}