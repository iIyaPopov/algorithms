#include <iostream>
#include <stdio.h>
using namespace std;
void degree(int n, int* op){
	int i, j, tmp;
	int d1, d2, d3, d4;
	int min;
	op[0] = 0;
	op[1] = 0;
	for(i = 2; i <= n; i++){
		cout << i << ": ";
		op[i] = op[i-1] + 1;
		d1 = i - 1;
		min = 1;
		for(j = 2; j < i; j++){
			tmp = op[j] + op[i-j] + 1;
			if(op[i] > tmp){
				op[i] = tmp;
				d2 = i;
				d3 = i - j;
				min = 23;
			}
			if(i % j == 0){
				tmp = op[i/j] + j - 1;
				if(op[i] > tmp){
					op[i] = tmp;
					d4 = i/j;
					min = 4;
				}
			}
		}
		cout << op[i] << ' ';
		if(min == 1){
			cout << "(" << d1 << ")";
		}
		else{
			if(min == 23)
				cout << "(" << d2 << '*' << d3 << ")";
			else
				cout << "(" << d4 << ")";
		}
		cout << endl;
	}
}
void main(){
	int* op;
	int n, i;
	cout << "n = ";
	cin >> n;
	op = new int[n+1];
	degree(n, op);
	delete op;
}