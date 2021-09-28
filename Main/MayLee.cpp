#include "MayLee.h"
#include "Image.h"
#include "KeyManager.h"
#include "BattleManager.h"

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


void MayLee::Init(bool isPlayer1)
{
	if (isPlayer1)
	{
		idle = new Image;			// 대기
		idle->Init("Image/Character/may_lee/MayLee_Idle_8F.bmp", 528, 100, 8, 1, true, RGB(108, 156, 114));
		frontWalk = new Image;		// 앞으로
		frontWalk->Init("Image/Character/may_lee/MayLee_Walk_5F.bmp", 270, 112, 5, 1, true, RGB(108, 156, 114));
		backWalk = new Image;		// 뒤로
		backWalk->Init("Image/Character/may_lee/MayLee_Back_5F.bmp", 270, 112, 5, 1, true, RGB(108, 156, 114));
		weakPunch = new Image;		// 약주먹
		weakPunch->Init("Image/Character/may_lee/MayLee_WeakPunchNormal_4F.bmp", 400, 103, 4, 1, true, RGB(108, 156, 114));
		strongPunch = new Image;	// 강주먹
		strongPunch->Init("Image/Character/may_lee/MayLee_StrongPunchNormal_8F.bmp", 1200, 119, 8, 1, true, RGB(108, 156, 114));
		weakLeg = new Image;		// 약발차기
		weakLeg->Init("Image/Character/may_lee/MayLee_WeakKickNormal_10F.bmp", 1500, 107, 10, 1, true, RGB(108, 156, 114));
		strongLeg = new Image;		// 강발차기
		strongLeg->Init("Image/Character/may_lee/MayLee_StrongKickNormal_13F.bmp", 1800, 120, 13, 1, true, RGB(108, 156, 114));
		hit = new Image;		// 피격
		hit->Init("Image/Character/may_lee/MayLee_Attacked_5F.bmp", 374, 91, 5, 1, true, RGB(108, 156, 114));
		die = new Image;		// 사망
		die->Init("Image/Character/may_lee/MayLee_Lose_9F.bmp", 1125, 100, 9, 1, true, RGB(108, 156, 114));
	}
	else
	{
		mirroringIdle = new Image;			// 대기
		mirroringIdle->Init("Image/Character/may_lee/MayLee_Idle_8F_mirroring.bmp", 528, 100, 8, 1, true, RGB(108, 156, 114));
		mirroringFrontWalk = new Image;		// 앞으로
		mirroringFrontWalk->Init("Image/Character/may_lee/MayLee_Walk_5F_mirroring.bmp", 270, 112, 5, 1, true, RGB(108, 156, 114));
		mirroringBackWalk = new Image;		// 뒤로
		mirroringBackWalk->Init("Image/Character/may_lee/MayLee_Back_5F_mirroring.bmp", 270, 112, 5, 1, true, RGB(108, 156, 114));
		mirroringWeakPunch = new Image;		// 약주먹
		mirroringWeakPunch->Init("Image/Character/may_lee/MayLee_WeakPunchNormal_4F_mirroring.bmp", 400, 103, 4, 1, true, RGB(108, 156, 114));
		mirroringStrongPunch = new Image;	// 강주먹
		mirroringStrongPunch->Init("Image/Character/may_lee/MayLee_StrongPunchNormal_8F_mirroring.bmp", 1200, 119, 8, 1, true, RGB(108, 156, 114));
		mirroringWeakLeg = new Image;		// 약발차기
		mirroringWeakLeg->Init("Image/Character/may_lee/MayLee_WeakKickNormal_10F_mirroring.bmp", 1500, 107, 10, 1, true, RGB(108, 156, 114));
		mirroringstrongLeg = new Image;		// 강발차기
		mirroringstrongLeg->Init("Image/Character/may_lee/MayLee_StrongKickNormal_13F_mirroring.bmp", 1800, 120, 13, 1, true, RGB(108, 156, 114));
		mirroringHit = new Image;		// 피격
		mirroringHit->Init("Image/Character/may_lee/MayLee_Attacked_5F_mirroring.bmp", 374, 91, 5, 1, true, RGB(108, 156, 114));
		mirroringDie = new Image;		// 사망
		mirroringDie->Init("Image/Character/may_lee/MayLee_Lose_9F_mirroring.bmp", 1125, 100, 9, 1, true, RGB(108, 156, 114));
	}

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
	isMeet = false;
}

void MayLee::Update()
{
	if (isPlayer1) {
		if (BattleManager::GetSingleton()->player1Hp <= 0) {
			state = State::Die;
		}
	}
	else {
		if (BattleManager::GetSingleton()->player2Hp <= 0) {
			state = State::Die;
		}
	}
	if (BattleManager::GetSingleton()->CheckMeet())
	{
		isMeet = true;
	}
	else
	{
		isMeet = false;
	}
	if(isPlayer1)
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
			}
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
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER1_STRONG_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchStrong;
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
			if (!isMeet)
			{
				frameX = 0;
				state = State::Walk;
				moveDir = MoveDir::Left;
				isAttack = false;
			}
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
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(PLAYER2_STRONG_PUNCH) && !isAttack) // A누르고 공격중이 아닐때만 가능
		{
			frameX = 0;
			isAttack = true;
			state = State::PunchStrong;
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

		if (KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_RIGHT_KEY) || KeyManager::GetSingleton()->IsOnceKeyUp(PLAYER2_LEFT_KEY))
		{
			frameX = 0;
			state = State::IDLE;
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
		else if (frameX > 2)
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
		if (frameX > 1 && frameX < 4)
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
					cout << "attackCollider2 : " << BattleManager::GetSingleton()->attackCollider2[1].isAttack << endl;
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
	else if (isAttack && state == State::LegStrong)
	{
	if (frameX > 6 && frameX < 9)
	{
		if (this->isPlayer1)
		{
			BattleManager::GetSingleton()->attackCollider[3].isAttack = true;
			if (BattleManager::GetSingleton()->CheckCollision(&BattleManager::GetSingleton()->attackCollider[2].collider, true) && !isHit)
			{
				isHit = true;
				elpasedCount = -3; // Hit했을 때 경직도
			}
		}
		else
		{
			BattleManager::GetSingleton()->attackCollider2[3].isAttack = true;
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
			cout << "damaged" << endl;

		}
		else
		{
			state = State::Damaged;
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

void MayLee::Render(HDC hdc)
{
	if (isPlayer1)
	{
		if (idle)
		{
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

			switch (state)
			{
			case State::IDLE:
				idle->Render(hdc, pos.x, pos.y, frameX, frameY);
				ElpasedCount(fps, frameX, true);
				if (frameX >= 8) frameX = 0;
				break;
			case State::Walk:
				if (moveDir == MoveDir::Right) {
					frontWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
					ElpasedCount(fps, frameX, true);
					if (frameX >= 5) frameX = 0;
					if (!isMeet) {
						BattleManager::GetSingleton()->player1MoveCheck = 2;
						if (pos.x <= 281) pos.x += moveSpeed / 3;

					}
				}
				else {
					backWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
					ElpasedCount(fps, frameX, true);
					if (frameX >= 5) frameX = 0;
					BattleManager::GetSingleton()->player1MoveCheck = 1;
					if (pos.x >= 40)pos.x -= moveSpeed / 3;
				}
				break;
			case State::PunchWeak:
				if (!originCheck) {
					originCheck = true;
					originPos = pos.x;
				}
				if (frameX == 0 && elpasedCount == 0)pos.x += 0;
				weakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
				elpasedCount = ElpasedCount(fps, frameX, true);
				if (frameX >= 4)
				{
					originCheck = false;
					pos.x = originPos;
					isAttack = false;
					state = State::IDLE;
					frameX = 0;
				}
				break;
			case State::PunchStrong:
				if (!originCheck) {
					originCheck = true;
					originPos = pos.x;
				}
				if (frameX == 0 && elpasedCount == 0)pos.x += 15;
				strongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
				elpasedCount = ElpasedCount(fps, frameX, true);
				if (frameX >= 8)
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
				if (frameX >= 10)
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
				if (frameX == 0 && elpasedCount == 0)pos.x += 40;
				if (frameX == 1 && elpasedCount == 0)pos.x -= 15;
				if (frameX == 3 && elpasedCount == 0)pos.x -= 10;
				strongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
				elpasedCount = ElpasedCount(fps, frameX, true);

				if (frameX >= 13)
				{
					originCheck = false;
					pos.x = originPos;
					isAttack = false;
					state = State::IDLE;
					frameX = 0;
				}
				break;
			case State::Damaged:
				{static bool check = true;
				if (check) {
					frameX = 0;
					check = false;
				}
				if (isPlayer1) {
					hit->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				else {
					mirroringHit->Render(hdc, pos.x, pos.y, frameX, frameY);
				}

				elpasedCount++;
				if (elpasedCount == 3)
				{
					elpasedCount = 0;
					frameX++;
				}
				if (frameX >= 4)
				{
					check = true;
					isAttack = false;
					state = State::IDLE;
					frameX = 0;
				}
				}
					break;
			case State::Die:
				cout << frameX << endl;
				if (isPlayer1) {
					die->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				else {
					mirroringDie->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				elpasedCount++;
				if (elpasedCount == 12)
				{
					elpasedCount = 0;
					frameX++;
				}
				if (frameX >= 8)
				{
					frameX = 8;
					BattleManager::GetSingleton()->SetDie();
				}

				break;
		
			}
			
		}
	}
	else
	{
		if (mirroringIdle)
		{
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	
			switch (state)
			{
			case State::IDLE:
				mirroringIdle->Render(hdc, pos.x, pos.y, frameX, frameY);
				ElpasedCount(fps, frameX, true);
				if (frameX >= 8) frameX = 0;
				break;
			case State::Walk:
				if (moveDir == MoveDir::Right) {
					mirroringFrontWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
					ElpasedCount(fps, frameX, true);
					if (frameX >= 5) frameX = 0;
					BattleManager::GetSingleton()->player2MoveCheck = 2;
					if (pos.x <= 281) pos.x += moveSpeed / 3;
				}
				else {
					mirroringBackWalk->Render(hdc, pos.x, pos.y, frameX, frameY);
					ElpasedCount(fps, frameX, true);
					if (frameX >= 5) frameX = 0;
					if (!isMeet) {
						BattleManager::GetSingleton()->player2MoveCheck = 1;
						if (pos.x >= 40)pos.x -= moveSpeed / 3;

					}
				}
				break;
			case State::PunchWeak:
				if (!originCheck) {
					originCheck = true;
					originPos = pos.x;
				}
				if (frameX == 0 && elpasedCount == 0)pos.x += 0;
				mirroringWeakPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
				elpasedCount = ElpasedCount(fps, frameX, true);
				if (frameX >= 4)
				{
					originCheck = false;
					pos.x = originPos;
					isAttack = false;
					state = State::IDLE;
					frameX = 0;
				}
				break;
			case State::PunchStrong:
				if (!originCheck) {
					originCheck = true;
					originPos = pos.x;
				}
				if (frameX == 0 && elpasedCount == 0)pos.x += 15;
				mirroringStrongPunch->Render(hdc, pos.x, pos.y, frameX, frameY);
				elpasedCount = ElpasedCount(fps, frameX, true);
				if (frameX >= 8)
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
				mirroringWeakLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
				elpasedCount = ElpasedCount(fps, frameX, true);
				if (frameX >= 10)
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
				if (frameX == 0 && elpasedCount == 0)pos.x += 40;
				if (frameX == 1 && elpasedCount == 0)pos.x -= 15;
				if (frameX == 3 && elpasedCount == 0)pos.x -= 10;
				mirroringstrongLeg->Render(hdc, pos.x, pos.y, frameX, frameY);
				elpasedCount = ElpasedCount(fps, frameX, true);
	
				if (frameX >= 13)
				{
					originCheck = false;
					pos.x = originPos;
					isAttack = false;
					state = State::IDLE;
					frameX = 0;
				}
				break;
			case State::Damaged:
			{static bool check = true;
			if (check) {
				frameX = 0;
				check = false;
			}
			if (isPlayer1) {
				hit->Render(hdc, pos.x, pos.y, frameX, frameY);
			}
			else {
				mirroringHit->Render(hdc, pos.x, pos.y, frameX, frameY);
			}

			elpasedCount++;
			if (elpasedCount == 3)
			{
				elpasedCount = 0;
				frameX++;
			}
			if (frameX >= 4)
			{
				check = true;
				isAttack = false;
				state = State::IDLE;
				frameX = 0;
			}
			}
				break;
			case State::Die:
				if (isPlayer1) {
					die->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				else {
					mirroringDie->Render(hdc, pos.x, pos.y, frameX, frameY);
				}
				elpasedCount++;
				if (elpasedCount == 12)
				{
					elpasedCount = 0;
					frameX++;
				}
				if (frameX >= 8)
				{
					frameX = 8;
					BattleManager::GetSingleton()->SetDie();
				}

				break;
			}
		}
	}
}

void MayLee::Release()
{
	if (idle) delete idle;
	if (frontWalk) delete frontWalk;
	if (backWalk) delete backWalk;
	if (strongPunch) delete strongPunch;
	if (weakLeg) delete weakLeg;
	if (strongLeg) delete strongLeg;
	if (weakPunch) delete weakPunch;
}

