#include<stdio.h>

typedef struct ListNode {
	char data[10];
	Node* link;
} Node;

int main(void) {
	int a = 3;
	int* p = &a;
	int** pp = &p;

	int arr[5] = { 1,2,3,4,5 };
	int* ap = arr + 4;
	
	printf("a = %d\t\tp = %d\t\t\tpp = %d\n", a, p, pp);
	printf("&a = %d\t&p = %d\n", &a, &p);

	printf("*p = %d\t\t*pp = %d\t\t\t**pp = %d\n", *p, *pp, **pp);

	printf("&a Å©±â : %d\n", sizeof(&a));

	printf("ap = %d\n", *ap);
	printf("&arr = %p\n", (&arr));

	printf("%d", NULL);

	return 0;
}