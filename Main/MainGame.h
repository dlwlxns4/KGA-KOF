#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Tank.h"
#include "Ammo.h"
#include <vector>

class MainTitle;
class Image;
class Iori;
class Kim;
class Kyo;
class MayLee;
class BackGround;
class CharacterSelect;
// �츮�� ������ ���� ����
class MainGame : public GameEntity
{
private:
	// Ÿ�̸�
	HANDLE hTimer;

	// �����
	Image* backBuffer;
	BackGround* backGround;
	CharacterSelect* characterSelect;
	MainTitle* mainTitle;
	// ��� �̹���
	Iori* iori;
	Kim* kim;
	Kyo* kyo;
	MayLee* may;

	Iori* iori2;
	Kim* kim2;
	Kyo* kyo2;
	MayLee* may2;
	
public:
	void Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

//int MainGame::clickedMousePosX = 0;