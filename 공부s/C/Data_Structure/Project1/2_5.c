#include<stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} Polynomial;

Polynomial read_poly() {
	int i;
	Polynomial p;

	printf("다항식의 최고 차수를 입력하시오: ");
	scanf("%d", &p.degree);
	printf("각 항의 계수를 입력하시오 (총  %d개): ", p.degree + 1);
	for (i = 0; i <= p.degree; i++) {			//큰 차수부터 입력
		scanf("%f", p.coef + i);
	}
	return p;
}