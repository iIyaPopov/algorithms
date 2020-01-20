#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
class vector{
public:
	//координаты начала
	int x1;
	int y1;
	//координаты конца
	int x2;
	int y2;
	//координаты вектора
	int x;
	int y;
};
float len_vec(vector v){//длина вектора
	return (sqrt((float)(v.x * v.x + v.y * v.y)));
}
float cos_vec(vector v1, vector v2){//угол между векторами
	int scal = v1.x * v2.x + v1.y * v2.y;
	int mod1 = v1.x * v1.x + v1.y * v1.y;
	int mod2 = v2.x * v2.x + v2.y * v2.y;
	return (float)(scal / (sqrt((float)mod1) * sqrt((float)mod2)));
}
void get_file(FILE* in_file, int* x, int* y, int n){//считывание из файла
	for(int i = 0; i < n; i++){
		fscanf(in_file, "%d", &x[i]);
		fscanf(in_file, "%d", &y[i]);
	}
}
void put_file(FILE* out_file, int* set_point, int* x, int* y, int k){//запись в файл
	for(int i = 0; i < k; i++){
		fprintf(out_file, "%d %d\n", x[set_point[i]], y[set_point[i]]);
	}
}
void main(){
	char file_name[] = "coord2.txt";//название входного файла
	FILE* in_file = fopen(file_name, "r");//открытие входного файла
	FILE* out_file = fopen("result.txt", "w");//открытие выходного файла
	char c;
	int n = 0;//кол-во точек
	int begin_x, begin_y;//координаты старта (левая нижняя точка) //так удобнее
	int i, i_tmp;
	int k = 0;//кол-во точек в оболочке
	float min, max_len, tmp;//временные переменные
	int* x;//координаты
	int* y;//точек
	int* set_point;//набор точек в оболочке
	vector v1, v2, v_tmp;//вектора
	int* visited;//обозначение включения точки в оболочку

	//определение кол-ва точек
	while(!feof(in_file)){//пока не конец файла
		c = fgetc(in_file);//чтение символа
		if(c == '\n')//если символ - enter
			n++;
	}
	n++;//последняя точка, т.к. в конце нет enter

	fclose(in_file);//закрытие файла

	//выделение памяти
	x = new int[n];
	y = new int[n];
	set_point = new int[n];
	visited = new int[n];

	//инициализация
	for(i = 0; i < n; i++){
		visited[i] = 0;
		set_point[i] = -1;
	}

	in_file = fopen(file_name, "r");
	//считывание координат точек
	get_file(in_file, x, y, n);//считывание координат из файла

	//нахождение левой нижней точки
	begin_x = x[0];
	begin_y = y[0];
	i_tmp = 0;
	for(i = 0; i < n; i++){//обход всех точек
		if(y[i] < begin_y){
			begin_x = x[i];
			begin_y = y[i];
			i_tmp = i;
		}
		else{
			if(y[i] == begin_y && x[i] < begin_x){
				begin_x = x[i];
				begin_y = y[i];
				i_tmp = i;
			}
		}
	}
	set_point[k++] = i_tmp;//включение в набор точек

	//начальный единичный вектор
	v1.x1 = begin_x;
	v1.y1 = begin_y;
	v1.x2 = begin_x + 1;//единичный вектор
	v1.y2 = begin_y;
	v1.x = v1.x2 - v1.x1;
	v1.y = v1.y2 - v1.y1;

	min = -1;//для косинуса угла между векторами
	max_len = -1;

	//начало следующего вектора
	v_tmp.x1 = v1.x2;
	v_tmp.y1 = v1.y2;

	//поиск самого первого вектора
	for(i = 0; i < n; i++){//обход всех точек
		if(!visited[i]){//если не включили в оболочку i-ую вершину
			v_tmp.x2 = x[i];
			v_tmp.y2 = y[i];
			v_tmp.x = v_tmp.x2 - v_tmp.x1;
			v_tmp.y = v_tmp.y2 - v_tmp.y1;
			tmp = cos_vec(v1, v_tmp);//косинус меджу векторами
			if(tmp >= min){
				if(tmp == min && len_vec(v_tmp) > max_len){
					max_len = len_vec(v_tmp);
					min = tmp;
					//копирование
					v2.x1 = v_tmp.x1;
					v2.x2 = v_tmp.x2;
					v2.y1 = v_tmp.y1;
					v2.y2 = v_tmp.y2;
					v2.x = v_tmp.x;
					v2.y = v_tmp.y;
					i_tmp = i;
				}
				else{
					if(tmp > min){
						max_len = len_vec(v_tmp);
						min = tmp;
						//копирование
						v2.x1 = v_tmp.x1;
						v2.x2 = v_tmp.x2;
						v2.y1 = v_tmp.y1;
						v2.y2 = v_tmp.y2;
						v2.x = v_tmp.x;
						v2.y = v_tmp.y;
						i_tmp = i;
					}
				}
			}
		}
	}
	visited[i_tmp] = 1;
	set_point[k++] = i_tmp;

	//нашли первые две точки, т.е. составим первый вектор
//	v1.x1;
//	v1.y1;
//	v1.x2 = v2.x2;
//	v1.y2 = v2.y2;
	v1.x = v1.x2 - v1.x1;
	v1.y = v1.y2 - v1.y1;

	//поиск оболочки
	v_tmp.x1 = v1.x2;
	v_tmp.y1 = v1.y2;
	v_tmp.x2 = v1.x2;
	v_tmp.y2 = v1.y2;
	while(1){//пока не дойдем до начала
		min = -1;
		for(i = 0; i < n; i++){
			if(!visited[i]){//если не включена в оболочку
				//временный вектор
				v_tmp.x2 = x[i];
				v_tmp.y2 = y[i];
				v_tmp.x = v_tmp.x2 - v_tmp.x1;
				v_tmp.y = v_tmp.y2 - v_tmp.y1;

				tmp = cos_vec(v1, v_tmp);//косинус
				if(tmp > min){//если временный вектор подходит
					//сохранение
					min = tmp;
					i_tmp = i;

					//копирование
					v2.x1 = v_tmp.x1;
					v2.x2 = v_tmp.x2;
					v2.y1 = v_tmp.y1;
					v2.y2 = v_tmp.y2;
					v2.x = v_tmp.x;
					v2.y = v_tmp.y;
				}
			}
		}
		//копирование
		v1.x1 = v2.x1;
		v1.x2 = v2.x2;
		v1.y1 = v2.y1;
		v1.y2 = v2.y2;
		v1.x = v2.x;
		v1.y = v2.y;
		v_tmp.x1 = v1.x2;
		v_tmp.y1 = v1.y2;
		if(v_tmp.x1 == begin_x && v_tmp.y1 == begin_y)//если пришли в начало
			break;//выход из while
		visited[i_tmp] = 1;
		set_point[k++] = i_tmp;
	}

	put_file(out_file, set_point, x, y, k);//вывод в файл

	//освобождение памяти
	delete x;
	delete y;
	delete visited;
	delete set_point;

	//закрытие файлов
	fclose(out_file);
	fclose(in_file);
}