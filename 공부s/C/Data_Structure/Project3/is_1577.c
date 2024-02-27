#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
typedef int Element;

Element data[MAX_STACK_SIZE];
int top;

void error(char str[]) {		//������ ���� ���ڿ� ���
	printf("%s\n", str);
	exit(1);
}

void init_stack() {
	top = -1;
}

int is_empty() {
	return top == -1;
}

int is_full() {
	return top == MAX_STACK_SIZE - 1;
}

int size() {
	return top + 1;
}

void push(Element e) {
	if (is_full()) {
		error("���� ��ȭ ����");
	}
	data[++top] = e;
}

Element pop() {
	if (is_empty()) {
		error("���� ���� ����");
	}
	//	data[top] = '\0';
	return data[top--];
}

Element peek() {
	if (is_empty()) {
		error("���� ���� ����");
	}
	return data[top];
}

void print_stack(char msg[]) {
	int i;
	printf("%s[%2d]= ", msg, size());
	for (i = 0; i < size(); i++) {
		printf("%2d ", data[i]);
	}
	printf("\n");
}

int main(void)
{
	int check = 1;
	init_stack();
	char str[MAX_STACK_SIZE];
	gets(str);

	while()
}