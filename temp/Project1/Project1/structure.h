#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*����ü*/
//����ü ���� + typedef�� �ڷ��� ����
typedef struct Student {
	int stdNum;
	int age;
	char name[20];
} Student;

//Student ����ü ���� ���
void print_structure(Student* std)
{
	printf("�̸� : %s\n", std->name);
	printf("�й� : %d\n", std->stdNum);
	printf("���� : %d\n", std->age);
}

//Student B = A : ���� ���� ����
//Student *B = &A : ���� ��ü ����Ŵ
//���� ���� ���ڿ� ������ �Ҵ��� strcpy()�Լ� ���


typedef struct {
	int real;
	int imagine;
}Complex;

Complex add_comple(Complex a, Complex b) {
	Complex tmp = { a.real + b.real, a.imagine + b.imagine };
	return tmp;
}