#include "MayLee.h"
#include "Image.h"
#include "KeyManager.h"

int MayLee::ElpasedCount(int fps, int& frameX, bool check) {
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


void MayLee::Init()
{
	idle = new Image;	// 대기
	idle->Init("Image/Character/may_lee/MayLee_Idle_8F.bmp", 528, 100, 8, 1, true, RGB(108, 156, 114));
	frontWalk = new Image;	// 앞으로
	frontWalk->Init("Image/Character/may_lee/MayLee_Walk_5F.bmp", 270, 112, 5, 1, true, RGB(108, 156, 114));
	backWalk = new Image;	// 뒤로
	backWalk->Init("Image/Character/may_lee/MayLee_Back_5F.bmp", 270, 112, 5, 1, true, RGB(108, 156, 114));
	weakPunch = new Image;	// 약주먹
	weakPunch->Init("Image/Character/may_lee/MayLee_WeakPunchNormal_4F.bmp", 400, 103, 4, 1, true, RGB(108, 156, 114));
	weakLeg = new Image;	// 약발차기
	weakLeg->Init("Image/Character/may_lee/MayLee_WeakKickNormal_10F.bmp", 1100, 107, 10, 1, true, RGB(108, 156, 114));
	strongLeg = new Image;	// 강발차기
	strongLeg->Init("Image/Character/may_lee/MayLee_StrongKickNormal_13F.bmp", 1400, 120, 13, 1, true, RGB(108, 156, 114));

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

void MayLee::Update()
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

	if (KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_LEFT_KEY))
	{
		frameX = 0;
		state = State::IDLE;
	}
}

void MayLee::Render(HDC hdc)
{
	if (idle)
	{
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		switch (state)
		{
		case State::IDLE:
			idle->Render(hdc, pos.x, pos.y, frameX, frameY);
			ElpasedCount(fps, frameX, true);
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

void MayLee::Release()
{
	if (idle) delete idle;
	if (frontWalk) delete frontWalk;
	if (backWalk) delete backWalk;
	if (weakLeg) delete weakLeg;
	if (strongLeg) delete strongLeg;
	if (weakPunch) delete weakPunch;
}

