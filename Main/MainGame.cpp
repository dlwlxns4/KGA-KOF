#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Iori.h"
#include "Kim.h"
#include "BackGround.h"
#include "CharacterSelect.h"
#include "MainTitle.h"
#include "Kyo.h"
#include "MayLee.h"
#include "BattleManager.h"
#include "UIManager.h"


void MainGame::Init()
{
	UIManager::GetSingleton()->Init2();
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, FPS, NULL);


	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	// 배경
	backGround = new BackGround;
	backGround->Init();
	mainTitle = new MainTitle;
	mainTitle->Init();
	characterSelect = new CharacterSelect;
	characterSelect->Init();
	
	// 플레이어1
	iori = new Iori;
	iori->Init(true);
	kim = new Kim;
	kim->Init(true);
	kyo = new Kyo;
	kyo->Init(true);
	may = new MayLee;
	may->Init(true);

	// 플레이어2
	iori2 = new Iori;
	iori2->Init(false);
	kim2 = new Kim;
	kim2->Init(false);
	kyo2 = new Kyo;
	kyo2->Init(false);
	may2 = new MayLee;
	may2->Init(false);
}

void MainGame::GameInit()
{
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();


	// 배경
	backGround = new BackGround;
	backGround->Init();

	// 플레이어1
	iori = new Iori;
	iori->Init(true);
	kim = new Kim;
	kim->Init(true);
	kyo = new Kyo;
	kyo->Init(true);
	may = new MayLee;
	may->Init(true);

	// 플레이어2
	iori2 = new Iori;
	iori2->Init(false);
	kim2 = new Kim;
	kim2->Init(false);
	kyo2 = new Kyo;
	kyo2->Init(false);
	may2 = new MayLee;
	may2->Init(false);
}

void MainGame::Update()
{

	if (SceneManager::GetSingleton()->GetIsSceneState() == "MainTitle") {
		mainTitle->Update();
		if (gameInit)
		{
			GameRelease();
			GameInit();
			gameInit = false;
			BattleManager::GetSingleton()->GameInit();
		}
	}else if (SceneManager::GetSingleton()->GetIsSceneState() == "Loading") {
		mainTitle->Update();
	}else if (SceneManager::GetSingleton()->GetIsSceneState() == "CharacterSelect") {
		characterSelect->Update();
	}else if (SceneManager::GetSingleton()->GetIsSceneState() == "Battle") {
		backGround->Update();
		UIManager::GetSingleton()->Update();
		if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kim") {
			kim->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(true), true, kim->GetPos());
		}
		if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Iori") {
			iori->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(true), true, iori->GetPos());
		}
		if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kyo") {
			kyo->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(true), true, kyo->GetPos());
		}
		if (SceneManager::GetSingleton()->GetPlayerChar(true) == "May") {
			may->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(true), true, may->GetPos());
		}

		//플레이어 2
		if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Kim") {
			kim2->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(false), false, kim2->GetPos());
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Iori") {
			iori2->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(false), false, iori2->GetPos());
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Kyo") {
			kyo2->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(false), false, kyo2->GetPos());
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "May") {
			may2->Update();
			BattleManager::GetSingleton()->SetColliderPos(SceneManager::GetSingleton()->GetPlayerChar(false), false, may2->GetPos());
		}
	}

	//if (!SceneManager::GetSingleton()->selectCheck1 ||
	//	!SceneManager::GetSingleton()->selectCheck2) {
	//	characterSelect->Update();
	//} else {
	//	if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kim") {
	//		kim->Update();
	//	}
	//	if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Iori") {
	//		iori->Update();
	//	}
	//}
	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();
	if (SceneManager::GetSingleton()->GetIsSceneState() == "MainTitle") {
		mainTitle->Render(hBackBufferDC);
	}
	else if (SceneManager::GetSingleton()->GetIsSceneState() == "Loading") {
		mainTitle->Render(hBackBufferDC);
	}
	else if (SceneManager::GetSingleton()->GetIsSceneState() == "CharacterSelect") {
		characterSelect->Render(hBackBufferDC);
	}
	else if (SceneManager::GetSingleton()->GetIsSceneState() == "Battle") {
		backGround->Render(hBackBufferDC);
		BattleManager::GetSingleton()->Render(hBackBufferDC);
		UIManager::GetSingleton()->Render(hBackBufferDC);

		if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kim") {
			kim->Render(hBackBufferDC);
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Iori") {
			iori->Render(hBackBufferDC);
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kyo") {
			kyo->Render(hBackBufferDC);
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "May") {
			may->Render(hBackBufferDC);
		}

		if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Kim") {
			kim2->Render(hBackBufferDC);
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Iori") {
			iori2->Render(hBackBufferDC);
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "Kyo") {
			kyo2->Render(hBackBufferDC);
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(false) == "May") {
			may2->Render(hBackBufferDC);
		}


		backGround->sceneTransformRender(hBackBufferDC);
		gameInit = BattleManager::GetSingleton()->SceneTransform(hBackBufferDC);
		if(gameInit) mainTitle->Render(hBackBufferDC);
	}

	backBuffer->Render(hdc);
}

void MainGame::GameRelease()
{
	SAFE_RELEASE(backGround);
	delete iori;
	delete kyo;
	delete may;
	delete kim;
	delete iori2;
	delete kyo2;
	delete may2;
	delete kim2;

}

void MainGame::Release()
{
	SAFE_RELEASE(backGround);
	SAFE_RELEASE(backBuffer);

	delete iori;
	delete kyo;
	delete may;
	delete kim;
	delete iori2;
	delete kyo2;
	delete may2;
	delete kim2;

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}

void MainGame::setEnemy()
{

}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
