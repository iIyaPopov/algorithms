#include "coding.h"
void FrequencyCounting(FILE* file, int* countSymbols){
	char c;	//символьная переменная
	while(!feof(file)){	//пока не конец файла
		c = fgetc(file);	//считать символ из файла
		if(c == ' ')	//если пробел
			countSymbols[SIZE-4]++;	//увеличить счетчик пробела (50 позиция)
		else	
			if(c == '.')	//если точка...
				countSymbols[SIZE-3]++;
			else
				if(c == ',')	//если запятая...
					countSymbols[SIZE-2]++;
				else
					if(c == '\n')	//если Enter...
						countSymbols[SIZE-1]++;
					else	//если буква...
						if(c - 'a' >= 0)	//если строчная буква(т.к. заглавные стоят раньше, то и код меньше)
							countSymbols[c-'a']++;	//код буквы в таблице ASCII минус код буквы "a"(+26, т.к. сначала ячейки для заглавных)
						else
							if(c-'A' >= 0)
								countSymbols[int(c-'A'+26)]++;	//заглавные буквы
	}
}
void bubbleSort(Tree* mas, int* counting, int size){//про сортировку "пузырьком" можешь найти в интернете (тут я ничего не придумывал)
	for(int i = 0; i < size; i++){
		for(int j = size - 1; j > i; j--){
			if(mas[j-1].weight < mas[j].weight){//сравниваю частоты встречаемости и меняю местами узлы в случае true
				Tree x = mas[j-1];
				mas[j-1] = mas[j];
				mas[j] = x;
			}
		}
	}
}
void createTree(Tree* mas, int* countSymbols, int size, int countIndex){
	Tree* tmp;	//временная переменная для создания узлов дерева
	for(int k = countIndex - 1; k > 0; k--){
		bubbleSort(mas, countSymbols, countIndex);	//сначала сортируем
		tmp = new Tree[1];	//новый узел создаем
		tmp->left = new Tree[1];	//создаем левого и правого потомков
		tmp->right = new Tree[1];	//
		*tmp->left = mas[k-1];	//меняем соответственно указатели
		*tmp->right = mas[k];	//
		tmp->weight = tmp->left->weight + tmp->right->weight;	//у нового узла вес равно сумме весов потомков
		mas[k-1] = *tmp;	//запись временного узла на соседнее место
	}
}
void coding(Tree* root, int* code, int i, char* symbols, int** symbolCode, int* index){
	if(root->left == NULL || root->right == NULL){					//пока не дошли донизу
		if((int)root->symbol < 26){									//если строчная буква
			symbols[*index] = (int)'a' + (int)root->symbol;
		}
		else{
			if((int)root->symbol >= 26 && (int)root->symbol < 52){	//если заглавная буква
				symbols[*index] = (int)'A' + root->symbol;
			}
			else{													//если другие символы (enter, запятая, точка, пробел соответственно)
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
		if(root->left != NULL){	//рекурсиво в зависимости от лево или право присваивается биту 1 или 0  (лево - 0, право - 1)
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
	int k = 0;	//контроль кол-ва записанных бит в байт
	char c = 0;	//кодируемый байт, который будем составлять и записывать в файл
	while(!feof(inFile)){	//пока не конец файла
		tmp = fgetc(inFile);	//читаем символ из inFile
		for(int i = 0; i < index; i++){	//проходим все символы, которые встречались в исходном тексте
			if(tmp == symbols[i]){	//нашли нужный символ с его кодом
				for(int j = 0; j < 6; j++){	//записываем побитно код в байт
					if(k == 8){	//если байт составлен
						fprintf(outFile, "%c", c);	//выводим символ в файл
						cout << ' ' << (int)c << endl;
						k = 0;	//новый счетчик битов
						c = 0;	//новый байт
					}
					if(symbolCode[i][j] == 1){	//если бит в коде = 1
						c = c << 1;	//сдвиг битов влево
						c += 1;	//добавляем 1
						cout << '1';
						k++;	//счетчик битов, т.к. добавили 1
					}
					else{
						if(symbolCode[i][j] == 0){	//если бит в коде = 0
							c = c << 1;	//просто сдвигаем без +1
							cout << '0';
							k++;	//счетчик битов
						}
						else{
							break;	//код у символа закончился
						}
					}
				}
				break;	//символ записали в байт, выход из цикла
			}
		}
	}
	fprintf(outFile, "#");	//запишем символ # (обозначим так конец файла)
	fprintf(outFile, "%c", (int)k);
	fprintf(outFile, "%c", c);
	cout << ' ' << (int)c << endl;
	//fprintf(outFile, "#");	//запишем символ # (обозначим так конец файла)
}
void decoding(FILE* inFile, FILE* outFile, Tree* root, int* countSymbols){
	inFile = fopen("output.txt", "r");
	Tree* tmp = root;	//чтобы не потерять корень дерева, создаем временный корень, который и будем менять
	char c;
	char mask;	//маска, я определения битов в байте
	fscanf(inFile, "%c", &c);	//чтение байта
	while(c != '#'){	//пока не конец файла
		mask = -128;	//это 10000000 в двоичной, постепенно будет меняться: 10000000..01000000..00100000..00010000..1000..100..00000010..1..0
		while(mask != 0){	//пока не прочитали один байт (char) побитово полностью (8 шагов)
			if(tmp->left == NULL && tmp->right == NULL)	//если потомков нет
				tmp = root;	//идем опять с корня дерева
			while(tmp->left != NULL && tmp->right != NULL && (mask == -128 || mask > 0)){	//пока не вычислили символ по коду
				if((bool)(c & mask) == true){	//логическое умножение (если 1, то вправо в дереве)
					tmp = tmp->right;	//идем по дереву вправо
				}
				else{
					if((bool)(c & mask) == false){	//иначе - влево
						tmp = tmp->left;	//влево
					}
				}
				mask = mask >> 1;	//сдвигаем на 1 бит вправо (например, 1000 -> 0100 -> 0010)
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
	//считываем кол-во бит в последнем байте
	fscanf(inFile, "%c", &c);
	int k = 8 - c;	//т.к. 8 бит в байте, то из 8 вычитаем кол-во битов в последнем байте, чтобы сдвинуть маску на нужное кол-во бит
	//считываем последний байт
	fscanf(inFile, "%c", &c);
	mask = -128;
	mask = mask >> k;	//здесь и сдвигаем маску на нужное кол-во бит
	if(mask < 0)
		mask *= -1;
	//cout << (int)mask << endl;
	//то же самое, что выше
	while(mask != 0){	//пока не прочитали один байт (char) побитово полностью (8 шагов)
		if(tmp->left == NULL && tmp->right == NULL)
			tmp = root;
		while(tmp->left != NULL && tmp->right != NULL && (mask == -128 || mask > 0)){	//пока не вычислили символ по коду
			if((bool)(c & mask) == true){	//логическое умножение (если 1, то вправо в дереве)
				tmp = tmp->right;
			}
			else{
				if((bool)(c & mask) == false){	//иначе - влево
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