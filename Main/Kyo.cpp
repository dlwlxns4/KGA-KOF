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

		frameX = frameY = 0;
	}
	else
	{
		MirroringIdle = new Image;
		MirroringIdle->Init("Image/Character/Kyo/Kyo_idle_mirroring.bmp", 1120, 116, 10, 1, true, RGB(240, 0, 240));
		MirroringWalk = new Image;
		MirroringWalk->Init("Image/Character/Kyo/Kyo_walk_mirroring.bmp", 1344, 116, 12, 1, true, RGB(240, 0, 240));
		MirroringWeakPunch = new Image;
		MirroringWeakPunch->Init("Image/Character/Kyo/Kyo_smallPunch_mirroring.bmp", 336, 116, 3, 1, true, RGB(240, 0, 240));
		MirroringStrongPunch = new Image;
		MirroringStrongPunch->Init("Image/Character/Kyo/Kyo_strongPunch_mirroring.bmp", 2016, 116, 18, 1, true, RGB(240, 0, 240));
		MirroringWeakLeg = new Image;
		MirroringWeakLeg->Init("Image/Character/Kyo/Kyo_weakLeg_mirroring.bmp", 1008, 116, 9, 1, true, RGB(240, 0, 240));
		MirroringStrongLeg = new Image;
		MirroringStrongLeg->Init("Image/Character/Kyo/Kyo_strongLeg_mirroring.bmp", 1680, 116, 15, 1, true, RGB(240, 0, 240));
		MirroringAttacked = new Image;
		MirroringAttacked->Init("Image/Character/Kyo/Kyo_attacked_mirroring.bmp", 560, 116, 5, 1, true, RGB(240, 0, 240));

		frameX = 9;
		frameY = 0;
	}

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
}

void Kyo::Init(int posX, int posY, bool isMoveRight)
{
}

void Kyo::Update()
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

		// A누르고 공격중이 아닐때만 가능
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_KICK) && !isAttack)
		{
			frameX = 0;
			isAttack = true;
			state = State::LegWeak;
		}
		// A누르고 공격중이 아닐때만 가능
		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_STRONG_KICK) && !isAttack)
		{
			frameX = 0;
			isAttack = true;
			state = State::LegStrong;
		}
		// A누르고 공격중이 아닐때만 가능
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_PUNCH) && !isAttack)
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchWeak;
		}
		// A누르고 공격중이 아닐때만 가능
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_STRONG_PUNCH) && !isAttack)
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchStrong;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_LEFT_KEY))
		{
			frameX = 0;
			state = State::IDLE;
		}
	}

	//Collider 관리 파트 
	if (isAttack && state == State::PunchWeak)
	{
		cout << frameX << endl;
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
					cout << "attackCollider2 : " << BattleManager::GetSingleton()->attackCollider2[1].isAttack << endl;
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

	if (BattleManager::GetSingleton()->CheckDamaged(isPlayer1))
	{
		state = State::Damaged;
	}

}

void Kyo::Render(HDC hdc)
{
	static bool check = true;
	static bool idelCheck = true;
	if (isPlayer1)
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
			case State::Damaged:
				if (isPlayer1) {
					attacked->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				elapsedCount++;
				if (elapsedCount == 3)
				{
					elapsedCount = 0;
					frameX++;
				}
				if (frameX == 4)
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
					if (frameX >= 11)
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
						frameX = 11;
					}
					pos.x -= moveSpeed / 3;
				}
				break;
			}
		}
	}
	else
	{
		if (MirroringIdle)
		{
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

			switch (state)
			{
			case State::IDLE:
				MirroringIdle->Render(hdc, pos.x, pos.y, frameX, frameY);
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
				MirroringWeakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
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
				MirroringStrongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
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
				MirroringWeakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
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
				MirroringStrongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
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
			case State::Damaged:
				if (isPlayer1) {
					MirroringAttacked->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				elapsedCount++;
				if (elapsedCount == 3)
				{
					elapsedCount = 0;
					frameX++;
				}
				if (frameX == 4)
				{
					isAttack = false;
					state = State::IDLE;
					frameX = 0;
				}
				break;
			case State::Walk:
				MirroringWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
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
						frameX = 11;
					}
					pos.x -= moveSpeed / 3;
				}
				break;
			}
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


