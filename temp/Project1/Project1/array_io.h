#include<stdio.h>

int n = 10;
//�ǹ� �ִ� ������ ������ n�� �迭�� loc�� index�� value �����ϰ� �� ĭ�� �ڷ�

void insert(int array[], int loc, int value) {
	for (int i = n; i > loc; i--)
	{
		array[i] = array[i - 1];
	}
	array[loc] = value;
}


void delete(int array[], int loc){
	for (int i = loc; i < n; i++)
	{
		array[i] = array[i + 1];
	}
}

void print_array(int n, int array[])
{
	for (int i = 0; i < n; i++) printf("array[%d] = %d\n", i, array[i]);
}