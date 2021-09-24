#include "Kyo.h"
#include "Image.h"
#include "KeyManager.h"

void Kyo::Init()
{
	idle = new Image;
	idle->Init("Image/Character/Kyo/Kyo_idle.bmp", 1120, 116, 10, 1, true, RGB(240, 0, 240));
	walk = new Image;
	walk->Init("Image/Character/Kyo/Kyo_walk.bmp", 1344, 116, 12, 1, true, RGB(240, 0, 240));
	weakPunch = new Image;
	weakPunch->Init("Image/Character/Kyo/Kyo_smallPunch.bmp", 336, 116, 3, 1, true, RGB(240, 0, 240));
	strongPunch = new Image;
	strongPunch->Init("Image/Character/Kyo/Kyo_strongPunch.bmp", 2016, 116, 18, 1, true, RGB(240, 0, 240));
	weakLeg = new Image;
	weakLeg->Init("Image/Character/Kyo/Kyo_weakLeg.bmp", 1008, 116, 9, 1, true, RGB(240, 0, 240));
	strongLeg = new Image;
	strongLeg->Init("Image/Character/Kyo/Kyo_strongLeg.bmp", 1680, 116, 15, 1, true, RGB(240, 0, 240));
	attacked = new Image;
	attacked->Init("Image/Character/Kyo/Kyo_attacked.bmp", 560, 116, 5, 1, true, RGB(240, 0, 240));

	moveDir = MoveDir::Right;

	state = State::IDLE;

	isAttack = false;

	frameX = frameY = 0;
	elapsedCount = 0;
	moveSpeed = 10.0f;
	this->pos.x = WIN_SIZE_X / 3;
	this->pos.y = WIN_SIZE_Y / 1.3;
}

void Kyo::Init(int posX, int posY, bool isMoveRight)
{
}

void Kyo::Update()
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

	// A누르고 공격중이 아닐때만 가능
	if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_KICK) && !isAttack)
	{
		frameX = 0;
		isAttack = true;
		state = State::LegWeak;
	}
	// A누르고 공격중이 아닐때만 가능
	if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_STRONG_KICK) && !isAttack)
	{
		frameX = 0;
		isAttack = true;
		state = State::LegStrong;
	}
	// A누르고 공격중이 아닐때만 가능
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_PUNCH) && !isAttack)
	{
		frameX = 0;
		isAttack = true;
		state = State::PunchWeak;
	}
	// A누르고 공격중이 아닐때만 가능
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_STRONG_PUNCH) && !isAttack)
	{
		frameX = 0;
		isAttack = true;
		state = State::PunchStrong;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_LEFT_KEY))
	{
		frameX = 0;
		state = State::IDLE;
	}
}

void Kyo::Render(HDC hdc)
{
	if (idle)
	{
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		switch (state)
		{
		case State::IDLE:
			idle->Render(hdc, pos.x, pos.y, frameX, frameY);
			elapsedCount++;
			if (elapsedCount == 5)
			{
				elapsedCount = 0;
				frameX++;
			}
			if (frameX == 10)
			{
				frameX = 0;
			}
			break;
		case State::LegWeak:
			weakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			elapsedCount++;
			if (elapsedCount == 5)
			{
				elapsedCount = 0;
				frameX++;
			}
			if (frameX == 9)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::LegStrong:
			strongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			elapsedCount++;
			if (elapsedCount == 5)
			{
				elapsedCount = 0;
				frameX++;
			}
			if (frameX == 15)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::PunchWeak:
			weakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			elapsedCount++;
			if (elapsedCount == 5)
			{
				elapsedCount = 0;
				frameX++;
			}
			if (frameX == 3)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::PunchStrong:
			strongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			elapsedCount++;
			if (elapsedCount == 5)
			{
				elapsedCount = 0;
				frameX++;
			}
			if (frameX == 18)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::Walk:
			walk->Render(hdc, pos.x, pos.y, frameX, frameY);
			elapsedCount++;
			if (moveDir == MoveDir::Right)
			{
				if (elapsedCount == 5)
				{
					elapsedCount = 0;
					frameX++;
				}
				if (frameX >= 12)
				{
					frameX = 0;
				}
				pos.x += moveSpeed / 3;
			}
			else
			{
				if (elapsedCount == 5)
				{
					elapsedCount = 0;
					frameX--;
				}
				if (frameX <= 0)
				{
					frameX = 12;
				}
				pos.x -= moveSpeed / 3;
			}
			break;
		}
	}
}

void Kyo::Release()
{
	SAFE_RELEASE(idle);
	SAFE_RELEASE(walk);
	SAFE_RELEASE(weakLeg);
	SAFE_RELEASE(weakPunch);
	SAFE_RELEASE(strongPunch);
}

void Kyo::IsCollision()
{
}


