#include<stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} Polynomial;

Polynomial add_poly(Polynomial a, Polynomial b) {
	int i;
	Polynomial p, q;
	//if (a.degree > b.degree) {			//큰 놈 = p
	//	p = a;
	//	for (i = 0; i <= b.degree; i++) {
	//		p.coef[i + (p.degree - b.degree)] += b.coef[i];		//배열 방이 큰 차수부터 시작 -> (큰 놈과 작은 놈의 차수의 차이)번 째 인덱스부터 순서대로 덧셈
	//	}
	//}
	//else {
	//	p = b;
	//	for (i = 0; i <= a.degree; i++) {
	//		p.coef[i + (p.degree - a.degree)] += a.coef[i];
	//	}
	//}
	//
	//if문 반목문으로 차수가 같을 때 더하기
	if (a.degree > b.degree) {
		p = a;
		q = b;
	}
	else {
		p = b;
		q = a;
	}
	
	int defer, s = p.degree;	//최고차항이 더 큰 다항식의 최고차수 저장
	
	while (1) {
		if (s == q.degree)
			break;
		s--;
	}

	defer = p.degree - s;		//최고차수사이의 차를 저장

	for (i = 0; i <= p.degree; i++) {
		p.coef[i + defer] += q.coef[i];
	}

	return p;
}