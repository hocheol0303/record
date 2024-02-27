#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
typedef int Element;

Element data[MAX_STACK_SIZE];
int top;

void error(char*);
void init_stack();			//top ������ -1�� (����ٰ� ǥ��)
int is_empty();				//top = -1�̴�?
int is_full();				//top = MAX_STACK_SIZE - 1 �̴�?
int size();					//top + 1 �˷��ֱ� (1~n��)
void push(Element);			//�� ����á����(is_full) �μ��� �߰�
Element pop();				//�� �������(is_empty) �� �� �μ� ������ ���
Element peek();				//�� �������(is_empty) �� �� �μ� ��¸�
void print_stack(char*);	//


int main(void)
{
	int i;
	init_stack();
	for (i = 0; i < 10; i++) {
		push(i);
	}
	for (i = 0; i < 10; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");
	print_stack("���� push 10ȸ");
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());

	print_stack("���� pop 3ȸ");

	//printf("\n%d", data[8]);

	return 0;
}


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