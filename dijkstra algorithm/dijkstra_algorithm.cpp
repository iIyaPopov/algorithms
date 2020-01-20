#include <iostream>
#include <stdio.h>

using namespace std;
/*
	p[] - из какой вершины пришли в i-ую
	m[] - матрица смежности
	d[] - стоимость пути
	u[] - подобно visited[]
	source - откуда начинать алгоритм
	infinity - бесконечность или максимально возможное значение + 1
	n - количество вершин
*/
void dijkstra(int** m, int* p, int* d, int* u, int source, int infinity, int n){
	int i, j, v, tmp, min = 0, i_min;

	//инициализация
	i_min = source;
	for(i = 0; i < n; i++){
		d[i] = m[source][i];
		if(m[source][i] == infinity)
			p[i] = infinity;
		else
			p[i] = source;
	}

	//основная часть алгоритма
	u[source] = 1;
	for(i = 0; i < n - 1+10; i++){//т.к. минимум необходимо искать n - 1 раз
		min = infinity;
		for(j = 0; j < n; j++){//поиск минимума в d[]
			if(d[j] < min){// && u[j] == 0){
				min = d[j];
				i_min = j;
			}
		}
		u[i_min] = 1;//исключение из рассмотрения
		for(v = 0; v < n; v++){//попытка добраться в вершины через i_min
			tmp = d[i_min] + m[i_min][v];
			if(d[v] > tmp && v != source){
				d[v] = tmp;
				p[v] = i_min;//меняется, если изменилсяя путь
			}
		}
	}
}


void main(){
	char file_name[] = "input.txt";
	FILE* in_file = fopen(file_name, "r");
	int infinity = 0, i, j, min, v;
	int value, n = 0;
	char c;
	int** m;
	int* p;
	int* d;
	int source;
	int* u;

	//нахождение максимальной стоимости
	while(!feof(in_file)){
		fscanf(in_file, "%d", &value);
		if(value > infinity)
			infinity = value;
	}
	fclose(in_file);
	in_file = fopen(file_name, "r");

	//определение кол-ва вершин
	while(1){
		c = fgetc(in_file);
		if(c == '\n'){
			n++;
			break;
		}
		else{
			if(c == ' ')
				n++;
		}
	}
	infinity = infinity * (n - 1) + 1;//максимально возможная стоимость
	fclose(in_file);

	//выделение памяти
	m = new int*[n];
	for(i = 0; i < n; i++)
		m[i] = new int[n];
	d = new int[n];
	p = new int[n];
	u = new int[n];
	for(i = 0; i < n; i++)
		u[i] = 0;

	//заполнение матрицы смежности
	int tmp;
	in_file = fopen(file_name, "r");
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			fscanf(in_file, "%d", &tmp);
			if(tmp == 0) //нет пути
				m[i][j] = infinity;
			else
				m[i][j] = tmp;
		}
	}
	fclose(in_file);

	//запуск алгоритма Дейкстра
	cout << "source = ";
	cin >> source; //откуда начинать
	dijkstra(m, p, d, u, source, infinity, n);

	//вывод результатов
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++)
			cout << m[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
	cout << "d[]: ";
	for(i = 0; i < n; i++)
		cout << d[i] << ' ';
	cout << endl;
	cout << "p[]: ";
	for(i = 0; i < n; i++)
		cout << p[i] << ' ';
	cout << endl;

	//освобождение памяти
	for(i = 0; i < n; i++)
		delete[] m[i];
	delete m;
	delete d;
	delete p;
	delete u;
	
}
