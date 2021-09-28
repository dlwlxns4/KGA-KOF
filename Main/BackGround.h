#pragma once
#include "Config.h"
#include <string>

class Image;
class BackGround
{
private:
protected:
	Image* bulGukSa[8];
	Image* desert[8];
	Image* garden[29];
	Image* harbor1[8];
	Image* harbor2[8];
	Image* hwaHongMun[8];
	Image* racing[8];
	Image* street[16];
	Image* underBridge[16];

	Image* ui;

	int player1Pos, player2Pos;
	int backGroundPos;
	int backGroundPrint;
	Image* sceneTransform[11];


	bool isSceneTransform=true;
	int transformFrame=0;
	int transformElpasedCount = 0;

	int elapsedCount;
	int frame;

public:
	enum class IsBackGround{ 
		BulGukSa, 
		Desert,
		Garden,
		Harbor1,
		Harbor2,
		HwaHongMun,
		Racing,
		Street,
		UnderBridge
	};
	IsBackGround isBackGround;


	void Init();
	void Update();
	void Render(HDC hdc);
	void sceneTransformRender(HDC hdc);
	void Release();
};

