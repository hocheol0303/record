#include<stdio.h>
#include "Stack.h"

//�ڷᱸ�� init() ���� �߿���

int main(void)
{
	init();
	char s[130] = "fd(jsa[lh]}efwq";

	printf("bracket checking result : %d\n", bracket_checker(s));

	return 0;
}