#include "Config.h"
#include "Collider.h"
#include "Singleton.h"
#include <string>

class BattleManager : public Singleton<BattleManager>
{
public:
	Collider attackCollider[5];
	Collider damagedCollider[6];

	Collider attackCollider2[5];
	Collider damagedCollider2[6];

	POINTFLOAT playerPos1;
	POINTFLOAT playerPos2;

	int player1Hp = 100;
	int player2Hp = 100;

	int player1MoveCheck = 0;
	int player2MoveCheck = 0;
	int backGroundMove = 0;

	bool isPlayer1Damaged = false;
	bool isPlayer2Damaged = false;

	void Init(string player, bool isPlayer1, POINTFLOAT pos);
	void Render(HDC hdc);
	bool CheckCollision(RECT* rect, bool isPlayer1);
	bool CheckDamaged(bool isPlayer1);
};
