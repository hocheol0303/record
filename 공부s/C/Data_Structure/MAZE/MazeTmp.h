#pragma once
void print_check() {
	printf("헤더파일 인크루드 안해도 도미\n\n");
}


typedef struct Position {
	int x;
	int y;
} Location2D;

typedef Location2D Element;

typedef struct MazeMap {
	int width;
	int height;
	int** map;				//정수로 된 포인터포인터 : 2차원 배열
	Location2D enter;
	Location2D exit;
} Maze;

void init_maze(Maze* m, int w, int h)
{
	printf("init : Start\n");
	int i;
	m->width = w;
	m->height = h;
	m->map = (int**)malloc(sizeof(int*) * h);		//정수형 포인터를 h개만큼 곱한 크기를 할당
	/*
	map 그림
	{ ~, ~, ~, ...}
	{ ~, ~, ~, ...}
	{ ~, ~, ~, ...}
	{ ~, ~, ~, ...}
	...
	..
	.

	중괄호를 가리킬 자리가 h개 만들어짐
	*/

	for (i = 0; i < h; i++)
		m->map[i] = (int*)malloc(sizeof(int) * w);	//h개만큼 만들어진 중괄호 내부가 각각 w개만큼의 원소로 채워짐


	//포인터로 공간을 할당하기 때문에 malloc하는 순간 원소의 개수가 정해짐?
}
void reset_maze(Maze* m)
{
	int i;
	for (i = 0; i < m->height; i++)
		free(m->map[i]);		//행 없애기			: (int*)malloc(sizeof(int) * w)와 짝꿍
	free(m->map);				//뭉퉁그려 없애기		: (int**)malloc(sizeof(int*) * h)와 짝꿍
	m->map = NULL;
	m->width = m->height = 0;
}

Maze* load_maze()
{
	printf("load : Start\n");
	Maze* p = (Maze*)malloc(sizeof(Maze));

	int height, width;
	char* tmp;
	char str[100];

	FILE* fp = fopen("maze1.txt", "r");
	if (fp == NULL) printf("아무고토 없었다.");			// 파일 없어
	else					//파일 열렸어
	{

		//첫 줄에서 숫자 뽑아내기
		fgets(str, 100, fp);
		///////
		width = atoi(strtok(str, " "));
		height = atoi(strtok(NULL, " "));			//NULL로 지정하면 다음으로 넘어감 : strtok 함수 안에 주소가 남아있는듯

		printf("load : (height, width) = (%d, %d)\n", height, width);

		init_maze(p, width, height);


		//Maze 구조체에 맵 담기
		printf("load : 맵 입력\n");
		for (int i = 0; i < height; i++)			//행 하나씩 올리기
		{
			fgets(str, 100, fp);					//맵 긁어와
			tmp = strtok(str, " ");					//첫 번째 숫자 가져

			for (int j = 0; j < width; j++)			//열 하나씩 올리기
			{
				p->map[i][j] = *tmp;					//숫자 넣어
				printf("%c ", p->map[i][j]);
				tmp = strtok(NULL, " ");			//다음 숫자 가져
			}
			printf("\n");
		}
		printf("load : 맵 다 입력\n");
	}
	return p;
}
void print_maze(Maze* p)
{
	printf("맵그려어어ㅓ어ㅓㅇ어ㅓ어어ㅓㅇ어어어ㅓ어어어어어ㅓ어\n");
	for (int i = 0; i < p->height; i++)
	{
		for (int j = 0; j < p->width; j++)
		{
			switch (p->map[i][j])
			{
			case '0':
				printf("■");
				break;
			case '1':
				printf("　");
				break;
			case '5':
				printf("○");
				break;
			case '9':
				printf("◎");
				break;
			case '.':
				printf("□");
				break;
			}
		}
		printf("\n");
	}
}



///////////////////////////////////////////////////////////////////////////깊이우선탐색 : Stack형태

int is_valid(Maze* p, int x, int y) {			//(x, y)가 유효한 길인지 확인확인
	printf("is_valid\n");
	if (x < 0 || y < 0 || x >= p->width || y >= p->height) return 0;
	//배열은 먼저 나오는게 행, 뒤에 나오는게 열이기 때문에 [y][x]꼴로 표시하면 좌표는 (x, y)인 격
	else return p->map[y][x] == '1' || p->map[y][x] == '9';						//1은 길, 9는 출구
}

Location2D getStart2D(Maze* p) {
	Location2D l;
	for (int i = 0; i < p->height; i++)
	{
		for (int j = 0; j < p->width; j++)
		{
			if (p->map[i][j] == '5')
			{
				l.x = j;
				l.y = i;
				return l;
			}
		}
	}
}
Location2D getLocation2D(int x, int y)
{
	Location2D p;
	p.x = x;
	p.y = y;
	return p;
}

/////////////////////////////////////////////////덱 함수
#define MAX_QUEUE_SIZE 100
Element data[MAX_QUEUE_SIZE];
int front;
int rear;
void error(char* str) {
	printf("%s\n", str);
	exit(1);
}
void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }
void enqueue(Element val)
{
	if (is_full())
		error(" 큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
	printf("Enque : (%d, %d)\n", val.x, val.y);
}
Element dequeue()
{
	if (is_empty())
		error(" 큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}
Element peek()
{
	if (is_empty())
		error(" 큐 공백 에러");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}
void init_deque() { init_queue(); }
void add_rear(Element val) { enqueue(val); }
Element delete_front() { return dequeue(); }
Element get_front() { return peek(); }
void add_front(Element val)
{
	if (is_full())
		error(" 덱 포화 에러");
	data[front] = val;
	front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
Element delete_rear()
{
	int prev = rear;
	if (is_empty())
		error(" 덱 공백 에러");
	rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return data[prev];
}
Element get_rear()
{
	if (is_empty())
		error(" 덱 공백 에러");
	return data[rear];
}
/////////////////////////////////////////////////덱 함수

void search_exit(Maze* p)
{
	printf("찾아아ㅏ아아앙앙아아아ㅏㅏㅏ\n");
	int a = 0;
	int x, y;
	Location2D here;
	init_deque();

	add_rear(getStart2D(p));

	while (is_empty() == 0)
	{
		printf("while-loop\n");
		here = delete_rear();
		x = here.x;
		y = here.y;
		printf("현위치 : (%d, %d)\n", x, y);
		if (p->map[y][x] == '9')
		{
			printf("잡았죠\n");
			return 0;
		}
		else {
			p->map[y][x] = '.';
			if (is_valid(p, x - 1, y)) { printf("%d, %d\n", x - 1, y); add_rear(getLocation2D(x - 1, y)); }
			if (is_valid(p, x + 1, y)) { printf("%d, %d\n", x + 1, y); add_rear(getLocation2D(x + 1, y)); }
			if (is_valid(p, x, y - 1)) { printf("%d, %d\n", x, y - 1); add_rear(getLocation2D(x, y - 1)); }
			if (is_valid(p, x, y + 1)) { printf("%d, %d\n", x, y + 1); add_rear(getLocation2D(x, y + 1)); }
		}
	}
	printf("엠티엠티\n");
}