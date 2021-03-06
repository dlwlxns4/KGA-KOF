#pragma once
#include "Config.h"
#include "GameEntity.h"
#include <vector>
#include "Singleton.h"

class MainTitle;
class Image;
class Iori;
class Kim;
class Kyo;
class MayLee;
class BackGround;
class CharacterSelect;
// 우리가 구성할 게임 월드
class MainGame : public GameEntity
{
private:
	// 타이머
	HANDLE hTimer;

	// 백버퍼
	Image* backBuffer;
	BackGround* backGround;
	CharacterSelect* characterSelect;
	MainTitle* mainTitle;
	// 배경 이미지
	Iori* iori;
	Kim* kim;
	Kyo* kyo;
	MayLee* may;

	Iori* iori2;
	Kim* kim2;
	Kyo* kyo2;
	MayLee* may2;
	
	bool gameInit=false;



	bool showCollider = true;

public:
	void Init();
	void GameInit();
	void Update();
	//void Render();			// 오버라이딩 : 상속 관계에서 부모클래스의 함수를 재정의
	void Render(HDC hdc);	// 오버로딩
	void GameRelease();
	void Release();
	void setEnemy();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

//int MainGame::clickedMousePosX = 0;