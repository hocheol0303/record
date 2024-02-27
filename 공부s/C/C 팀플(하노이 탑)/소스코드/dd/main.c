#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <windows.h>
#define SIZE 3

//朕辞 戚疑 獣 琶推廃 葵
enum keyInput { UP, DOWN, LEFT, RIGHT, SUBMIT };

typedef struct UserInfo {		//政煽 舛左 脊径
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
void gotoxy(int, int); // 疎妊走舛 敗呪
void hanoi(char, char, char, int, int*);	//置旋税 井稽 貼事
void hanoiGame(Rate* U);		//馬葛戚転 惟績

extern update(Rate* U, int lev);	//授是妊 穣汽戚闘 敗呪
extern openRank(int lev);			//授是妊 窒径 敗呪
extern createFile(int lev);			//授是妊 糎仙食採 溌昔 / 持失 敗呪

int main() {
	unblink();
	while (1) {
		title();

		int menu_Selcet = menu();
		if (menu_Selcet == 0) { //惟績獣拙
			// 惟績 獣拙 敗呪 隔澗員 
			Rate s;
			hanoiGame(&s);
		}
		else if (menu_Selcet == 2) {
			int n;
			int count = 0;
			system("cls");
			printf("護 鯵税 据毒聖 戚遂廃 置社井稽亜 叡榎廃亜推?:");
			scanf("%d", &n);
			hanoi('A', 'B', 'C', n, &count);
			printf("恥 %d噺 戚疑梅柔艦陥.\n", count);
			goBack();
			//置社葵 域至 敗呪
		}
		else if (menu_Selcet == 4) {
			printTemplates(); // 坪球左奄
		}
		else if (menu_Selcet == 6) {
			system("cls");
			printf("授是妊研 左壱粛精 貝戚亀研 脊径馬室推:");
			int lev;
			scanf("%d", &lev);
			openRank(lev); //授是妊
			goBack();
		}
		else if (menu_Selcet == 8) {// 覗稽益轡 曽戟
			system("cls");
			printf("呪壱馬写柔艦陥.\n");
			return 0;
		}
		system("cls");
	}
	return 0;
}

void title() {
	printf(" __________________\n");
	printf("| 繕拙狛:   w      |\n");
	printf("|         a s d    |\n");
	printf("| 識澱: 什凪戚什郊 |\n");
	printf("|__________________|\n");
	printf("				  ____________________________________________________ \n");
	printf("				 |                                                    |\n");
	printf("				 |  け  け      け      け    け     けけ     けけけ  |\n");
	printf("				 |  け  け    け  け    けけ  け    け  け      け    |\n");
	printf("				 |  けけけ    けけけ    け け け   け    け     け    |\n");
	printf("				 |  け  け    け  け    け  けけ    け  け      け    | 20220846 重精七\n");
	printf("				 |  け  け    け  け    け    け     けけ     けけけ  | 20220848 丞硲旦\n");
	printf("				 |____________________________________________________| 20220850 神走舶 ");

}

int menu() {
	int x = 55;
	int y = 15;
	gotoxy(x - 2, y); // >亜 級嬢赤奄 凶庚拭 -2
	printf("> 惟績 獣拙");
	gotoxy(x, y + 2);
	printf("置舘 井稽");
	gotoxy(x, y + 4);
	printf("坪球 左奄");
	gotoxy(x, y + 6);
	printf(" 授是妊 ");
	gotoxy(x, y + 8);
	printf("  曽戟  ");


	while (1) {
		int n = keyControl(); // 徹左球 脊径聖 閤焼身
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				printf(" ");  // 据掘 切軒拭 赤揮 >研 肢薦敗
				--y;
				gotoxy(x - 2, --y);
				printf(">");  // 戚疑廃 切軒拭 陥獣 妊獣敗
			}
			break;
		}

		case DOWN: {
			if (y < 23) { // 原走厳 獄動税 是帖
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
// 朕辞 是帖 戚疑
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
// 朕辞亜 鉛冊戚澗 依聖 需沿
void unblink() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

int keyControl() {
	char temp = getch(); // 渠傾戚蒸戚 郊稽 脊径

	// 企庚切 社庚切 搭析貢 脊径
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

//馬葛戚転 仙瑛敗呪研 幻級奄 是廃 奴巴鹸 薦因
void printTemplates() {
	system("cls");
	printf("馬葛戚転 坪漁拭 嬢形崇聖 汗晦澗 俳持級拭惟 琶推廃 奴巴鹸\n\n");
	printf("-----------------------------------------\n");
	printf("#include<stdio.h>\n#define SIZE (number)\n\n");
	printf("void hanoi(char, char, char, int)\n{");
	printf("\n\tif(n == 1)\n\t\t");
	textColor(yellow);
	printf("曽戟繕闇~~\n\t");
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

//戚穿 五敢稽 鞠宜焼亜惟 馬澗 敗呪
void goBack() {
	printf("及稽 亜形檎 什凪戚什郊研 刊牽室推.");
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

//馬葛戚転 硝壱軒葬聖 搭背 護 腰拭 魁鎧澗走 硝焼鎧奄
void hanoi(char from, char other, char to, int n, int* cnt) {
	if (n == 1) {
		printf("%c -> %c\n", from, to);
		(*cnt)++;
	}
	else
	{
		hanoi(from, to, other, n - 1, cnt);			//廃 腰 何焼操醤 1.a->b 2.a->b人 旭精 井酔亜 照持演艦陥.
		printf("%c -> %c\n", from, to);
		(*cnt)++;
		hanoi(other, from, to, n - 1, cnt);
	}

}

//馬葛戚転 惟績
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

	printf("戚硯聖 脊径馬室推:");
	scanf("%s", U->name);
	printf("蟹戚研 脊径馬室推:");
	scanf("%d", U->age);

	printf("据毒税 姐呪研 脊径馬室推(1鯵 戚雌):");
	scanf("%d", &lv);
	if (lv <= 0)
	{
		printf("据毒税 姐呪澗 1鯵 戚雌戚嬢醤 杯艦陥.\n");
		return 0;
	}
	char target[3][10];
	char pic[3][10];
	//湛 腰属: 奄逆 腰硲
	//砧 腰属: 寵 腰硲
	//砧 腰属 葵: 朔切軒 -1, 照搾檎 据毒 腰硲

	//0拭 据毒 穿採 赤澗 杏稽 帖壱 2腰生稽 乞砧 左鎧遂

	for (i = 0; i < 3; i++)		//据毒 段奄鉢
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
	printf("徹左球税 a, b, c研 脊径馬食 奄逆聖 識澱拝 呪 赤柔艦陥.\n\n");
	printf("A 奄逆拭 赤澗 乞窮 据毒聖 C 奄逆生稽 薪奄室推\n\n");
	printf("薪掩 是帖拭 赤澗 据毒戚 崇送析 据毒左陥 拙聖 呪 蒸柔艦陥.\n\n");
	printf("戚背 馬写生檎 焼巷 徹蟹 刊牽室推.");
	temp = getch();
	system("cls");

	while (1)		//惟績 獣拙
	{
		printf("\n\n");
		for (j = lv - 1; j > -1; j--)	//寵 貼事(是拭辞採斗)
		{
			for (i = 0; i < 3; i++)		//奄逆 貼事
			{
				printf("|");
				if (target[i][j] == -1)		//target = -1 税 倶精 益 切軒拭 焼巷 据毒戚 赤走 省陥澗 倶脊艦陥.
				{
					for (k = 0; k < 10; k++)
					{
						printf(" ");		//i = 奄逆税 腰硲, j = 寵, k研 搭背 背雁 寵聖 朔牒生稽 砧奄 恥 10牒
					}
				}
				else
				{
					for (k = -1; k < target[i][j]; k++)
						printf("*");			//target精 据毒税 腰硲研 倶敗, k亜 -1採斗 獣拙昔 戚政澗 据毒 腰硲研 0腰採斗 走舛梅奄 凶庚拭 0採斗 獣拙馬澗 鎧遂戚虞檎 朔牒生稽 害惟喫
					for (k = 10 - target[i][j] - 1; k > 0; k--)
						printf(" ");			//穿端 10牒 掻 *稽 辰酔走 省精 採歳聖 因拷生稽 辰酔奄
				}
				printf("|");
			}
			printf("\n");
		}
		for (i = 0; i < 3; i++)
		{
			printf("%7c", 'A' + i);		//惟績 焼熊採歳 A, B, C 窒径馬澗 採歳 奄逆引 湿斗研 限茶 %7c澗 穿端 7牒 掻 神献楕拭 細食辞 'A' + i 拭 背雁馬澗 奄硲研 窒径
			printf("%5c", ' ');			//是人 疑析
		}

		int from, to;
		printf("\n嬢恐 切軒税 据毒聖 薪奄壱 粛柔艦猿? (a, b, c): ");
		from = getch();
		putch(from);
		printf("\n嬢巨稽 左鎧壱 粛柔艦猿? (a, b, c): ");
		to = getch();
		putch(to);
		printf("\n");

		if (from >= 'A' && from <= 'C')
			from += 32;
		else if (to >= 'A' && to <= 'C')
			to += 32;
		else
		{
			from -= 'a';		//叔薦 奄逆税 昔畿什澗 0, 1, 2 戚奄 凶庚拭 a, b, c稽 脊径閤壱 'a'研 皐爽檎 唖唖 0, 1, 2税 葵戚 幻級嬢像 (焼什徹坪球 凧壱)
			to -= 'a';
		}

		if (from < 0 || from > 2 || to < 0 || to > 2)	//惟績 掻 a, b, c亜 焼観 陥献 脊径聖 梅聖 凶 神嫌 降持
		{
			printf("設公 脊径馬写柔艦陥. a~c 紫戚 硝督昏幻 脊径背爽室推.");
			continue;
		}
		i = lv - 1;
		while (1)	//窒降繊税 固 是 据毒 達奄
		{
			if ((i < 0 && hand == -1) || from == to)		//森須坦軒 
			{
				printf("\n\n杭亜 設公馬写浦推. 陥獣 脊径馬室推.\n");
				break;
			}
			if (target[from][i] >= 0)
			{
				hand = target[from][i];
				temp = i;
				target[from][i] = -1;
				printf("\n%d腰 属 戚疑: %c -> %c\n", ++count, from + 'A', to + 'A');
				break;
			}
			i--;
		}

		i = 0;
		while (1)		//亀鐸走税 固 性腰硲人 謝拭 槽 据毒 腰硲 搾嘘
		{
			if (hand == -1)
				break;
			if (target[to][i] == -1) {
				if (i == 0)
				{
					target[to][i] = hand;
					printf("薪延 据毒 腰硲:%d\n\n", hand);
					hand = -1;
					break;
				}
				else if (target[to][i - 1] != -1 && target[to][i - 1] < hand) {
					printf("設公 吉 識澱走脊艦陥. 陥獣 脊径馬室推.\n");
					target[from][temp] = hand;
					hand = -1;
					count--;
					printf("%d噺 稽 呪舛\n\n", count);
					break;
				}
				else if (target[to][i - 1] > hand)
				{
					printf("薪延 据毒 腰硲:%d\n", hand);
					target[to][i] = hand;
					hand = -1;
					break;
				}

			}
			i++;
		}

		for (i = 0; i < lv; i++)
		{
			if (target[2][i] != -1) {	//C 奄逆税 乞窮 牒拭 据毒戚 晦趨閃赤澗走 溌昔
				finish = 1;
			}
			else
			{
				finish = 0;
				break;
			}
		}
		if (finish == 1)				//finish亜 1昔 辰稽 魁概陥檎 惟績戚 魁概製聖 硝顕
		{
			printf("恥 %d噺 崇送心柔艦陥.\n\n", count);
			U->count = count;
			update(U, lv);

			printf("及稽 亜獣形檎 什凪戚什郊研 刊牽獣神");
			while (1) {
				if (keyControl() == SUBMIT) {
					return 0;
				}
			}
		}
	}
}