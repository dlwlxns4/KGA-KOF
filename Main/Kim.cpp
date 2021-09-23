#include "Kim.h"
#include "Image.h"
#include "KeyManager.h"

int ElpasedCount(int fps, int& frameX, bool check) {
	static int elpasedCount = 0;
	elpasedCount++;
	if (elpasedCount == fps)
	{
		elpasedCount = 0;
		if (check) {
			frameX++;
		}
		else 
		{
			frameX--;
		}
	}
	return elpasedCount;
}


void Kim::Init()
{
	idle = new Image;	// 대기
	idle->Init("Image/Character/kim/kim_Idle.bmp", 682, 120, 11, 1, true, RGB(255, 0, 255));
	frontWalk = new Image;	// 앞으로
	frontWalk->Init("Image/Character/kim/kim_FrontWalk.bmp", 372, 120, 6, 1, true, RGB(255, 0, 255));
	backWalk = new Image;	// 뒤로
	backWalk->Init("Image/Character/kim/kim_BackWalk.bmp", 348, 120, 6, 1, true, RGB(255, 0, 255));
	weakPunch = new Image;	// 약주먹
	weakPunch->Init("Image/Character/kim/kim_WeakPunch.bmp", 590, 120, 5, 1, true, RGB(255, 0, 255));
	weakLeg = new Image;	// 약발차기
	weakLeg->Init("Image/Character/kim/kim_WeakKick.bmp", 909, 120, 9, 1, true, RGB(255, 0, 255));
	strongLeg = new Image;	// 강발차기
	strongLeg->Init("Image/Character/kim/kim_StrongKick.bmp", 1287, 120, 11, 1, true, RGB(255, 0, 255));

	moveDir = MoveDir::Right;

	state = State::IDLE;

	isAttack = false;
	originCheck = false;
	fps = 3;
	frameX = frameY = 0;
	elpasedCount = 0;
	moveSpeed = 10.0f;
	this->pos.x = WIN_SIZE_X / 3;
	this->pos.y = WIN_SIZE_Y / 1.4;
}

void Kim::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER1_RIGHT_KEY) && state == State::IDLE)
	{
		frameX = 0;
		pos.x += moveSpeed;
		state = State::Walk;
		moveDir = MoveDir::Right;
		isAttack = false;

	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER1_LEFT_KEY) && state == State::IDLE)
	{
		frameX = 0;
		state = State::Walk;
		moveDir = MoveDir::Left;
		isAttack = false;
	}
	if (state == State::IDLE)
	{
		isAttack = false;
		state = State::IDLE;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
	{
		frameX = 0;
		isAttack = true;
		state = State::PunchWeak;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_KICK) && !isAttack) // A누르고 공격중이 아닐때만 가능
	{
		frameX = 0;
		isAttack = true;
		state = State::LegWeak;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_STRONG_KICK) && !isAttack) // A누르고 공격중이 아닐때만 가능
	{
		frameX = 0;
		isAttack = true;
		state = State::LegStrong;
	}

	if ( (KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_LEFT_KEY)) && !isAttack)
	{
		frameX = 0;
		state = State::IDLE;
	}
}

void Kim::Render(HDC hdc)
{
	if (idle)
	{
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		switch (state)
		{
		case State::IDLE:
			idle->Render(hdc, pos.x, pos.y, frameX, frameY);
			ElpasedCount(fps, frameX,true);
			if (frameX >= 11) frameX = 0;
			break;
		case State::Walk:
			if (moveDir == MoveDir::Right) {
				frontWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
				ElpasedCount(fps, frameX, true);
				if (frameX >= 6) frameX = 0;
				pos.x += moveSpeed / 3;
			}
			else {
				backWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
				ElpasedCount(fps, frameX, true);
				if (frameX >= 6) frameX = 0;
				pos.x -= moveSpeed / 3;
			}
			break;
		case State::PunchWeak:
			if (!originCheck) {
				originCheck = true;
				originPos = pos.x;
			}
			if (frameX == 0 && elpasedCount == 0)pos.x += 25;
			weakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			elpasedCount = ElpasedCount(fps, frameX, true);
			if (frameX >= 5) 
			{
				originCheck = false;
				pos.x = originPos;
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::LegWeak:
			if (!originCheck) {
				originCheck = true;
				originPos = pos.x;
			}
			if (frameX == 0 && elpasedCount == 0)pos.x += 25;
			weakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			elpasedCount = ElpasedCount(fps, frameX, true);
			if (frameX >= 9)
			{
				originCheck = false;
				pos.x = originPos;
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::LegStrong:
			if (!originCheck) {
				originCheck = true;
				originPos = pos.x;
			}
			if (frameX == 0 && elpasedCount == 0)pos.x += 25;
			if (frameX == 1 && elpasedCount == 0)pos.x -= 15;
			if (frameX == 3 && elpasedCount == 0)pos.x += 10;
			strongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			elpasedCount = ElpasedCount(fps, frameX, true);
			if (frameX >= 11)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			if (frameX >= 9)
			{
				originCheck = false;
				pos.x = originPos;
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		}
	}
}

void Kim::Release()
{
	if(idle) delete idle;
	if(frontWalk) delete frontWalk;
	if(backWalk) delete backWalk;
	if(weakLeg) delete weakLeg;
	if(strongLeg) delete strongLeg;
	if(weakPunch) delete weakPunch;
}
