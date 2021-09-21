#pragma once
#include "Singleton.h"
#include "Config.h"
#include <string>
class Image;
class SceneManager : public Singleton<SceneManager>
{
private:
protected:
	enum class IsSceneState {
		MainTitle, CharacterSelect, Battle
	};
	IsSceneState isSceneState;


public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

};

