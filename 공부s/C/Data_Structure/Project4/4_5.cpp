#include<stdio.h>
#include<stdlib.h>
#define MAX_QUEUE_SIZE 100
typedef int Element;

void error(const char* str) 
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

class Queue {
	Element data[MAX_QUEUE_SIZE];
	int front;
	int rear;
public:
	void init_queue() { front = rear = 0;; }
	int is_empty() { return front == rear;; }
	int is_full() { return (rear + 1) % MAX_QUEUE_SIZE == front; }
	int size() { return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

	void enqueue(Element val)
	{
		if (is_full())
			error(" 큐 포화 에러");
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		data[rear] = val;
	}
	Element dequeue()
	{
		if (is_empty())
			error(" 큐 공백 에러");
		front = (front + 1) % MAX_QUEUE_SIZE;
		return data[front];
	}
	Element peek()
	{
		if (is_empty())
			error(" 큐 공백 에러");
		return data[(front + 1) % MAX_QUEUE_SIZE];
	}
	void print_queue(const char* msg) {
		int i, maxi = rear;
		if (front >= rear) maxi += MAX_QUEUE_SIZE;
		printf(" %s[%2d]= ", msg, size());
		for (i = front + 1; i <= maxi; i++)
			printf("%2d ", data[i % MAX_QUEUE_SIZE]);
		printf("\n");
	}
};

int main(void)
{
	int i;
	Queue q;
	q.init_queue();

	for (i = 1; i < 10; i++)
		q.enqueue(i);
	q.print_queue("원형큐 enqueue 9회");
	printf("\tdequeue() --> %d\n", q.dequeue());
	printf("\tdequeue() --> %d\n", q.dequeue());
	printf("\tdequeue() --> %d\n", q.dequeue());
	q.print_queue("원형큐 dequeue 3회");
}