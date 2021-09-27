#pragma once
#include "Singleton.h"
#include "Config.h"
#include <string>
class Image;
class SceneManager : public Singleton<SceneManager>
{
private:
	enum class IsSceneState {
		MainTitle, Loading, CharacterSelect, Battle, Error
	};
	IsSceneState isSceneState;

	enum class PlayerChar {
		Empty, May, Kyo, Iori, Kim
	};
	PlayerChar playerChar1;
	PlayerChar playerChar2;
protected:

public:
	bool selectCheck1;
	bool selectCheck2;

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void SetPlayerChar(string charName, bool player);
	string GetPlayerChar(bool check);
	void SetIsSceneState(string isSceneName);
	string GetIsSceneState();
};

