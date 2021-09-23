#include "Iori.h"
#include "Image.h"
#include "KeyManager.h"

void Iori::Init(bool isPlayer1)
{
	img = new Image;
	img->Init("Image/Character/Iori/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255,0,255));
	idle = new Image;
	idle->Init("Image/Character/Iori/Iori_Idle.bmp", 664, 109, 8, 1, true, RGB(255, 0, 255));
	weakLeg = new Image;
	weakLeg->Init("Image/Character/Iori/Iori_WeakLeg.bmp", 768, 109, 8, 1, true, RGB(255, 0, 255));
	weakPunch = new Image;
	weakPunch->Init("Image/Character/Iori/lori_WeakPunch.bmp", 600, 112, 5, 1, true, RGB(255, 0, 255));
	strongPunch = new Image;
	strongPunch->Init("Image/Character/Iori/Iori_StrongPunch2.bmp", 777, 121, 7, 1, true, RGB(255, 0, 255));

	moveDir = MoveDir::Right;

	state = State::IDLE;

	isAttack = false;

	frameX = frameY = 0;
	elpasedCount = 0;
	moveSpeed = 10.0f;
	this->pos.x = WIN_SIZE_X / 4;
	this->pos.y = WIN_SIZE_Y / 1.3;
 
	for (int i = 0; i < 4; i++)
	{
		attackCollider[i].init();
	}

	damagedCollider[0].init(pos.x - 25, pos.x + 25, pos.y - 40, pos.y + 50);

	this->isPlayer1 = isPlayer1;
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
			elpasedCount = 0;
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
			cout << 1;
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
			elpasedCount = 0;
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

		if ((KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER1_LEFT_KEY)) && !isAttack)
		{
			frameX = 0;
			state = State::IDLE;
			elpasedCount = 0;
		}
	}


	//Collider 관리 파트 
	if (state == State::Walk)
	{
		damagedCollider->setColliderPos(pos.x - 25, pos.x + 25, pos.y - 40, pos.y + 50);
	}
	else if (isAttack && state==State::PunchWeak)
	{
		if (frameX > 2)
		{
			attackCollider[0].setColliderPos(pos.x + 20, pos.x + 70, pos.y + 10, pos.y - 20);
		}
		else
		{
			attackCollider[0].setColliderPos(0, 0, 0, 0);
		}
	}
	else if (isAttack && state == State::PunchStrong)
	{
		if (frameX > 2 && frameX < 5)
		{
			attackCollider[1].setColliderPos(pos.x + 20, pos.x + 70, pos.y + 10, pos.y - 50);
		}
		else 
		{
			attackCollider[1].setColliderPos(0,0,0,0);
		}
	}
	else if (isAttack && state == State::LegWeak)
	{
		if (frameX > 2 && frameX <5 )
		{
			attackCollider[2].setColliderPos(pos.x + 20, pos.x + 70, pos.y + 50, pos.y - 20);
		}
		else 
		{
			attackCollider[2].setColliderPos(0, 0, 0, 0);
		}
	}
	
	if (!isAttack)
	{
		for (int i = 0; i < 4; i++)
		{
			attackCollider[i].setColliderPos(0, 0, 0, 0);
			damagedCollider[i+2].setColliderPos(0, 0, 0, 0);
		}
	}

}



void Iori::Render(HDC hdc)
{

	if (img) 
	{
		//콜라이더 출력
		for (int i = 0; i < 6; i++) 
		{
			damagedCollider[i].Render(hdc);
		}
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		for (int i = 0; i < 4; i++)
		{
			
			attackCollider[i].Render(hdc);
		}
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
		switch (state) 
		{
		case State::IDLE:
			idle->Render(hdc, pos.x, pos.y, frameX, frameY);
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
			weakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
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
				frameX = 0;
			}
			break;
		case State::PunchWeak:
			weakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
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
				frameX = 0;
			}
			break;
		case State::PunchStrong:
			strongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
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
				frameX = 0;
			}
			break;
		case State::Walk:
			img->Render(hdc, pos.x, pos.y, frameX, frameY);
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
		}
	}
}

void Iori::Release()
{
	if (img) 
	{
		delete img;
	}
}

void Iori::IsCollision()
{
}


