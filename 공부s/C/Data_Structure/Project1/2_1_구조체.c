#include<stdio.h>
#include<string.h>

typedef struct Student {
	int id;
	char name[20];
	double score;
} Ho;

int main(void)
{
	struct Student a ;
	Ho b = { 20220848, "ȣ����", 2800.2 };

	a.id = 20220848;
	strcpy(a.name, "ȣ�����θ���");
	a.score = 40000.3;
	
	printf("a\n");
	printf("�й�\t\t�̸�\t\t����\n");
	printf("%d\t%s\t%.1f\n\n", a.id, a.name, a.score);

	printf("b\n");
	printf("�й�\t\t�̸�\t\t����\n");
	printf("%d\t%s\t\t%.1f\n\n", b.id, b.name, b.score);

	Ho c = a;		//�ʵ�
	printf("c\n");
	printf("�й�\t\t�̸�\t\t����\n");
	printf("%d\t%s\t\t%.1f\n", c.id, c.name, c.score);



	return 0;
}