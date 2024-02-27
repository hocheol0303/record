#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
typedef double Element;

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

double calc_postfix(char*);

int main(void)
{
	char expr[2][80] = { "8 2 / 3 - 3 2 * +", "1 2 / 4 * 1 4 / *" };

	printf("수식: %s = %lf\n", expr[0], calc_postfix(expr[0]));
	printf("수식: %s = %lf\n", expr[1], calc_postfix(expr[1]));
}

void error(char* str) {		//에러가 나면 문자열 출력
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

double calc_postfix(char* expr) {
	char c;
	int i = 0;
	double val, val1, val2;

	init_stack();
	while (expr[i] != '\0')
	{
		c = expr[i++];
		if (c >= '0' && c <= '9')
		{
			val = c - '0';
			push(val);
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			val2 = pop();
			val1 = pop();
			switch (c) {
			case '+': push(val1 + val2); break;
			case '-': push(val1 - val2); break;
			case '*': push(val1 * val2); break;
			case '/': push(val1 / val2); break;
			}
		}
	}
	return pop();
}