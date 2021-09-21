#include "CharacterSelect.h"
#include "Image.h"

void CharacterSelect::Init()
{
	for (int i = 0; i < 14; i++)
	{
		backGround[i] = new Image;
		char cha[100];
		string str = "Image/CharSelect/BackGround/BackGround";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		backGround[i]->Init(cha, 680 / 2.1, 491 / 2.1, 1, 1, false, RGB(255, 0, 255));
	}
	playerSelect1 = new Image;
	playerSelect1->Init("Image/CharSelect/PlayerSelect/PlayerSelect1.bmp", 91 / 4, 130 / 4, 1, 1, true, RGB(255, 0, 255));
	playerSelect2 = new Image;
	playerSelect2->Init("Image/CharSelect/PlayerSelect/PlayerSelect2.bmp", 94 / 4, 127 / 4, 1, 1, true, RGB(255, 0, 255));
	// ¼±ÅÃ Ç¥½Ã

	playerIori1 = new Image;
	playerIori1->Init("Image/CharSelect/PlayerSelect/PlayerIori1.bmp", 91 / 4, 130 / 4, 1, 1, true, RGB(255, 0, 255));
	playerIori2 = new Image;
	playerIori2->Init("Image/CharSelect/PlayerSelect/PlayerIori2.bmp", 94 / 4, 127 / 4, 1, 1, true, RGB(255, 0, 255));
	// ÀÌ¿À¸®

	playerMay1 = new Image;
	playerMay1->Init("Image/CharSelect/PlayerSelect/PlayerMay1.bmp", 91 / 4, 130 / 4, 1, 1, true, RGB(255, 0, 255));
	playerMay2 = new Image;
	playerMay2->Init("Image/CharSelect/PlayerSelect/PlayerMay2.bmp", 94 / 4, 127 / 4, 1, 1, true, RGB(255, 0, 255));
	// ¸ÞÀÌ ¸®

	playerKyo1 = new Image;
	playerKyo1->Init("Image/CharSelect/PlayerSelect/PlayerKyo1.bmp", 91 / 4, 130 / 4, 1, 1, true, RGB(255, 0, 255));
	playerKyo2 = new Image;
	playerKyo2->Init("Image/CharSelect/PlayerSelect/PlayerKyo2.bmp", 94 / 4, 127 / 4, 1, 1, true, RGB(255, 0, 255));
	// Äì

	playerKim1 = new Image;
	playerKim1->Init("Image/CharSelect/PlayerSelect/PlayerKim1.bmp", 91 / 4, 130 / 4, 1, 1, true, RGB(255, 0, 255));
	playerKim2 = new Image;
	playerKim2->Init("Image/CharSelect/PlayerSelect/PlayerKim2.bmp", 94 / 4, 127 / 4, 1, 1, true, RGB(255, 0, 255));
	// ±è°©È¯

	elpasedCount = 0;
	frame = 0;
	backGroundPos.x = WIN_SIZE_Y / 1.5;
	backGroundPos.y = WIN_SIZE_Y / 2;
	selectPos1[0].x = selectPos1[0].y = 0;
	selectPos1[1].x = selectPos1[1].y = 0;
	selectPos2[0].x = selectPos2[0].y = 0;
	selectPos2[1].x = selectPos2[1].y = 0;
}

void CharacterSelect::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT)) {
		if (!(selectPos1[0].x == 3 && selectPos1[0].y == 3)) {
			if (selectPos1[0].x > 0) selectPos1[0].x -= 1;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT)) {
		if (selectPos1[0].x < 5) selectPos1[0].x += 1;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP)) {
		if (selectPos1[0].y > 0) selectPos1[0].y -= 1;
		if (selectPos1[0].y ==3 &&
			(selectPos1[0].x == 0 ||
			selectPos1[0].x == 1 ||
			selectPos1[0].x == 2)) selectPos1[0].y -= 1;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN)) {
		if (selectPos1[0].y < 6) selectPos1[0].y += 1;
		if (selectPos1[0].y == 3 &&
			(selectPos1[0].x == 0 ||
			selectPos1[0].x == 1 ||
			selectPos1[0].x == 2)) selectPos1[0].y += 1;

	}
	selectPos1[1].x = 204 + (20 * selectPos1[0].x);
	selectPos1[1].y = 37 + (29 * selectPos1[0].y);
	if (selectPos1[0].x >= 3)selectPos1[1].x += 2;
	if (selectPos1[0].y >= 3)selectPos1[1].y += 2;
	if (selectPos1[0].y >= 4)selectPos1[1].y += 2;

}

void CharacterSelect::Render(HDC hdc)
{
	elpasedCount++;
	backGround[frame]->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	playerSelect1->Render(hdc, selectPos1[1].x,selectPos1[1].y, 0, 0);
	if (elpasedCount >= 2) 
	{
		elpasedCount = 0;
		frame++;
		if (frame >= 14) frame = 0;
	}
}

void CharacterSelect::Release()
{
	delete backGround;
	delete playerSelect1;
	delete playerSelect2;
}
