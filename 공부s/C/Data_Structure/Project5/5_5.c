#include<stdio.h>
#include<stdlib.h>

typedef int Element;
typedef struct LinkedNode {
	Element data;
	struct LinkedNode* link;
} Node;

Node* top = NULL;

void error(char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}

int is_empty() { return top == NULL; }
void init_stack() { top = NULL; }
int size() {
	int cnt = 0;
	Node* p;
	for (p = top; p != NULL; p = p->link)
	{
		cnt++;
	}
	return cnt;
}
void push(Element e) {
	Node* p;
	p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->link = top;
	top = p;
}
Element pop() {
	Node* p;
	if (is_empty()) error("스택 공백 에러");

	p = top;

	Element val = p->data;
	top = p->link;

	free(p);
	return val;
}
Element peek() {
	if (is_empty()) error("스택 공백 에러");
	return (*top).data;
}
void destroy_stack() {
	while (!is_empty())
	{
		pop();
	}
}
void print_stack(char* str) {
	Node* p;
	printf("%s[%2d]= ", str, size());
	for (p = top; p != NULL; p = (*p).link) printf("%2d", (*p).data);
	printf("\n");
}

int main(void)
{
	int i;

	init_stack();

	for (i = 1; i < 10; i++)
	{
		push(i);
	}
	print_stack("연결된 스택 push 9회");
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	print_stack("연결된 스택 pop 3회");
	destroy_stack();
	print_stack("연결된 스택 destroy");

	return 0;
}