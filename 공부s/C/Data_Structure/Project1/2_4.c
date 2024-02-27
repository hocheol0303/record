#include<stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} Polynomial;

void print_poly(Polynomial p, char str[]) {
	int i;
	printf("\t%s", str);
	for (i = 0; i < p.degree; i++) {			//p.degree�������� ���ʴ�� ��� �Է�
		printf("%5.1f x^%d + ", p.coef[i], p.degree - i);		//ū �������� �������鼭 ���� �Է� -> ������ ������ �۾���
	}
	printf("%4.1f\n", p.coef[p.degree]);
}