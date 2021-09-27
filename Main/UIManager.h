#include "Singleton.h"
#include "Config.h"

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


	void Init();
	void SetPlayerImage();
	void Render(HDC hdc);
	void Update();
	void Release();
};

