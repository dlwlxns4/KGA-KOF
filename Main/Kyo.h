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
	Image* die;

	Image* mirroringIdle;
	Image* mirroringWalk;
	Image* mirroringWeakPunch;
	Image* mirroringStrongPunch;
	Image* mirroringWeakLeg;
	Image* mirroringStrongLeg;
	Image* mirroringAttacked;
	Image* mirroringDie;

	int frameX, frameY;
	int elapsedCount;
	bool isAttack;
	MoveDir moveDir;
	Collider attackCollider[4];
	Collider damagedCollider[6];
	bool isDie=false;

public:
	RECT rect;
	State state;

	bool isPlayer1;

	bool isHit;


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

