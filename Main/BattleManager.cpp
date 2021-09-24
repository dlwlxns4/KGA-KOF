#include "BattleManager.h"
#include "UIManager.h"

void BattleManager::Init(string player, bool isPlayer1, POINTFLOAT pos)
{
	if (isPlayer1) //플레이어 1일 때
	{
		if (player._Equal("Iori")) {
			damagedCollider[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider[0].setColliderPos(pos.x + 20, pos.y - 20, pos.x + 60, pos.y); attackCollider[0].damage = 5;
			attackCollider[1].setColliderPos(pos.x + 10, pos.y - 50, pos.x + 60, pos.y + 10); attackCollider[1].damage = 10;
			attackCollider[2].setColliderPos(pos.x + 20, pos.y - 20, pos.x + 50, pos.y + 50); attackCollider[2].damage = 8;
		}
	}
	else // 플레이어 2일 때
	{
		if (player._Equal("Iori")) {
			damagedCollider2[0].setColliderPos(pos.x - 25, pos.y - 40, pos.x + 25, pos.y + 50);
			attackCollider2[0].setColliderPos(pos.x + 20, pos.y - 20, pos.x + 60, pos.y);  attackCollider2[0].damage = 5;
			attackCollider2[1].setColliderPos(pos.x + 10, pos.y - 50, pos.x + 60, pos.y + 10); attackCollider2[1].damage = 10;
			attackCollider2[2].setColliderPos(pos.x + 20, pos.y - 20, pos.x + 50, pos.y + 50); attackCollider2[2].damage = 8;
		}
	}
}

void BattleManager::Render(HDC hdc)
{
	for (int i = 0; i < 6; i++) {
		Rectangle(hdc, damagedCollider[i].collider.left, damagedCollider[i].collider.top, damagedCollider[i].collider.right, damagedCollider[i].collider.bottom);
		Rectangle(hdc, damagedCollider2[i].collider.left, damagedCollider2[i].collider.top, damagedCollider2[i].collider.right, damagedCollider2[i].collider.bottom);

	}
	for (int i = 0; i < 4; i++) {
		if(attackCollider[i].isAttack)
			Rectangle(hdc, attackCollider[i].collider.left, attackCollider[i].collider.top, attackCollider[i].collider.right, attackCollider[i].collider.bottom);
		if (attackCollider2[i].isAttack)
			Rectangle(hdc, attackCollider2[i].collider.left, attackCollider2[i].collider.top, attackCollider2[i].collider.right, attackCollider2[i].collider.bottom);
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
			for (int i = 0; i < 3; i++)
			{
				if (IntersectRect(&a, &damagedCollider[j].collider, &attackCollider2[i].collider) && attackCollider2[i].isAttack && !isPlayer1Damaged) { // 해당콜라이더가 공격 상태인 경우
					player1Hp -= attackCollider2[i].damage;
					isPlayer1Damaged = true;
					cout << "player1Hp : " << player1Hp << endl;
					//UIManager::GetSingleton()->ReduceHP(true, 10);
					return true;
				}
			}
		}
	}
	else
	{
		for (int j = 0; j < 1; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (IntersectRect(&a, &damagedCollider2[j].collider, &attackCollider[i].collider) && attackCollider[i].isAttack && !isPlayer2Damaged) {
					player2Hp -= attackCollider[i].damage;
					isPlayer2Damaged = true;
					cout << "player2Hp : " << player2Hp << endl;
					return true;
				}
			}
		}
	}


	return false;
}


