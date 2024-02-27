#include<stdio.h>
#define MAX_TERMS 100

typedef struct {	//하나의 항씩 저장하는 구조체
	int expon;		//차수
	float coeff;	//계수
}Term;

typedef struct {
	int nTerms;
	Term term[MAX_TERMS];
	scanf("%d", &nTerms);

} SparsePoly;

int main(void)
{
	
}