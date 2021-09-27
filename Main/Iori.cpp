#include "Iori.h"
#include "Image.h"
#include "KeyManager.h"
#include "BattleManager.h"

void Iori::Init(bool isPlayer1)
{

	img = new Image;
	img->Init("Image/Character/Iori/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255));
	idle = new Image;
	idle->Init("Image/Character/Iori/Iori_Idle.bmp", 664, 109, 8, 1, true, RGB(255, 0, 255));
	weakLeg = new Image;
	weakLeg->Init("Image/Character/Iori/Iori_WeakLeg.bmp", 768, 109, 8, 1, true, RGB(255, 0, 255));
	weakPunch = new Image;
	weakPunch->Init("Image/Character/Iori/lori_WeakPunch.bmp", 600, 112, 5, 1, true, RGB(255, 0, 255));
	strongPunch = new Image;
	strongPunch->Init("Image/Character/Iori/Iori_StrongPunch2.bmp", 777, 121, 7, 1, true, RGB(255, 0, 255));
	damaged = new Image;
	damaged->Init("Image/Character/Iori/Iori_Damaged.bmp", 462, 115, 6, 1, true, RGB(255, 0, 255));
	die = new Image;
	die->Init("Image/Character/Iori/Iori_Die.bmp", 888, 131, 7, 1, true, RGB(255, 0, 255));


	MirroringImg = new Image;
	MirroringImg->Init("Image/Character/Iori/Iori_walk_mirroring.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255));
	MirroringIdle = new Image;
	MirroringIdle->Init("Image/Character/Iori/Iori_Idle_mirroring.bmp", 664, 109, 8, 1, true, RGB(255, 0, 255));
	MirroringWeakLeg = new Image;
	MirroringWeakLeg->Init("Image/Character/Iori/Iori_WeakLeg_mirroring.bmp", 768, 109, 8, 1, true, RGB(255, 0, 255));
	MirroringWeakPunch = new Image;
	MirroringWeakPunch->Init("Image/Character/Iori/lori_WeakPunch_mirroring.bmp", 600, 112, 5, 1, true, RGB(255, 0, 255));
	MirroringStrongPunch = new Image;
	MirroringStrongPunch->Init("Image/Character/Iori/Iori_StrongPunch2_mirroring.bmp", 777, 121, 7, 1, true, RGB(255, 0, 255));
	MirroringDamaged = new Image;
	MirroringDamaged->Init("Image/Character/Iori/Iori_Damaged_mirroring.bmp", 462, 115, 6, 1, true, RGB(255, 0, 255));

	moveDir = MoveDir::Right;

	state = State::IDLE;

	isAttack = false;

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

	this->isPlayer1 = isPlayer1;
	isHit = false;
}

void Iori::Init(int posX, int posY, bool isMoveRight)
{
	//this->pos.x = posX, this->pos.y = posY;

	//img = new Image;
	//img->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255));

	//frameX = frameY = 0;
	//elpasedCount = 0;
	//moveSpeed = 10.0f;

	//isMoveRight ? moveDir = MoveDir::Right : moveDir = MoveDir::Left;
}

void Iori::Update()
{
	if (isPlayer1) {
		if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER1_RIGHT_KEY) && state == State::IDLE)
		{
			frameX = 0;
			pos.x += moveSpeed;
			state = State::Walk;
			moveDir = MoveDir::Right;
			isAttack = false;
			elpasedCount = 0;

		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER1_LEFT_KEY) && state == State::IDLE)
		{

			frameX = 0;
			state = State::Walk;
			moveDir = MoveDir::Left;
			isAttack = false;
			elpasedCount = 0;
		}
		if (state == State::IDLE)
		{
			isAttack = false;
			state = State::IDLE;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_KICK) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::LegWeak;
			elpasedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_WEAK_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchWeak;
			elpasedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_STRONG_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchStrong;
			elpasedCount = 0;
		}

		if ((KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_LEFT_KEY)) && !isAttack)
		{
			frameX = 0;
			state = State::IDLE;
			elpasedCount = 0;
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
			elpasedCount = 0;

		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(PLAYER2_LEFT_KEY) && state == State::IDLE)
		{
			frameX = 0;
			state = State::Walk;
			moveDir = MoveDir::Left;
			isAttack = false;
			elpasedCount = 0;
		}

		if (state == State::IDLE)
		{
			isAttack = false;
			state = State::IDLE;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_KICK) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::LegWeak;
			elpasedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_WEAK_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchWeak;
			elpasedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_STRONG_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchStrong;
			elpasedCount = 0;
		}

		if ((KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_LEFT_KEY)) && !isAttack)
		{
			frameX = 0;
			state = State::IDLE;
			elpasedCount = 0;
		}
	}


	//Collider 관리 파트 

	if (isAttack && state == State::PunchWeak)
	{
		if (frameX > 1 && frameX < 3)
		{
			if (this->isPlayer1)
			{
				BattleManager::GetSingleton()->attackCollider[0].isAttack = true;
				if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[0].collider, true) && !isHit)
				{
					isHit = true;
					elpasedCount = -5; // Hit했을 때 경직도
				}

			}
			else
			{
				BattleManager::GetSingleton()->attackCollider2[0].isAttack = true;
				if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[0].collider, false) && !isHit)
				{
					isHit = true;
					elpasedCount = -5; // Hit했을 때 경직도
				}

			}
		}
		else if (frameX > 3)
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
		if (frameX > 2 && frameX < 5)
		{
			if (this->isPlayer1)
			{
				BattleManager::GetSingleton()->attackCollider[1].isAttack = true;
				if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[1].collider, true) && !isHit)
				{
					isHit = true;
					elpasedCount = -3; // Hit했을 때 경직도
				}
			}
			else
			{
				BattleManager::GetSingleton()->attackCollider2[1].isAttack = true;
				if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[1].collider, false) && !isHit)
				{
					isHit = true;
					elpasedCount = -3; // Hit했을 때 경직도
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
					elpasedCount = -3; // Hit했을 때 경직도
				}
			}
			else
			{
				BattleManager::GetSingleton()->attackCollider2[2].isAttack = true;
				if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider2[2].collider, false) && !isHit)
				{
					isHit = true;
					elpasedCount = -3; // Hit했을 때 경직도
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
			frameX = 0;
			state = State::Die;
		}
		else
		{
			state = State::Damaged;
		}
	}
}



void Iori::Render(HDC hdc)
{
	if (img && MirroringIdle)
	{
		switch (state)
		{
		case State::IDLE:
			if (isPlayer1) {
				idle->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				MirroringIdle->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elpasedCount++;
			if (elpasedCount == 5)
			{
				elpasedCount = 0;
				frameX++;
			}
			if (frameX == 8)
			{
				frameX = 0;
			}
			break;
		case State::LegWeak:
			if (isPlayer1) {
				weakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				MirroringWeakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elpasedCount++;
			if (elpasedCount == 3)
			{
				elpasedCount = 0;
				frameX++;
			}
			if (frameX == 8)
			{
				isAttack = false;
				state = State::IDLE;
				isHit = false;
				frameX = 0;
			}
			break;
		case State::PunchWeak:
			if (isPlayer1) {
				weakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				MirroringWeakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elpasedCount++;
			if (elpasedCount == 3)
			{
				elpasedCount = 0;
				frameX++;
			}
			if (frameX == 5)
			{
				isAttack = false;
				state = State::IDLE;
				isHit = false;
				frameX = 0;
			}
			break;
		case State::PunchStrong:
			if (isPlayer1) {
				strongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				MirroringStrongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
			}

			elpasedCount++;
			if (elpasedCount == 3)
			{
				elpasedCount = 0;
				frameX++;
			}
			if (frameX == 7)
			{
				isAttack = false;
				state = State::IDLE;
				isHit = false;
				frameX = 0;
			}
			break;
		case State::Damaged:
			if (isPlayer1) {
				damaged->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				MirroringDamaged->Render(hdc, pos.x, pos.y, frameX, frameY);
			}

			elpasedCount++;
			if (elpasedCount == 3)
			{
				elpasedCount = 0;
				frameX++;
			}
			if (frameX == 6)
			{
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			break;
		case State::Walk:
			if (isPlayer1) {
				img->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				MirroringImg->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elpasedCount++;
			if (moveDir == MoveDir::Right) {
				if (elpasedCount == 5)
				{

					elpasedCount = 0;
					frameX++;
				}
				if (frameX >= 8)
				{
					frameX = 0;
				}
				pos.x += moveSpeed / 3;
			}
			else {
				if (elpasedCount == 5)
				{

					elpasedCount = 0;
					frameX--;
				}
				if (frameX <= 0)
				{
					frameX = 8;
				}
				pos.x -= moveSpeed / 3;

			}
			break;
		case State::Die:
			if (isPlayer1) {
				die->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				die->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			elpasedCount++;
			if (elpasedCount == 12)
			{
				elpasedCount = 0;
				frameX++;
			}

			if (frameX >= 6 && !isDie)
			{
				frameX = 6;
				isDie = true;
				BattleManager::GetSingleton()->SetDie();
			}

			break;
		}
	}

}




void Iori::Release()
{
	if (img) { delete img; }
	if (idle) { delete idle; }
	if (strongPunch) { delete strongPunch; }
	if (weakLeg) { delete weakLeg; }
	if (weakPunch) { delete weakPunch; }
}

