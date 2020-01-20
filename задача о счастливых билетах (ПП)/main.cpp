#include <iostream>
#include <stdio.h>
using namespace std;
bool check(int* ticket, int n){//проверка на симметрию
	int sum1 = 0, sum2 = 0;
	for(int i = 0; i < n / 2; i++){
		sum1 += ticket[i];
		sum2 += ticket[n-1-i];
	}
	if(sum1 == sum2)
		return true;
	else
		return false;
}
int happy_ticket(int n, int* ticket, int ind){
	int counter = 0;
	if(ind == n){
		if(check(ticket, n)){
			for(int j = 0; j < n; j++)
				cout << ticket[j];
			cout << endl;
			return 1;
		}
		return 0;
	}
	else{
		for(int i = 0; i < 10; i++){
			ticket[ind] = i;
			counter += happy_ticket(n, ticket, ind + 1);
			ticket[ind] = -1;
		}
		return counter;
	}
}
void main(){
	int i, n, amount;
	int* ticket;
	cout << "n = ";
	cin >> n;
	ticket = new int[n];
	for(i = 0; i < n; i++)
		ticket[i] = -1;
	amount = happy_ticket(n, ticket, 0);
	cout << "Amount = " << amount << endl;
	delete ticket;
}