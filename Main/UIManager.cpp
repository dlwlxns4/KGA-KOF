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
	cout << BattleManager::GetSingleton()->player1Hp << "!!!" << endl;
	playerHP2->Render(hdc, WIN_SIZE_X-89, 23, BattleManager::GetSingleton()->player2Hp, false);

}

void UIManager::Update()
{
}

void UIManager::Release()
{
}
