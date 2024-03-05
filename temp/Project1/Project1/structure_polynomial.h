#include<stdio.h>
#define MAX_DEGREE 10
#define MAX_TERMS 10	//항의 최대 개수

typedef struct {
	int degree;
	int coef[MAX_DEGREE];
} Polynomial;

//다항식 출력
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

//다항식 출력 업글 문제 1-(3)
void print_Poly(Polynomial p) {
	for (int i = p.degree-1; i > 0; i--) {		//0차항 존재하기 때문에 최고차항이 n이면 배열은 n-1까지
		if (p.coef[i] != 0 && p.coef[i] != 1) printf("%d x^%d + ", p.coef[i], i);
		else if (p.coef[i] == 1) printf("x^%d + ", p.coef[i], i);
	}
	if (p.coef[0] == 1) printf("1\n");
	else printf("%d\n");
}

//다항식 만들기
Polynomial read_poly()
{
	Polynomial p;
	printf("최고차항 입력 : ");
	scanf("%d", &p.degree);
	
	printf("최고차항 계수부터 차례대로 입력\n");

	for (int i = p.degree; i >= 0; i--)
	{
		printf("%d차항 계수 : ", i);
		scanf("%d", &p.coef[i]);
	}
	return p;
}

//두 다항식의 합 연산
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

//희소다항식(메모리 낭비가 심한 경우)의 구조체 : 항의 최대 개수 정해놓고 {계수, 차수} 형태의 다항식

//문제 2-(1)
typedef struct {
	int coeff;		//계수
	int expon;		//지수
} Term;

typedef struct {
	int nTerms;		//계수가 0이 아닌 항의 개수
	Term* term;		//계수가 0이 아닌 항의 배열
	//포인터를 사용하지 않으면 배열의 주소를 전달하는 방식으로 초기화 불가능
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
	printf("항 몇 개 : ");
	scanf("%d", &i);

	SparsePoly a = { i, t };

	for (i = 0; i < a.nTerms; i++) {
		printf("%d번 째 항 계수 : ", i);
		scanf("%d", &t[i].coeff);
		printf("%d번 째 항 지수 : ", i);
		scanf("%d", &t[i].expon);
	}

	return a;
}

//모르겠어요
//뤼튼 답
SparsePoly add_spoly(SparsePoly a, SparsePoly b) {
	int i = a.nTerms - 1;
	int j = b.nTerms - 1;
	int k = 0;
	Term t[MAX_TERMS] = { 0, };

	while (i >= 0 && j >= 0) {
		if (a.term[i].expon == b.term[j].expon) {
			t[k].coeff = a.term[i].coeff + b.term[j].coeff;
			t[k].expon = a.term[i].expon; // 또는 t[k].expon = b.term[j].expon;
			i--; j--; k++;
		}

		////////////////////////////여기 못함
		//각 term 내림차순 가정하고 차수 높은 놈꺼 내려가면서 타타타타
		else if (a.term[i].expon > b.term[j].expon) {
			t[k] = a.term[i];
			i--; k++;
		}
		else {
			t[k] = b.term[j];
			j--; k++;
		}
	}

	//다 훑기 전에 끝난거 줍기
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
