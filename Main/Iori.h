#pragma once
#include "GameObject.h"
#include "Config.h"
//#include "Image.h"			// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;					// ���԰���
class Iori : public GameObject  // ��Ӱ���
{

private:
	Image* img;
	Image* idle;
	Image* weakLeg;
	Image* weakPunch;
	Image* strongPunch;


	int frameX, frameY;
	int elpasedCount;
	bool isAttack;
	MoveDir moveDir;

	

public:
	RECT rect;
	State state;


public:
	void Init();
	void Init(int posX, int posY, bool isMoveRight);
	void Update();
	void Render(HDC hdc);
	void Release();
	MoveDir GetMoveDir() { return moveDir; };
	void SetMoveDir(MoveDir moveDir) { this->moveDir = moveDir; };
	void IsCollision();
};

