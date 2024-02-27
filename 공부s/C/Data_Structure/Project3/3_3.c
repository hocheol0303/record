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

int check_matching(char* expr);

int main(void)
{
	char expr[4][80] = { "{A[(i+1)]=0;}", "if((i==0) && (j==0)", "A[(i+1])=0;", "A[i] = f)(;" };
	
	int errCode, i;

	for (i = 0; i < 4; i++)
	{
		errCode = check_matching(expr[i]);
		if (errCode == 0) {
			printf(" 정상: %s\n", expr[i]);
		}
		else {
			printf(" 오류: %s (조건%d 위반)\n", expr[i], errCode);
		}
	}
}

void error(char *str) {		//에러가 나면 문자열 출력
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

int check_matching(char* expr) {
	int i = 0;
	int prev;
	char ch;
	init_stack();

	while (expr[i] != '\0') 
	{
		ch = expr[i++];
		
		if (ch == '[' || ch == '(' || ch == '{') 
		{
			push(ch);
		}

		else if (ch == ']' || ch == ')' || ch == '}') 
		{
			if (is_empty()) 
			{
				return 2;
			}
			prev = pop();
			if ((ch == ']' && prev != '[') || (ch == ')' && prev != '(') || (ch == '}' && prev != '{') )
			{
				return 3;
			}
		}
	}
	if(is_empty() == 0) return 1;
	return 0;
}

