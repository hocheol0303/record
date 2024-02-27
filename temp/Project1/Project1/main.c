#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
	clock_t start, finish;
	double duration;
	int tmp;

	scanf("%d", &tmp);

	start = clock();
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			printf("hihi\n");
		}
	}
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f\n", duration);
	printf("1ÃÊ = %d CLOCKS_PER_SEC = %dms\n", (clock_t)CLOCKS_PER_SEC, (clock_t)CLOCKS_PER_SEC);

	return 0;
}