#define _CRT_SECURE_NO_WARNINGS 1

void welcometogame()
{
	int n;
	int i, j = 1;
	gotoxy(43, 18);
	color(11);
	printf("贪吃蛇游戏");
	color(14);
	for (i = 20; i < 26; i++)
	{
		for (j = 27; j <= 74; j++)
		{
			gotoxy(j, i);
			if (i == 20 || i == 26)
			{
				printf("-");
			}
			else if (j == 27 || j == 74)
			{
				printf("|");
			}
		}
	}
	color(12);
	gotoxy(35, 22);
	printf("1.开始游戏");
	gotoxy(55, 22);
	printf("2.游戏说明");
	gotoxy(35, 24);
	printf("3.退出游戏");
	gotoxy(29, 27);
	color(3);
	printf("请选择【1 2 3】：[ ]\b\b");
	color(14);
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		system("cls");
		createMap();
		initsnake();
		createfood();
		keyboardControl();
		break;
	case 2:
		explation();
		break;
	case 3:
		exit(0);
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("请输入1--3之间的数");
		_getch();
		system("cls");
		printsnake();
		welcometogame();
	}
}

int main()
{
	system("mode con cols=100 lines=30");
	printsnake();
	welcometogame();
	File_out();
	keyboardControl();
	endgame();
	system("pause");
}