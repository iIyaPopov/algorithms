#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;	//для cin и cout
			//matr - указатель на матрицу смежности
			//source - отправная точка
			//distance - текущее пройденное расстояние (для way)
			//min_distance - минимальное найденное расстояние (для min_way)
			//n - кол-во точек (городов)
			//m - кол-во оставшихся точек (изначально n = m)
			//current - текущий город (точка)
			//visited - указатель на массив, где указано, посетили точку (город) или нет
			//way - текущий путь
			//min_way - минимальный путь (тот, который нас интересует)
void solve(int** matr, int source, int distance, int* min_distance, int n, int m, int current, int* visited, int* way, int* min_way){		//функция решения задачи (необходимо пройти все точки кратчайшим путем) - рекурсия
	if(m == 0){									//если не осталось непройденных точек
		distance += matr[current][source];		//добраться до своего города обратно
		if(distance < *min_distance){			//сравнить текущее расстояние с минимальным
			*min_distance = distance;			//поменять минимум
			min_way[0] = min_way[n] = source;	//откуда ушли, туда пришли
			for(int i = 1; i < n; i++)			//скопировать минимальный путь
				min_way[i] = way[i];
		}
	}
	else{
		for(int i = 0; i < n; i++){					//перебор всех точек
			if(!visited[i] && matr[current][i]){	//если не посещена и есть путь
				visited[i] = 1;						//отмечаем, что посетили
				distance += matr[current][i];		//добавляем путь
				way[n-m] = i;						//добавляем к маршруту
				solve(matr, source, distance, min_distance, n, m-1, i, visited, way, min_way);	//идем дальше через выбранную точку
				way[n-m] = -1;						//убираем из набора точку
				distance -= matr[current][i];		//убираем расстояние для последующего рассмотрения
				visited[i] = 0;						//отмечаем как непосещенную
			}
		}
	}
}
void main(){
	int source;							//начальный пункт (город)
	int** matr;							//матрица смежности для графа, где указано расстояние м/у городами
	int n = 0;							//кол-во городов
	char c;								//символьная переменная
	int i, j, tmp = -1;					//переменные
	int min_dist;						//минимальное расстояние
	int* p_min_dist;					//указатель на min_dist
	int* min_way;						//последовательность точек минимального расстояния (путь, который нас интересует)
	int* way;							//путь
	int* visited;						//для "посещения" точек
	char str[] = "matr.txt";			//название файла, где нах-ся матрица смежности
	FILE* out_file = fopen("graphviz.txt", "w"); //открыли файл для программы graphviz
	FILE* in_file = fopen(str, "r");	//открытие файла для чтения (in_file - указатель на структуру, т.е. файл)
	while(!feof(in_file)){				//пока не конец файла
		c = getc(in_file);				//чтение символа в файле
		if(c == '\n')					//если символ - Enter
			n++;						//увеличиваем счетчик кол-ва городов
	}
	n++;								//необходимо прибавить еще, т.к. в самом конце нет Enter
	fclose(in_file);					//закрытие файла

	//выделение памяти
	visited = new int[n];				//память на n элементов для visited
	matr = new int*[n];					//выделение n указателей
	for(i = 0; i < n; i++){				//память на каждого из n указателей на n элементов (получается матрица n*n)
		matr[i] = new int[n];
		visited[i] = 0;
	}
	min_way = new int[n+1];				//память под минимальный путь
	way = new int[n+1];					//память под путь
	
	in_file = fopen(str, "r");					//опять открываем файл (можно было бы и не закрывать в прошлый раз, но так понятнее принцип)
	for(i = 0; i < n; i++){						//высота n (посчитано выше)
		for(j = 0; j < n; j++){					//ширина n (тоже известно)
			fscanf(in_file, "%d", &matr[i][j]);	//считываем из файла матрицу смежности n*n (предполагается связь м\у всеми городами)
			if(tmp < matr[i][j])				//нахождение максимального расстояния м/у двумя точками
				tmp = matr[i][j];
		}
	}
	
	min_dist = tmp * n + 1;						//что-то в роде бесконечности (больше этого числа пути не найти никак)
	p_min_dist = &min_dist;						//p_min_dist указывает на min_dist
	cout << "Enter a source: ";
	cin >> source;								//ввод начальной точки
	visited[source] = 1;						//отмечаем, что в source побывали
	solve(matr, source, 0, p_min_dist, n, n-1, source, visited, way, min_way);	//запуск рекурсии (полный перебор)
				//matr - матрица смежности
				//source - точка отправления
				//0 - т.к. только начинаем, то еще ничего не прошли, и дистанция равна нулю
				//p_min_dist - указывает на min_dist, которая равна tmp * n + 1 (в любом случае найдется путь, меньше этого)
				//n - кол-во точек
				//n-1 - т.к. начинаем с source, то уже на одну точку меньше
				//source - текущая точка, т.к. с нее начинаем

	//вывод результата в консоль
	for(i = 0; i <= n; i++)
		cout << min_way[i] << ' ';
	cout << endl;

	//файл для graphviz (путь выводится сплошной линией, пунктиром - связанные ребра)
	int cur, next;
	fprintf(out_file, "digraph G{\n");	//надо написать в файле эту вещь
	for(i = 0; i < n; i++){				//n вершин со всеми ребрами
		cur = min_way[i];				
		next = min_way[i+1];
		for(j = 0; j < n; j++){
			if(next == j)
				fprintf(out_file, "\t%d->%d;\n", cur, j);
			else
				fprintf(out_file, "\t%d->%d [style=dotted];\n", cur, j);	//пунктирная линия
		}
	}
	fprintf(out_file, "}");				//так тоже надо
	fclose(out_file); //закрыли файл

	//освобождение памяти
	for(i = 0; i < n; i++)
		delete[] matr[i];
	delete matr;
	delete visited;
	delete min_way;
	delete way;
}