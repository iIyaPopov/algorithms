#include <iostream>
#include <stdio.h>
using namespace std;
bool check(int** desk, int x, int y, int n){
	if(x >= 0 && x < n && y >= 0 && y < n && desk[x][y] == 0)
		return 1;
	return 0;
}
int horse(int** desk, int sqr_n, int n, int numb, int i, int j){
	int counter = 0;
	int x[] = {-2, -1, 1, 2,  2,  1, -1, -2};
	int y[] = { 1,  2, 2, 1, -1, -2, -2, -1};
	if(numb > sqr_n){
		/*for(int i1 = 0; i1 < n; i1++){
			for(int j1 = 0; j1 < n; j1++){
				if(desk[i1][j] > 999)
					cout << desk[i1][j1] << " ";
				else{
					if(desk[i1][j1] > 99)
						cout << desk[i1][j1] << "  ";
					else{
						if(desk[i1][j1] > 9)
							cout << desk[i1][j1] << "   ";
						else
							cout << desk[i1][j1] << "    ";
					}
				}
			}
			cout << endl;
		}
		cout << endl;*/
		return 1;
	}
	else{
		for(int m = 0; m < 8; m++){
			if(check(desk, i + x[m], j + y[m], n)){
				desk[i+x[m]][j+y[m]] = numb;
				counter += horse(desk, sqr_n, n, numb + 1, i + x[m], j + y[m]);
				desk[i+x[m]][j+y[m]] = 0;
			}
		}
		return counter;
	}
}
void main(){
	int** desk;
	int n, i, j, sqr_n, counter = 0;
	cout << "n = ";
	cin >> n;
	desk = new int*[n];
	for(i = 0; i < n; i++){
		desk[i] = new int[n];
		for(j = 0; j < n; j++)
			desk[i][j] = 0;
	}
	sqr_n = n * n;
//	for(i = 0; i < n; i++){
//		for(j = 0; j < n; j++){
	i = 0;
	j = 0;
			desk[i][j] = 1;
			counter += horse(desk, sqr_n, n, 2, i, j);
//			desk[i][j] = 0;
//		}
//	}
	cout << counter << endl;
	for(i = 0; i < n; i++)
		delete[] desk[i];
	delete desk;
}