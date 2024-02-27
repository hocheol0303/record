#pragma once
void print_check() {
	printf("������� ��ũ��� ���ص� ����\n\n");
}


typedef struct Position {
	int x;
	int y;
} Location2D;

typedef Location2D Element;

typedef struct MazeMap {
	int width;
	int height;
	int** map;				//������ �� ������������ : 2���� �迭
	Location2D enter;
	Location2D exit;
} Maze;

void init_maze(Maze* m, int w, int h)
{
	printf("init : Start\n");
	int i;
	m->width = w;
	m->height = h;
	m->map = (int**)malloc(sizeof(int*) * h);		//������ �����͸� h����ŭ ���� ũ�⸦ �Ҵ�
	/*
	map �׸�
	{ ~, ~, ~, ...}
	{ ~, ~, ~, ...}
	{ ~, ~, ~, ...}
	{ ~, ~, ~, ...}
	...
	..
	.

	�߰�ȣ�� ����ų �ڸ��� h�� �������
	*/

	for (i = 0; i < h; i++)
		m->map[i] = (int*)malloc(sizeof(int) * w);	//h����ŭ ������� �߰�ȣ ���ΰ� ���� w����ŭ�� ���ҷ� ä����


	//�����ͷ� ������ �Ҵ��ϱ� ������ malloc�ϴ� ���� ������ ������ ������?
}
void reset_maze(Maze* m)
{
	int i;
	for (i = 0; i < m->height; i++)
		free(m->map[i]);		//�� ���ֱ�			: (int*)malloc(sizeof(int) * w)�� ¦��
	free(m->map);				//�����׷� ���ֱ�		: (int**)malloc(sizeof(int*) * h)�� ¦��
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
	if (fp == NULL) printf("�ƹ����� ������.");			// ���� ����
	else					//���� ���Ⱦ�
	{

		//ù �ٿ��� ���� �̾Ƴ���
		fgets(str, 100, fp);
		///////
		width = atoi(strtok(str, " "));
		height = atoi(strtok(NULL, " "));			//NULL�� �����ϸ� �������� �Ѿ : strtok �Լ� �ȿ� �ּҰ� �����ִµ�

		printf("load : (height, width) = (%d, %d)\n", height, width);

		init_maze(p, width, height);


		//Maze ����ü�� �� ���
		printf("load : �� �Է�\n");
		for (int i = 0; i < height; i++)			//�� �ϳ��� �ø���
		{
			fgets(str, 100, fp);					//�� �ܾ��
			tmp = strtok(str, " ");					//ù ��° ���� ����

			for (int j = 0; j < width; j++)			//�� �ϳ��� �ø���
			{
				p->map[i][j] = *tmp;					//���� �־�
				printf("%c ", p->map[i][j]);
				tmp = strtok(NULL, " ");			//���� ���� ����
			}
			printf("\n");
		}
		printf("load : �� �� �Է�\n");
	}
	return p;
}
void print_maze(Maze* p)
{
	printf("�ʱ׷����þ�ä���þ��ä�����þ�����þ�\n");
	for (int i = 0; i < p->height; i++)
	{
		for (int j = 0; j < p->width; j++)
		{
			switch (p->map[i][j])
			{
			case '0':
				printf("��");
				break;
			case '1':
				printf("��");
				break;
			case '5':
				printf("��");
				break;
			case '9':
				printf("��");
				break;
			case '.':
				printf("��");
				break;
			}
		}
		printf("\n");
	}
}



///////////////////////////////////////////////////////////////////////////���̿켱Ž�� : Stack����

int is_valid(Maze* p, int x, int y) {			//(x, y)�� ��ȿ�� ������ Ȯ��Ȯ��
	printf("is_valid\n");
	if (x < 0 || y < 0 || x >= p->width || y >= p->height) return 0;
	//�迭�� ���� �����°� ��, �ڿ� �����°� ���̱� ������ [y][x]�÷� ǥ���ϸ� ��ǥ�� (x, y)�� ��
	else return p->map[y][x] == '1' || p->map[y][x] == '9';						//1�� ��, 9�� �ⱸ
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

/////////////////////////////////////////////////�� �Լ�
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
		error(" ť ��ȭ ����");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
	printf("Enque : (%d, %d)\n", val.x, val.y);
}
Element dequeue()
{
	if (is_empty())
		error(" ť ���� ����");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}
Element peek()
{
	if (is_empty())
		error(" ť ���� ����");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}
void init_deque() { init_queue(); }
void add_rear(Element val) { enqueue(val); }
Element delete_front() { return dequeue(); }
Element get_front() { return peek(); }
void add_front(Element val)
{
	if (is_full())
		error(" �� ��ȭ ����");
	data[front] = val;
	front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
Element delete_rear()
{
	int prev = rear;
	if (is_empty())
		error(" �� ���� ����");
	rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return data[prev];
}
Element get_rear()
{
	if (is_empty())
		error(" �� ���� ����");
	return data[rear];
}
/////////////////////////////////////////////////�� �Լ�

void search_exit(Maze* p)
{
	printf("ã�ƾƤ��ƾƾӾӾƾƾƤ�����\n");
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
		printf("����ġ : (%d, %d)\n", x, y);
		if (p->map[y][x] == '9')
		{
			printf("�����\n");
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
	printf("��Ƽ��Ƽ\n");
}