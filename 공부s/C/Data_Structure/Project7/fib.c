#include<stdio.h>

int i;

int fib(int n)
{
	i++;
	if (n == 0) {
		printf("0\n");
		return 0;
	}
	if (n == 1) {
		printf("1\n");
		return 1;
	}


	return fib(n - 1) + fib(n - 2);
}

int main(void)
{
	printf("%d\n", fib(10));

	printf("함수 %d회 호출", i);
	return 0;
}