#include<stdio.h>
#define MAX_DEGREE 10
#define MAX_TERMS 10	//���� �ִ� ����

typedef struct {
	int degree;
	int coef[MAX_DEGREE];
} Polynomial;

//���׽� ���
/*
void print_Poly(Polynomial p)
{
	for (int i = p.degree; i > 0; i--)
	{
		if (p.coef[i] == 0) continue;
		printf("%d x^%d  +  ", p.coef[i], i);
	}
	printf("%d\n", p.coef[0]);
}
*/

//���׽� ��� ���� ���� 1-(3)
void print_Poly(Polynomial p) {
	for (int i = p.degree-1; i > 0; i--) {		//0���� �����ϱ� ������ �ְ������� n�̸� �迭�� n-1����
		if (p.coef[i] != 0 && p.coef[i] != 1) printf("%d x^%d + ", p.coef[i], i);
		else if (p.coef[i] == 1) printf("x^%d + ", p.coef[i], i);
	}
	if (p.coef[0] == 1) printf("1\n");
	else printf("%d\n");
}

//���׽� �����
Polynomial read_poly()
{
	Polynomial p;
	printf("�ְ����� �Է� : ");
	scanf("%d", &p.degree);
	
	printf("�ְ����� ������� ���ʴ�� �Է�\n");

	for (int i = p.degree; i >= 0; i--)
	{
		printf("%d���� ��� : ", i);
		scanf("%d", &p.coef[i]);
	}
	return p;
}

//�� ���׽��� �� ����
Polynomial add_poly(Polynomial a, Polynomial b)
{
	Polynomial p, higher, lower;
	if (a.degree > b.degree)
	{
		higher = a;
		lower = b;
	}
	else
	{
		higher = b;
		lower = a;
	}
	
	p.degree = higher.degree;

	for (int i = higher.degree; i > lower.degree; i--)
	{
		p.coef[i] = higher.coef[i];
	}
	for (int i = lower.degree; i >= 0; i--)
	{
		p.coef[i] = higher.coef[i] + lower.coef[i];
	}

	return p;
}

//��Ҵ��׽�(�޸� ���� ���� ���)�� ����ü : ���� �ִ� ���� ���س��� {���, ����} ������ ���׽�

//���� 2-(1)
typedef struct {
	int coeff;		//���
	int expon;		//����
} Term;

typedef struct {
	int nTerms;		//����� 0�� �ƴ� ���� ����
	Term* term;		//����� 0�� �ƴ� ���� �迭
	//�����͸� ������� ������ �迭�� �ּҸ� �����ϴ� ������� �ʱ�ȭ �Ұ���
}SparsePoly;

void printSPoly(SparsePoly p) {
	for (int i = p.nTerms - 1; i > 0; i--) {
		printf("%d x^%d + ", p.term[i].coeff, p.term[i].expon);
	}
	if (p.term[0].coeff == 1 && p.term[0].expon == 0) printf("1\n", p.term[0].coeff, p.term[0].expon);
	else if (p.term[0].expon == 0) printf("%d\n", p.term[0].coeff);
	else if (p.nTerms == 1) printf("%d x^%d\n", p.term[0].coeff, p.term[0].expon);
}

SparsePoly read_spoly() {
	int i;
	Term t[MAX_TERMS] = { 0, };
	printf("�� �� �� : ");
	scanf("%d", &i);

	SparsePoly a = { i, t };

	for (i = 0; i < a.nTerms; i++) {
		printf("%d�� ° �� ��� : ", i);
		scanf("%d", &t[i].coeff);
		printf("%d�� ° �� ���� : ", i);
		scanf("%d", &t[i].expon);
	}

	return a;
}

//�𸣰ھ��
//��ư ��
SparsePoly add_spoly(SparsePoly a, SparsePoly b) {
	int i = a.nTerms - 1;
	int j = b.nTerms - 1;
	int k = 0;
	Term t[MAX_TERMS] = { 0, };

	while (i >= 0 && j >= 0) {
		if (a.term[i].expon == b.term[j].expon) {
			t[k].coeff = a.term[i].coeff + b.term[j].coeff;
			t[k].expon = a.term[i].expon; // �Ǵ� t[k].expon = b.term[j].expon;
			i--; j--; k++;
		}

		////////////////////////////���� ����
		//�� term �������� �����ϰ� ���� ���� �� �������鼭 ŸŸŸŸ
		else if (a.term[i].expon > b.term[j].expon) {
			t[k] = a.term[i];
			i--; k++;
		}
		else {
			t[k] = b.term[j];
			j--; k++;
		}
	}

	//�� �ȱ� ���� ������ �ݱ�
	while (i >= 0) {
		t[k] = a.term[i];
		i--; k++;
	}

	while (j >= 0) {
		t[k] = b.term[j];
		j--; k++;
	}

	SparsePoly result = { k, t };
	return result;
}
