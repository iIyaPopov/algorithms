#include "coding.h"
void FrequencyCounting(FILE* file, int* countSymbols){
	char c;	//���������� ����������
	while(!feof(file)){	//���� �� ����� �����
		c = fgetc(file);	//������� ������ �� �����
		if(c == ' ')	//���� ������
			countSymbols[SIZE-4]++;	//��������� ������� ������� (50 �������)
		else	
			if(c == '.')	//���� �����...
				countSymbols[SIZE-3]++;
			else
				if(c == ',')	//���� �������...
					countSymbols[SIZE-2]++;
				else
					if(c == '\n')	//���� Enter...
						countSymbols[SIZE-1]++;
					else	//���� �����...
						if(c - 'a' >= 0)	//���� �������� �����(�.�. ��������� ����� ������, �� � ��� ������)
							countSymbols[c-'a']++;	//��� ����� � ������� ASCII ����� ��� ����� "a"(+26, �.�. ������� ������ ��� ���������)
						else
							if(c-'A' >= 0)
								countSymbols[int(c-'A'+26)]++;	//��������� �����
	}
}
void bubbleSort(Tree* mas, int* counting, int size){//��� ���������� "���������" ������ ����� � ��������� (��� � ������ �� ����������)
	for(int i = 0; i < size; i++){
		for(int j = size - 1; j > i; j--){
			if(mas[j-1].weight < mas[j].weight){//��������� ������� ������������� � ����� ������� ���� � ������ true
				Tree x = mas[j-1];
				mas[j-1] = mas[j];
				mas[j] = x;
			}
		}
	}
}
void createTree(Tree* mas, int* countSymbols, int size, int countIndex){
	Tree* tmp;	//��������� ���������� ��� �������� ����� ������
	for(int k = countIndex - 1; k > 0; k--){
		bubbleSort(mas, countSymbols, countIndex);	//������� ���������
		tmp = new Tree[1];	//����� ���� �������
		tmp->left = new Tree[1];	//������� ������ � ������� ��������
		tmp->right = new Tree[1];	//
		*tmp->left = mas[k-1];	//������ �������������� ���������
		*tmp->right = mas[k];	//
		tmp->weight = tmp->left->weight + tmp->right->weight;	//� ������ ���� ��� ����� ����� ����� ��������
		mas[k-1] = *tmp;	//������ ���������� ���� �� �������� �����
	}
}
void coding(Tree* root, int* code, int i, char* symbols, int** symbolCode, int* index){
	if(root->left == NULL || root->right == NULL){					//���� �� ����� ������
		if((int)root->symbol < 26){									//���� �������� �����
			symbols[*index] = (int)'a' + (int)root->symbol;
		}
		else{
			if((int)root->symbol >= 26 && (int)root->symbol < 52){	//���� ��������� �����
				symbols[*index] = (int)'A' + root->symbol;
			}
			else{													//���� ������ ������� (enter, �������, �����, ������ ��������������)
				if(root->symbol == 55)
					symbols[*index] = '\n';
				if(root->symbol == 54)
					symbols[*index] = (char)',';
				if(root->symbol == 53)
					symbols[*index] = (char)'.';
				if(root->symbol == 52)
					symbols[*index] = ' ';
			}
		}
		for(int j = 0; j < i; j++){
			symbolCode[*index][j] = code[j];
		}
		(*index)++;
	}
	else{
		if(root->left != NULL){	//��������� � ����������� �� ���� ��� ����� ������������� ���� 1 ��� 0  (���� - 0, ����� - 1)
			code[i] = 0;
			coding(root->left, code, i + 1, symbols, symbolCode, index);
			code[i] = -1;
		}
		if(root->right != NULL){
			code[i] = 1;
			coding(root->right, code, i + 1, symbols, symbolCode, index);
			code[i] = -1;
		}
	}
}
void printCode(char* symbols, int** symbolCode, int index){
	for(int i = 0; i < index; i++){
		if(symbols[i] == '\n')
			cout << "\\n\t";
		else
			cout << symbols[i] << '\t';
		for(int j = 0; j < 8; j++)
			if(symbolCode[i][j] == 1 || symbolCode[i][j] == 0)
				cout << (int) symbolCode[i][j];
		cout << endl;
	}
	cout << endl;
}
void writingCode(FILE* inFile, FILE* outFile, char* symbols, int** symbolCode, int index,int* countSymbols){
	char tmp;
	int k = 0;	//�������� ���-�� ���������� ��� � ����
	char c = 0;	//���������� ����, ������� ����� ���������� � ���������� � ����
	while(!feof(inFile)){	//���� �� ����� �����
		tmp = fgetc(inFile);	//������ ������ �� inFile
		for(int i = 0; i < index; i++){	//�������� ��� �������, ������� ����������� � �������� ������
			if(tmp == symbols[i]){	//����� ������ ������ � ��� �����
				for(int j = 0; j < 6; j++){	//���������� ������� ��� � ����
					if(k == 8){	//���� ���� ���������
						fprintf(outFile, "%c", c);	//������� ������ � ����
						cout << ' ' << (int)c << endl;
						k = 0;	//����� ������� �����
						c = 0;	//����� ����
					}
					if(symbolCode[i][j] == 1){	//���� ��� � ���� = 1
						c = c << 1;	//����� ����� �����
						c += 1;	//��������� 1
						cout << '1';
						k++;	//������� �����, �.�. �������� 1
					}
					else{
						if(symbolCode[i][j] == 0){	//���� ��� � ���� = 0
							c = c << 1;	//������ �������� ��� +1
							cout << '0';
							k++;	//������� �����
						}
						else{
							break;	//��� � ������� ����������
						}
					}
				}
				break;	//������ �������� � ����, ����� �� �����
			}
		}
	}
	fprintf(outFile, "#");	//������� ������ # (��������� ��� ����� �����)
	fprintf(outFile, "%c", (int)k);
	fprintf(outFile, "%c", c);
	cout << ' ' << (int)c << endl;
	//fprintf(outFile, "#");	//������� ������ # (��������� ��� ����� �����)
}
void decoding(FILE* inFile, FILE* outFile, Tree* root, int* countSymbols){
	inFile = fopen("output.txt", "r");
	Tree* tmp = root;	//����� �� �������� ������ ������, ������� ��������� ������, ������� � ����� ������
	char c;
	char mask;	//�����, � ����������� ����� � �����
	fscanf(inFile, "%c", &c);	//������ �����
	while(c != '#'){	//���� �� ����� �����
		mask = -128;	//��� 10000000 � ��������, ���������� ����� ��������: 10000000..01000000..00100000..00010000..1000..100..00000010..1..0
		while(mask != 0){	//���� �� ��������� ���� ���� (char) �������� ��������� (8 �����)
			if(tmp->left == NULL && tmp->right == NULL)	//���� �������� ���
				tmp = root;	//���� ����� � ����� ������
			while(tmp->left != NULL && tmp->right != NULL && (mask == -128 || mask > 0)){	//���� �� ��������� ������ �� ����
				if((bool)(c & mask) == true){	//���������� ��������� (���� 1, �� ������ � ������)
					tmp = tmp->right;	//���� �� ������ ������
				}
				else{
					if((bool)(c & mask) == false){	//����� - �����
						tmp = tmp->left;	//�����
					}
				}
				mask = mask >> 1;	//�������� �� 1 ��� ������ (��������, 1000 -> 0100 -> 0010)
				if(mask < 0)
					mask *= -1;
			}
			if(tmp->symbol > 25 && tmp->symbol >= 0 && tmp->symbol < 52)
				fprintf(outFile, "%c", 'A' + tmp->symbol);
			else{
				if(tmp->symbol <= 25 && tmp->symbol >= 0)
					fprintf(outFile, "%c", 'a' + tmp->symbol);
				else{
					if(tmp->symbol == 52)
						fprintf(outFile, "%c", ' ' );
					else
						if(tmp->symbol == 53)
							fprintf(outFile, "%c", '.');
						else
							if(tmp->symbol == 54)
								fprintf(outFile, "%c", ',');
							else
								if(tmp->symbol == 55)
									fprintf(outFile, "%c", '\n');
				}
			}
			//cout << (int)tmp->symbol << ' ';
		}
		//cout << endl;
		fscanf(inFile, "%c", &c);
	}
	//��������� ���-�� ��� � ��������� �����
	fscanf(inFile, "%c", &c);
	int k = 8 - c;	//�.�. 8 ��� � �����, �� �� 8 �������� ���-�� ����� � ��������� �����, ����� �������� ����� �� ������ ���-�� ���
	//��������� ��������� ����
	fscanf(inFile, "%c", &c);
	mask = -128;
	mask = mask >> k;	//����� � �������� ����� �� ������ ���-�� ���
	if(mask < 0)
		mask *= -1;
	//cout << (int)mask << endl;
	//�� �� �����, ��� ����
	while(mask != 0){	//���� �� ��������� ���� ���� (char) �������� ��������� (8 �����)
		if(tmp->left == NULL && tmp->right == NULL)
			tmp = root;
		while(tmp->left != NULL && tmp->right != NULL && (mask == -128 || mask > 0)){	//���� �� ��������� ������ �� ����
			if((bool)(c & mask) == true){	//���������� ��������� (���� 1, �� ������ � ������)
				tmp = tmp->right;
			}
			else{
				if((bool)(c & mask) == false){	//����� - �����
					tmp = tmp->left;
				}
			}
			mask = mask >> 1;
			if(mask < 0)
				mask *= -1;
		}
		if(tmp->symbol > 25 && tmp->symbol >= 0 && tmp->symbol < 52)
			fprintf(outFile, "%c", 'A' + tmp->symbol);
		else{
			if(tmp->symbol <= 25 && tmp->symbol >= 0)
				fprintf(outFile, "%c", 'a' + tmp->symbol);
			else{
				if(tmp->symbol == 52)
					fprintf(outFile, "%c", ' ' );
				else
					if(tmp->symbol == 53)
						fprintf(outFile, "%c", '.');
					else
						if(tmp->symbol == 54)
							fprintf(outFile, "%c", ',');
						else
							if(tmp->symbol == 55)
								fprintf(outFile, "%c", '\n');
			}
		}
		//cout << (int)tmp->symbol << ' ';
	}
	fclose(inFile);
}