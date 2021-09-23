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


void MainGame::Init()
{
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
	
	// 플레이어
	iori = new Iori;
	iori->Init(true);
	kim = new Kim;
	kim->Init();
	kyo = new Kyo;
	kyo->Init();
	may = new MayLee;
	may->Init();

	// 플레이어2
	iori2 = new Iori;
	iori2->Init(false);
	kim2 = new Kim;
	kim2->Init();
	kyo2 = new Kyo;
	kyo2->Init();
	may2 = new MayLee;
	may2->Init();
}

void MainGame::Update()
{

	if (SceneManager::GetSingleton()->GetIsSceneState() == "MainTitle") {
		mainTitle->Update();
	}else if (SceneManager::GetSingleton()->GetIsSceneState() == "Loading") {
		mainTitle->Update();
	}else if (SceneManager::GetSingleton()->GetIsSceneState() == "CharacterSelect") {
		characterSelect->Update();
	}else if (SceneManager::GetSingleton()->GetIsSceneState() == "Battle") {
		backGround->Update();
		if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kim") {
			kim->Update();
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Iori") {
			iori->Update();
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kyo") {
			kyo->Update();
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "May") {
			may->Update();
		}

		//플레이어 2
		if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kim") {
			kim2->Update();
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Iori") {
			iori2->Update();
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kyo") {
			kyo2->Update();
		}
		else if (SceneManager::GetSingleton()->GetPlayerChar(true) == "May") {
			may2->Update();
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
	}

	//if (!SceneManager::GetSingleton()->selectCheck1 ||
	//	!SceneManager::GetSingleton()->selectCheck2) {
	//	characterSelect->Render(hBackBufferDC);
	//}
	//else {
	//	backGround->Render(hBackBufferDC);
	//	if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Kim") {
	//		kim->Render(hBackBufferDC);

	//	}
	//	if (SceneManager::GetSingleton()->GetPlayerChar(true) == "Iori") {
	//		iori->Render(hBackBufferDC);

	//	}
	//}
	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(backGround);


	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
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
