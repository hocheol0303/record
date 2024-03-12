#include<stdio.h>
#include "Stack.h"

//자료구조 init() 졸라리 중요함

int main(void)
{
	init();
	char s[130] = "fd(jsa[lh]}efwq";

	printf("bracket checking result : %d\n", bracket_checker(s));

	return 0;
}