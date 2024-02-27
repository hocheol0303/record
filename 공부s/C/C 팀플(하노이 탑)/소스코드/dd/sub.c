#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>		//system("cls")
#include<stdlib.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS

char* randomName[10] = { "워웍", "호빵맨", "버즈", "장첸", "장이수", "변기태", "시저", "피카츄", "부머", "예수" };

enum keyInput { UP, DOWN, LEFT, RIGHT, SUBMIT };

extern keyControl();
void createFile(int lev);
char* makeText(int n);		//난이도를 입력 받아서 텍스트로 출력할 것이기 때문에 리턴값 포인터변수.

typedef struct UserInfo {		//유저 정보 입력
	char name[20];
	int age;
	int count;
} Rate;

//순위표가 있는지 확인하고 없다면 새로 생성하는 함수
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
	if (rank == NULL)				//읽기 전용으로 파일이 열리지 않았다는 것은 파일이 존재하지 않다는 뜻 파일 입출력의 fopen(~~, "r")에서 "r"의 기능
	{
		rank = fopen(text, "w");
		//임의로 기록 생성	횟수, 이름, 나이 순 횟수만 작은 순서대로 입력
		for (i = 0; i < 5; i++)
		{
			count[i] = rand() % 100 + 5;
			name[i] = randomName[rand() % 10];	//전역변수로 저장된 이름들의 주소값을 임의로 저장
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
	//최대 29 칸의 정보를 입력
	int i, j;
	int count[5];
	int age[5];
	char name[5][20];				//파일에서 읽어서 저장할 자리
	char text[20];
	strcpy(text, makeText(lev));	//해당 난이도에 대한 파일 이름을 만들어서 text 변수에 넣습니다.

	createFile(lev);
	FILE* rank;
	rank = fopen(text, "a+");	//파일 생성 text = "rank난이도.txt"를 가지고 있음

	if (rank == NULL)
	{
		printf("새로운 파일을 생성할 수 없습니다.\n");
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			fgets(ch, 30, rank);				//한 줄씩 읽어오는 함수 (버퍼의 주소, 문자열 최대 길이, 파일변수의 주소)
			count[i] = atoi(strtok(ch, " "));	//첫 번째 토큰을 int로 받음
			strcpy(name[i], strtok(NULL, " "));	//두 번째 토큰을 문자열로 받음
			age[i] = atoi(strtok(NULL, " "));	//세 번째 토큰을 int로 받음
		}
	}

	for (i = 0; i < 5; i++)			//새로운 값 입력받아서 해당 순위에 밀어넣기
	{
		if (s->count < count[i])		//s->count = (*s).count
		{								//구조체 포인터 변수에 대해 배운 내용입니다.
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

	//새 양식 넣기
	rank = fopen(text, "w");	//새로 추가한 정보를 이용해 새로운 파일 만듦
	for (int i = 0; i < 5; i++)
	{
		fprintf(rank, "%d ", count[i]);
		fprintf(rank, "%s ", name[i]);
		fprintf(rank, "%d\n", age[i]);
	}
	fclose(rank);

}

//rank숫자.txt 파일을 읽어서 출력하는 함수
void openRank(int lev)
{
	system("cls");
	createFile(lev);
	FILE* rank;
	char ch[30];
	char text[20];
	strcpy(text, makeText(lev));

	int count[5];
	char name[5][20];	//이름이 한글로 9글자가 넘어가면 오류 납니다. 조절 가능합니다.
	int age[5];

	rank = fopen(text, "r");
	if (rank == NULL)
	{
		printf("실패");
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			fgets(ch, 30, rank);					//rank라는 텍스트 파일에서 30글자 이내의 문자열을 ch에 출력하는 함수
			count[i] = atoi(strtok(ch, " "));
			strcpy(name[i], strtok(NULL, " "));		//strtok함수에 NULL값을 넣으면 이전에 입력 되었던 변수의 구분 구간 이후를 읽습니다.
			age[i] = atoi(strtok(NULL, " "));
		}
	}
	fclose(rank);

	printf("%50s\n", "순위표");
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("|%20s|", "순위");
	printf("|%20s|", "이름");
	printf("|%20s|", "나이");
	printf("|%20s|\n", "이동 횟수");
	for (int i = 0; i < 5; i++)
	{
		printf("|%20d|", i + 1);
		printf("|%20s|", name[i]);
		printf("|%20d|", age[i]);
		printf("|%20d|\n", count[i]);
	}
}

//입력받은 난이도에 따라서 읽을 점수판 파일의 이름을 만드는 함수
char* makeText(int n)
{
	char buffer[10];
	sprintf(buffer, "%d", n);
	char text[20] = "rank";
	strcat(text, buffer);
	strcat(text, ".txt");
	return text;
}