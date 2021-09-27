#pragma once
#include "Config.h"
#include <string>
class Image;
class MainTitle
{
private:
	Image* mainTitle[2];
	Image* loading[41];
	POINTFLOAT backGroundPos;		// ¹è°æÁÂÇ¥

	int elpasedCount;
	int maxElpasedCount;
	int frame;
	int maxFrame;
	
	bool isLoading;

protected:
public:

	inline bool GetIsLoading() { return isLoading; }
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

