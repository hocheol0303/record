#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <windows.h>
#define SIZE 3

//Ŀ�� �̵� �� �ʿ��� ��
enum keyInput { UP, DOWN, LEFT, RIGHT, SUBMIT };

typedef struct UserInfo {		//���� ���� �Է�
	char name[20];
	int age;
	int count;
} Rate;

void unblink();
void goBack();
void printTemplates();
int keyControl();
void title();
int menu();
void gotoxy(int, int); // ��ǥ���� �Լ�
void hanoi(char, char, char, int, int*);	//������ ��� Ž��
void hanoiGame(Rate* U);		//�ϳ���ž ����

extern update(Rate* U, int lev);	//����ǥ ������Ʈ �Լ�
extern openRank(int lev);			//����ǥ ��� �Լ�
extern createFile(int lev);			//����ǥ ���翩�� Ȯ�� / ���� �Լ�

int main() {
	unblink();
	while (1) {
		title();

		int menu_Selcet = menu();
		if (menu_Selcet == 0) { //���ӽ���
			// ���� ���� �Լ� �ִ°� 
			Rate s;
			hanoiGame(&s);
		}
		else if (menu_Selcet == 2) {
			int n;
			int count = 0;
			system("cls");
			printf("�� ���� ������ �̿��� �ּҰ�ΰ� �ñ��Ѱ���?:");
			scanf("%d", &n);
			hanoi('A', 'B', 'C', n, &count);
			printf("�� %dȸ �̵��߽��ϴ�.\n", count);
			goBack();
			//�ּҰ� ��� �Լ�
		}
		else if (menu_Selcet == 4) {
			printTemplates(); // �ڵ庸��
		}
		else if (menu_Selcet == 6) {
			system("cls");
			printf("����ǥ�� ������� ���̵��� �Է��ϼ���:");
			int lev;
			scanf("%d", &lev);
			openRank(lev); //����ǥ
			goBack();
		}
		else if (menu_Selcet == 8) {// ���α׷� ����
			system("cls");
			printf("�����ϼ̽��ϴ�.\n");
			return 0;
		}
		system("cls");
	}
	return 0;
}

void title() {
	printf(" __________________\n");
	printf("| ���۹�:   w      |\n");
	printf("|         a s d    |\n");
	printf("| ����: �����̽��� |\n");
	printf("|__________________|\n");
	printf("				  ____________________________________________________ \n");
	printf("				 |                                                    |\n");
	printf("				 |  ��  ��      ��      ��    ��     ����     ������  |\n");
	printf("				 |  ��  ��    ��  ��    ����  ��    ��  ��      ��    |\n");
	printf("				 |  ������    ������    �� �� ��   ��    ��     ��    |\n");
	printf("				 |  ��  ��    ��  ��    ��  ����    ��  ��      ��    | 20220846 ������\n");
	printf("				 |  ��  ��    ��  ��    ��    ��     ����     ������  | 20220848 ��ȣö\n");
	printf("				 |____________________________________________________| 20220850 ������ ");

}

int menu() {
	int x = 55;
	int y = 15;
	gotoxy(x - 2, y); // >�� ����ֱ� ������ -2
	printf("> ���� ����");
	gotoxy(x, y + 2);
	printf("�ִ� ���");
	gotoxy(x, y + 4);
	printf("�ڵ� ����");
	gotoxy(x, y + 6);
	printf(" ����ǥ ");
	gotoxy(x, y + 8);
	printf("  ����  ");


	while (1) {
		int n = keyControl(); // Ű���� �Է��� �޾ƿ�
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				printf(" ");  // ���� �ڸ��� �ִ� >�� ������
				--y;
				gotoxy(x - 2, --y);
				printf(">");  // �̵��� �ڸ��� �ٽ� ǥ����
			}
			break;
		}

		case DOWN: {
			if (y < 23) { // ������ ��ư�� ��ġ
				gotoxy(x - 2, y);
				printf(" ");
				++y;
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			return y - 15;
		}
		}
	}
}
// Ŀ�� ��ġ �̵�
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
// Ŀ���� �����̴� ���� ����
void unblink() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

int keyControl() {
	char temp = getch(); // �����̾��� �ٷ� �Է�

	// �빮�� �ҹ��� ���Ϲ� �Է�
	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') {
		return SUBMIT;
	}
}

enum color { green = 10, blue, red, pink, yellow, white };
void textColor(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
};

//�ϳ���ž ����Լ��� ����� ���� ���ø� ����
void printTemplates() {
	system("cls");
	printf("�ϳ���ž �ڵ��� ������� ������ �л��鿡�� �ʿ��� ���ø�\n\n");
	printf("-----------------------------------------\n");
	printf("#include<stdio.h>\n#define SIZE (number)\n\n");
	printf("void hanoi(char, char, char, int)\n{");
	printf("\n\tif(n == 1)\n\t\t");
	textColor(yellow);
	printf("��������~~\n\t");
	textColor(white);
	printf("else\n\t{\n\t\t");
	textColor(yellow);
	printf("hanoi(~~);\n\t\tprintf(~~);\n\t\thanoi(~~);\n\t");
	textColor(white);
	printf("}\n}\n\n");
	printf("int main (void)\n");
	printf("{\n\thanoi('A','B','C',SIZE)\n}\n");
	printf("-----------------------------------------\n");

	goBack();
}

//���� �޴��� �ǵ��ư��� �ϴ� �Լ�
void goBack() {
	printf("�ڷ� ������ �����̽��ٸ� ��������.");
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

//�ϳ���ž �˰����� ���� �� ���� �������� �˾Ƴ���
void hanoi(char from, char other, char to, int n, int* cnt) {
	if (n == 1) {
		printf("%c -> %c\n", from, to);
		(*cnt)++;
	}
	else
	{
		hanoi(from, to, other, n - 1, cnt);			//�� �� ������� 1.a->b 2.a->b�� ���� ��찡 �Ȼ���ϴ�.
		printf("%c -> %c\n", from, to);
		(*cnt)++;
		hanoi(other, from, to, n - 1, cnt);
	}

}

//�ϳ���ž ����
void hanoiGame(Rate* U)
{
	int count = 0;
	int lv;
	int i, j, k;
	int hand = -1;
	int finish = 0;
	int temp;
	U->count = 0;
	system("cls");

	printf("�̸��� �Է��ϼ���:");
	scanf("%s", U->name);
	printf("���̸� �Է��ϼ���:");
	scanf("%d", U->age);

	printf("������ ������ �Է��ϼ���(1�� �̻�):");
	scanf("%d", &lv);
	if (lv <= 0)
	{
		printf("������ ������ 1�� �̻��̾�� �մϴ�.\n");
		return 0;
	}
	char target[3][10];
	char pic[3][10];
	//ù ��°: ��� ��ȣ
	//�� ��°: �� ��ȣ
	//�� ��° ��: ���ڸ� -1, �Ⱥ�� ���� ��ȣ

	//0�� ���� ���� �ִ� �ɷ� ġ�� 2������ ��� ������

	for (i = 0; i < 3; i++)		//���� �ʱ�ȭ
	{
		for (j = 0; j < lv; j++)
		{
			if (i == 0)
			{
				target[i][j] = lv - 1 - j;
			}
			else
			{
				target[i][j] = -1;
			}
		}
	}

	system("cls");
	printf("Ű������ a, b, c�� �Է��Ͽ� ����� ������ �� �ֽ��ϴ�.\n\n");
	printf("A ��տ� �ִ� ��� ������ C ������� �ű⼼��\n\n");
	printf("�ű� ��ġ�� �ִ� ������ ������ ���Ǻ��� ���� �� �����ϴ�.\n\n");
	printf("���� �ϼ����� �ƹ� Ű�� ��������.");
	temp = getch();
	system("cls");

	while (1)		//���� ����
	{
		printf("\n\n");
		for (j = lv - 1; j > -1; j--)	//�� Ž��(����������)
		{
			for (i = 0; i < 3; i++)		//��� Ž��
			{
				printf("|");
				if (target[i][j] == -1)		//target = -1 �� ���� �� �ڸ��� �ƹ� ������ ���� �ʴٴ� ���Դϴ�.
				{
					for (k = 0; k < 10; k++)
					{
						printf(" ");		//i = ����� ��ȣ, j = ��, k�� ���� �ش� ���� ��ĭ���� �α� �� 10ĭ
					}
				}
				else
				{
					for (k = -1; k < target[i][j]; k++)
						printf("*");			//target�� ������ ��ȣ�� ����, k�� -1���� ������ ������ ���� ��ȣ�� 0������ �����߱� ������ 0���� �����ϴ� �����̶�� ��ĭ���� ���Ե�
					for (k = 10 - target[i][j] - 1; k > 0; k--)
						printf(" ");			//��ü 10ĭ �� *�� ä���� ���� �κ��� �������� ä���
				}
				printf("|");
			}
			printf("\n");
		}
		for (i = 0; i < 3; i++)
		{
			printf("%7c", 'A' + i);		//���� �Ʒ��κ� A, B, C ����ϴ� �κ� ��հ� ���͸� ���� %7c�� ��ü 7ĭ �� �����ʿ� �ٿ��� 'A' + i �� �ش��ϴ� ��ȣ�� ���
			printf("%5c", ' ');			//���� ����
		}

		int from, to;
		printf("\n� �ڸ��� ������ �ű�� �ͽ��ϱ�? (a, b, c): ");
		from = getch();
		putch(from);
		printf("\n���� ������ �ͽ��ϱ�? (a, b, c): ");
		to = getch();
		putch(to);
		printf("\n");

		if (from >= 'A' && from <= 'C')
			from += 32;
		else if (to >= 'A' && to <= 'C')
			to += 32;
		else
		{
			from -= 'a';		//���� ����� �ε����� 0, 1, 2 �̱� ������ a, b, c�� �Է¹ް� 'a'�� ���ָ� ���� 0, 1, 2�� ���� ������� (�ƽ�Ű�ڵ� ����)
			to -= 'a';
		}

		if (from < 0 || from > 2 || to < 0 || to > 2)	//���� �� a, b, c�� �ƴ� �ٸ� �Է��� ���� �� ���� �߻�
		{
			printf("�߸� �Է��ϼ̽��ϴ�. a~c ���� ���ĺ��� �Է����ּ���.");
			continue;
		}
		i = lv - 1;
		while (1)	//������� �� �� ���� ã��
		{
			if ((i < 0 && hand == -1) || from == to)		//����ó�� 
			{
				printf("\n\n���� �߸��ϼ̱���. �ٽ� �Է��ϼ���.\n");
				break;
			}
			if (target[from][i] >= 0)
			{
				hand = target[from][i];
				temp = i;
				target[from][i] = -1;
				printf("\n%d�� ° �̵�: %c -> %c\n", ++count, from + 'A', to + 'A');
				break;
			}
			i--;
		}

		i = 0;
		while (1)		//�������� �� ����ȣ�� �տ� �� ���� ��ȣ ��
		{
			if (hand == -1)
				break;
			if (target[to][i] == -1) {
				if (i == 0)
				{
					target[to][i] = hand;
					printf("�ű� ���� ��ȣ:%d\n\n", hand);
					hand = -1;
					break;
				}
				else if (target[to][i - 1] != -1 && target[to][i - 1] < hand) {
					printf("�߸� �� �������Դϴ�. �ٽ� �Է��ϼ���.\n");
					target[from][temp] = hand;
					hand = -1;
					count--;
					printf("%dȸ �� ����\n\n", count);
					break;
				}
				else if (target[to][i - 1] > hand)
				{
					printf("�ű� ���� ��ȣ:%d\n", hand);
					target[to][i] = hand;
					hand = -1;
					break;
				}

			}
			i++;
		}

		for (i = 0; i < lv; i++)
		{
			if (target[2][i] != -1) {	//C ����� ��� ĭ�� ������ �������ִ��� Ȯ��
				finish = 1;
			}
			else
			{
				finish = 0;
				break;
			}
		}
		if (finish == 1)				//finish�� 1�� ä�� �����ٸ� ������ �������� �˸�
		{
			printf("�� %dȸ ���������ϴ�.\n\n", count);
			U->count = count;
			update(U, lv);

			printf("�ڷ� ���÷��� �����̽��ٸ� �����ÿ�");
			while (1) {
				if (keyControl() == SUBMIT) {
					return 0;
				}
			}
		}
	}
}