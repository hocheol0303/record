#include<stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} Polynomial;

Polynomial read_poly();
void print_poly(Polynomial p, char str[]);
Polynomial add_poly(Polynomial a, Polynomial b);

void main() {
	Polynomial a, b, c;
	a = read_poly();
	b = read_poly();
	c = add_poly(a, b);
	print_poly(a, "A = ");
	print_poly(b, "B = ");
	print_poly(c, "A + B = ");

	return 0;
}