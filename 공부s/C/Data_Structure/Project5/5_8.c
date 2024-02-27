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
	fprintf(stderr, "%s\n", str);		//타입?, 입력할 문자열, 추가자료
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
	if (is_empty()) error("큐 공백 에러");

	Element e;
	Node* p = front;
	front = front->link;
	
	if (front == NULL) rear = NULL;
	
	e = p->data;
	free(p);
	return e;
}
Element peek() {
	if (is_empty()) error("큐 공백 에러");
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
	
	print_queue("연결된 큐 enqueue() 9회");
	printf("\tdequeue() --> %d\n", dequeue());
	printf("\tdequeue() --> %d\n", dequeue());
	printf("\tdequeue() --> %d\n", dequeue());
	print_queue("연결된 큐 dequeue() 3회");
	destroy_queue();
	print_queue("연결된 큐 destroy");

}