#include "coding.h"
void main(){
	const char name[] = "input.txt";//имя файла
	FILE* inputFile = fopen(name, "r");	//открытие файла для чтения
	FILE* outputFile = fopen("output.txt", "w");	//открытие файла для записи 
	int* countSymbols;	//массив (на самом деле указатель на массив, далее со знаком '*' будут массивы) для подсчета встречаемости в текстовом файле
	Tree* mas;	//массив для сортировки индексов частот по убыванию (чтобы построить двоичное дерево)
	int countIndex;	//временная переменная
	Tree* list;	//бинарное дерево
	int* code;	//временная
	char* symbols;	//символы
	int** symbolCode;	//коды символов

	//выделение памяти
	countSymbols = new int[SIZE];	//выделение памяти под 56 элементов (т.к. 52 буквы(заглавные и строчные) + ' ' + '.' + ',')
	mas = new Tree[SIZE];
	list = new Tree[1];

	//инициализация (первоначальные значения)
	for(int i = 0; i < SIZE; i++){
		countSymbols[i] = 0;//пока ничего
		mas[i].symbol = -1;	//пока что нет символа
		mas[i].left = NULL;	//т.к. в дереве после симолов ничего быть не может
		mas[i].right = NULL; //то же самое
	}
	
	//запуск функции подсчета кол-ва символов (частоты встречаемости)
	FrequencyCounting(inputFile, countSymbols);
	fclose(inputFile);	//закрытие файла

	//подсчет кол-ва различных встретившися символов для более быстрой обработки массивов
	countIndex = 0;
	for(int i = 0; i < SIZE; i++){
		if(countSymbols[i] != 0){
			mas[countIndex].symbol = i;
			mas[countIndex].weight = countSymbols[i];
			countIndex++;
		}
	}

	//выделение памяти
	code = new int[countIndex];	//для рекурсивной функции (составление кода)
	symbols = new char[countIndex];
	symbolCode = new int*[countIndex];
	for(int i = 0; i < countIndex; i++)
		symbolCode[i] = new int[6];	//т.к. максимальная длина кода не мб больше 6 в принципе (2^6 = 64, а у нас 56 символов)

	//посторение дерева
	createTree(mas, countSymbols, SIZE, countIndex);

	//вывод результатов
	for(int i = 0; i < (SIZE-4)/2; i++)//вывод в консоль кол-во строчных букв
		cout << countSymbols[i] << ' ';	//тоже самое, что printf("%d ", countSymbols[i]);
	cout << endl;
	for(int i = (SIZE-4)/2; i < SIZE-4; i++)//вывод в консоль кол-во заглавных букв
		cout << countSymbols[i] << ' ';
	cout << endl;
	for(int i = SIZE-4; i < SIZE; i++)//вывод в консоль кол-во знаков
		cout << countSymbols[i] << ' ';
	cout << endl << endl;

	Tree* head = &mas[0];	//"голова" дерева
	int index = 0;	//для кол-ва "рабочих" символов
	int* p;	//указатель на index
	p = &index;

	//функция кодирования
	coding(head, code, 0, symbols, symbolCode, p);	//вывод в консоль
	
	//вывод в консоль символов и их код
	printCode(symbols, symbolCode, index);

	//запись в файл
	inputFile = fopen(name, "r");
	writingCode(inputFile, outputFile, symbols, symbolCode, index, countSymbols);
	cout << endl;
	fclose(outputFile);

	//декодирование
	head = &mas[0];
	FILE* outFile = fopen("output2.txt", "w");
	decoding(outputFile, outFile, head, countSymbols);
	fclose(outFile);

	//освобождение памяти
	delete countSymbols;
	delete mas;
	delete list;
	delete code;
	delete symbols;
	for(int i = 0; i < countIndex; i++)
		delete[] symbolCode[i];
	delete symbolCode;

	//закрытие файла
	fclose(inputFile);
}