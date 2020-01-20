#include <iostream>
#include <stdio.h>
using namespace std;
void rucksack(int* w, int* c, int v, int cur_v, int* set, int n, int cur_i, int cur_val, int* max_val, int* max_set){
	if(v == 0 || cur_i == n){
		if(cur_val > *max_val){
			*max_val = cur_val;
			for(int k = 0; k < n; k++){
				max_set[k] = set[k];
				//cout << set[k] << ' ';
			}
			//cout << ": " << *max_val << endl;
		}
	}
	else{
		for(int i = 0; i <= v / w[cur_i]; i++){
			cur_v += w[cur_i] * i;
			cur_val += c[cur_i] * i;
			set[cur_i] = i;
			rucksack(w, c, v - w[cur_i] * i, cur_v, set, n, cur_i + 1, cur_val, max_val, max_set);
			set[cur_i] = 0;
			cur_v -= w[cur_i] * i;
			cur_val -= c[cur_i] * i;
		}
	}
}
void main(){
	int n = 7;
	int weight[] = {3, 4, 2, 3, 5, 2, 4};
	int cost[]   = {11, 20, 17, 32, 1, 10, 20};
	int* w = &weight[0];
	int* c = &cost[0];
	int max_value = 0;
	int* max_val = &max_value;
	int* set = new int[n];
	int* max_set = new int[n];
	for(int i = 0; i < n; i++){
		set[i] = max_set[i] = 0;
	}
	int i, v;
	cout << "V = ";
	cin >> v;
	rucksack(w, c, v, 0, set, n, 0, 0, max_val, max_set);
	for(int k = 0; k < n; k++)
		cout << max_set[k] << ' ';
	cout << endl;
	delete set;
	delete max_set;
}