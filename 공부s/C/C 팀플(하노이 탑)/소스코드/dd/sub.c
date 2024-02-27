#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>		//system("cls")
#include<stdlib.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS

char* randomName[10] = { "����", "ȣ����", "����", "��þ", "���̼�", "������", "����", "��ī��", "�θ�", "����" };

enum keyInput { UP, DOWN, LEFT, RIGHT, SUBMIT };

extern keyControl();
void createFile(int lev);
char* makeText(int n);		//���̵��� �Է� �޾Ƽ� �ؽ�Ʈ�� ����� ���̱� ������ ���ϰ� �����ͺ���.

typedef struct UserInfo {		//���� ���� �Է�
	char name[20];
	int age;
	int count;
} Rate;

//����ǥ�� �ִ��� Ȯ���ϰ� ���ٸ� ���� �����ϴ� �Լ�
void createFile(int lev)
{
	srand(time(NULL));
	char ch[30];
	int count[5];
	int age;
	char* name[5];
	int i, j = 0;
	int temp;
	char text[20];
	strcpy(text, makeText(lev));

	FILE* rank;
	rank = fopen(text, "r");
	if (rank == NULL)				//�б� �������� ������ ������ �ʾҴٴ� ���� ������ �������� �ʴٴ� �� ���� ������� fopen(~~, "r")���� "r"�� ���
	{
		rank = fopen(text, "w");
		//���Ƿ� ��� ����	Ƚ��, �̸�, ���� �� Ƚ���� ���� ������� �Է�
		for (i = 0; i < 5; i++)
		{
			count[i] = rand() % 100 + 5;
			name[i] = randomName[rand() % 10];	//���������� ����� �̸����� �ּҰ��� ���Ƿ� ����
		}
		for (i = 0; i < 5; i++)
		{
			for (j = i + 1; j < 5; j++)
			{
				if (count[i] > count[j])
				{
					temp = count[i];
					count[i] = count[j];
					count[j] = temp;
				}
			}
		}
		for (i = 0; i < 5; i++)
		{
			age = rand() % 150;
			fprintf(rank, "%d ", count[i]);
			fprintf(rank, "%s ", name[i]);
			fprintf(rank, "%d\n", age);
		}
	}
	fclose(rank);
}

void update(Rate* s, int lev)
{
	char ch[30];
	//�ִ� 29 ĭ�� ������ �Է�
	int i, j;
	int count[5];
	int age[5];
	char name[5][20];				//���Ͽ��� �о ������ �ڸ�
	char text[20];
	strcpy(text, makeText(lev));	//�ش� ���̵��� ���� ���� �̸��� ���� text ������ �ֽ��ϴ�.

	createFile(lev);
	FILE* rank;
	rank = fopen(text, "a+");	//���� ���� text = "rank���̵�.txt"�� ������ ����

	if (rank == NULL)
	{
		printf("���ο� ������ ������ �� �����ϴ�.\n");
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			fgets(ch, 30, rank);				//�� �پ� �о���� �Լ� (������ �ּ�, ���ڿ� �ִ� ����, ���Ϻ����� �ּ�)
			count[i] = atoi(strtok(ch, " "));	//ù ��° ��ū�� int�� ����
			strcpy(name[i], strtok(NULL, " "));	//�� ��° ��ū�� ���ڿ��� ����
			age[i] = atoi(strtok(NULL, " "));	//�� ��° ��ū�� int�� ����
		}
	}

	for (i = 0; i < 5; i++)			//���ο� �� �Է¹޾Ƽ� �ش� ������ �о�ֱ�
	{
		if (s->count < count[i])		//s->count = (*s).count
		{								//����ü ������ ������ ���� ��� �����Դϴ�.
			for (j = 4; j > i; j--)
			{
				count[j] = count[j - 1];
				age[j] = age[j - 1];
				strcpy(name[j], name[j - 1]);
			}
			count[i] = s->count;
			age[i] = s->age;
			strcpy(name[i], s->name);
			break;
		}
	}
	fclose(rank);

	//�� ��� �ֱ�
	rank = fopen(text, "w");	//���� �߰��� ������ �̿��� ���ο� ���� ����
	for (int i = 0; i < 5; i++)
	{
		fprintf(rank, "%d ", count[i]);
		fprintf(rank, "%s ", name[i]);
		fprintf(rank, "%d\n", age[i]);
	}
	fclose(rank);

}

//rank����.txt ������ �о ����ϴ� �Լ�
void openRank(int lev)
{
	system("cls");
	createFile(lev);
	FILE* rank;
	char ch[30];
	char text[20];
	strcpy(text, makeText(lev));

	int count[5];
	char name[5][20];	//�̸��� �ѱ۷� 9���ڰ� �Ѿ�� ���� ���ϴ�. ���� �����մϴ�.
	int age[5];

	rank = fopen(text, "r");
	if (rank == NULL)
	{
		printf("����");
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			fgets(ch, 30, rank);					//rank��� �ؽ�Ʈ ���Ͽ��� 30���� �̳��� ���ڿ��� ch�� ����ϴ� �Լ�
			count[i] = atoi(strtok(ch, " "));
			strcpy(name[i], strtok(NULL, " "));		//strtok�Լ��� NULL���� ������ ������ �Է� �Ǿ��� ������ ���� ���� ���ĸ� �н��ϴ�.
			age[i] = atoi(strtok(NULL, " "));
		}
	}
	fclose(rank);

	printf("%50s\n", "����ǥ");
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("|%20s|", "����");
	printf("|%20s|", "�̸�");
	printf("|%20s|", "����");
	printf("|%20s|\n", "�̵� Ƚ��");
	for (int i = 0; i < 5; i++)
	{
		printf("|%20d|", i + 1);
		printf("|%20s|", name[i]);
		printf("|%20d|", age[i]);
		printf("|%20d|\n", count[i]);
	}
}

//�Է¹��� ���̵��� ���� ���� ������ ������ �̸��� ����� �Լ�
char* makeText(int n)
{
	char buffer[10];
	sprintf(buffer, "%d", n);
	char text[20] = "rank";
	strcat(text, buffer);
	strcat(text, ".txt");
	return text;
}