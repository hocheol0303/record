#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*구조체*/
//구조체 정의 + typedef로 자료형 변경
typedef struct Student {
	int stdNum;
	int age;
	char name[20];
} Student;

//Student 구조체 변수 출력
void print_structure(Student* std)
{
	printf("이름 : %s\n", std->name);
	printf("학번 : %d\n", std->stdNum);
	printf("나이 : %d\n", std->age);
}

//Student B = A : 값에 의한 참조
//Student *B = &A : 같은 객체 가리킴
//선언 이후 문자열 변수의 할당은 strcpy()함수 사용


typedef struct {
	int real;
	int imagine;
}Complex;

Complex add_comple(Complex a, Complex b) {
	Complex tmp = { a.real + b.real, a.imagine + b.imagine };
	return tmp;
}