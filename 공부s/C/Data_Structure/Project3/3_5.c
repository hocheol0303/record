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

int precedence(char);
void infix_to_postfix(char* expr);

int main(void)
{
	char expr[2][80] = { "8 / 2 - 3 + (3 * 2)", "1 / 2 * 4 * (1 / 4)" };

	printf("중위수식 : %s ==> 후위수식:", expr[0]);
	infix_to_postfix(expr[0]);
	printf("중위수식 : %s ==> 후위수식:", expr[1]);
	infix_to_postfix(expr[1]);

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


int precedence(char op){
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*' : case '/' : return 2;
	}
	return -1;
}
void infix_to_postfix(char* expr) {
	int i = 0;
	char c, op;

	init_stack();
	while (expr[i] != '\0') {
		c = expr[i++];
		if ((c >= '0' && c <= '9')) {
			printf("%c ", c);
		}
		else if (c == '(') {
			push(c);
		}
		else if (c == ')') {
			while (is_empty() == 0) {
				op = pop();
				if (op == '(') break;
				else printf("%c ", op);
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (is_empty() == 0) {
				op = peek();
				if (precedence(c) <= precedence(op)) {
					printf("%c ", op);
					pop();
				}
				else break;
			}
			push(c);
		}
	}
	while (is_empty() == 0) {
		printf("%c ", pop());
	}
	printf("\n");
}