#include "Config.h"
#include "Collider.h"
#include "Singleton.h"
#include <string>

class Image;
class BattleManager : public Singleton<BattleManager>
{
public:
	enum class State { Playing, Die, End };

	Collider attackCollider[4];
	Collider damagedCollider[6];


	Collider attackCollider2[4];
	Collider damagedCollider2[6];

	int player1Hp = 10;
	int player2Hp = 10;

	bool isPlayer1Damaged = false;
	bool isPlayer2Damaged = false;

	Image* ko[21];
	Image* win[25];
	
	State gameState;

	int elpasedCount = 0;
	int maxElpasedCount = 2;
	int frame = 0;
	int maxFrame = 21;

	void Init();
	void Update();
	void SetColliderPos(string player, bool isPlayer1, POINTFLOAT pos);
	void Render(HDC hdc);
	bool CheckCollision(RECT* rect, bool isPlayer1);
	bool CheckDamaged(bool isPlayer1);
	void KORender(HDC hdc);
	inline void SetDie() { gameState = State::Die; };
};
