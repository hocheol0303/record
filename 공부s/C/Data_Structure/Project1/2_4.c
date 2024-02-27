#include<stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} Polynomial;

void print_poly(Polynomial p, char str[]) {
	int i;
	printf("\t%s", str);
	for (i = 0; i < p.degree; i++) {			//p.degree차수부터 차례대로 계수 입력
		printf("%5.1f x^%d + ", p.coef[i], p.degree - i);		//큰 차수부터 내려가면서 차수 입력 -> 차수는 갈수록 작아짐
	}
	printf("%4.1f\n", p.coef[p.degree]);
}