#include "Collider.h"

void Collider::init()
{
	collider.left = 0, collider.right = 0, collider.top = 0, collider.bottom = 0;
	damage = 0;
}

void Collider::init(int left, int right, int bottom, int top)
{
	collider.left = left, collider.right = right, collider.bottom = bottom, collider.top = top;
}

void Collider::setColliderPos(int left, int top, int right, int bottom)
{
	collider.left = left, collider.right = right, collider.bottom = bottom, collider.top = top;
}

void Collider::Render(HDC hdc)
{
	Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);
}
