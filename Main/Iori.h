#pragma once
#include "GameObject.h"
#include "Config.h"
#include <vector>
#include "Collider.h"

//#include "Image.h"			// 컴파일 관계가 복잡, 컴파일 시간이 오래 걸림

class Image;					// 포함관계
class Iori : public GameObject  // 상속관계
{

private:
	Image* img;
	Image* idle;
	Image* weakLeg;
	Image* weakPunch;
	Image* strongPunch;
	Image* damaged;

	int frameX, frameY;
	int elpasedCount;
	bool isAttack;
	bool isHit;
	MoveDir moveDir;

public:
	RECT collider[3]; 
	State state;
	Collider attackCollider[4];
	Collider damagedCollider[6];
	bool isPlayer1;


public:
	void Init(bool isPlayer1);
	void Init(int posX, int posY, bool isMoveRight);
	void Update();
	void Render(HDC hdc);
	void Release();
};

