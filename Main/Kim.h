#pragma once
#include "GameObject.h"
#include "Config.h"
#include <vector>
#include "Collider.h"

class Image;
class Kim : public GameObject
{
private:
	Image* idle;
	Image* frontWalk;
	Image* backWalk;
	Image* weakLeg;
	Image* strongLeg;
	Image* weakPunch;
	Image* strongPunch;
	Image* hit1;
	Image* hit2;
	Image* hit3;

	Image* mirroringIdle;
	Image* mirroringFrontWalk;
	Image* mirroringBackWalk;
	Image* mirroringWeakLeg;
	Image* mirroringStrongPunch;
	Image* mirroringStrongLeg;
	Image* mirroringWeakPunch;
	Image* mirroringHit1;
	Image* mirroringHit2;
	Image* mirroringHit3;

	int frameX, frameY;
	int elpasedCount;
	int fps;
	float originPos;
	bool originCheck;
	bool isAttack;
	bool isHit;
	MoveDir moveDir;
protected:
	RECT rect;
	State state;
	bool isPlayer1;

	bool isMeet;

public:
	Collider attackCollider[4];
	Collider damagedCollider[6];
	void Init(bool isPlayer1);
	void Update();
	int ElpasedCount(int fps, int& frameX, bool check);
	void Collision(int frameX, int frameMin, int frameMax, int colliderNum, int& elpasedCount, bool& isHit);
	void Render(HDC hdc);
	void Release();
};

