#include "MainTitle.h"
#include "Image.h"
#include "KeyManager.h"
#include "SceneManager.h"

void MainTitle::Init()
{
	for (int i = 0; i < 2; i++)
	{
		mainTitle[i] = new Image;
		char cha[100];
		string str = "Image/MainTitle/MainTitle";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		mainTitle[i]->Init(cha, 680 / 2.1, 492 / 2.0, 1, 1, false, RGB(255, 0, 255));
	}

	for (int i = 0; i < 41; i++)
	{
		loading[i] = new Image;
		char cha[100];
		string str = "Image/MainTitle/Loading";
		str += to_string(i + 1);
		str += ".bmp";
		strcpy_s(cha, str.c_str());
		loading[i]->Init(cha, 680 / 2.1, 492 / 2.0, 1, 1, false, RGB(255, 0, 255));
	}

	backGroundPos.x = WIN_SIZE_Y / 1.5;
	backGroundPos.y = WIN_SIZE_Y / 2;

	frame = 0;
	maxFrame = 2;
	elpasedCount = 0;
	maxElpasedCount = 20;

	isLoading = false;
}

void MainTitle::Update()
{
	elpasedCount++;
	if (elpasedCount >= maxElpasedCount)
	{
		elpasedCount = 0;
		frame++;
		if (frame == 41) 
		{
			SceneManager::GetSingleton()->SetIsSceneState("CharacterSelect");
			Init();
		}
		if (frame >= maxFrame) frame = 0;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('A') && !isLoading) {
		frame = 0;
		maxFrame = 41;
		elpasedCount = 0;
		maxElpasedCount = 2;
		SceneManager::GetSingleton()->SetIsSceneState("Loading");
		isLoading = true;
	}

}

void MainTitle::Render(HDC hdc)
{
	if (SceneManager::GetSingleton()->GetIsSceneState() == "MainTitle") {
		mainTitle[frame]->Render(hdc, backGroundPos.x, backGroundPos.y, 0, 0);
	}
	if (SceneManager::GetSingleton()->GetIsSceneState() == "Loading") {
		loading[frame]->Render(hdc, backGroundPos.x, backGroundPos.y + 1, 0, 0);
	}
	
}

void MainTitle::Release()
{
}
