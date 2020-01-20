#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

//структура описания ребер
struct edge{
	int a, b, cost;
};


//source - стартовая вершина
//p[] - откуда пришли в i-ую вершину
//d[] - минимальный путь в i-ую вершину
//infinity - бесконечность
//e[] - массив ребер
//m - кол-во ребер
//n - кол-во вершин
void BellmanFord(int n, int m, edge* e, int infinity, int source, int* d, int* p) {
	int i;
	int circle;//для нахождения цикла отрицательной стоимости (флаг)

	//инициализация
	for(i = 0; i < n; i++)
		p[i] = -1;
	for(i = 0; i < n; i++)
		d[i] = infinity;
	d[source] = 0; //начальную вершину не рассматриваем

	for(int i = 0; i < n; i++){ //выполнять n-1 раз
		circle = -1; //нет отрицательного цикла
		for(int j = 0; j < m; j++){ //проходим все ребра
			if(d[e[j].a] < infinity){ //если есть ребро между вершинами
				int tmp = d[e[j].a] + e[j].cost; //путь через другую вершину
				if(tmp < d[e[j].b]){ //если нашли вариант лучше
					d[e[j].b] = tmp; //меняем на лучшую
					p[e[j].b] = e[j].a; //запоминаем откуда
					circle = e[j].b; //запоминание последней рассмотренной вершины
				}
			}
		}
	}
	if(circle == -1) //если не выполнился цикл n раз
		cout << "No negative cycle from " << source << endl;
	else{ //если выполнился цикл n раз, т.е. есть отрицательный цикл
		int y = circle;
		for(i = 0; i < n; i++)
			y = p[y];
		vector<int> path; //результат для отрицательного цикла
		for(int cur = y; ; cur = p[cur]){
			path.push_back(cur); //вставка cur в конец вектора
			if(cur == y && path.size() > 1) //если вернулись в начальную и кол-во вершин в отр. цикле больше 1
				break;//завершение цикла
		}
		//вывод цикла в консоль
		cout << "Negative cycle: ";
		for(i = 0; i < path.size(); i++)
			cout << path[i] << ' ';
		cout << endl;
	}

	//данные для graphviz
	FILE* out_file = fopen("graphviz.txt", "w");
	fprintf(out_file, "digraph G{\n");
	for(i = 0; i < m; i++){
		fprintf(out_file, "%d->%d;\n", e[i].a, e[i].b);
	}
	fprintf(out_file, "}");
	fclose(out_file);
}


void main(){
	FILE* in_file; //указатель на структуру
	edge* e; //массив ребер
	char file_name[] = "edges.txt"; //название файла, откуда берем список ребер
	int infinity = -INT_MAX;
	int i, j, tmp;
	int value;
	int m = 0; //кол-во ребер
	int n = 0; //кол-во вершин
	int source; //стартовая вершина
	int* d; //расстояния
	int* p; //для восстановления путей

	//нахождение максимальной стоимости, кол-ва вершин и кол-ва ребер
	in_file = fopen(file_name, "r");
	while(!feof(in_file)){
		fscanf(in_file, "%d", &tmp);//поиск номара максимальной вершины
		if(tmp > n)
			n = tmp;
		fscanf(in_file, "%d", &tmp);
		if(tmp > n)
			n = tmp;
		fscanf(in_file, "%d", &value);//вес ребра
		m++;
		if(value > infinity)
			infinity = value;
	}
	n++;
	fclose(in_file);
	infinity = infinity * n + 1; //максимально возможная стоимость

	//выделение памяти
	e = new edge[m];
	d = new int[n];
	p = new int[n];

	//считывание ребер
	in_file = fopen(file_name, "r");
	for(i = 0; i < m; i++){//m ребер
		fscanf(in_file, "%d", &e[i].a); //одна вершина
		fscanf(in_file, "%d", &e[i].b); //другая вершина
		fscanf(in_file, "%d", &e[i].cost); //вес ребра
	}
	fclose(in_file);

	//считывание страртовой вершины
	cout << "source = ";
	cin >> source;

	//Алгоритм Беллмана_Форда
	BellmanFord(n, m, e, infinity, source, d, p);

	//вывод результатов
	/*
	for(i = 0; i < m; i++)
		cout << e[i].a << ' ' << e[i].b << ' ' << e[i].cost << endl;
	cout << endl;
	for(i = 0; i < n ;i++)
		cout << d[i] << ' ';
	cout << endl << endl;
	for(i = 0; i < n; i++)
		cout << p[i] << ' ';
	cout << endl;
	*/

	//освобождение памяти
	delete e;
	delete d;
	delete p;
	
}
