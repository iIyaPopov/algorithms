#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
class vector{
public:
	//���������� ������
	int x1;
	int y1;
	//���������� �����
	int x2;
	int y2;
	//���������� �������
	int x;
	int y;
};
float len_vec(vector v){//����� �������
	return (sqrt((float)(v.x * v.x + v.y * v.y)));
}
float cos_vec(vector v1, vector v2){//���� ����� ���������
	int scal = v1.x * v2.x + v1.y * v2.y;
	int mod1 = v1.x * v1.x + v1.y * v1.y;
	int mod2 = v2.x * v2.x + v2.y * v2.y;
	return (float)(scal / (sqrt((float)mod1) * sqrt((float)mod2)));
}
void get_file(FILE* in_file, int* x, int* y, int n){//���������� �� �����
	for(int i = 0; i < n; i++){
		fscanf(in_file, "%d", &x[i]);
		fscanf(in_file, "%d", &y[i]);
	}
}
void put_file(FILE* out_file, int* set_point, int* x, int* y, int k){//������ � ����
	for(int i = 0; i < k; i++){
		fprintf(out_file, "%d %d\n", x[set_point[i]], y[set_point[i]]);
	}
}
void main(){
	char file_name[] = "coord2.txt";//�������� �������� �����
	FILE* in_file = fopen(file_name, "r");//�������� �������� �����
	FILE* out_file = fopen("result.txt", "w");//�������� ��������� �����
	char c;
	int n = 0;//���-�� �����
	int begin_x, begin_y;//���������� ������ (����� ������ �����) //��� �������
	int i, i_tmp;
	int k = 0;//���-�� ����� � ��������
	float min, max_len, tmp;//��������� ����������
	int* x;//����������
	int* y;//�����
	int* set_point;//����� ����� � ��������
	vector v1, v2, v_tmp;//�������
	int* visited;//����������� ��������� ����� � ��������

	//����������� ���-�� �����
	while(!feof(in_file)){//���� �� ����� �����
		c = fgetc(in_file);//������ �������
		if(c == '\n')//���� ������ - enter
			n++;
	}
	n++;//��������� �����, �.�. � ����� ��� enter

	fclose(in_file);//�������� �����

	//��������� ������
	x = new int[n];
	y = new int[n];
	set_point = new int[n];
	visited = new int[n];

	//�������������
	for(i = 0; i < n; i++){
		visited[i] = 0;
		set_point[i] = -1;
	}

	in_file = fopen(file_name, "r");
	//���������� ��������� �����
	get_file(in_file, x, y, n);//���������� ��������� �� �����

	//���������� ����� ������ �����
	begin_x = x[0];
	begin_y = y[0];
	i_tmp = 0;
	for(i = 0; i < n; i++){//����� ���� �����
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
	set_point[k++] = i_tmp;//��������� � ����� �����

	//��������� ��������� ������
	v1.x1 = begin_x;
	v1.y1 = begin_y;
	v1.x2 = begin_x + 1;//��������� ������
	v1.y2 = begin_y;
	v1.x = v1.x2 - v1.x1;
	v1.y = v1.y2 - v1.y1;

	min = -1;//��� �������� ���� ����� ���������
	max_len = -1;

	//������ ���������� �������
	v_tmp.x1 = v1.x2;
	v_tmp.y1 = v1.y2;

	//����� ������ ������� �������
	for(i = 0; i < n; i++){//����� ���� �����
		if(!visited[i]){//���� �� �������� � �������� i-�� �������
			v_tmp.x2 = x[i];
			v_tmp.y2 = y[i];
			v_tmp.x = v_tmp.x2 - v_tmp.x1;
			v_tmp.y = v_tmp.y2 - v_tmp.y1;
			tmp = cos_vec(v1, v_tmp);//������� ����� ���������
			if(tmp >= min){
				if(tmp == min && len_vec(v_tmp) > max_len){
					max_len = len_vec(v_tmp);
					min = tmp;
					//�����������
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
						//�����������
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

	//����� ������ ��� �����, �.�. �������� ������ ������
//	v1.x1;
//	v1.y1;
//	v1.x2 = v2.x2;
//	v1.y2 = v2.y2;
	v1.x = v1.x2 - v1.x1;
	v1.y = v1.y2 - v1.y1;

	//����� ��������
	v_tmp.x1 = v1.x2;
	v_tmp.y1 = v1.y2;
	v_tmp.x2 = v1.x2;
	v_tmp.y2 = v1.y2;
	while(1){//���� �� ������ �� ������
		min = -1;
		for(i = 0; i < n; i++){
			if(!visited[i]){//���� �� �������� � ��������
				//��������� ������
				v_tmp.x2 = x[i];
				v_tmp.y2 = y[i];
				v_tmp.x = v_tmp.x2 - v_tmp.x1;
				v_tmp.y = v_tmp.y2 - v_tmp.y1;

				tmp = cos_vec(v1, v_tmp);//�������
				if(tmp > min){//���� ��������� ������ ��������
					//����������
					min = tmp;
					i_tmp = i;

					//�����������
					v2.x1 = v_tmp.x1;
					v2.x2 = v_tmp.x2;
					v2.y1 = v_tmp.y1;
					v2.y2 = v_tmp.y2;
					v2.x = v_tmp.x;
					v2.y = v_tmp.y;
				}
			}
		}
		//�����������
		v1.x1 = v2.x1;
		v1.x2 = v2.x2;
		v1.y1 = v2.y1;
		v1.y2 = v2.y2;
		v1.x = v2.x;
		v1.y = v2.y;
		v_tmp.x1 = v1.x2;
		v_tmp.y1 = v1.y2;
		if(v_tmp.x1 == begin_x && v_tmp.y1 == begin_y)//���� ������ � ������
			break;//����� �� while
		visited[i_tmp] = 1;
		set_point[k++] = i_tmp;
	}

	put_file(out_file, set_point, x, y, k);//����� � ����

	//������������ ������
	delete x;
	delete y;
	delete visited;
	delete set_point;

	//�������� ������
	fclose(out_file);
	fclose(in_file);
}