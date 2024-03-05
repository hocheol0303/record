#include<stdio.h>

int n = 10;
//의미 있는 원소의 개수가 n인 배열의 loc번 index에 value 삽입하고 한 칸씩 뒤로

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