#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;
void main(){
	int m, n, i, j;
	int** table;
	int** up;
	int** right;
	cout << "n = ";
	cin >> n;
	cout << "m = ";
	cin >> m;

	table = new int*[n+1];
	for(i = 0; i < n + 1; i++){
		table[i] = new int[m+1];
		for(j = 0; j < m + 1; j++)
			table[i][j] = 0;
	}

	up = new int*[n];
	for(i = 0; i < n; i++){
		up[i] = new int[m+1];
		for(j = 0; j < m + 1; j++)
			cin >> up[i][j];
	}
	cout << endl;

	right = new int*[n+1];
	for(i = 0; i < n + 1; i++){
		right[i] = new int[m];
		for(j = 0; j < m; j++)
			cin >> right[i][j];
	}
	cout << endl;
	//заполнение крайних €чеек
	for(i = n - 1; i >= 0; i--)
		table[i][0] = table[i+1][0] + up[i][0];
	for(j = 1; j < m + 1; j++)
		table[n][j] = table[n][j-1] + right[n][j-1];

	for(i = n - 1; i >= 0; i--){
		for(j = 1; j < m + 1; j++){
			table[i][j] = max(table[i+1][j] + up[i][j], table[i][j-1] + right[i][j-1]);
		}
	}

	for(i = 0; i < n + 1; i++){
		for(j = 0; j < m + 1; j++){
			if(table[i][j] > 9)
				cout << table[i][j] << ' ';
			else
				cout << table[i][j] << "  ";
		}
		cout << endl;
	}

	for(i = 0; i < n + 1; i++)
		delete[] table[i];
	delete table;
	for(i = 0; i < n; i++)
		delete[] up[i];
	delete up;
	for(i = 0; i < n; i++)
		delete[] right[i];
	delete right;
}