#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int* (arr[5]);
	for (int i = 0; i < 5; i++) {
		int* p = (int*)malloc(sizeof(int));
		scanf("%d", p);
		arr[i] = p;
	}
	for (int i = 0; i < 5; i++) {
		printf("%d\n", *(arr[i]));
	}

	return 0;
}