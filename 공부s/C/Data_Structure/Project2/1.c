#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int ArrayMax(int*, int);

void main(void)
{

	srand(time(NULL));
	clock_t start, finish;
	double duration;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		continue;
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f초입니다.\n", duration);





	int a[5];

	for (int i = 0; i < 5; i++) {
		a[i] = rand()%100;
	}

	for (int i = 0; i < 5; i++)
	{
		printf("a[%d] = %d", i, a[i]);
		if (i < 4)
			printf(", ");
	}

	printf("\n");

	int t = ArrayMax(a, 5);
	printf("%d\n", t);

	return 0;
}