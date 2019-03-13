#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>


#define U 1
#define D 2
#define L 3
#define R 4

typedef struct snake  //蛇身节点
{ 
	int x;  //节点的x坐标
	int y;  //节点的y坐标
	struct snake *next;  //蛇身的下一个节点
}snake;

int score = 0, add = 10;  //总得分和每一次吃食物得分
int HighScore = 0;  //最高分
int status, sleeptime = 200;  //蛇前进状态，每次运行的时间间隔
snake *head, *food;  //蛇头指针，食物指针
snake *q;  //遍历蛇时候用的指针
int endgamestatus = 0;  //游戏结束的情况，1：撞到墙，2：咬到自己，3：主动退出游戏
HANDLE hOut;  //控制台句柄


void gotoxy(int x, int y); //设置光标位置
int color(int c);//更改文字颜色
void printsnake();//字符画——蛇
void welcometogame();//开始画面
void createMap();//绘制地图
void scoreandtips();//游戏界面右侧的得分和小提示
void initsnake();//初始化蛇身，画蛇身
void createfood();//创建并随机出现食物
int biteself();//判断是否咬到自己
void cantcrosswall();//设置蛇撞墙的情况
void speedup();//加速
void speeddown();//减速
void snakemove();//控制蛇前进方向
void keyboardControl();//控制键盘按键
void Lostdraw();//游戏结束界面
void endgame();//游戏结束
void choose();//游戏失败之后的选择
void File_out();//在文件中读取最高分
void File_in();//存储最高分文件
void explation();//游戏说明
