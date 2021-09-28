#pragma once
#include "GameObject.h"
#include "Config.h"
#include <vector>
#include "Collider.h"

class Image;
class MayLee : public GameObject
{
private:
	Image* idle;
	Image* frontWalk;
	Image* backWalk;
	Image* weakLeg;
	Image* strongLeg;
	Image* weakPunch;
	Image* strongPunch;
	Image* hit;
	Image* die;

	Image* mirroringIdle;
	Image* mirroringFrontWalk;
	Image* mirroringBackWalk;
	Image* mirroringWeakLeg;
	Image* mirroringstrongLeg;
	Image* mirroringWeakPunch;
	Image* mirroringStrongPunch;
	Image* mirroringHit;
	Image* mirroringDie;

	int frameX, frameY;
	int elpasedCount;
	int fps;
	float originPos;
	bool originCheck;
	bool isAttack;
	bool isHit;
	bool isMeet;
	bool isDie;
	MoveDir moveDir;

protected:
	RECT rect;
	State state;
	bool isPlayer1;


public:

	Collider attackCollider[4];
	Collider damagedCollider[6];
	void Init(bool isPlayer1);
	void Update();
	void Render(HDC hdc);
	void Release();
	int ElpasedCount(int fps, int& frameX, bool check);
};


