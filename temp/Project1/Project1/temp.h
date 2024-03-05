/*
//순차탐색
int sequential_search(int list[], int n, int key) {
	int i;
	for (int i = 0; i < n; i++)
	{
		if (list[i] == key) return i;
	}
	return -1;
}

//이진탐색
int binary_search(int list[], int n, int key) {
	int i = n / 2;
	while (1)
	{
		if (list[i] == key) return i;
		if (list[i] > key)
		{
			i = (i + i * 2) / 2;
		}
		else if (list[i] < key)
		{
			i /= 2;
		}
	}
}

//정렬된 리스트 랜덤생성
void get_sorted_list(int list[])
{
	srand(time(NULL));
	int i = 1;
	list[0] = rand();
	while (1)
	{
		if (list[0] > RAND_MAX - 9)
		{
			list[0] = list[0] - 9;
		}
		if (list[9] != NULL) break;
		int tmp = rand();
		if (tmp > list[i - 1] && tmp <= RAND_MAX - (9 - i))
		{
			list[i] = tmp;
			i++;
		}
	}
}

//1~n 합 구하기
int sum_algorithmC(int n)
{
	int tmp = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			tmp++;
		}
	}
	return tmp;
}
*/