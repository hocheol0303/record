#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_STACK_SIZE 100
typedef int Element;

Element inputStack[MAX_STACK_SIZE], outputStack[MAX_STACK_SIZE];
int top;


void error(char*);
void init_stack();			//top 변수를 -1로 (비었다고 표시)
int is_empty();				//top = -1이니?
int is_full();				//top = MAX_STACK_SIZE - 1 이니?
int size();					//top + 1 알려주기 (1~n개)
void push(Element);			//안 가득찼으면(is_full) 인수를 추가
Element pop();				//안 비었으면(is_empty) 맨 위 인수 버리고 출력
Element peek();				//안 비었으면(is_empty) 맨 위 인수 출력만
void print_stack(char*);

int topQue;
void init_queue() { topQue = -1; for (int i = 0; i < MAX_STACK_SIZE; i++) outputStack[i] = -1; }
int is_emptyQue() { return topQue == -1; }
int is_fullQue() { return topQue == MAX_STACK_SIZE - 1; }
int sizeQue() { return topQue + 1; }


void pushQue()
{
	if (is_fullQue()) error("큐 참");
	outputStack[++topQue] = pop();
}

Element peekQue()
{
	return outputStack[topQue];
}

Element popQue() {
	if (is_emptyQue())
	{
		while (1)
		{
			if (is_empty())
				break;
			pushQue();
		}
	}

	return outputStack[topQue--];
}

void printQue(char const *str)
{
	if (is_emptyQue())
	{
		while (1)
		{
			if (is_empty())
				break;
			pushQue();
		}
	}
	printf("%s[%2d]=", str, sizeQue());
	for (int i = 0; i < sizeQue(); i++) {
		printf(" %2d", outputStack[i]);
	}
	printf("\n");
}

int main(void) {
	srand(time(NULL));

	init_stack();
	init_queue();

	for (int i = 0; i < 10; i++)
		push(rand() % 100);
	print_stack("stack");
	
	printQue("printQue()");
	
	printf("\tpopQue() --> %d\n", popQue());
	printf("\tpopQue() --> %d\n", popQue());
	printf("\tpopQue() --> %d\n", popQue());
	printQue("printQue()");
	while(1)
	printf("\n호철짱짱맨\n");

	return 0;
}





void error(char str[]) {		//에러가 나면 문자열 출력
	printf("%s\n", str);
	exit(1);
}

void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX_STACK_SIZE - 1; }
int size() { return top + 1; }

void push(Element e) {
	if (is_full()) 	error("스택 포화 에러");
	inputStack[++top] = e;
}

Element pop() {
	if (is_empty()) {
		error("스택 공백 에러");
	}
	//	data[top] = '\0';
	return inputStack[top--];
}
Element peek() {
	if (is_empty()) {
		error("스택 공백 에러");
	}
	return inputStack[top];
}

void print_stack(char msg[]) {
	int i;
	printf("%s[%2d]= ", msg, size());
	for (i = 0; i < size(); i++) {
		printf("%2d ", inputStack[i]);
	}
	printf("\n");
}