#include "Config.h"
#include "Collider.h"
#include "Singleton.h"
#include <string>

class Image;
class BattleManager : public Singleton<BattleManager>
{
public:
	enum class State { Playing, Die, KO, WIN, END };
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
  
	Image* ko[21];
	Image* win[25];
	Image* sceneTransform[20];
  
	State gameState;

	int elapsedCount = 0;
	int maxElpasedCount = 3;
	int frame = 0;
	int maxFrame = 21;
	bool isUpdata = true;


	bool isPlayer1Damaged = false;
	bool isPlayer2Damaged = false;

	void Init(string player, bool isPlayer1, POINTFLOAT pos);
	void Init();
	void Render(HDC hdc);
	bool CheckCollision(RECT* rect, bool isPlayer1);
	bool CheckDamaged(bool isPlayer1);

	//0927 ?÷??̾?? ???? ????
	bool CheckMeet();
	
	void SetColliderPos(string player, bool isPlayer1, POINTFLOAT pos);
	void KORender(HDC hdc);
	void WinRender(HDC hdc);
	bool SceneTransform(HDC hdc);
	void InitCollider();
	inline void SetDie() { gameState = State::Die; };

	void GameInit();

};
