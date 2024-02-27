#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <windows.h>
#define SIZE 3

//커서 이동 시 필요한 값
enum keyInput { UP, DOWN, LEFT, RIGHT, SUBMIT };

typedef struct UserInfo {		//유저 정보 입력
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
void gotoxy(int, int); // 좌표지정 함수
void hanoi(char, char, char, int, int*);	//최적의 경로 탐색
void hanoiGame(Rate* U);		//하노이탑 게임

extern update(Rate* U, int lev);	//순위표 업데이트 함수
extern openRank(int lev);			//순위표 출력 함수
extern createFile(int lev);			//순위표 존재여부 확인 / 생성 함수

int main() {
	unblink();
	while (1) {
		title();

		int menu_Selcet = menu();
		if (menu_Selcet == 0) { //게임시작
			// 게임 시작 함수 넣는곳 
			Rate s;
			hanoiGame(&s);
		}
		else if (menu_Selcet == 2) {
			int n;
			int count = 0;
			system("cls");
			printf("몇 개의 원판을 이용한 최소경로가 궁금한가요?:");
			scanf("%d", &n);
			hanoi('A', 'B', 'C', n, &count);
			printf("총 %d회 이동했습니다.\n", count);
			goBack();
			//최소값 계산 함수
		}
		else if (menu_Selcet == 4) {
			printTemplates(); // 코드보기
		}
		else if (menu_Selcet == 6) {
			system("cls");
			printf("순위표를 보고싶은 난이도를 입력하세요:");
			int lev;
			scanf("%d", &lev);
			openRank(lev); //순위표
			goBack();
		}
		else if (menu_Selcet == 8) {// 프로그램 종료
			system("cls");
			printf("수고하셨습니다.\n");
			return 0;
		}
		system("cls");
	}
	return 0;
}

void title() {
	printf(" __________________\n");
	printf("| 조작법:   w      |\n");
	printf("|         a s d    |\n");
	printf("| 선택: 스페이스바 |\n");
	printf("|__________________|\n");
	printf("				  ____________________________________________________ \n");
	printf("				 |                                                    |\n");
	printf("				 |  ㅁ  ㅁ      ㅁ      ㅁ    ㅁ     ㅁㅁ     ㅁㅁㅁ  |\n");
	printf("				 |  ㅁ  ㅁ    ㅁ  ㅁ    ㅁㅁ  ㅁ    ㅁ  ㅁ      ㅁ    |\n");
	printf("				 |  ㅁㅁㅁ    ㅁㅁㅁ    ㅁ ㅁ ㅁ   ㅁ    ㅁ     ㅁ    |\n");
	printf("				 |  ㅁ  ㅁ    ㅁ  ㅁ    ㅁ  ㅁㅁ    ㅁ  ㅁ      ㅁ    | 20220846 신은섭\n");
	printf("				 |  ㅁ  ㅁ    ㅁ  ㅁ    ㅁ    ㅁ     ㅁㅁ     ㅁㅁㅁ  | 20220848 양호철\n");
	printf("				 |____________________________________________________| 20220850 오지혁 ");

}

int menu() {
	int x = 55;
	int y = 15;
	gotoxy(x - 2, y); // >가 들어있기 때문에 -2
	printf("> 게임 시작");
	gotoxy(x, y + 2);
	printf("최단 경로");
	gotoxy(x, y + 4);
	printf("코드 보기");
	gotoxy(x, y + 6);
	printf(" 순위표 ");
	gotoxy(x, y + 8);
	printf("  종료  ");


	while (1) {
		int n = keyControl(); // 키보드 입력을 받아옴
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				printf(" ");  // 원래 자리에 있던 >를 삭제함
				--y;
				gotoxy(x - 2, --y);
				printf(">");  // 이동한 자리에 다시 표시함
			}
			break;
		}

		case DOWN: {
			if (y < 23) { // 마지막 버튼의 위치
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
// 커서 위치 이동
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
// 커서가 깜빡이는 것을 숨김
void unblink() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

int keyControl() {
	char temp = getch(); // 딜레이없이 바로 입력

	// 대문자 소문자 통일및 입력
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

//하노이탑 재귀함수를 만들기 위한 템플릿 제공
void printTemplates() {
	system("cls");
	printf("하노이탑 코딩에 어려움을 느끼는 학생들에게 필요한 템플릿\n\n");
	printf("-----------------------------------------\n");
	printf("#include<stdio.h>\n#define SIZE (number)\n\n");
	printf("void hanoi(char, char, char, int)\n{");
	printf("\n\tif(n == 1)\n\t\t");
	textColor(yellow);
	printf("종료조건~~\n\t");
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

//이전 메뉴로 되돌아가게 하는 함수
void goBack() {
	printf("뒤로 가려면 스페이스바를 누르세요.");
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

//하노이탑 알고리즘을 통해 몇 번에 끝내는지 알아내기
void hanoi(char from, char other, char to, int n, int* cnt) {
	if (n == 1) {
		printf("%c -> %c\n", from, to);
		(*cnt)++;
	}
	else
	{
		hanoi(from, to, other, n - 1, cnt);			//한 번 꼬아줘야 1.a->b 2.a->b와 같은 경우가 안생깁니다.
		printf("%c -> %c\n", from, to);
		(*cnt)++;
		hanoi(other, from, to, n - 1, cnt);
	}

}

//하노이탑 게임
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

	printf("이름을 입력하세요:");
	scanf("%s", U->name);
	printf("나이를 입력하세요:");
	scanf("%d", U->age);

	printf("원판의 갯수를 입력하세요(1개 이상):");
	scanf("%d", &lv);
	if (lv <= 0)
	{
		printf("원판의 갯수는 1개 이상이어야 합니다.\n");
		return 0;
	}
	char target[3][10];
	char pic[3][10];
	//첫 번째: 기둥 번호
	//두 번째: 층 번호
	//두 번째 값: 빈자리 -1, 안비면 원판 번호

	//0에 원판 전부 있는 걸로 치고 2번으로 모두 보내용

	for (i = 0; i < 3; i++)		//원판 초기화
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
	printf("키보드의 a, b, c를 입력하여 기둥을 선택할 수 있습니다.\n\n");
	printf("A 기둥에 있는 모든 원판을 C 기둥으로 옮기세요\n\n");
	printf("옮길 위치에 있는 원판이 움직일 원판보다 작을 수 없습니다.\n\n");
	printf("이해 하셨으면 아무 키나 누르세요.");
	temp = getch();
	system("cls");

	while (1)		//게임 시작
	{
		printf("\n\n");
		for (j = lv - 1; j > -1; j--)	//층 탐색(위에서부터)
		{
			for (i = 0; i < 3; i++)		//기둥 탐색
			{
				printf("|");
				if (target[i][j] == -1)		//target = -1 의 뜻은 그 자리에 아무 원판이 있지 않다는 뜻입니다.
				{
					for (k = 0; k < 10; k++)
					{
						printf(" ");		//i = 기둥의 번호, j = 층, k를 통해 해당 층을 빈칸으로 두기 총 10칸
					}
				}
				else
				{
					for (k = -1; k < target[i][j]; k++)
						printf("*");			//target은 원판의 번호를 뜻함, k가 -1부터 시작인 이유는 원판 번호를 0번부터 지정했기 때문에 0부터 시작하는 내용이라면 빈칸으로 남게됨
					for (k = 10 - target[i][j] - 1; k > 0; k--)
						printf(" ");			//전체 10칸 중 *로 채우지 않은 부분을 공백으로 채우기
				}
				printf("|");
			}
			printf("\n");
		}
		for (i = 0; i < 3; i++)
		{
			printf("%7c", 'A' + i);		//게임 아랫부분 A, B, C 출력하는 부분 기둥과 센터를 맞춤 %7c는 전체 7칸 중 오른쪽에 붙여서 'A' + i 에 해당하는 기호를 출력
			printf("%5c", ' ');			//위와 동일
		}

		int from, to;
		printf("\n어떤 자리의 원판을 옮기고 싶습니까? (a, b, c): ");
		from = getch();
		putch(from);
		printf("\n어디로 보내고 싶습니까? (a, b, c): ");
		to = getch();
		putch(to);
		printf("\n");

		if (from >= 'A' && from <= 'C')
			from += 32;
		else if (to >= 'A' && to <= 'C')
			to += 32;
		else
		{
			from -= 'a';		//실제 기둥의 인덱스는 0, 1, 2 이기 때문에 a, b, c로 입력받고 'a'를 빼주면 각각 0, 1, 2의 값이 만들어짐 (아스키코드 참고)
			to -= 'a';
		}

		if (from < 0 || from > 2 || to < 0 || to > 2)	//게임 중 a, b, c가 아닌 다른 입력을 했을 때 오류 발생
		{
			printf("잘못 입력하셨습니다. a~c 사이 알파벳만 입력해주세요.");
			continue;
		}
		i = lv - 1;
		while (1)	//출발점의 맨 위 원판 찾기
		{
			if ((i < 0 && hand == -1) || from == to)		//예외처리 
			{
				printf("\n\n뭔가 잘못하셨군요. 다시 입력하세요.\n");
				break;
			}
			if (target[from][i] >= 0)
			{
				hand = target[from][i];
				temp = i;
				target[from][i] = -1;
				printf("\n%d번 째 이동: %c -> %c\n", ++count, from + 'A', to + 'A');
				break;
			}
			i--;
		}

		i = 0;
		while (1)		//도착지의 맨 윗번호와 손에 쥔 원판 번호 비교
		{
			if (hand == -1)
				break;
			if (target[to][i] == -1) {
				if (i == 0)
				{
					target[to][i] = hand;
					printf("옮긴 원판 번호:%d\n\n", hand);
					hand = -1;
					break;
				}
				else if (target[to][i - 1] != -1 && target[to][i - 1] < hand) {
					printf("잘못 된 선택지입니다. 다시 입력하세요.\n");
					target[from][temp] = hand;
					hand = -1;
					count--;
					printf("%d회 로 수정\n\n", count);
					break;
				}
				else if (target[to][i - 1] > hand)
				{
					printf("옮긴 원판 번호:%d\n", hand);
					target[to][i] = hand;
					hand = -1;
					break;
				}

			}
			i++;
		}

		for (i = 0; i < lv; i++)
		{
			if (target[2][i] != -1) {	//C 기둥의 모든 칸에 원판이 끼워져있는지 확인
				finish = 1;
			}
			else
			{
				finish = 0;
				break;
			}
		}
		if (finish == 1)				//finish가 1인 채로 끝났다면 게임이 끝났음을 알림
		{
			printf("총 %d회 움직였습니다.\n\n", count);
			U->count = count;
			update(U, lv);

			printf("뒤로 가시려면 스페이스바를 누르시오");
			while (1) {
				if (keyControl() == SUBMIT) {
					return 0;
				}
			}
		}
	}
}