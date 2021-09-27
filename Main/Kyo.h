#pragma once

#include "GameObject.h"
#include "Collider.h"

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

	Image* MirroringIdle;
	Image* MirroringWalk;
	Image* MirroringWeakPunch;
	Image* MirroringStrongPunch;
	Image* MirroringWeakLeg;
	Image* MirroringStrongLeg;
	Image* MirroringAttacked;

	int frameX, frameY;
	int elapsedCount;
	bool isAttack;
	MoveDir moveDir;
	Collider attackCollider[4];
	Collider damagedCollider[6];

public:
	RECT rect;
	State state;

	bool isPlayer1;


public:
	void Init(bool isPlayer1);
	void Init(int posX, int posY, bool isMoveRight);
	void Update();
	void Render(HDC hdc);
	void Release();
	MoveDir GetMoveDir() { return moveDir; };
	void SetMoveDir(MoveDir moveDir) { this->moveDir = moveDir; };
	void IsCollision();
};

