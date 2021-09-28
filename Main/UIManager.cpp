#include "UIManager.h"
#include "Image.h"
#include "SceneManager.h"
#include "BattleManager.h"

void UIManager::Init()
{
	backGroundUI = new Image;
	backGroundUI->Init("Image/UI/BackGroundUI.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	playerHP1 = new Image;
	playerHP1->Init("Image/UI/1HP.bmp", 106, 7, true, RGB(255, 0, 255));
	playerHP2 = new Image;
	playerHP2->Init("Image/UI/1HP.bmp", 107, 7,  true, RGB(255, 0, 255));

}
void UIManager::Init2()
{

	for (int i = 0; i < 21; i++)
	{
		static int num = 0;
		time10[i] = new Image;
		char cha[100];
		if (i != 0 && (i % 3) == 0) num++;
		string str = "Image/UI/TimeNum/Time";
		str += to_string(num);
		str += "-";
		str += to_string((i % 3) + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		time10[i]->Init(cha, 680 / 2.1, 492 / 2, 1, 1, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 30; i++)
	{
		static int num = 0;
		time1[i] = new Image;
		char cha[100];
		if (i != 0 && (i % 3) == 0) num++;
		string str = "Image/UI/TimeNum/Time";
		str += to_string(num);
		str += "-";
		str += to_string((i % 3) + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		time1[i]->Init(cha, 680 / 2.1, 492 / 2, 1, 1, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 13; i++)
	{
		timeLoading[i] = new Image;
		char cha[100];
		string str = "Image/UI/TimeLoading/TimeLoading";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		timeLoading[i]->Init(cha, 680 / 2.1, 492 / 2, 1, 1, true, RGB(255, 0, 255));
	}

	timeLoadingNum = 0;
	timeNum10 = 18;
	timeNum1 = 0;
	timeOut = false;
	timeOutDead = false;
	num = 0;
	time1Check = true;
	time10Check = true;
}
void UIManager::SetPlayerImage()
{
	player1 = new Image;
	player2 = new Image;

	if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Iori")
	{
		player1->Init("Image/UI/CharImage/Iori1.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}
	else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kyo")
	{
		player1->Init("Image/UI/CharImage/Kyo1.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}
	else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "May")
	{
		player1->Init("Image/UI/CharImage/May1.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}
	else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kim")
	{
		player1->Init("Image/UI/CharImage/Kim1.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}

	if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Iori")
	{
		player2->Init("Image/UI/CharImage/Iori2.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}
	else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Kyo")
	{
		player2->Init("Image/UI/CharImage/Kyo2.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}
	else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "May")
	{
		player2->Init("Image/UI/CharImage/May2.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}
	else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Kim")
	{
		player2->Init("Image/UI/CharImage/Kim2.bmp", 680 / 2.1, 492 / 2, true, RGB(255, 0, 255));
	}

}
void UIManager::Render(HDC hdc)
{
	
	backGroundUI->Render(hdc, WIN_SIZE_Y / 1.5 , WIN_SIZE_Y / 2);
	player1->Render(hdc, WIN_SIZE_Y / 1.5, WIN_SIZE_Y / 2);
	player2->Render(hdc, WIN_SIZE_Y / 1.5, WIN_SIZE_Y / 2);
	playerHP1->Render(hdc, 90, 23, BattleManager::GetSingleton()->player1Hp, true);
	playerHP2->Render(hdc, WIN_SIZE_X-89, 23, BattleManager::GetSingleton()->player2Hp, false);
	if (!timeOut)
	{
		timeLoading[timeLoadingNum]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		time1[timeNum1]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		time10[timeNum10]->Render(hdc, WIN_SIZE_X / 2 - 14, WIN_SIZE_Y / 2);
	} else {
		timeLoading[0]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		time1[2]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		time10[2]->Render(hdc, WIN_SIZE_X / 2 - 14, WIN_SIZE_Y / 2);
		if (!timeOutDead) {
			timeOutDead = true;
			if (BattleManager::GetSingleton()->player1Hp <
				BattleManager::GetSingleton()->player2Hp) {
				BattleManager::GetSingleton()->player1Hp = -5;
			} else {
				BattleManager::GetSingleton()->player2Hp = -5;
			}
		}
	}
}

void UIManager::Update()
{
	if (!timeOut && (BattleManager::GetSingleton()->player1Hp >0 && (BattleManager::GetSingleton()->player2Hp > 0)))
	{
		
		
		
		num++;
		if (num == 3) {
			num = 0;
			timeLoadingNum++;
		}

		if (timeLoadingNum == 13) {
			timeLoadingNum = 0;
			time1Check = true;
			if (timeNum1 == 2) {
				timeNum1 = 27;
				if (timeNum10 == 2) timeOut = true;
				timeNum10 -= 6;
				time10Check = true;
			}
			else {
				timeNum1 -= 6;
			}
		}

		if (time1Check && num == 0) {
			timeNum1++;
			if ((timeNum1 + 1) % 3 == 0) time1Check = false;
		}
		if (time10Check && num == 0) {
			timeNum10++;
			if ((timeNum10 + 1) % 3 == 0) time10Check = false;

		}
	}
}

void UIManager::Release()
{
}

void UIManager::TimeInit()
{
	timeLoadingNum = 0;
	timeNum10 = 18;
	timeNum1 = 0;
	timeOut = false;
	timeOutDead = false;
	num = 0;
	time1Check = true;
	time10Check = true;
}
