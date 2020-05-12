/**********************************************
	��Ŀ������ʵ��һ��̰����
	�ļ�������playsnake.cpp
	���뻷����vs2017
	�������ڣ�2019.10.19
***********************************************/
#include<graphics.h>	//ͼ�ο�ͷ�ļ�
#include<conio.h>		//�������
#include<time.h>		//ʱ�����

#define MAX  1000   //�ߵ�������
#define SIZE 20    //�ߵĳߴ�

struct COOR
{
	int x;
	int y;
};


enum CH
{
	up = 72,	 //����ֵ
	down = 80,
	left = 75,
	right = 77
};


//����   �ṹ��  �Զ�������
struct SNAKE
{
	int n;  //�ߵĽ���
	COOR scr[MAX];  //�ߵ�����
	CH ch;  //�ߵķ���
}snake;

//�ṹ��ѧϰ
/*
struct PEOPLE                 �������ṹ��
{
	int shenggao;
	char name[10];
	...
}Andy;

Andy.shenggao=180;

*/

//ʳ����
struct FOOD
{
	COOR fcr; //ʳ�������
	int flag; //ʳ���Ƿ����ɵı�־	0Ϊ��Ҫ����ʳ��  1Ϊ����Ҫ����ʳ��
}food;

//������
void SnakePaint()
{
	//��ͷ
	setlinecolor(RGB(0, 0, 255));
	setfillcolor(RGB(255, 255, 255));
	fillrectangle(snake.scr[0].x, snake.scr[0].y, snake.scr[0].x + SIZE, snake.scr[0].y + SIZE);

	//����
	for (int i = snake.n - 1; i > 0; i--)
	{
		setlinecolor(RGB(0, 0, 255));
		setfillcolor(RGB(255, 255, 255));
		fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + SIZE, snake.scr[i].y + SIZE);
	}

}

//��ʼ��
void initGame()
{
	initgraph(640, 480);    //��ȣ�640    �߶ȣ�480
	snake.n = 1;		//

	//�����±��Ǵ�0
	snake.scr[0].x = 0;
	snake.scr[0].y = 0;
	snake.ch = right;
	food.flag = 0;  //����ʳ�� 0
}


//�ߵ��ƶ�
void SnakeMove()
{
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.scr[i].x = snake.scr[i - 1].x;
		snake.scr[i].y = snake.scr[i - 1].y;
	}

	switch (snake.ch)
	{
	case up:
		snake.scr[0].y -= SIZE;
		break;
	case down:
		snake.scr[0].y += SIZE;
		break;
	case left:
		snake.scr[0].x -= SIZE;
		break;
	case right:
		snake.scr[0].x += SIZE;
		break;
	default:
		break;
	}

}

//�����ߵķ���
void ChangeSnakeCh()
{
	switch (getch())  //��ȡһ���ַ�
	{
	case 72:	//��
		if (snake.ch != down)
			snake.ch = up;
		break;
	case 80:	//��
		if (snake.ch != up)
			snake.ch = down;
		break;
	case 75:	//��
		if (snake.ch != right)
			snake.ch = left;
		break;
	case 77:	//��
		if (snake.ch != left)
			snake.ch = right;
		break;
	default:
		break;
	}
}

//����ʳ������
void FoodCoor()
{
	//���������
	srand((unsigned)time(NULL));

	food.fcr.x = rand() % 32 * SIZE;	//0-31   20   0-620
	food.fcr.y = rand() % 24 * SIZE;	//0-23   20   0-460

	food.flag = 1;	//���������Ժ��Ȳ�����ʳ��
}

//����ʳ��
void FoodPaint()
{
	setlinecolor(RGB(255, 0, 0));
	roundrect(food.fcr.x, food.fcr.y, food.fcr.x + SIZE, food.fcr.y + SIZE, 10, 10); //����Բ�Ǿ���

}

//��ʳ��
void EatFood()
{
	//��ʾ�߳Ե���ʳ��
	if (snake.scr[0].x == food.fcr.x&&snake.scr[0].y == food.fcr.y)
	{
		snake.n++;
		food.flag = 0;
	}
}


int judge()
{
	cleardevice();
	outtextxy(400, 400, "game over");
	Sleep(2000);
	exit(0);
}


//�ж���Ϸ��Ӯ
void GameOver()
{
	//��ͷײ����ǽ
	if (snake.scr[0].x < 0 || snake.scr[0].x>620 || snake.scr[0].y < 0 || snake.scr[0].y>460)
	{
		judge();
	}

	//��ͷײ��������
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.scr[i].x == snake.scr[0].x&&snake.scr[i].y == snake.scr[0].y)
		{
			judge();
		}
	}
}




//����������������
int main()
{
	
	initGame();
	while (1)	 
	{
		while (!kbhit())  //��ⰴ��  ���㰴�°��� ���˳�ѭ��
		{
			if (food.flag == 0)
				FoodCoor();
			cleardevice();//ˢ����Ļ
			FoodPaint();
			SnakeMove();
			SnakePaint();
			Sleep(200);  //200����
			EatFood();
			GameOver();
			
		}
		ChangeSnakeCh();
	}
	return 0;
}