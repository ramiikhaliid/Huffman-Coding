#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<math.h>

struct INPUT {
	char x;
	INPUT* next;
};

INPUT* insertinput(INPUT* p, char c) {
	if (p == NULL)
		//LinkedList Isn't Created
	{
		p = (INPUT*)malloc(sizeof(INPUT));
		p->x = c;
		p->next = NULL;
		return p;
	}
	else {
		INPUT* temp;
		temp = (INPUT*)malloc(sizeof(INPUT));
		temp->x = c;
		temp->next = p;
		p = temp;
	}
	return p;


}

struct Node {
	char data;
	int freq;
	Node* parent;
	Node* right;
	Node* left;
};

struct LL
{
	Node* x;
	LL* next;
};

struct zero {
	char data;
	char code[10];
};

struct LX {
	zero* x;
	LX* next;
};

struct ASC {
	char c;
	int x;
	ASC* next;
};

ASC* insertasc(ASC* p, char c, int n) {

	if (p == NULL)
	{
		p = (ASC*)malloc(sizeof(ASC));
		p->c = c;
		p->x = n;
		p->next = NULL;
		return p;
	}
	else {
		ASC* temp;
		temp = (ASC*)malloc(sizeof(ASC));
		temp->c = c;
		temp->x = n;
		temp->next = p;
		p = temp;
	}
	return p;
}

LL* insert(LL* p, Node* d)
{
	if (p == NULL)
	{
		p = (LL*)malloc(sizeof(LL));
		p->x = d;
		p->next = NULL;
		return p;
	}
	else {
		LL* temp;
		temp = (LL*)malloc(sizeof(LL));
		temp->x = d;
		temp->next = p;
		p = temp;
	}
	return p;
}

LL* removeFirst(LL* p) {
	if (p == NULL)
		return NULL;
	LL* temp = p;;
	temp = temp->next;
	delete(p);
	p = temp;
	return p;
}

int check(char c, char* arr, int* count)
{
	for (int i = 0; i < (*count) + 1; i++) {
		if (arr[i] == c)
			return 1;
	}
	arr[(*count)++] = c;
	return 0;
}

Node* init(char c) {
	Node* tmp;
	tmp = (Node*)malloc(sizeof(Node));
	tmp->data = c;
	tmp->freq = 1;
	tmp->parent = tmp->right = tmp->left = NULL;
	return tmp;
}

LL* incFreq(LL* p, char c) {
	LL* it = p;
	while (it->x->data != c)
		it = it->next;
	it->x->freq++;
	return p;
}

INPUT* readC(INPUT* p, int* i) {
	FILE* f1 = fopen("input.txt", "rb");
	char c;
	while ((c = fgetc(f1)) != EOF)
		(*i)++;
	fclose(f1);
	return p;
}

void file(char* x, int k) {
	FILE* f1 = fopen("input.txt", "rb");
	char c;
	int i = 0;
	while ((c = fgetc(f1)) != EOF) {
		x[i] = c;
		i++;
	}
	x[i] = NULL;
	fclose(f1);
}

LL* read(LL* list, int* count, char* dyna, int size) {
	char c;
	int i = 0;
	char* in = (char*)malloc(100);
	while (i < size) {
		c = dyna[i];
		if (!check(c, in, count)) {
			Node* tmp = init(c);
			list = insert(list, tmp);
		}
		else
			list = incFreq(list, c);
		i++;
	}
	free(in);
	return list;
}

LL* sort(LL* p, int count) {
	int i = 0;
	LL* head = p;
	LL* prev;
	LL* it;
	while (i != count - 1) {
		it = head;
		prev = it;
		while (it->next != NULL) {
			if (it == head) {
				if (it->x->freq > it->next->x->freq) {
					LL* tmp = it->next;
					it->next = it->next->next;
					tmp->next = it;
					it = tmp;
					head = it;
					prev = head;
				}
			}
			else {
				if (it->x->freq > it->next->x->freq) {
					LL* tmp1 = it;
					prev->next = it->next;
					tmp1->next = it->next->next;
					prev->next->next = tmp1;
					it = prev->next;
				}
			}
			if (it != head)
				prev = prev->next;
			it = it->next;
		}
		i++;
	}
	return head;
}

LL* createTree(LL* p, int count) {
	if (count == 1) {
		return p;
	}
	else {
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->data = '*';
		temp->freq = p->x->freq + p->next->x->freq;
		temp->left = p->x;
		temp->right = p->next->x;
		temp->left->parent = temp;
		temp->right->parent = temp;
		p = removeFirst(p);
		p = removeFirst(p);
		p = insert(p, temp);
		p = sort(p, count - 1);
		return createTree(p, count - 1);
	}
}

zero* init2(char c, char arr[], int* count) {
	zero* tmp;
	int i;
	tmp = (zero*)malloc(sizeof(zero));
	tmp->data = c;
	for (i = 0; i < *count; i++)
		tmp->code[i] = arr[i];
	tmp->code[i++] = NULL;
	return tmp;
}

LX* insert2(LX* p, zero* d) {
	if (p == NULL)
		//LinkedList Isn't Created
	{
		p = (LX*)malloc(sizeof(LX));
		p->x = d;
		p->next = NULL;
		return p;
	}
	else {
		LX* temp;
		temp = (LX*)malloc(sizeof(LX));
		temp->x = d;
		temp->next = p;
		p = temp;
	}
	return p;
}

LX* checkOne(LL* p, LX* list) {
	if (p->x->data != '*') {
		char str[2] = { '0' };
		zero* tmp = (zero*)malloc(sizeof(zero));
		tmp->data = p->x->data;
		strcpy(tmp->code, str);
		list = insert2(list, tmp);
	}
	else
		list = NULL;
	return list;
}

LX* generateCode(Node* p, char arr[], int* i, LX* s)
{
	if (p != NULL && p->data != '*' && (*i) == 0)
		return s;
	if (p == NULL)
		return s;
	if (p->left != NULL)
		arr[(*i)++] = '0';
	s = generateCode(p->left, arr, i, s);

	if (p->right != NULL)
		arr[(*i)++] = '1';
	s = generateCode(p->right, arr, i, s);

	if (p->right == NULL && p->left == NULL) {
		zero* tmp = init2(p->data, arr, i);
		s = insert2(s, tmp);
		(*i)--;
	}
	else (*i)--;
	return s;
}

INPUT* binary(char* dyna, LX* p, int* x, INPUT* xx, int* yy, int size, char* zerOne) {
	char c;
	LX* it2 = p;
	int i, j = 0, u = 0;
	while (j < size) {
		it2 = p;
		c = dyna[j];
		while (it2 != NULL) {
			i = 0;
			if (it2->x->data == c) {
				while (isalnum(it2->x->code[i])) {
					zerOne[u] = it2->x->code[i];
					(*x)++;
					u++;
					i++;
				}break;
			}
			it2 = it2->next;
		}
		j++;
	}
	(*yy) = (*x);
	while ((*yy) % 8 != 0) {
		zerOne[(*yy)] = '0';
		(*yy)++;
	}
	zerOne[*yy] = NULL;
	return xx;
}

int int_pow(int base, int exp)
{
	int result = 1;
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp /= 2;
		base *= base;
	}
	return result;
}

int afterconvert(int arr[]) {
	int n = 0;
	for (int i = 0; i < 8; i++) {
		n = n + arr[i] * int_pow(10, 7 - i);
	}
	return n;
}

void convert(int* arr, int x, char* zerOne) {
	int a[9];
	int u = 0;
	int k, num, count = 0;
	for (int j = 0; j < (x / 8); j++) {
		for (int i = 0; i < 8; i++) {
			if (u == x)
				return;
			a[i] = zerOne[u] - '0';
			u++;
		}
		num = afterconvert(a);
		arr[count++] = num;
	}
}

int convertBinaryToDecimal(int n)
{
	int decimalNumber = 0, i = 0, remainder;
	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder * pow(2, i);
		++i;
	}
	return decimalNumber;
}

void decimal(int* arr, int x) {
	for (int i = 0; i < (x / 8); i++)
		arr[i] = convertBinaryToDecimal(arr[i]);
}

ASC* ascii(int* arr, unsigned char* arr2, int x, ASC* p) {
	int i;
	for (i = 0; i < (x / 8); i++) {
		if (arr[i] == 0)
			p = insertasc(p, 'a', i);
		else
			arr2[i] = arr[i];
	}
	arr2[i] = NULL;
	return p;
}

void printstruct(LX* p, int y, ASC* ptr) {
	FILE* f1 = fopen("comde.txt", "ab");
	LX* it = p;
	ASC* it2 = ptr;
	int i = 0, j;
	char* arr = new char[y * 2];
	while (it != NULL) {
		j = 0;
		arr[i++] = it->x->data;
		while (isalnum(it->x->code[j])) {
			arr[i++] = it->x->code[j++];
		}
		arr[i++] = ' ';
		it = it->next;
	}
	arr[i] = NULL;
	fprintf(f1, "%s", arr);
	fclose(f1);
	FILE* f2 = fopen("ASC.txt", "wb");
	while (it2 != NULL) {
		fprintf(f2, "%c%d ", it2->c, it2->x);
		it2 = it2->next;
	}
	fclose(f2);
}

void comp(unsigned char* arr, int y, int x, LX* p, ASC* ptr) {
	FILE* f1 = fopen("comde.txt", "wb");
	fprintf(f1, "%d\n%d\n", y, (x / 8));
	fclose(f1);
	printstruct(p, y, ptr);
	f1 = fopen("output.txt", "wb");
	fprintf(f1, "%s", arr);
	fclose(f1);
}

LX* readcomde(int* cc, int* xx, LX* p) {
	FILE* f1 = fopen("comde.txt", "rb");
	fscanf(f1, "%d", cc);
	fscanf(f1, "%d", xx);
	char c, k;
	char* arr;
	int i;
	fscanf(f1, "%c");
	while ((c = fgetc(f1)) != EOF) {
		arr = new char[20];
		i = 0;
		k = c;
		while ((c = fgetc(f1)) != ' ') {
			arr[i] = c;
			i++;
		}
		zero* tmp = init2(k, arr, &i);
		p = insert2(p, tmp);
		delete(arr);
	}
	fclose(f1);
	return p;
}

ASC* readASC(ASC* p, int* jj) {
	int num, i, n = 0;
	char c, k;
	FILE* f2 = fopen("ASC.txt", "rb");
	char* str = new char[30];
	while ((c = fgetc(f2)) != EOF) {
		i = 0;
		k = c;
		while ((c = fgetc(f2)) != ' ') {
			str[i] = c;
			i++;
		}
		num = atoi(str);
		p = insertasc(p, k, num);
		delete(str);
		str = new char[30];
		if (n == 0)
			*jj = num;
		n++;
	}
	delete(str);
	return p;
}

void ascArr(unsigned char* arr, ASC* p) {
	ASC* it = p;
	int i = 0;
	while (it != NULL) {
		i = it->x;
		if (it->c == 'a')
			arr[i] = '0';
		else
			arr[i] = '1';
		it = it->next;
	}
	arr[i + 1] = NULL;
}

void readXX(unsigned char* arr, int xx) {
	FILE* f1 = fopen("output.txt", "rb");
	//fgets(arr, xx, f1);
	fread(arr, 1, xx, f1);
	arr[xx + 1] = NULL;
	fclose(f1);
}

void back2ascii(int* arr, unsigned char* arrXX, int xx, int* i, unsigned char* rt) {
	ASC* tmp = NULL;
	unsigned char c;
	int j = 0;
	while (j != xx) {
		c = arrXX[j];
		if (rt[*i] == '0') {
			arr[*i] = 0;
		}
		else if (c < 0)
			arr[(*i)] = c + 256;
		else
			arr[(*i)] = c;
		(*i)++;
		j++;
	}
}

void DTB(char* str, int* arr, int it, int cc, LX* comde)
{
	int j, n, i = 0;
	char* uu = new char[9];
	for (j = 0; j <= (it - 1); j++) {
		n = arr[j];
		_itoa(n, uu, 2);
		int pp = strlen(uu);
		int kk = strlen(uu);
		while (kk < 8) {
			str[i] = '0';
			i++; kk++;
		}
		for (int j = 0; j < pp - 0; j++) {
			str[i] = uu[j];
			i++;
		}
	}
	str[cc] = NULL;
	//delete(uu);
}

int checkFinal(char* x, LX* p, char* c) {
	LX* it = p;
	int i = 0;
	while (it != NULL) {
		//while ((x[i] == 1 || x[i] == 0) && (it->x->code[i] == 1 || it->x->code[i] == 0)) {
		//  if ()
		while (x[i] == it->x->code[i]) {
			if (it->x->code[i + 1] == NULL) {
				*c = it->x->data;
				return 1;
			}
			i++;
		}
		it = it->next;
		i = 0;
	}
	return 0;
}

void final(int cc, LX* p, char* str) {
	FILE* f1 = fopen("decomp.txt", "wb");
	char* x = new char[20];
	char* ff = new char[cc + 1];
	int i = 0, count = 0, j = 0;
	char c;
	while (str[j] != NULL) {
		x[i] = str[j];
		if (checkFinal(x, p, &c)) {
			ff[count++] = c;
			delete(x);
			x = new char[20];
			i = -1;
		}
		j++;
		i++;
	}
	ff[count] = NULL;
	fprintf(f1, "%s", ff);
	fclose(f1);
}

void initRT(unsigned char* rt, int size2) {
	for (int i = 0; i < size2; i++) {
		rt[i] = '9';
	}
	rt[size2] = NULL;
}

int main() {

	//Compress
	int count = 0, i = 0, x = 0, y = 0, size = 0;
	char arr[10];
	ASC* ptr = NULL;
	LL* tree = NULL;
	LX* list = NULL;
	INPUT* input = NULL;
	INPUT* code = NULL;
	input = readC(input, &size);
	char* dyna = new char[(size + 1)];
	file(dyna, size);
	tree = read(tree, &count, dyna, size);
	tree = sort(tree, count);
	tree = createTree(tree, count);
	list = checkOne(tree, list);
	list = generateCode(tree->x, arr, &i, list);
	free(tree);
	char* zerOne = new char[size * 7];
	code = binary(dyna, list, &y, code, &x, size, zerOne);
	delete(dyna);
	int* arr2 = new int[(x / 8)];
	convert(arr2, x, zerOne);
	free(code);
	//	delete(zerOne);
	decimal(arr2, x);
	unsigned char* as = new unsigned char[(x / 8) + 1];
	ptr = ascii(arr2, as, x, ptr);
	//	delete(arr2);
	comp(as, y, x, list, ptr);
	free(list);
	free(input);
	//delete(as);
	free(ptr);

	//Decompress
	int it = 0, cc = 0, size2 = 0, xx = 0;
	ASC* asc = NULL;
	LX* comde = NULL;
	comde = readcomde(&cc, &xx, comde);
	asc = readASC(asc, &size2);
	unsigned char* rt = new unsigned char[xx + 1];
	initRT(rt, xx);
	//rt[size2] = NULL;
	ascArr(rt, asc);
	free(asc);
	int* as2 = new int[(cc + 8) / 8];
	unsigned char* arrXX = new unsigned char[xx + 1];
	readXX(arrXX, xx);
	back2ascii(as2, arrXX, xx, &it, rt);
	//delete(rt);
	char* kk = new char[cc + 8];
	DTB(kk, as2, it, cc, comde);
	final(cc, comde, kk);
	delete(kk);
	free(comde);
	delete(as2);
	system("pause");

	
}