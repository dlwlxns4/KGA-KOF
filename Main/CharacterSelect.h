#pragma once
#include<string>
#include "Config.h"
#include "KeyManager.h"
#include "SceneManager.h"

using namespace std;
class Image;
class CharacterSelect
{
private:
	POINTFLOAT backGroundPos;		// 배경좌표
	POINTFLOAT selectPos1[2];		// 플레이어1 선택좌표
	POINTFLOAT selectPos2[2];		// 플레이어2 선택좌표

	Image* backGround[14];
	Image* playerSelect1;
	Image* playerSelect2;
	Image* playerIori1;
	Image* playerIori2;
	Image* playerMay1;
	Image* playerMay2;
	Image* playerKyo1;
	Image* playerKyo2;
	Image* playerKim1;
	Image* playerKim2;
	
	int elapsedCount;
	int frame;
	bool Twinkle;
protected:

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

