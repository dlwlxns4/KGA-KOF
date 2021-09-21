#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Iori.h"
#include "Kim.h"
#include "BackGround.h"
#include "CharacterSelect.h"
void MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, FPS, NULL);

	mousePosX = 0;
	mousePosY = 0;
	clickedMousePosY = 0; 

	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	// 배경
	backGround = new BackGround;
	backGround->Init();
	characterSelect = new CharacterSelect;
	characterSelect->Init();
	
	// 플레이어
	iori = new Iori;
	iori->Init();
	kim = new Kim;
	kim->Init();
}

void MainGame::Update()
{
	//iori->Update();
	//kim->Update();
	characterSelect->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();
	//backGround->Render(hBackBufferDC);
	//iori->Render(hBackBufferDC);
	//kim->Render(hBackBufferDC);

	characterSelect->Render(hBackBufferDC);

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
			//playerTank.Fire();
			break;
		case VK_UP:
			//playerTank.Move(MoveDir::Up);
			break;
		case VK_DOWN:
			//playerTank.Move(MoveDir::Down);
			break;
		case VK_LEFT:
			//playerTank.Move(MoveDir::Left);
			break;
		case VK_RIGHT:
			//playerTank.Move(MoveDir::Right);
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
