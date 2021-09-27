#include "SceneManager.h"
#include "Image.h"

void SceneManager::Init()
{
	isSceneState = IsSceneState::MainTitle;
	playerChar1 = PlayerChar::Empty;
	playerChar2 = PlayerChar::Empty;
	selectCheck1 = selectCheck2 = false;
}

void SceneManager::Update()
{

}

void SceneManager::Render(HDC hdc)
{

}

void SceneManager::Release()
{

}


void SceneManager::SetIsSceneState(string isSceneName)
{
	isSceneState = IsSceneState::Error;
	if (isSceneName == "MainTitle")isSceneState = IsSceneState::MainTitle;
	if (isSceneName == "Loading")isSceneState = IsSceneState::Loading;
	if (isSceneName == "CharacterSelect")isSceneState = IsSceneState::CharacterSelect;
	if (isSceneName == "Battle")isSceneState = IsSceneState::Battle;
}

string SceneManager::GetIsSceneState()
{
	if (isSceneState == IsSceneState::MainTitle) return "MainTitle";
	if (isSceneState == IsSceneState::Loading) return "Loading";
	if (isSceneState == IsSceneState::CharacterSelect) return "CharacterSelect";
	if (isSceneState == IsSceneState::Battle) return "Battle";
	return "Error";
}

void SceneManager::SetPlayerChar(string charName, bool player)
{
	if (player)
	{
		if (charName == "Kyo")playerChar1 = PlayerChar::Kyo;
		if (charName == "May")playerChar1 = PlayerChar::May;
		if (charName == "Kim")playerChar1 = PlayerChar::Kim;
		if (charName == "Iori")playerChar1 = PlayerChar::Iori;
		if (charName == "Empty")playerChar1 = PlayerChar::Empty;
	}
	else
	{
		if (charName == "Kyo")playerChar2 = PlayerChar::Kyo;
		if (charName == "May")playerChar2 = PlayerChar::May;
		if (charName == "Kim")playerChar2 = PlayerChar::Kim;
		if (charName == "Iori")playerChar2 = PlayerChar::Iori;
		if (charName == "Empty")playerChar2 = PlayerChar::Empty;
	}
	if (isSceneState == IsSceneState::MainTitle)
	{
		if ((playerChar1 != PlayerChar::Empty) && (playerChar2 != PlayerChar::Empty))
		{
			isSceneState = IsSceneState::Loading;
		}
	}
}

string SceneManager::GetPlayerChar(bool check)
{
	if (check) {
		if (playerChar1 == PlayerChar::Kyo) return "Kyo";
		if (playerChar1 == PlayerChar::May) return "May";
		if (playerChar1 == PlayerChar::Iori) return "Iori";
		if (playerChar1 == PlayerChar::Kim) return "Kim";
		if (playerChar1 == PlayerChar::Empty) return "Empty";
	}
	else 
	{
		if (playerChar2 == PlayerChar::Kyo) return "Kyo";
		if (playerChar2 == PlayerChar::May) return "May";
		if (playerChar2 == PlayerChar::Iori) return "Iori";
		if (playerChar2 == PlayerChar::Kim) return "Kim";
		if (playerChar2 == PlayerChar::Empty) return "Empty";
	}
	return "Error";
}


