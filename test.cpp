#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define SNAKE_NUM 500
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Snake
{
	int size;
	int dir;
	int speed;
	POINT coor[SNAKE_NUM];
}snake;

struct Food
{
	int x;
	int y;
	int r;
	bool flag;
}food;

void GameInit()
{
	mciSendString("open ./PVZ_BGM.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	initgraph(640, 480);
	srand(GetTickCount());
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for(int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - 10 * i;
		snake.coor[i].y = 10;
	}
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.r = 5;
	food.flag = true;
}

void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	setfillcolor(BLUE);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

void SnakeMove()
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y <= 0)
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x >= 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	}
}

void KeyControl()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}			
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		}
	}
}

void EatFood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r && 
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.r = 5;
		food.flag = true;
	}
}

int main()
{
	GameInit();
	GameDraw();
	while (1)
	{
		GameDraw();
		SnakeMove();
		KeyControl();
		EatFood();
		Sleep(40);
	}
	return 0;
}