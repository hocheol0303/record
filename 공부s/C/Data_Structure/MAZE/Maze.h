#include<windows.h>
typedef struct Position {
	int x;
	int y;
} Location2D;

typedef Location2D Element;

typedef struct MazeMap {
	int width;
	int height;
	int** map;
	Location2D enter;
	Location2D exit;
} Maze;

void init_maze(Maze* m, int w, int h)
{
	int i;
	m->width = w;
	m->height = h;
	m->map = (int**)malloc(sizeof(int*) * h);

	for (i = 0; i < h; i++)
		m->map[i] = (int*)malloc(sizeof(int) * w);
}
void reset_maze(Maze* m)
{
	int i;
	for (i = 0; i < m->height; i++)
		free(m->map[i]);		
	free(m->map);
	m->map = NULL;
	m->width = m->height = 0;
}

Maze* load_maze()
{
	Maze* p = (Maze*)malloc(sizeof(Maze));

	int height, width;
	char* tmp;
	char str[100];

	FILE* fp = fopen("maze1.txt", "r");
	if (fp == NULL) printf("FILE is not nominated\n");
	else
	{
		fgets(str, 100, fp);
		width = atoi(strtok(str, " "));
		height = atoi(strtok(NULL, " "));
		
		init_maze(p, width, height);

		for (int i = 0; i < height; i++)
		{
			fgets(str, 100, fp);
			tmp = strtok(str, " ");

			for (int j = 0; j < width; j++)
			{
				p->map[i][j] = *tmp;
				tmp = strtok(NULL, " ");
			}
		}
	}
	return p;
}
void print_maze(Maze* p)
{
	printf("\t전체 미로의 크기 = %d X %d\n", p->width, p->height);
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
			case '3':
				printf("♬");
				break;
			}
		}
		printf("\n");
	}
}

int is_valid(Maze* p, int x, int y) {
	if (x < 0 || y < 0 || x >= p->width || y >= p->height) return 0;
	else return p->map[y][x] == '1' || p->map[y][x] == '9';
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
void print_dequeue()
{
	int i = rear;
	while (i > -1)
	{
		if (data[i].x == 0 && data[i].y == 0) { i--; continue; }
		printf("(%d, %d)\n", data[i].x, data[i].y);
		i--;
	}
}
/////////////////////////////////////////////////덱 함수

void search_exit(Maze* p)
{
	int x, y;
	Location2D here;
	init_deque();

	add_rear(getStart2D(p));


	while (is_empty() == 0)
	{
		here = delete_rear();
		x = here.x;
		y = here.y;
		if (p->map[y][x] == '9')
		{
			print_maze(p);
			printf(" ==> 출구가 탐지되었습니다.\n");
			return 0;
		}
		else {
			p->map[y][x] = '.';
			if (is_valid(p, x - 1, y)) add_rear(getLocation2D(x - 1, y));
			if (is_valid(p, x + 1, y)) add_rear(getLocation2D(x + 1, y));
			if (is_valid(p, x, y - 1)) add_rear(getLocation2D(x, y - 1));
			if (is_valid(p, x, y + 1)) add_rear(getLocation2D(x, y + 1));
		}
	}
}

void search_chagunchagun(Maze* p)
{
	char tmp;
	int x, y;
	Location2D here;
	init_deque();

	print_dequeue();
	add_rear(getStart2D(p));

	while (is_empty() == 0)
	{
		here = delete_rear();
		x = here.x;
		y = here.y;
		if (p->map[y][x] == '9')
		{
			print_maze(p);
			printf(" ==> 출구가 탐지되었습니다.\n");
			return 0;
		}
		else {
			p->map[y][x] = '3';
			print_maze(p);
			p->map[y][x] = '.';
			if (is_valid(p, x - 1, y)) add_rear(getLocation2D(x - 1, y));		//왼쪽 탐색
			if (is_valid(p, x + 1, y)) add_rear(getLocation2D(x + 1, y));		//오른쪽 탐색
			if (is_valid(p, x, y - 1)) add_rear(getLocation2D(x, y - 1));		//아래 탐색
			if (is_valid(p, x, y + 1)) add_rear(getLocation2D(x, y + 1));		//위 탐색
		}
		print_dequeue();
		printf("그만 보려면 q\n");
		tmp = getch();
		if (tmp == 'q') break;
		system("cls");
	}
}

void search_BFS(Maze* p)
{
	char tmp;
	int x, y;
	Location2D here;
	init_deque();

	add_rear(getStart2D(p));

	while (is_empty() == 0)
	{
		here = delete_front();
		x = here.x;
		y = here.y;
		if (p->map[y][x] == '9')
		{
			print_maze(p);
			printf(" ==> 출구가 탐지되었습니다.\n");
			return 0;
		}
		else {
			p->map[y][x] = '3';
			print_maze(p);
			p->map[y][x] = '.';
			if (is_valid(p, x - 1, y)) add_rear(getLocation2D(x - 1, y));		//왼쪽 탐색
			if (is_valid(p, x + 1, y)) add_rear(getLocation2D(x + 1, y));		//오른쪽 탐색
			if (is_valid(p, x, y - 1)) add_rear(getLocation2D(x, y - 1));		//아래 탐색
			if (is_valid(p, x, y + 1)) add_rear(getLocation2D(x, y + 1));		//위 탐색
		}
		printf("그만 보려면 q\n");
		tmp = getch();
		if (tmp == 'q') break;
		system("cls");
	}
}