#include "Config.h"
#include "Collider.h"
#include "Singleton.h"
#include <string>

class BattleManager : public Singleton<BattleManager>
{
public:
	Collider attackCollider[4];
	Collider damagedCollider[6];


	Collider attackCollider2[4];
	Collider damagedCollider2[6];

	int player1Hp = 100;
	int player2Hp = 100;

	bool isPlayer1Damaged=false;
	bool isPlayer2Damaged = false;

	void Init(string player, bool isPlayer1, POINTFLOAT pos);
	void Init2(string player1, POINTFLOAT pos);
	void Render(HDC hdc);
	bool CheckCollision(RECT* rect, bool isPlayer1);
	bool CheckDamaged(bool isPlayer1);
};
