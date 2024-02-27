#include<stdio.h>

int main(void)
{
	char str[100];
	gets(str);
	int i = -1;

	while (str[++i] != '\0');

	//printf("%d\n", i);

	while (i>-1) {
		printf("%c", str[i--]);
	}
}