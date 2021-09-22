#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>

using namespace std;

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100
#define ORIGINAL_WIN_SIZE_X 320
#define ORIGINAL_WIN_SIZE_Y 240
#define WIN_MULTIPLI 3
#define WIN_SIZE_X	(ORIGINAL_WIN_SIZE_X)
#define WIN_SIZE_Y	(ORIGINAL_WIN_SIZE_Y)

#define FPS (1000/60)
#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)
#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)
#define SAFE_RELEASE(p) { if(p) {p->Release(); delete p; p=nullptr;} }

#define PLAYER1_RIGHT_KEY 'H'
#define PLAYER1_LEFT_KEY 'F'
#define PLAYER1_UP_KEY 'T'
#define PLAYER1_DOWN_KEY 'G'
#define PLAYER1_WEAK_PUNCH 'A'
#define PLAYER1_STRONG_PUNCH 'S'
#define PLAYER1_WEAK_KICK 'Q'
#define PLAYER1_STRONG_KICK 'W'

#define PLAYER2_RIGHT_KEY VK_RIGHT
#define PLAYER2_LEFT_KEY VK_LEFT
#define PLAYER2_UP_KEY VK_UP
#define PLAYER2_DOWN_KEY VK_DOWN
#define PLAYER2_WEAK_PUNCH 'K'
#define PLAYER2_STRONG_PUNCH 'L'
#define PLAYER2_WEAK_KICK 'O'
#define PLAYER2_STRONG_KICK 'P'


enum TankType { Player, Enemy };
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;