#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Maze.h"

Maze* maze;

int main(void)
{
	maze = load_maze();
	print_maze(maze);
	printf(" �Ա� �� �� �ⱸ�� ���ã�� ����\n==========���� �켱 Ž��==========\nn : �� ����\nc : ��������\n==========�ʺ� �켱 Ž��==========\nb\n");

	char cm = getch();
	switch (cm)
	{
	case 'n':
		search_exit(maze);
		break;
	case 'c':
		system("cls");
		search_chagunchagun(maze);
		break;
	case 'b':
		system("cls");
		search_BFS(maze);
		break;
	}

	return 0;
}