#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
typedef int Element;

Element data[MAX_STACK_SIZE];
int top;

void error(char*);
void init_stack();			//top 변수를 -1로 (비었다고 표시)
int is_empty();				//top = -1이니?
int is_full();				//top = MAX_STACK_SIZE - 1 이니?
int size();					//top + 1 알려주기 (1~n개)
void push(Element);			//안 가득찼으면(is_full) 인수를 추가
Element pop();				//안 비었으면(is_empty) 맨 위 인수 버리고 출력
Element peek();				//안 비었으면(is_empty) 맨 위 인수 출력만
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
	print_stack("스택 push 10회");
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());

	print_stack("스택 pop 3회");

	//printf("\n%d", data[8]);

	return 0;
}


void error(char str[]) {		//에러가 나면 문자열 출력
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
		error("스택 포화 에러");
	}
	data[++top] = e;
}

Element pop() {
	if (is_empty()) {
		error("스택 공백 에러");
	}
//	data[top] = '\0';
	return data[top--];
}

Element peek() {
	if (is_empty()) {
		error("스택 공백 에러");
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