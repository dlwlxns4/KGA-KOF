#include "Singleton.h"
#include "Config.h"
#include <string>
#pragma once
class Image;
class UIManager : public Singleton<UIManager>
{
public:
	Image* backGroundUI;
	Image* player1;
	Image* player2;
	Image* playerHP1;
	Image* playerHP2;
	Image* timeLoading[13];
	Image* time10[21];
	Image* time1[30];

	int timeLoadingNum;
	int timeNum10;
	int timeNum1;
	bool timeOut;
	bool timeOutDead;
	int num = 0;
	bool time1Check = true;
	bool time10Check = true;

	void Init();
	void Init2();
	void SetPlayerImage();
	void Render(HDC hdc);
	void Update();
	void Release();
	void TimeInit();
};

