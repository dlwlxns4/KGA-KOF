#include "BackGround.h"
#include "Image.h"
#include "BattleManager.h"
using namespace std;
void BackGround::Init()
{

	for (int i = 0; i < 8; i++)
	{
		bulGukSa[i] = new Image;
		char cha[100];
		string str = "Image/Background/Bulguksa/Bulguksa_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		bulGukSa[i]->Init(cha, 752 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 불국사 이미지 초기화
	
	for (int i = 0; i < 8; i++)
	{
		desert[i] = new Image;
		char cha[100];
		string str = "Image/Background/Desert/Desert_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		desert[i]->Init(cha, 752 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 사막 이미지 초기화

	for (int i = 0; i < 29; i++)
	{
		garden[i] = new Image;
		char cha[100];
		string str = "Image/Background/Garden/Garden_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		garden[i]->Init(cha, 768, 248, 1, 1, false, RGB(255, 0, 255));
	}
	// 정원 이미지 초기화

	for (int i = 0; i < 8; i++)
	{
		harbor1[i] = new Image;
		char cha[100];
		string str = "Image/Background/Harbor1/Harbor1_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		harbor1[i]->Init(cha, 750 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 항구1 이미지 초기화

	for (int i = 0; i < 8; i++)
	{
		harbor2[i] = new Image;
		char cha[100];
		string str = "Image/Background/Harbor2/Harbor2_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		harbor2[i]->Init(cha, 750 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 항구2 이미지 초기화

	for (int i = 0; i < 8; i++)
	{
		hwaHongMun[i] = new Image;
		char cha[100];
		string str = "Image/Background/Hwahongmun/Hwahongmun_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		hwaHongMun[i]->Init(cha, 752 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 화홍문 이미지 초기화

	for (int i = 0; i < 8; i++)
	{
		racing[i] = new Image;
		char cha[100];
		string str = "Image/Background/Racing/Racing_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		racing[i]->Init(cha, 752 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 레이싱 이미지 초기화

	for (int i = 0; i < 16; i++)
	{
		street[i] = new Image;
		char cha[100];
		string str = "Image/Background/Street/Street_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		street[i]->Init(cha, 752 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 거리 이미지 초기화

	for (int i = 0; i < 16; i++)
	{
		underBridge[i] = new Image;
		char cha[100];
		string str = "Image/Background/UnderBridge/UnderBridge_Layer";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		underBridge[i]->Init(cha, 752 * 1.1, 224 * 1.1, 1, 1, false, RGB(255, 0, 255));
	}
	// 다리밑 이미지 초기화

	backGroundPos = WIN_SIZE_X / 2;
	elpasedCount = 0;
	frame = 0;

	ui = new Image;
	char cha[100];
	string str = "Image/UI";
	str += ".bmp";
	strcpy_s(cha, str.c_str());
	ui->Init(cha, 640/2, 114/1.5, 1, 1, false, RGB(255, 0, 255));

	srand(time(NULL));
	switch (rand() % 9) {
	case 0:
		isBackGround = IsBackGround::BulGukSa;
		backGroundPrint = 250;
		break;
	case 1:
		isBackGround = IsBackGround::Desert;
		backGroundPrint = 250;
		break;
	case 2:
		isBackGround = IsBackGround::Garden;
		backGroundPrint = 230;
		break;
	case 3:
		isBackGround = IsBackGround::Harbor1;
		backGroundPrint = 250;
		break;
	case 4:
		isBackGround = IsBackGround::Harbor2;
		backGroundPrint = 250;
		break;
	case 5:
		isBackGround = IsBackGround::HwaHongMun;
		backGroundPrint = 250;
		break;
	case 6:
		isBackGround = IsBackGround::Racing;
		backGroundPrint = 250;
		break;
	case 7:
		isBackGround = IsBackGround::Street;
		backGroundPrint = 250;
		break;
	case 8:
		isBackGround = IsBackGround::UnderBridge;
		backGroundPrint = 250;
		break;

	}
	// 배경 랜덤설정

}

void BackGround::Update()
{
	BattleManager::GetSingleton()->backGroundMove = 0;
	player1Pos = BattleManager::GetSingleton()->playerPos1.x;
	player2Pos = BattleManager::GetSingleton()->playerPos2.x;
	if (!((player1Pos >= 40 && player1Pos <= 280) && (player2Pos >= 40 && player2Pos <= 280))) {
		if ((player1Pos <= 40 || player2Pos <= 40) && (player1Pos >= 280 || player2Pos >= 280)) {
		} else if ((player1Pos <= 40 && BattleManager::GetSingleton()->player1MoveCheck == 1)||
			(player2Pos <= 40 && BattleManager::GetSingleton()->player2MoveCheck == 1)) {
			if (backGroundPos < 160 + backGroundPrint) {
				BattleManager::GetSingleton()->backGroundMove = 1;
				backGroundPos += 3;
			}
		} else if ((player1Pos >= 280 && BattleManager::GetSingleton()->player1MoveCheck == 2) ||
			(player2Pos >= 280 && BattleManager::GetSingleton()->player2MoveCheck == 2)) {
			if (backGroundPos > 160 - backGroundPrint) {
				BattleManager::GetSingleton()->backGroundMove = 2;
				backGroundPos -= 3;

			}
		}
	}
}

void BackGround::Render(HDC hdc)
{

	switch (isBackGround) {
	case IsBackGround::BulGukSa:
		bulGukSa[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;

		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 8) frame = 0;
		}
		break;
	case IsBackGround::Desert:
		desert[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 8) frame = 0;
		}
		break;
	case IsBackGround::Garden:
		garden[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 29) frame = 0;
		}
		break;
	case IsBackGround::Harbor1:
		harbor1[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 8) frame = 0;
		}
		break;
	case IsBackGround::Harbor2:
		harbor2[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 8) frame = 0;
		}
		break;
	case IsBackGround::HwaHongMun:
		hwaHongMun[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 8) frame = 0;
		}
		break;
	case IsBackGround::Racing:
		racing[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 8) frame = 0;
		}
		break;
	case IsBackGround::Street:
		street[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 16) frame = 0;
		}
		break;
	case IsBackGround::UnderBridge:
		underBridge[frame]->Render(hdc, backGroundPos, WIN_SIZE_Y / 2, 0, 0);
		elpasedCount++;
		if (elpasedCount == 5)
		{
			elpasedCount = 0;
			frame++;
			if (frame >= 16) frame = 0;
		}
		break;
	}


	//ui->Render(hdc, WIN_SIZE_X / 2, 0);
}


void BackGround::Release()
{
}
