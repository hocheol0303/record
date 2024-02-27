#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100

int top = -1;
typedef int Element;

Element stack[MAX_SIZE];

void error(const char* str) {
	printf("%s\n", str);
	exit(1);
}

void init_stack() { top = -1; }
int is_empty() { return top == -1; }				//비어있으면 1, 안비어있으면 0 반환
int is_full() { return top == MAX_SIZE - 1; }		//차있으면 1, 안차있으면 0 반환
int size() { return top + 1; }
void push(Element a) 
{
	if (is_full() == 1)
		error("꽉 참");
	else
	{
		stack[top++ + 1] = a;
	}
}
Element pop() {
	if (is_empty() == 1)
		error("텅 빔");
	else
		return stack[top--];
}
Element peek() { return stack[top]; }
int main(void)
{
	init_stack();
	int n = 4096;
	while (n > 0)
	{
		push(n % 2);
		n /= 2;
	}
	while (!is_empty()) {
		printf("%d", pop());
	}
	printf("\n양호철, 조동현, 하다현");
}