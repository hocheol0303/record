#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Maze.h"

Maze* maze;

int main(void)
{
	maze = load_maze();
	print_maze(maze);
	printf(" 입구 ○ → 출구◎ 경로찾기 시작\n==========깊이 우선 탐색==========\nn : 한 번에\nc : 차근차근\n==========너비 우선 탐색==========\nb\n");

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