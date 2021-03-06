#include "BattleManager.h"
#include "Image.h"
#include "SceneManager.h"

void BattleManager::Init(string player, bool isPlayer1, POINTFLOAT pos)
{
	if (isPlayer1) //플레이어 1일 때
	{
		playerPos1 = pos;
	}
}

void BattleManager::Init()
{
	for (int i = 0; i < 21; i++)
	{
		ko[i] = new Image;
		char cha[100];
		string str = "Image/UI/KO/KO";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		ko[i]->Init(cha, 680 / 2.1, 492 / 2.0, 1, 1, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 25; i++)
	{
		win[i] = new Image;
		char cha[100];
		string str = "Image/UI/KO/Winner";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		win[i]->Init(cha, 680 / 2.1, 492 / 2.0, 1, 1, true, RGB(255, 0, 255));
	}

	for (int i = 0; i < 20; i++)
	{
		sceneTransform[i] = new Image;
		char cha[100];
		string str = "Image/UI/SceneTransform/CutChange";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		sceneTransform[i]->Init(cha, 680 / 2.1, 492 / 2.0, 1, 1, true, RGB(255, 0, 255));
	}
}



void BattleManager::SetColliderPos(string player, bool isPlayer1, POINTFLOAT pos)
{
	if (isPlayer1) //플레이어 1일 때
	{
		playerPos1 = pos;
		if (player._Equal("Iori")) 
		{
			damagedCollider[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider[0].setColliderPos(pos.x + 20, pos.y - 20, pos.x + 60, pos.y); attackCollider[0].damage = 5;
			attackCollider[1].setColliderPos(pos.x + 10, pos.y - 50, pos.x + 60, pos.y + 10); attackCollider[1].damage = 10;
			attackCollider[2].setColliderPos(pos.x + 20, pos.y - 20, pos.x + 50, pos.y + 50); attackCollider[2].damage = 8;
		}

		if (player._Equal("Kim")) 
		{
			damagedCollider[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider[0].setColliderPos(pos.x + 20, pos.y - 15, pos.x + 60, pos.y + 5); attackCollider[0].damage = 5;		// 약손
			attackCollider[1].setColliderPos(pos.x + 10, pos.y - 50, pos.x + 50, pos.y - 10); attackCollider[1].damage = 7;		// 강손1
			attackCollider[2].setColliderPos(pos.x + 10, pos.y - 45, pos.x + 50, pos.y - 10); attackCollider[2].damage = 8;		// 약발
			attackCollider[3].setColliderPos(pos.x + 20, pos.y - 40, pos.x + 60, pos.y - 10); attackCollider[3].damage = 12;	// 강발
			attackCollider[4].setColliderPos(pos.x + 10, pos.y - 65, pos.x + 50, pos.y - 30); attackCollider[4].damage = 7;		// 강손2
		}
		if (player._Equal("Kyo")) 
		{
			damagedCollider[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider[0].setColliderPos(pos.x + 20, pos.y - 35, pos.x + 50, pos.y - 15); attackCollider[0].damage = 5;		// 약손
			attackCollider[1].setColliderPos(pos.x + 20, pos.y - 15, pos.x + 60, pos.y + 10); attackCollider[1].damage = 7;		// 강손
			attackCollider[2].setColliderPos(pos.x + 20, pos.y - 25, pos.x + 60, pos.y - 10); attackCollider[2].damage = 8;		// 약발
			attackCollider[3].setColliderPos(pos.x + 20, pos.y - 40, pos.x + 50, pos.y - 20); attackCollider[3].damage = 12;	// 강발
		}
		if (player._Equal("May")) 
		{
			damagedCollider[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider[0].setColliderPos(pos.x + 10, pos.y - 30, pos.x + 55, pos.y - 20); attackCollider[0].damage = 5;        // 약손
			attackCollider[1].setColliderPos(pos.x + 15, pos.y - 25, pos.x + 70, pos.y); attackCollider[1].damage = 7;        // 강손
			attackCollider[2].setColliderPos(pos.x + 10, pos.y - 15, pos.x + 70, pos.y + 15); attackCollider[2].damage = 8;        // 약발
			attackCollider[3].setColliderPos(pos.x + 10, pos.y - 50, pos.x + 65, pos.y); attackCollider[3].damage = 12;    // 강발
		}
	}
	else // 플레이어 2일 때
	{
		playerPos2 = pos;
		if (player._Equal("Iori")) 
		{
			damagedCollider2[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider2[0].setColliderPos(pos.x - 60, pos.y - 20, pos.x - 20, pos.y);  attackCollider2[0].damage = 5;
			attackCollider2[1].setColliderPos(pos.x - 60, pos.y - 50, pos.x - 10, pos.y + 10); attackCollider2[1].damage = 10;
			attackCollider2[2].setColliderPos(pos.x - 50, pos.y - 20, pos.x - 20, pos.y + 50); attackCollider2[2].damage = 8;
		}


		if (player._Equal("Kim")) 
		{
			damagedCollider2[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider2[0].setColliderPos(pos.x - 60, pos.y - 15, pos.x - 20, pos.y + 5); attackCollider2[0].damage = 5;	 // 약손
			attackCollider2[1].setColliderPos(pos.x + 10, pos.y - 50, pos.x + 60, pos.y + 10); attackCollider2[1].damage = 7;	 // 강손1
			attackCollider2[2].setColliderPos(pos.x - 10, pos.y - 45, pos.x - 50, pos.y - 10); attackCollider2[2].damage = 8;	 // 약발
			attackCollider2[3].setColliderPos(pos.x - 60, pos.y - 40, pos.x - 20, pos.y - 10); attackCollider2[3].damage = 12;	 // 강발
			attackCollider2[4].setColliderPos(pos.x - 60, pos.y - 50, pos.x - 10, pos.y + 10); attackCollider2[4].damage = 7;	 // 강손2
		}

		if (player._Equal("Kyo"))
		{
			damagedCollider2[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider2[0].setColliderPos(pos.x - 50, pos.y - 35, pos.x - 20, pos.y - 15); attackCollider2[0].damage = 5;		// 약손
			attackCollider2[1].setColliderPos(pos.x - 60, pos.y - 15, pos.x - 20, pos.y + 10); attackCollider2[1].damage = 7;		// 강손1
			attackCollider2[2].setColliderPos(pos.x - 60, pos.y - 25, pos.x - 20, pos.y - 10); attackCollider2[2].damage = 8;		// 약발
			attackCollider2[3].setColliderPos(pos.x - 50, pos.y - 40, pos.x - 20, pos.y - 20); attackCollider2[3].damage = 12;		// 강발
		}
		if (player._Equal("May"))
		{
			damagedCollider2[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider2[0].setColliderPos(pos.x - 55, pos.y - 30, pos.x - 10, pos.y - 20); attackCollider2[0].damage = 5;        // 약손
			attackCollider2[1].setColliderPos(pos.x - 70, pos.y - 25, pos.x - 15, pos.y); attackCollider2[1].damage = 7;        // 강손
			attackCollider2[2].setColliderPos(pos.x - 70, pos.y - 15, pos.x - 10, pos.y + 15); attackCollider2[2].damage = 8;        // 약발
			attackCollider2[3].setColliderPos(pos.x - 65, pos.y - 50, pos.x - 10, pos.y); attackCollider2[3].damage = 12;    // 강발
		}
	}
}

void BattleManager::Render(HDC hdc)
{
	for (int i = 0; i < 6; i++) 
	{
		Rectangle(hdc, damagedCollider[i].collider.left, damagedCollider[i].collider.top, damagedCollider[i].collider.right, damagedCollider[i].collider.bottom);
		Rectangle(hdc, damagedCollider2[i].collider.left, damagedCollider2[i].collider.top, damagedCollider2[i].collider.right, damagedCollider2[i].collider.bottom);

	}
	for (int i = 0; i < 5; i++)
	{
		if(attackCollider[i].isAttack)
			Rectangle(hdc, attackCollider[i].collider.left, attackCollider[i].collider.top, attackCollider[i].collider.right, attackCollider[i].collider.bottom);
		if (attackCollider2[i].isAttack)
			Rectangle(hdc, attackCollider2[i].collider.left, attackCollider2[i].collider.top, attackCollider2[i].collider.right, attackCollider2[i].collider.bottom);
	}


	if ((player1Hp <= 0 || player2Hp <= 0) )
	{
		if (gameState != State::KO && gameState != State::END)
		{
			
			if( gameState == State::Die && gameState != State::END)
			{ 
				elapsedCount++;
				if (elapsedCount >= maxElpasedCount)
				{
					elapsedCount = 0;
					frame++;

					if (frame >= maxFrame )
					{
						maxElpasedCount = 3;
						frame = 0; maxFrame = 25;
						gameState = State::KO;
					}
				}
				KORender(hdc);
			}
		}
		else if(gameState != State::END)
		{
			elapsedCount++;
			if (elapsedCount >= maxElpasedCount)
			{
				elapsedCount = 0;
				frame++;

				if (frame >= maxFrame )
				{
					maxElpasedCount = 1;
					frame = 0; maxFrame = 20;
					gameState = State::END;
				}
			}
			WinRender(hdc);
		}

	}

}

bool BattleManager::CheckCollision(RECT *rect, bool isPlayer1)
{
	RECT a;
	if (isPlayer1)
	{
		for (int i = 0; i < 2; i++) 
		{
			if (IntersectRect(&a, rect, &damagedCollider2[i].collider)) {
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			if (IntersectRect(&a, rect, &damagedCollider[i].collider)) {
				return true;
			}
		}
	}
	return false;
}


bool BattleManager::CheckDamaged(bool isPlayer1)
{
	RECT a;
	if (isPlayer1) //플레이어 1일경우
	{
		for (int j = 0; j < 1; j++)
		{
			for (int i = 0; i < 5; i++)
			{
				if (IntersectRect(&a, &damagedCollider[j].collider, &attackCollider2[i].collider) && attackCollider2[i].isAttack && !isPlayer1Damaged) 
				{ // 해당콜라이더가 공격 상태인 경우
					player1Hp -= attackCollider2[i].damage;
					isPlayer1Damaged = true;
					return true;
				}
			}
		}
	}
	else
	{
		for (int j = 0; j < 1; j++)
		{
			for (int i = 0; i < 5; i++)
			{
				if (IntersectRect(&a, &damagedCollider2[j].collider, &attackCollider[i].collider) && attackCollider[i].isAttack && !isPlayer2Damaged) 
				{
					player2Hp -= attackCollider[i].damage;
					isPlayer2Damaged = true;
					return true;
				}
			}
		}
	}


	return false;
}

void BattleManager::KORender(HDC hdc)
{
	if (player1Hp <= 0 || player2Hp <= 0)
	{
		ko[frame]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0);
	}
}

void BattleManager::WinRender(HDC hdc)
{
	if (player1Hp <= 0)
	{
		win[frame]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0);
	}
	else
	{	
		win[frame]->Render(hdc, WIN_SIZE_X / 1.2 - WIN_SIZE_X , WIN_SIZE_Y / 2, 0, 0);
	}
}

bool BattleManager::SceneTransform(HDC hdc)
{
	if (gameState == State::END)
	{
		elapsedCount++;
		if (elapsedCount >= maxElpasedCount)
		{
			elapsedCount = 0;
			frame++;

			if (frame >= maxFrame)
			{
				SceneManager::GetSingleton()->SetIsSceneState("MainTitle");
				return true;

			}
		}
		sceneTransform[frame]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0);
	}
}

void BattleManager::InitCollider()
{
	damagedCollider[0].setColliderPos(0, 0, 0, 0);
	attackCollider[0].setColliderPos(0, 0, 0, 0);
	attackCollider[1].setColliderPos(0, 0, 0, 0);
	attackCollider[2].setColliderPos(0, 0, 0, 0);
	attackCollider[3].setColliderPos(0, 0, 0, 0);
	damagedCollider[0].isAttack = false;
	attackCollider[0].isAttack = false;
	attackCollider[1].isAttack = false;
	attackCollider[2].isAttack = false;
	attackCollider[3].isAttack = false;



	damagedCollider2[0].setColliderPos(0,0,0,0);
	attackCollider2[0].setColliderPos(0,0,0,0); attackCollider2[0].damage = 5;        // 약손
	attackCollider2[1].setColliderPos(0,0,0,0); attackCollider2[1].damage = 7;        // 강손
	attackCollider2[2].setColliderPos(0,0,0,0); attackCollider2[2].damage = 8;        // 약발
	attackCollider2[3].setColliderPos(0,0,0,0); attackCollider2[3].damage = 12;    // 강발
	damagedCollider2[0].isAttack = false;
	attackCollider2[0].isAttack = false;
	attackCollider2[1].isAttack = false;
	attackCollider2[2].isAttack = false;
	attackCollider2[3].isAttack = false;

}

bool BattleManager::CheckMeet()
{
	RECT a;
	if (IntersectRect(&a, &damagedCollider[0].collider, &damagedCollider2[0].collider))
	{
		return true;
	}
	return false;
}


void BattleManager::GameInit()
{
	player1Hp = 100;
	player2Hp = 100;

	isPlayer1Damaged = false;
	isPlayer2Damaged = false;

	player1MoveCheck = 0;
	player2MoveCheck = 0;
	backGroundMove = 0;

	elapsedCount = 0;
	maxElpasedCount = 3;
	frame = 0;
	maxFrame = 21;
	gameState = State::Playing;

	SceneManager::GetSingleton()->SetPlayerChar("Empty", true);
	SceneManager::GetSingleton()->SetPlayerChar("Empty", false);
}

