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

//pop, push에서 top 어떻게 연산할지 맞추고 다른 함수 따라가
//이 상태로는 top가 마지막 요소가 있는 칸을 가리키도록 되어있음 비어있으면 -1
void init() {
	top = -1;
}
void push(Element x) {
	if (is_full() == 1) {
		printf("stack is full\n");
		exit(1);
	}
	else {
		data[++top] = x;	//가득차면 top = MAX_STACK_SIZE
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

//Element에 따라 수정
void print_stack() {
	for (int i = 0; i < size(); i++)
	{
		printf("data[%2d] = %c\n", i, data[i]);		//괄호 검사로 %c 만듦
	}
}

//구조체용 print
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


//괄호 엇갈릴 때, 개수 안맞을 때(열린/닫힌)으로 검사 기준 3개
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
		printf("괄호 짝 잘 맞어라\n");
		return 1;
	}
	else {
		printf("괄호 짝 잘 안맞어라\n");
		return 0;
	}
}