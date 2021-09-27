#pragma once
#include "GameObject.h"
#include "Config.h"

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

	Image* mirroringIdle;
	Image* mirroringFrontWalk;
	Image* mirroringBackWalk;
	Image* mirroringWeakLeg;
	Image* mirroringstrongLeg;
	Image* mirroringWeakPunch;
	Image* mirroringStrongPunch;

	int frameX, frameY;
	int elpasedCount;
	int fps;
	float originPos;
	bool originCheck;
	bool isAttack;
	MoveDir moveDir;

protected:
	RECT rect;
	State state;

	bool isPlayer1;

public:
	void Init(bool isPlayer1);
	void Update();
	void Render(HDC hdc);
	void Release();
	int ElpasedCount(int fps, int& frameX, bool check);
};


