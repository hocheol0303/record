#include<stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} Polynomial;

Polynomial add_poly(Polynomial a, Polynomial b) {
	int i;
	Polynomial p, q;
	//if (a.degree > b.degree) {			//ū �� = p
	//	p = a;
	//	for (i = 0; i <= b.degree; i++) {
	//		p.coef[i + (p.degree - b.degree)] += b.coef[i];		//�迭 ���� ū �������� ���� -> (ū ��� ���� ���� ������ ����)�� ° �ε������� ������� ����
	//	}
	//}
	//else {
	//	p = b;
	//	for (i = 0; i <= a.degree; i++) {
	//		p.coef[i + (p.degree - a.degree)] += a.coef[i];
	//	}
	//}
	//
	//if�� �ݸ����� ������ ���� �� ���ϱ�
	if (a.degree > b.degree) {
		p = a;
		q = b;
	}
	else {
		p = b;
		q = a;
	}
	
	int defer, s = p.degree;	//�ְ������� �� ū ���׽��� �ְ����� ����
	
	while (1) {
		if (s == q.degree)
			break;
		s--;
	}

	defer = p.degree - s;		//�ְ����������� ���� ����

	for (i = 0; i <= p.degree; i++) {
		p.coef[i + defer] += q.coef[i];
	}

	return p;
}