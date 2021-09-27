#include "CharacterSelect.h"
#include "Image.h"
#include "BattleManager.h"
#include "UIManager.h"

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
		backGround[i]->Init(cha, 680 / 2.1, 491 / 2.0, 1, 1, false, RGB(255, 0, 255));
	}
	playerSelect1 = new Image;
	playerSelect1->Init("Image/CharSelect/PlayerSelect/PlayerSelect1.bmp", 91 / 4, 130 / 4, 1, 1, true, RGB(255, 0, 255));
	playerSelect2 = new Image;
	playerSelect2->Init("Image/CharSelect/PlayerSelect/PlayerSelect2.bmp", 94 / 4, 127 / 4, 1, 1, true, RGB(255, 0, 255));
	// ¼±ÅÃ Ç¥½Ã

	playerIori1 = new Image;
	playerIori1->Init("Image/CharSelect/PlayerSelect/PlayerIori1.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	playerIori2 = new Image;
	playerIori2->Init("Image/CharSelect/PlayerSelect/PlayerIori2.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	// ÀÌ¿À¸®

	playerMay1 = new Image;
	playerMay1->Init("Image/CharSelect/PlayerSelect/PlayerMay1.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	playerMay2 = new Image;
	playerMay2->Init("Image/CharSelect/PlayerSelect/PlayerMay2.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	// ¸ÞÀÌ ¸®

	playerKyo1 = new Image;
	playerKyo1->Init("Image/CharSelect/PlayerSelect/PlayerKyo1.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	playerKyo2 = new Image;
	playerKyo2->Init("Image/CharSelect/PlayerSelect/PlayerKyo2.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	// Äì

	playerKim1 = new Image;
	playerKim1->Init("Image/CharSelect/PlayerSelect/PlayerKim1.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	playerKim2 = new Image;
	playerKim2->Init("Image/CharSelect/PlayerSelect/PlayerKim2.bmp", 680 / 2.1, 489 / 2.0, 1, 1, true, RGB(255, 0, 255));
	// ±è°©È¯

	backGroundPos.x = WIN_SIZE_Y / 1.5;
	backGroundPos.y = WIN_SIZE_Y / 2;
	
	
	selectPos1[0].x = 0;
	selectPos1[0].y = 2;
	selectPos1[1].x = selectPos1[1].y = 0;
	selectPos2[0].x = 0;
	selectPos2[0].y = 4;
	selectPos2[1].x = selectPos2[1].y = 0;
	
	Twinkle = true;
	elpasedCount = 0;
	frame = 0;
}

void CharacterSelect::Update()
{
	if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Empty") {
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_LEFT_KEY)) {
			if (!(selectPos1[0].x == 3 && selectPos1[0].y == 3)) {
				if (selectPos1[0].x > 0) selectPos1[0].x -= 1;
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_RIGHT_KEY)) {
			if (selectPos1[0].x < 5) selectPos1[0].x += 1;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_UP_KEY)) {
			if (selectPos1[0].y > 0) selectPos1[0].y -= 1;
			if (selectPos1[0].y == 3 &&
				(selectPos1[0].x == 0 ||
					selectPos1[0].x == 1 ||
					selectPos1[0].x == 2)) selectPos1[0].y -= 1;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_DOWN_KEY)) {
			if (selectPos1[0].y < 6) selectPos1[0].y += 1;
			if (selectPos1[0].y == 3 &&
				(selectPos1[0].x == 0 ||
					selectPos1[0].x == 1 ||
					selectPos1[0].x == 2)) selectPos1[0].y += 1;

		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_PUNCH)) {
			if (selectPos1[0].x == 0 && selectPos1[0].y == 2) {
				SceneManager::GetSingleton()->SetPlayerChar("Kyo", true);
			}
			if (selectPos1[0].x == 0 && selectPos1[0].y == 4) {
				SceneManager::GetSingleton()->SetPlayerChar("Iori", true);
			}
			if (selectPos1[0].x == 3 && selectPos1[0].y == 5) {
				SceneManager::GetSingleton()->SetPlayerChar("Kim", true);
			}
			if (selectPos1[0].x == 5 && selectPos1[0].y == 2) {
				SceneManager::GetSingleton()->SetPlayerChar("May", true);
			}

		}
	}
	
	if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Empty") {
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_LEFT_KEY)) {
			if (!(selectPos2[0].x == 3 && selectPos2[0].y == 3)) {
				if (selectPos2[0].x > 0) selectPos2[0].x -= 1;
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_RIGHT_KEY)) {
			if (selectPos2[0].x < 5) selectPos2[0].x += 1;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_UP_KEY)) {
			if (selectPos2[0].y > 0) selectPos2[0].y -= 1;
			if (selectPos2[0].y == 3 &&
				(selectPos2[0].x == 0 ||
					selectPos2[0].x == 1 ||
					selectPos2[0].x == 2)) selectPos2[0].y -= 1;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_DOWN_KEY)) {
			if (selectPos2[0].y < 6) selectPos2[0].y += 1;
			if (selectPos2[0].y == 3 &&
				(selectPos2[0].x == 0 ||
					selectPos2[0].x == 1 ||
					selectPos2[0].x == 2)) selectPos2[0].y += 1;

		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_PUNCH)) {
			if (selectPos2[0].x == 0 && selectPos2[0].y == 2) {	
				SceneManager::GetSingleton()->SetPlayerChar("Kyo", false);
			}
			if (selectPos2[0].x == 0 && selectPos2[0].y == 4) {
				SceneManager::GetSingleton()->SetPlayerChar("Iori", false);
			}
			if (selectPos2[0].x == 3 && selectPos2[0].y == 5) {
				SceneManager::GetSingleton()->SetPlayerChar("Kim", false);
			}
			if (selectPos2[0].x == 5 && selectPos2[0].y == 2) {
				SceneManager::GetSingleton()->SetPlayerChar("May", false);
			}
		}
	}
	if ((SceneManager::GetSingleton()->GetPlayerChar(true) != "Empty") && (SceneManager::GetSingleton()->GetPlayerChar(false) != "Empty")) 
	{
		UIManager::GetSingleton()->Init();
		UIManager::GetSingleton()->SetPlayerImage();
		BattleManager::GetSingleton()->Init();
		SceneManager::GetSingleton()->SetIsSceneState("Battle");
	}
	
	selectPos1[1].x = 204 + (20 * selectPos1[0].x);
	selectPos1[1].y = 31 + (31 * selectPos1[0].y);
	if (selectPos1[0].x >= 3)selectPos1[1].x += 2;
	if (selectPos1[0].y >= 3)selectPos1[1].y += 2;
	if (selectPos1[0].y >= 4)selectPos1[1].y += 2;

	selectPos2[1].x = 204 + (20 * selectPos2[0].x);
	selectPos2[1].y = 29 + (31 * selectPos2[0].y);
	if (selectPos2[0].x >= 3)selectPos2[1].x += 2;
	if (selectPos2[0].y >= 3)selectPos2[1].y += 2;
	if (selectPos2[0].y >= 4)selectPos2[1].y += 2;
}

void CharacterSelect::Render(HDC hdc)
{
	elpasedCount++;
	backGround[frame]->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	if (Twinkle) {
		playerSelect1->Render(hdc, selectPos1[1].x, selectPos1[1].y, 0, 0);
		playerSelect2->Render(hdc, selectPos2[1].x, selectPos2[1].y, 0, 0);
		Twinkle = !Twinkle;
	} else {
		playerSelect2->Render(hdc, selectPos2[1].x, selectPos2[1].y, 0, 0);
		playerSelect1->Render(hdc, selectPos1[1].x, selectPos1[1].y, 0, 0);
		Twinkle = !Twinkle;
	}

	if (selectPos1[0].x == 0 && selectPos1[0].y == 2) {
		playerKyo1->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}
	if (selectPos1[0].x == 0 && selectPos1[0].y == 4) {
		playerIori1->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}
	if (selectPos1[0].x == 5 && selectPos1[0].y == 2) {
		playerMay1->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}
	if (selectPos1[0].x == 3 && selectPos1[0].y == 5) {
		playerKim1->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}

	if (selectPos2[0].x == 0 && selectPos2[0].y == 2) {
		playerKyo2->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}			 
	if (selectPos2[0].x == 0 && selectPos2[0].y == 4) {
		playerIori2->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}			 
	if (selectPos2[0].x == 5 && selectPos2[0].y == 2) {
		playerMay2->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}			 
	if (selectPos2[0].x == 3 && selectPos2[0].y == 5) {
		playerKim2->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}


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