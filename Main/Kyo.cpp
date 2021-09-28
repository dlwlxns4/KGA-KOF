#include "Kyo.h"
#include "Image.h"
#include "KeyManager.h"
#include "BattleManager.h"

void Kyo::Init(bool isPlayer1)
{
	if (isPlayer1)
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
		die = new Image;
		die->Init("Image/Character/Kyo/Kyo_die.bmp", 640, 100, 5, 1, true, RGB(240, 0, 240));

	}
	else
	{
		mirroringIdle = new Image;
		mirroringIdle->Init("Image/Character/Kyo/Kyo_idle_mirroring.bmp", 1120, 116, 10, 1, true, RGB(240, 0, 240));
		mirroringWalk = new Image;
		mirroringWalk->Init("Image/Character/Kyo/Kyo_walk_mirroring.bmp", 1344, 116, 12, 1, true, RGB(240, 0, 240));
		mirroringWeakPunch = new Image;
		mirroringWeakPunch->Init("Image/Character/Kyo/Kyo_smallPunch_mirroring.bmp", 336, 116, 3, 1, true, RGB(240, 0, 240));
		mirroringStrongPunch = new Image;
		mirroringStrongPunch->Init("Image/Character/Kyo/Kyo_strongPunch_mirroring.bmp", 2016, 116, 18, 1, true, RGB(240, 0, 240));
		mirroringWeakLeg = new Image;
		mirroringWeakLeg->Init("Image/Character/Kyo/Kyo_weakLeg_mirroring.bmp", 1008, 116, 9, 1, true, RGB(240, 0, 240));
		mirroringStrongLeg = new Image;
		mirroringStrongLeg->Init("Image/Character/Kyo/Kyo_strongLeg_mirroring.bmp", 1680, 116, 15, 1, true, RGB(240, 0, 240));
		mirroringAttacked = new Image;
		mirroringAttacked->Init("Image/Character/Kyo/Kyo_attacked_mirroring.bmp", 560, 116, 5, 1, true, RGB(240, 0, 240));
		mirroringDie = new Image;
		mirroringDie->Init("Image/Character/Kyo/Kyo_die_mirroring.bmp", 640, 100, 5, 1, true, RGB(240, 0, 240));
	}

	frameX = frameY = 0;

	moveDir = MoveDir::Right;

	state = State::IDLE;

	isAttack = false;

	elapsedCount = 0;
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

	isMeet = false;
}

void Kyo::Init(int posX, int posY, bool isMoveRight)
{
}

void Kyo::Update()
{
	if (BattleManager::GetSingleton()->player1Hp <= 0 || BattleManager::GetSingleton()->player2Hp <= 0)
		isLive = false;

	if (isPlayer1) {
		if (BattleManager::GetSingleton()->player1Hp <= 0) {
			isLive = false;
			state = State::Die;
		}
	}
	else {
		if (BattleManager::GetSingleton()->player2Hp <= 0) {
			isLive = false;
			state = State::Die;
		}
	}
	cout << isLive<<endl;
	if (isLive)
	{
		if (BattleManager::GetSingleton()->CheckMeet())
		{
			isMeet = true;
		}
		else
		{
			isMeet = false;
		}
		if (isPlayer1)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER1_RIGHT_KEY) && state == State::IDLE)
			{
				if (!isMeet)
				{
					frameX = 0;
					pos.x += moveSpeed;
					state = State::Walk;
					moveDir = MoveDir::Right;
					isAttack = false;
					elapsedCount = 0;
				}
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER1_LEFT_KEY) && state == State::IDLE)
			{
				frameX = 0;
				state = State::Walk;
				moveDir = MoveDir::Left;
				isAttack = false;
				elapsedCount = 0;
				frameX = 0;
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
				elapsedCount = 0;
			}
			// A누르고 공격중이 아닐때만 가능
			if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_STRONG_KICK) && !isAttack)
			{
				frameX = 0;
				isAttack = true;
				state = State::LegStrong;
				elapsedCount = 0;
			}
			// A누르고 공격중이 아닐때만 가능
			else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_PUNCH) && !isAttack)
			{
				frameX = 0;
				isAttack = true;
				state = State::PunchWeak;
				elapsedCount = 0;
			}
			// A누르고 공격중이 아닐때만 가능
			else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_STRONG_PUNCH) && !isAttack)
			{
				frameX = 0;
				isAttack = true;
				state = State::PunchStrong;
				elapsedCount = 0;
			}

			if ((KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_LEFT_KEY)) && !isAttack && state != State::Damaged)
			{
				frameX = 0;
				state = State::IDLE;
				elapsedCount = 0;
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
				elapsedCount = 0;
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER2_LEFT_KEY) && state == State::IDLE)
			{
				if (!isMeet)
				{
					frameX = 0;
					state = State::Walk;
					moveDir = MoveDir::Left;
					isAttack = false;
					elapsedCount = 0;
				}
			}

			if (state == State::IDLE)
			{
				isAttack = false;
				state = State::IDLE;
			}

			// A누르고 공격중이 아닐때만 가능
			if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_KICK) && !isAttack)
			{
				frameX = 0;
				isAttack = true;
				state = State::LegWeak;
				elapsedCount = 0;
			}
			// A누르고 공격중이 아닐때만 가능
			if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_STRONG_KICK) && !isAttack)
			{
				frameX = 0;
				isAttack = true;
				state = State::LegStrong;
				elapsedCount = 0;
			}
			// A누르고 공격중이 아닐때만 가능
			else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_PUNCH) && !isAttack)
			{
				frameX = 0;
				isAttack = true;
				state = State::PunchWeak;
				elapsedCount = 0;
			}
			// A누르고 공격중이 아닐때만 가능
			else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_STRONG_PUNCH) && !isAttack)
			{
				frameX = 0;
				isAttack = true;
				state = State::PunchStrong;
				elapsedCount = 0;
			}

			if ((KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_LEFT_KEY)) && !isAttack && state != State::Damaged)
			{
				frameX = 0;
				state = State::IDLE;
				elapsedCount = 0;
			}
		}

		//Collider 관리 파트 
		if (isAttack && state == State::PunchWeak)
		{
			if (frameX > 0 && frameX < 2)
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[0].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[0].collider, true) && !isHit)
					{
						isHit = true;
						elapsedCount = -5; // Hit했을 때 경직도
					}

				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[0].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[0].collider, false) && !isHit)
					{
						isHit = true;
						elapsedCount = -5; // Hit했을 때 경직도
					}

				}
			}
			else if (frameX == 2)
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[0].isAttack = false;
					BattleManager::GetSingleton()->isPlayer2Damaged = false;
				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[0].isAttack = false;
					BattleManager::GetSingleton()->isPlayer1Damaged = false;
				}
			}
		}
		else if (isAttack && state == State::PunchStrong)
		{
			if (frameX > 6 && frameX < 11)
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[1].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[1].collider, true) && !isHit)
					{
						isHit = true;
						elapsedCount = -3; // Hit했을 때 경직도
					}
				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[1].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[1].collider, false) && !isHit)
					{
						isHit = true;
						elapsedCount = -3; // Hit했을 때 경직도
					}
				}
			}
			else
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[1].isAttack = false;
					BattleManager::GetSingleton()->isPlayer2Damaged = false;
				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[1].isAttack = false;
					BattleManager::GetSingleton()->isPlayer1Damaged = false;
				}
			}
		}
		else if (isAttack && state == State::LegWeak)
		{
			if (frameX > 2 && frameX < 5)
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[2].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[2].collider, true) && !isHit)
					{
						isHit = true;
						elapsedCount = -3; // Hit했을 때 경직도
					}
				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[2].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[2].collider, false) && !isHit)
					{
						isHit = true;
						elapsedCount = -3; // Hit했을 때 경직도
					}
				}
			}
			else
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[2].isAttack = false;
					BattleManager::GetSingleton()->isPlayer2Damaged = false;
				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[2].isAttack = false;
					BattleManager::GetSingleton()->isPlayer1Damaged = false;
				}
			}
		}
		else if (isAttack && state == State::LegStrong)
		{
			if (frameX > 3 && frameX < 8)
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[3].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[3].collider, true) && !isHit)
					{
						isHit = true;
						elapsedCount = -3; // Hit했을 때 경직도
					}
				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[3].isAttack = true;
					if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[3].collider, false) && !isHit)
					{
						isHit = true;
						elapsedCount = -3; // Hit했을 때 경직도
					}
				}
			}
			else
			{
				if (this->isPlayer1)
				{
					BattleManager::GetSingleton()->attackCollider[3].isAttack = false;
					BattleManager::GetSingleton()->isPlayer2Damaged = false;
				}
				else
				{
					BattleManager::GetSingleton()->attackCollider2[3].isAttack = false;
					BattleManager::GetSingleton()->isPlayer1Damaged = false;
				}
			}
		}


		// 배경 카메라 움직임 관련
		if (isPlayer1) {
			if (BattleManager::GetSingleton()->player2MoveCheck == 1 && BattleManager::GetSingleton()->backGroundMove == 1
				&& BattleManager::GetSingleton()->playerPos2.x <= 40) {
				if (!(pos.x >= 280)) {
					pos.x += moveSpeed / 3;
				}
			}
			if (BattleManager::GetSingleton()->player2MoveCheck == 2 && BattleManager::GetSingleton()->backGroundMove == 2
				&& BattleManager::GetSingleton()->playerPos2.x >= 280) {
				if (!(pos.x <= 40)) {
					pos.x -= moveSpeed / 3;
				}
			}
		}
		else {
			if (BattleManager::GetSingleton()->player1MoveCheck == 1 && BattleManager::GetSingleton()->backGroundMove == 1
				&& BattleManager::GetSingleton()->playerPos1.x <= 40) {
				if (!(pos.x >= 280)) {
					pos.x += moveSpeed / 3;
				}
			}
			if (BattleManager::GetSingleton()->player1MoveCheck == 2 && BattleManager::GetSingleton()->backGroundMove == 2
				&& BattleManager::GetSingleton()->playerPos1.x >= 280) {
				if (!(pos.x <= 40)) pos.x -= moveSpeed / 3;
			}
		}
	}
	
	//0927수정
	if (BattleManager::GetSingleton()->CheckDamaged(isPlayer1))
	{
		if (BattleManager::GetSingleton()->player1Hp <= 0)
		{
			frameX = 0;
			state = State::Die;
		}
		else if (BattleManager::GetSingleton()->player2Hp <= 0)
		{
			//cout << "damaged" << endl;
			frameX = 0;
			state = State::Die;

		}
		else
		{
			state = State::Damaged;
		}
	}
}

void Kyo::Render(HDC hdc)
{
	if (isPlayer1) {
		BattleManager::GetSingleton()->player1MoveCheck = 0;
	}
	else {
		BattleManager::GetSingleton()->player2MoveCheck = 0;
	}

	if (idle || mirroringIdle)
	{
		switch (state)
		{
		case State::IDLE:
			if (isPlayer1)
			{
				idle->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else
			{
				mirroringIdle->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
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
			if (isPlayer1)
			{
				weakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else
			{
				mirroringWeakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elapsedCount++;
			if (elapsedCount >= 3)
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
			if (isPlayer1)
			{
				strongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else
			{
				mirroringStrongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elapsedCount++;
			if (elapsedCount >= 3)
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
			if (isPlayer1)
			{
				weakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else
			{
				mirroringWeakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elapsedCount++;
			if (elapsedCount >= 3)
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
			if (isPlayer1)
			{
				strongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else
			{
				mirroringStrongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elapsedCount++;
			if (elapsedCount >= 3)
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
		case State::Damaged:
			if (isPlayer1)
			{
				attacked->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else
			{
				mirroringAttacked->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elapsedCount++;
			if (elapsedCount >= 3)
			{
				elapsedCount = 0;
				frameX++;
			}
			if (frameX >= 4)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::Die:
			if (isPlayer1)
			{
				die->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else
			{
				mirroringDie->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elapsedCount++;
			if (elapsedCount >= 12)
			{
				elapsedCount = 0;
				frameX++;
			}
			if (frameX >= 4 && !isDie)
			{
				frameX = 4;
				isDie = true;
				BattleManager::GetSingleton()->SetDie();
			}
			break;
		case State::Walk:
			if (isPlayer1)
			{
				walk->Render(hdc, pos.x, pos.y, frameX, frameY);
				elapsedCount++;
				if (moveDir == MoveDir::Right)
				{
					if (elapsedCount == 5)
					{
						elapsedCount = 0;
						frameX++;
					}
					if (frameX >= 11)
					{
						frameX = 0;
					}
					if (!isMeet)
					{
						BattleManager::GetSingleton()->player1MoveCheck = 2;
						if (pos.x <= 281) pos.x += moveSpeed / 3;
					}
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
						frameX = 11;
					}
					BattleManager::GetSingleton()->player1MoveCheck = 1;
					if (pos.x >= 40) pos.x -= moveSpeed / 3;
				}
			}
			else
			{
				mirroringWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
				elapsedCount++;
				if (moveDir == MoveDir::Right)
				{
					if (elapsedCount == 5)
					{
						elapsedCount = 0;
						frameX++;
					}
					if (frameX >= 11)
					{
						frameX = 0;
					}
					BattleManager::GetSingleton()->player2MoveCheck = 2;
					if (pos.x <= 281) pos.x += moveSpeed / 3;
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
						frameX = 11;
					}
					if (!isMeet)
					{
						BattleManager::GetSingleton()->player2MoveCheck = 1;
						if (pos.x >= 40) pos.x -= moveSpeed / 3;
					}
				}
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
	SAFE_RELEASE(die);
	SAFE_RELEASE(mirroringIdle);
	SAFE_RELEASE(mirroringWalk);
	SAFE_RELEASE(mirroringWeakLeg);
	SAFE_RELEASE(mirroringWeakPunch);
	SAFE_RELEASE(mirroringStrongPunch);
	SAFE_RELEASE(mirroringDie);
}

void Kyo::IsCollision()
{
}


