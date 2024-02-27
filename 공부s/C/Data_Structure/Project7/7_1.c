#include<stdio.h>

int fact(int n) 
{
	printf("factorial(%d)\n", n);
	if (n == 0) return 1;
	return n * fact(n - 1);
}

int main(void)
{
	int n = 3;
	printf("\nfactorial(%d) = %d\n", n, fact(n));
	
	int sum = 1;
	for (int i = n; i > 0; i--)
	{
		sum *= i;
	}
	printf("%d\n", sum);

	return 0;
}