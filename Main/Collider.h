#pragma once
#include "Config.h"

class Collider
{
public:
	RECT collider;
	int damage;
	bool isAttack=false;

public:
	void init();
	void init(int left, int right, int bottom, int top);
	void setColliderPos(int left, int top, int right, int bottom);
	void Render(HDC hdc);
};

