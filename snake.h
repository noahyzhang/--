#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>


#define U 1
#define D 2
#define L 3
#define R 4

typedef struct snake  //����ڵ�
{ 
	int x;  //�ڵ��x����
	int y;  //�ڵ��y����
	struct snake *next;  //�������һ���ڵ�
}snake;

int score = 0, add = 10;  //�ܵ÷ֺ�ÿһ�γ�ʳ��÷�
int HighScore = 0;  //��߷�
int status, sleeptime = 200;  //��ǰ��״̬��ÿ�����е�ʱ����
snake *head, *food;  //��ͷָ�룬ʳ��ָ��
snake *q;  //������ʱ���õ�ָ��
int endgamestatus = 0;  //��Ϸ�����������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ
HANDLE hOut;  //����̨���


void gotoxy(int x, int y); //���ù��λ��
int color(int c);//����������ɫ
void printsnake();//�ַ���������
void welcometogame();//��ʼ����
void createMap();//���Ƶ�ͼ
void scoreandtips();//��Ϸ�����Ҳ�ĵ÷ֺ�С��ʾ
void initsnake();//��ʼ������������
void createfood();//�������������ʳ��
int biteself();//�ж��Ƿ�ҧ���Լ�
void cantcrosswall();//������ײǽ�����
void speedup();//����
void speeddown();//����
void snakemove();//������ǰ������
void keyboardControl();//���Ƽ��̰���
void Lostdraw();//��Ϸ��������
void endgame();//��Ϸ����
void choose();//��Ϸʧ��֮���ѡ��
void File_out();//���ļ��ж�ȡ��߷�
void File_in();//�洢��߷��ļ�
void explation();//��Ϸ˵��
