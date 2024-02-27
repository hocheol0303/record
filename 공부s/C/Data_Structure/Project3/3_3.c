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

int check_matching(char* expr);

int main(void)
{
	char expr[4][80] = { "{A[(i+1)]=0;}", "if((i==0) && (j==0)", "A[(i+1])=0;", "A[i] = f)(;" };
	
	int errCode, i;

	for (i = 0; i < 4; i++)
	{
		errCode = check_matching(expr[i]);
		if (errCode == 0) {
			printf(" ����: %s\n", expr[i]);
		}
		else {
			printf(" ����: %s (����%d ����)\n", expr[i], errCode);
		}
	}
}

void error(char *str) {		//������ ���� ���ڿ� ���
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

