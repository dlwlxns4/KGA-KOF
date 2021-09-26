#include "Kim.h"
#include "Image.h"
#include "KeyManager.h"
#include "BattleManager.h"
int Kim::ElpasedCount(int fps, int& frameX, bool check) {
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
		return elpasedCount;
	}
}

void Kim::Collision(int frameX, int frameMin, int frameMax, int colliderNum,int& elpasedCount,bool& isHit) {
	if (frameX > frameMin && frameX < frameMax)
	{
		if (this->isPlayer1)
		{
			BattleManager::GetSingleton()->attackCollider[colliderNum].isAttack = true;
			if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[0].collider, true) && !isHit)
			{
				isHit = true;
				elpasedCount = -5; // Hit했을 때 경직도
			}
		}
		else
		{
			BattleManager::GetSingleton()->attackCollider2[colliderNum].isAttack = true;
			if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[0].collider, false) && !isHit)
			{
				isHit = true;
				elpasedCount = -5; // Hit했을 때 경직도
			}

		}
	}
	else //if (frameX > frameMax)
	{
		if (this->isPlayer1)
		{
			BattleManager::GetSingleton()->attackCollider[colliderNum].isAttack = false;
			BattleManager::GetSingleton()->isPlayer2Damaged = false;
		}
		else
		{
			BattleManager::GetSingleton()->attackCollider2[colliderNum].isAttack = false;
			BattleManager::GetSingleton()->isPlayer1Damaged = false;
		}
	}
}

void Kim::Init(bool isPlayer1)
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

	mirroringIdle = new Image;	// 대기
	mirroringIdle->Init("Image/Character/kim/kim_Idle_mirroring.bmp", 682, 120, 11, 1, true, RGB(255, 0, 255));
	mirroringFrontWalk = new Image;	// 앞으로
	mirroringFrontWalk->Init("Image/Character/kim/kim_FrontWalk_mirroring.bmp", 372, 120, 6, 1, true, RGB(255, 0, 255));
	mirroringBackWalk = new Image;	// 뒤로
	mirroringBackWalk->Init("Image/Character/kim/kim_BackWalk_mirroring.bmp", 348, 120, 6, 1, true, RGB(255, 0, 255));
	mirroringWeakPunch = new Image;	// 약주먹
	mirroringWeakPunch->Init("Image/Character/kim/kim_WeakPunch_mirroring.bmp", 590, 120, 5, 1, true, RGB(255, 0, 255));
	mirroringWeakLeg = new Image;	// 약발차기
	mirroringWeakLeg->Init("Image/Character/kim/kim_WeakKick_mirroring.bmp", 909, 120, 9, 1, true, RGB(255, 0, 255));
	mirroringStrongLeg = new Image;	// 강발차기
	mirroringStrongLeg->Init("Image/Character/kim/kim_StrongKick_mirroring.bmp", 1287, 120, 11, 1, true, RGB(255, 0, 255));

	moveDir = MoveDir::Right;

	state = State::IDLE;

	isAttack = false;
	originCheck = false;
	fps = 3;
	frameX = frameY = 0;
	elpasedCount = 0;
	moveSpeed = 10.0f;

	if (isPlayer1) {
		this->pos.x = WIN_SIZE_X / 4;
		this->pos.y = WIN_SIZE_Y / 1.3;
	}
	else {
		this->pos.x = WIN_SIZE_X - WIN_SIZE_X / 4;
		this->pos.y = WIN_SIZE_Y / 1.3;
	}
	
	for (int i = 0; i < 4; i++)
	{
		attackCollider[i].init();
	}
	damagedCollider[0].init(pos.x - 25, pos.x + 25, pos.y - 40, pos.y + 50);
	this->isPlayer1 = isPlayer1;
	isHit = false;
}

void Kim::Update()
{
	if (isPlayer1)
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

		if ((KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_LEFT_KEY)) && !isAttack)
		{
			frameX = 0;
			state = State::IDLE;
		}
	}
	else
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER2_RIGHT_KEY) && state == State::IDLE)
		{
			frameX = 0;
			pos.x += moveSpeed;
			state = State::Walk;
			moveDir = MoveDir::Right;
			isAttack = false;

		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER2_LEFT_KEY) && state == State::IDLE)
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

		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchWeak;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_KICK) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::LegWeak;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_STRONG_KICK) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::LegStrong;
		}

		if ((KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_LEFT_KEY)) && !isAttack)
		{
			frameX = 0;
			state = State::IDLE;
		}
	}

	if (isAttack && state == State::PunchWeak) {
		Collision(frameX, 1, 3, 0, elpasedCount, isHit);
	} else if (isAttack && state == State::PunchStrong) {
		Collision(frameX, 1, 3, 1, elpasedCount, isHit);
	} else if (isAttack && state == State::LegWeak) {
		Collision(frameX, 2, 4, 2, elpasedCount, isHit);
	} else if (isAttack && state == State::LegStrong) {
		Collision(frameX, 3, 5, 3, elpasedCount, isHit);
	}

	if (BattleManager::GetSingleton()->CheckDamaged(isPlayer1))
	{
		state = State::Damaged;
	}
}

void Kim::Render(HDC hdc)
{
	if (idle && mirroringIdle)
	{
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		switch (state)
		{
		case State::IDLE:
			if (isPlayer1) {
				idle->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				mirroringIdle->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			ElpasedCount(fps, frameX, true);
			if (frameX >= 11) frameX = 0;
			break;
		case State::Walk:
			if (moveDir == MoveDir::Right) {
				if (isPlayer1) {
					frontWalk->Render(hdc, pos.x, pos.y, frameX, frameY);

				} else {
					mirroringFrontWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				ElpasedCount(fps, frameX, true);
				if (frameX >= 6) frameX = 0;
				pos.x += moveSpeed / 3;
			}
			else {
				if (isPlayer1) {
					backWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
				} else {
					mirroringBackWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
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
			if (isPlayer1) {
				if (frameX == 0 && elpasedCount == 0) pos.x += 25;
				weakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			} else {
				if (frameX == 0 && elpasedCount == 0) pos.x -= 25;
				mirroringWeakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elpasedCount = ElpasedCount(fps, frameX, true);

			if (frameX >= 5)
			{
				originCheck = false;
				pos.x = originPos;
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
				isHit = false;
			}
			break;
		case State::LegWeak:
			if (!originCheck) {
				originCheck = true;
				originPos = pos.x;
			}
			
			if (isPlayer1) {
				if (frameX == 0 && elpasedCount == 0)this->pos.x += 25;
				weakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				if (frameX == 0 && elpasedCount == 0)this->pos.x -= 25;
				mirroringWeakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elpasedCount = ElpasedCount(fps, frameX, true);
			if (frameX >= 9)
			{
				originCheck = false;
				pos.x = originPos;
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
				isHit = false;
			}
			break;
		case State::LegStrong:
			if (!originCheck) {
				originCheck = true;
				originPos = pos.x;
			}

			if (isPlayer1) {
				if (frameX == 0 && elpasedCount == 0)this->pos.x += 25;
				if (frameX == 1 && elpasedCount == 0)this->pos.x -= 15;
				if (frameX == 3 && elpasedCount == 0)this->pos.x += 10;
				strongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			} else {
				if (frameX == 0 && elpasedCount == 0)this->pos.x -= 25;
				if (frameX == 1 && elpasedCount == 0)this->pos.x += 15;
				if (frameX == 3 && elpasedCount == 0)this->pos.x -= 10;
				mirroringStrongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}

			elpasedCount = ElpasedCount(fps, frameX, true);
			/*if (frameX >= 11)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}*/
			if (frameX >= 11)
			{
				originCheck = false;
				pos.x = originPos;
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
				isHit = false;
			}
			break;
		}
	}

	//if (mirroringIdle)
	//{
	//	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	//
	//	switch (state)
	//	{
	//	case State::IDLE:
	//		mirroringIdle->Render(hdc, pos.x, pos.y, frameX, frameY);
	//		ElpasedCount(fps, frameX, true);
	//		if (frameX >= 11) frameX = 0;
	//		break;
	//	case State::Walk:
	//		if (moveDir == MoveDir::Right) {
	//			mirroringFrontWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
	//			ElpasedCount(fps, frameX, true);
	//			if (frameX >= 6) frameX = 0;
	//			pos.x += moveSpeed / 3;
	//		}
	//		else {
	//			mirroringBackWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
	//			ElpasedCount(fps, frameX, true);
	//			if (frameX >= 6) frameX = 0;
	//			pos.x -= moveSpeed / 3;
	//		}
	//		break;
	//	case State::PunchWeak:
	//		if (!originCheck) {
	//			originCheck = true;
	//			originPos = pos.x;
	//		}
	//		if (frameX == 0 && elpasedCount == 0)pos.x += 25;
	//		mirroringWeakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
	//		elpasedCount = ElpasedCount(fps, frameX, true);
	//		if (frameX >= 5)
	//		{
	//			originCheck = false;
	//			pos.x = originPos;
	//			isAttack = false;
	//			state = State::IDLE;
	//			frameX = 0;
	//		}
	//		break;
	//	case State::LegWeak:
	//		if (!originCheck) {
	//			originCheck = true;
	//			originPos = pos.x;
	//		}
	//		if (frameX == 0 && elpasedCount == 0)pos.x += 25;
	//		mirroringWeakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
	//		elpasedCount = ElpasedCount(fps, frameX, true);
	//		if (frameX >= 9)
	//		{
	//			originCheck = false;
	//			pos.x = originPos;
	//			isAttack = false;
	//			state = State::IDLE;
	//			frameX = 0;
	//		}
	//		break;
	//	case State::LegStrong:
	//		if (!originCheck) {
	//			originCheck = true;
	//			originPos = pos.x;
	//		}
	//		if (frameX == 0 && elpasedCount == 0)pos.x += 25;
	//		if (frameX == 1 && elpasedCount == 0)pos.x -= 15;
	//		if (frameX == 3 && elpasedCount == 0)pos.x += 10;
	//		mirroringStrongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
	//		elpasedCount = ElpasedCount(fps, frameX, true);
	//		if (frameX >= 11)
	//		{
	//			isAttack = false;
	//			state = State::IDLE;
	//			frameX = 0;
	//		}
	//		if (frameX >= 9)
	//		{
	//			originCheck = false;
	//			pos.x = originPos;
	//			isAttack = false;
	//			state = State::IDLE;
	//			frameX = 0;
	//		}
	//		break;
	//	}
	//}
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
