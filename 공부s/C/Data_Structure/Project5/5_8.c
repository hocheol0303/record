#include<stdio.h>
#include<stdlib.h>

typedef int Element;
typedef struct LinkedNode {
	Element data;
	struct LinkedNode* link;
}Node;

Node* front = NULL;
Node* rear = NULL;

void error(char* str) {
	fprintf(stderr, "%s\n", str);		//Ÿ��?, �Է��� ���ڿ�, �߰��ڷ�
	exit(1);
}

int is_empty() { return front == NULL; }
void init_queue() { front = rear = NULL; }
int size() {
	Node* p;
	int count = 0;
	for (p = front; p != NULL; p = p->link) count++;
	return count;
}
void enqueue(Element e) {
	Node* p;
	p = (Node*)malloc(sizeof(Node));

	p->data = e;
	p->link = NULL;
	
	if (is_empty()) front = rear = p;
	else {
		rear->link = p;
		rear = p;
	}
}
Element dequeue() {
	if (is_empty()) error("ť ���� ����");

	Element e;
	Node* p = front;
	front = front->link;
	
	if (front == NULL) rear = NULL;
	
	e = p->data;
	free(p);
	return e;
}
Element peek() {
	if (is_empty()) error("ť ���� ����");
	return front->data;
}
void destroy_queue() {
	while (!is_empty()) dequeue();
}
void print_queue(char* str) {
	Node* p;
	printf("%s[%2d] = ", str, size());
	for (p = front; p != NULL; p = p->link) printf("%2d", p->data);
	printf("\n");
}

int main(void)
{
	int i;
	init_queue();

	for (i = 1; i < 10; i++) enqueue(i);
	
	print_queue("����� ť enqueue() 9ȸ");
	printf("\tdequeue() --> %d\n", dequeue());
	printf("\tdequeue() --> %d\n", dequeue());
	printf("\tdequeue() --> %d\n", dequeue());
	print_queue("����� ť dequeue() 3ȸ");
	destroy_queue();
	print_queue("����� ť destroy");

}