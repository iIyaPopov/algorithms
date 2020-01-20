#include <iostream>
#include <string.h>

using namespace std;

void nud_vunsh(int** m, char a[], char b[]){
	int i, j, lenA = strlen(a), lenB = strlen(b);
	for(j = 0; j < lenB + 1; j++)
		m[0][j] = 0;
	for(i = 0; i < lenA + 1; i++)
		m[i][0] = 0;
	for(i = 1; i < lenA + 1; i++){
		for(j = 1; j < lenB + 1; j++){
			if(a[i-1] == b[j-1])
				m[i][j] = m[i-1][j-1] + 1;
			else
				m[i][j] = max(m[i-1][j], m[i][j-1]);
		}
	}
}

void result(int** m, char a[], char b[]){
	char* lcs;
	int lenA = strlen(a), lenB = strlen(b);
	int y = lenB, x = lenA, k = m[lenA][lenB];
	lcs = new char[k+1];
	lcs[k] = '\0';
	while(x > 0 && y > 0){
		if(b[y-1] == a[x-1]){
			lcs[--k] = a[x-1];
			x--;
			y--;
		}
		else{
			if(m[x-1][y] > m[x][y-1])
				x--;
			else
				y--;
		}
	}
	cout << lcs << endl;
	delete lcs;
}

void main(){
	char a[50], b[50];
	int lenA, lenB, i, j;
	int** m;
	cin >> a;
	cin >> b;
	lenA = strlen(a);
	lenB = strlen(b);

	m = new int*[lenA+1];
	for(i = 0; i < lenA + 1; i++)
		m[i] = new int[lenB+1];

	nud_vunsh(m, a, b);
	result(m, a, b);

	/*for(i = 0; i < lenA + 1; i++){
		for(j = 0; j < lenB + 1; j++)
			cout << m[i][j] << ' ';
		cout << endl;
	}*/

	for(i = 0; i < lenA + 1; i++)
		delete[] m[i];
	delete m;
}
