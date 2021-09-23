#pragma once

#include "GameObject.h"

class Image;

class Kyo : public GameObject
{
private:
	Image* idle;
	Image* walk;
	Image* weakPunch;
	Image* strongPunch;
	Image* weakLeg;
	Image* strongLeg;
	Image* attacked;

	int frameX, frameY;
	int elapsedCount;
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

