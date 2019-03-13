#define _CRT_SECURE_NO_WARNINGS 1


#include"snake.h"

int color(int c)  //改变颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), c);
	return 0;
}

void gotoxy(int x, int y)  //设置光标位置
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), c);
}

void printsnake()
{
	gotoxy(35, 1);
	color(6);
	printf("/^\\/^\\");

	gotoxy(34, 2);
	printf("|_| O|");

	gotoxy(33, 2);
	color(2); 
	printf("_");

	gotoxy(25, 3);
	color(12);
	printf("\\/");

	gotoxy(31, 3);
	color(2);
	printf("/");

	gotoxy(37, 3);
	color(6);
	printf("\\_/");

	gotoxy(41, 3);
	color(10);
	printf("\\");

	gotoxy(26, 4);
	color(12);
	printf("\\____");

	gotoxy(32, 4);
	printf("__________/");

	gotoxy(31, 4);
	color(2);
	printf("|");

	gotoxy(43, 4);
	color(10);
	printf("\\");

	gotoxy(32, 5);
	color(2);
	printf("\\_____");

	gotoxy(44, 5);
	color(10);
	printf("\\");

	gotoxy(39, 6);
	printf("|    |             \\");

	gotoxy(38, 7);
	printf("/   /                \\");

	gotoxy(37, 8);
	printf("/  /                \\ \\");

	gotoxy(35, 9);
	printf("/  /                    \\ \\");

	gotoxy(34, 10);
	printf("/  /                        \\ \\");

	gotoxy(33, 11);
	printf("/  /          __---__     \\  \\");

	gotoxy(32, 12);
	printf("/  /        _-~     ~-_    \\  \\");

	gotoxy(31, 13);
	printf("             _-~    _--_  ~-_   -/  \ ");

	gotoxy(32, 14);
	printf("\\       ~-____-~   _-~    ~-_    ~-_-~    \\  \\");

	gotoxy(33, 15);
	printf("~-_         _-~    ~-_     _-~");

	gotoxy(35, 16);
	printf("~--______-~         ~-___-~");
}


void createMap()
{
	int i, j;
	for (i = 0; i < 58; i += 2)
	{
		gotoxy(i, 0);
		color(5);
		printf("□");
		gotoxy(i, 26);
		printf("□");
	}
	for (i = 1; i < 26; i++)
	{
		gotoxy(0, i);
		printf("□");
		gotoxy(56, i);
		printf("□");
	}
	for (i = 2; i < 56; i+=2)
	{
		for (j = 1; j < 26; j++)
		{
			gotoxy(i, j);
			color(3);
			printf("■\n\n");
		}
	}
}

void scoreandtips()
{
	File_out();
	gotoxy(64,4);
	color(11);
	printf("☆最高记录：%d", HighScore);
	gotoxy(64, 8);
	color(14);
	printf("得分：%d ", score);
	color(13);
	gotoxy(73, 11);
	printf("小 提 示");
	gotoxy(60, 13);
	color(6);
	printf("---------------------");
	gotoxy(60, 25);
	printf("---------------------");
	color(3);
	gotoxy(64, 14);
	printf("每个食物得分：%d分", add);
	gotoxy(64, 16);
	printf("不能穿墙，不能咬到自己");
	gotoxy(64, 18);
	printf("用↑↓←→分别控制蛇的移动");
	gotoxy(64, 20);
	printf("F1 为加速，F2 为减速");
	gotoxy(64, 22);
	printf("space:暂停游戏");
	gotoxy(64, 24);
	printf("ESC:退出游戏");
}

void File_out()
{
	FILE *fp;
	fp = fopen("E:\\vs 项目\贪吃蛇\Debug\save.txt","a+");
	fscanf(fp, "%d", &HighScore);
	fclose(fp);
}

void initsnake()
{
	snake *tail;
	int i;
	tail = (snake*)malloc(sizeof(snake));
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	for (int i = 1; i < 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	while (tail != NULL)
	{
		gotoxy(tail->x, tail->y);
		color(14);
		printf("★");
		tail = tail->next;
	}
}

void createfood()
{
	snake* food_1;
	srand((unsigned)time(NULL));
	food_1 = (snake*)malloc(sizeof(snake));
	while ((food_1->x % 2) != 0)
	{
		food_1->x = rand() % 52 + 2;
	}
	food_1->y = rand() % 24 + 1;
	q = head;
	while (q->next == NULL)
	{
		if (q->x == food_1->x&&q->y == food_1->y)
		{
			free(food_1);
			createfood();
		}
		q = q->next;
	}
	gotoxy(food_1->x, food_1->y);
	food = food_1;
	color(12);
	printf("●");
}

int biteself()
{
	snake* self;
	self = head->next;
	while (self != NULL)
	{
		if (self->x == head->x&&self->y == head->y)
		{
			return 1;
		}
		self = self->next;
	}
	return 0;
}

void cantcrosswall()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		endgamestatus = 1;
		endgame();
	}
}

void speedup()
{
	if (sleeptime >= 50)
	{
		sleeptime = sleeptime - 10;
		add = add + 2;
		if (sleeptime == 320)
		{
			add = 2;
		}
	}
}

void speeddown()
{
	if (sleeptime < 350)
	{
		sleeptime = sleeptime + 30;
		add = add - 2;
		if (sleeptime == 350)
		{
			add = 1;
		}
	}
}

void snakemove()
{
	snake *nexthead;
	cantcrosswall();
	nexthead = (snake*)malloc(sizeof(snake));
	if (status == U)
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		nexthead->next = head;
		head = nexthead;
		q = head;
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			score = score + add;
			speedup();
			createfood();
		}
		else
		{
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			color(3);
			printf("■");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == D)
	{
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		nexthead->next = head;
		head = nexthead;
		q = head;
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			score = score + add;
			speedup();
			createfood();
		}
		else
		{
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			color(3);
			printf("■");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == L)
	{
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		nexthead->next = head;
		head = nexthead;
		q = head;
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			score = score + add;
			speedup();
			createfood();
		}
		else
		{
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			color(3);
			printf("■");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == R)
	{
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		nexthead->next = head;
		head = nexthead;
		q = head;
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			while (q != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			score = score + add;
			speedup();
			createfood();
		}
		else
		{
			while (q->next->next != NULL)
			{
				gotoxy(q->x, q->y);
				color(14);
				printf("★");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			color(3);
			printf("■");
			free(q->next);
			q->next = NULL;
		}
	}
	if (biteself() == 1)
	{
		endgamestatus = 2;
		endgame();
	}
}

void keyboardControl()
{
	status = R;
	while (1)
	{
		scoreandtips();
		if (GetAsyncKeyState(VK_UP) && status != D)
		{
			status = U;
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != U)
		{
			status = D;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != R)
		{
			status = L;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != L)
		{
			status = R;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))
				{
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			endgamestatus = 3;
			break;
		}
		else if (GetAsyncKeyState(VK_F1))
		{
			speedup();
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime < 350)
			{
				sleeptime = sleeptime + 30;
				add = add - 2;
				if (sleeptime == 350)
				{
					add = 1;
				}
			}
		}
		Sleep(sleeptime);
		snakemove();
	}
}

void Lostdraw()
{
	system("cls");
	int i, j;
	gotoxy(45, 2);
	color(6);
	printf("\\\\\\|///");
	gotoxy(43, 3);
	printf("\\\\");
	gotoxy(47, 3);
	color(15);
	printf(".-.-");
	gotoxy(54, 3);
	color(6);
	printf("//");

	gotoxy(44, 4);
	color(14);
	printf("(");

	gotoxy(47, 4);
	color(15);
	printf(".@.@");

	gotoxy(54, 4);
	color(14);
	printf(")");


	gotoxy(17, 5);
	color(11);
	printf("+-----------------");

	gotoxy(35, 5);
	color(14);
	printf("oOOo");

	gotoxy(39, 5);
	color(11);
	printf("-------");

	gotoxy(48, 5);
	color(14);
	printf("(__)");

	gotoxy(51, 5);
	color(11);
	printf("--------");

	gotoxy(61, 5);
	color(14);
	printf("oOOo");

	gotoxy(65, 5);
	color(11);
	printf("--------");

	for (i = 6; i <= 19; i++)
	{
		gotoxy(17, i);
		printf("|");
		gotoxy(82, i);
		printf("|");
	}

	gotoxy(17, 20);
	printf("+-----------------");

	gotoxy(52, 20);
	color(14);
	printf("☆☆☆  ");

	gotoxy(60, 20);
	color(11);
	printf("-----------------+");
}

void endgame()
{
	system("cls");
	if (endgamestatus == 1)
	{
		Lostdraw();
		gotoxy(35, 9);
		color(12);
		printf("对不起，您撞到墙了。游戏结束！");
	}
	else if (endgamestatus == 2)
	{
		Lostdraw();
		gotoxy(35, 9);
		color(12);
		printf("对不起，您咬到自己了。游戏结束！");
	}
	else if (endgamestatus == 3)
	{
		Lostdraw();
		gotoxy(40, 9);
		color(12);
		printf("您已经结束了游戏！");
	}
	gotoxy(43, 12);
	color(13);
	printf("您的得分是 %d", score);
	if (score >= HighScore)
	{
		color(10);
		gotoxy(33, 16);
		printf("创造新记录了！最高分被你刷新了，真棒！！！");
		File_in();
	}
	else
	{
		color(10);
		gotoxy(33, 16);
		printf("继续努力吧~~~~你离最高分还差: %d", HighScore - score);
	}
	choose();
}

void File_in()
{
	FILE *fp;
	fp = fopen("E:\\vs 项目\贪吃蛇\Debug\save.txt", "w+");
	fprintf(fp, "%d", score);
	fclose(fp);
}

void choose()
{
	int n;
	gotoxy(25, 23);
	color(12);
	printf("我要重新玩一局------ 1");
	gotoxy(52, 23);
	printf("不玩了，退出吧------ 2");
	gotoxy(46, 25);
	color(11);
	printf("选择：");
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		system("cls");
		score = 0;
		sleeptime = 200;
		add = 10;
		printsnake();
		welcometogame();
		break;
	
	case 2:
		exit(0);
		break;
	default:
		gotoxy(35, 27);
		color(12);
		printf("XXX您的输入有误，请重新输入XXX");
		system("pause>nul");
		endgame();
		choose();
		break;
    }
}

void explation()
{
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(44, 3);
	printf("游戏说明");
	color(2);
	for (i = 6; i <= 22; i++)
	{
		for (j = 20; j <= 75; j++)
		{
			gotoxy(j, i);
			if (i == 6 || i == 22)
				printf("=");
			else if (j == 20 || j == 75)
				printf("||");
		}
	}
	color(3);
	gotoxy(30, 8);
	printf("tip1:不能穿墙，不能咬到自己");
	color(10);
	gotoxy(30, 11);
	printf("tip2:用↑.↓.←.→分别控制蛇的移动");
	color(14);
	gotoxy(30, 14);
	printf("tip3:F1为加速，F2为减速");
	color(11);
	gotoxy(30, 17);
	printf("tip4：按空格键暂停游戏，再按空格键继续");
	color(4);
	gotoxy(30, 20);
	printf("tip5:ESP：退出游戏, space : 暂停游戏");
	_getch();
	system("cls");
	printsnake();
	welcometogame();
}