#pragma once
#include<stdio.h>
#include<stdlib.h>
#define Element char
#define MAX_STACK_SIZE 20
int top;

typedef struct {
	int id;
	char name[32];
	char dept[32];
} Student;

Element data[MAX_STACK_SIZE] = { 0, };

//pop, push���� top ��� �������� ���߰� �ٸ� �Լ� ����
//�� ���·δ� top�� ������ ��Ұ� �ִ� ĭ�� ����Ű���� �Ǿ����� ��������� -1
void init() {
	top = -1;
}
void push(Element x) {
	if (is_full() == 1) {
		printf("stack is full\n");
		exit(1);
	}
	else {
		data[++top] = x;	//�������� top = MAX_STACK_SIZE
	}
}
Element pop() {
	if (is_empty() == 1) {
		printf("stack is empty\n");
		exit(1);
	}
	else {
		return data[top--];
	}
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
Element peek() {
	return data[top];
}

//Element�� ���� ����
void print_stack() {
	for (int i = 0; i < size(); i++)
	{
		printf("data[%2d] = %c\n", i, data[i]);		//��ȣ �˻�� %c ����
	}
}

//����ü�� print
//void print_stack() {
//	for (int i = 0; i < size(); i++) {
//		printf("data[%2d] : id = %12d\tname = %12s\tdept = %12s\n", i, data[i].id, data[i].name, data[i].dept);
//	}
//}

Student get_student(int id, char* name, char* dept)
{
	Student s;
	s.id = id;
	strcpy(s.name, name);
	strcpy(s.dept, dept);
	return s;
}


//��ȣ ������ ��, ���� �ȸ��� ��(����/����)���� �˻� ���� 3��
int bracket_checker(char* s)
{
	for (int i = 0; s[i] != 0; i++)
	{
		if (s[i] == '(' || s[i] == '{' || s[i] == '[') push(s[i]);

		if (s[i] == ')' || s[i] == '}' || s[i] == ']')
		{
			switch (s[i]) {
			case ')':
				if (peek() == '(') pop();
				break;
			case '}':
				if (peek() == '{') pop();
				break;
			case ']':
				if (peek() == '[') pop();
				break;
			}
		}
	}

	if (is_empty()) {
		printf("��ȣ ¦ �� �¾��\n");
		return 1;
	}
	else {
		printf("��ȣ ¦ �� �ȸ¾��\n");
		return 0;
	}
}