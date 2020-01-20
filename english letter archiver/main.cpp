#include "coding.h"
void main(){
	const char name[] = "input.txt";//��� �����
	FILE* inputFile = fopen(name, "r");	//�������� ����� ��� ������
	FILE* outputFile = fopen("output.txt", "w");	//�������� ����� ��� ������ 
	int* countSymbols;	//������ (�� ����� ���� ��������� �� ������, ����� �� ������ '*' ����� �������) ��� �������� ������������� � ��������� �����
	Tree* mas;	//������ ��� ���������� �������� ������ �� �������� (����� ��������� �������� ������)
	int countIndex;	//��������� ����������
	Tree* list;	//�������� ������
	int* code;	//���������
	char* symbols;	//�������
	int** symbolCode;	//���� ��������

	//��������� ������
	countSymbols = new int[SIZE];	//��������� ������ ��� 56 ��������� (�.�. 52 �����(��������� � ��������) + ' ' + '.' + ',')
	mas = new Tree[SIZE];
	list = new Tree[1];

	//������������� (�������������� ��������)
	for(int i = 0; i < SIZE; i++){
		countSymbols[i] = 0;//���� ������
		mas[i].symbol = -1;	//���� ��� ��� �������
		mas[i].left = NULL;	//�.�. � ������ ����� ������� ������ ���� �� �����
		mas[i].right = NULL; //�� �� �����
	}
	
	//������ ������� �������� ���-�� �������� (������� �������������)
	FrequencyCounting(inputFile, countSymbols);
	fclose(inputFile);	//�������� �����

	//������� ���-�� ��������� ������������ �������� ��� ����� ������� ��������� ��������
	countIndex = 0;
	for(int i = 0; i < SIZE; i++){
		if(countSymbols[i] != 0){
			mas[countIndex].symbol = i;
			mas[countIndex].weight = countSymbols[i];
			countIndex++;
		}
	}

	//��������� ������
	code = new int[countIndex];	//��� ����������� ������� (����������� ����)
	symbols = new char[countIndex];
	symbolCode = new int*[countIndex];
	for(int i = 0; i < countIndex; i++)
		symbolCode[i] = new int[6];	//�.�. ������������ ����� ���� �� �� ������ 6 � �������� (2^6 = 64, � � ��� 56 ��������)

	//���������� ������
	createTree(mas, countSymbols, SIZE, countIndex);

	//����� �����������
	for(int i = 0; i < (SIZE-4)/2; i++)//����� � ������� ���-�� �������� ����
		cout << countSymbols[i] << ' ';	//���� �����, ��� printf("%d ", countSymbols[i]);
	cout << endl;
	for(int i = (SIZE-4)/2; i < SIZE-4; i++)//����� � ������� ���-�� ��������� ����
		cout << countSymbols[i] << ' ';
	cout << endl;
	for(int i = SIZE-4; i < SIZE; i++)//����� � ������� ���-�� ������
		cout << countSymbols[i] << ' ';
	cout << endl << endl;

	Tree* head = &mas[0];	//"������" ������
	int index = 0;	//��� ���-�� "�������" ��������
	int* p;	//��������� �� index
	p = &index;

	//������� �����������
	coding(head, code, 0, symbols, symbolCode, p);	//����� � �������
	
	//����� � ������� �������� � �� ���
	printCode(symbols, symbolCode, index);

	//������ � ����
	inputFile = fopen(name, "r");
	writingCode(inputFile, outputFile, symbols, symbolCode, index, countSymbols);
	cout << endl;
	fclose(outputFile);

	//�������������
	head = &mas[0];
	FILE* outFile = fopen("output2.txt", "w");
	decoding(outputFile, outFile, head, countSymbols);
	fclose(outFile);

	//������������ ������
	delete countSymbols;
	delete mas;
	delete list;
	delete code;
	delete symbols;
	for(int i = 0; i < countIndex; i++)
		delete[] symbolCode[i];
	delete symbolCode;

	//�������� �����
	fclose(inputFile);
}