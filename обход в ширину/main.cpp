#include <iostream>
#include <stdio.h>
using namespace std;
//организация очереди
class queue{
	int* arr;
	int size;
	int cur;
public:
	queue(int n);
	~queue();
	bool empty();
	void enque(int x);
	int deque();
	void print();
};
queue::queue(int n){
	size = n;
	cur = 0;
	arr = new int[n];
	for(int i = 0; i < n; i++)
		arr[i] = -1;
}
queue::~queue(){
	delete arr;
}
bool queue::empty(){
	for(int i = 0; i < size; i++)
		if(arr[i] >= 0)
			return false;
	return true;
}
void queue::enque(int x){
	arr[cur] = x;
	cur++;
}
int queue::deque(){
	int tmp = arr[0];
	for(int i = 1; i < cur; i++)
		arr[i-1] = arr[i];
	arr[cur] = -1;
	cur--;
	return tmp;
}
void queue::print(){
	for(int i = 0; i < cur; i++)
		cout << arr[i] << ' ';
	cout << endl;
}
void bfs(int v, int** m, int* visited, int n){//обход в ширину
	queue s(n);
	visited[v] = 1;
	s.enque(v);
	while(!s.empty()){
		s.print();
		v = s.deque();
		for(int i = 0; i < n; i++){
			if(m[v][i] && !visited[i]){
				visited[i] = 1;
				s.enque(i);
			}
		}
		//s.print();
	}
	//s.print();
}
void main(){
	char matr[] = "matr.txt";
	int n = 0, i, j;
	char c;
	int** m;
	int* visited;
	FILE* in_file = fopen(matr, "r");

	//определение количества вершин
	while(!feof(in_file)){
		c = fgetc(in_file);
		if(c == ' ')
			n++;
		if(c == '\n'){
			n++;
			break;
		}
	}
	fclose(in_file);

	//выделение памяти
	m = new int*[n];
	for(i = 0; i < n; i++)
		m[i] = new int[n];
	visited = new int[n];
	for(i = 0; i < n; i++)
		visited[i] = 0;

	//считывание матрицы смежности
	in_file = fopen(matr, "r");
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			fscanf(in_file, "%d", &m[i][j]);
	fclose(in_file);

	//вывод матрицы смежности
	cout << "m[]:" << endl;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++)
			cout << m[i][j] << ' ';
		cout << endl;
	}
	cout << endl;

	//обход в ширину
	for(i = 0; i < n; i++){
		if(!visited[i]){
			cout << "From " << i << ':' << endl;
			bfs(i, m, visited, n);
			//cout << endl;
		}
	}

	//освобождение памяти
	for(i = 0; i < n; i++)
		delete[] m[i];
	delete m;
	delete visited;
}