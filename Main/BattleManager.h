#include "Config.h"
#include "Collider.h"
#include "Singleton.h"
#include <string>

class Image;
class BattleManager : public Singleton<BattleManager>
{
public:
	enum class State { Playing, Die, End };
	Collider attackCollider[5];
	Collider damagedCollider[6];

	Collider attackCollider2[5];
	Collider damagedCollider2[6];

	POINTFLOAT playerPos1;
	POINTFLOAT playerPos2;

	int player1Hp = 10;
	int player2Hp = 10;

	int player1MoveCheck = 0;
	int player2MoveCheck = 0;
	int backGroundMove = 0;
  
  Image* ko[21];
	Image* win[25];
  
  State gameState;

	int elpasedCount = 0;
	int maxElpasedCount = 5;
	int frame = 0;
	int maxFrame = 21;


	bool isPlayer1Damaged = false;
	bool isPlayer2Damaged = false;

	void Init(string player, bool isPlayer1, POINTFLOAT pos);
	void Init();
	void Render(HDC hdc);
	bool CheckCollision(RECT* rect, bool isPlayer1);
	bool CheckDamaged(bool isPlayer1);
	void SetColliderPos(string player, bool isPlayer1, POINTFLOAT pos);
	void KORender(HDC hdc);
	inline void SetDie() { gameState = State::Die; };
	string GetState();

};
