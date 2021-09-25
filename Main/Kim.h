#pragma once
#include "GameObject.h"
#include "Config.h"

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

	Image* mirroringIdle;
	Image* mirroringFrontWalk;
	Image* mirroringBackWalk;
	Image* mirroringWeakLeg;
	Image* mirroringStrongLeg;
	Image* mirroringWeakPunch;

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
};

