#include<stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} Polynomial;

Polynomial read_poly() {
	int i;
	Polynomial p;

	printf("���׽��� �ְ� ������ �Է��Ͻÿ�: ");
	scanf("%d", &p.degree);
	printf("�� ���� ����� �Է��Ͻÿ� (��  %d��): ", p.degree + 1);
	for (i = 0; i <= p.degree; i++) {			//ū �������� �Է�
		scanf("%f", p.coef + i);
	}
	return p;
}