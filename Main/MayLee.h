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
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	int ElpasedCount(int fps, int& frameX, bool check);
};


