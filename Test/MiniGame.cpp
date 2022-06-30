#include "stdafx.h"
#include "MiniGame.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "TileMgr.h"
#include "BlockMgr.h"
#include "UIMgr.h"
#include "Portal.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "RockPaperScissor.h"


CMiniGame::CMiniGame() : m_bCount(false), m_bWin(false), m_dwTime(GetTickCount()), 
m_bGameStart(false), m_bTextOut(false), m_bReady(true), m_bStart(false), MyTurn(nullptr), 
PCTurn(nullptr), m_bResult(false), m_bScoreCount(false)
{
	//ZeroMemory(&m_ShoesVec, sizeof(m_ShoesVec));
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
}


CMiniGame::~CMiniGame()
{
	Release();
}

void CMiniGame::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/RockPaperScissor.bmp", L"RockPaperScissor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/TextBar_RockPaperScissor.bmp", L"TextBar_RockPaperScissor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Ready.bmp", L"Text_Ready");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Start.bmp", L"Text_Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Clear.bmp", L"Text_Clear");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/TextBar_Win.bmp", L"TextBar_Win");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/TextBar_Lose.bmp", L"TextBar_Lose");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/TextBar_Draw.bmp", L"TextBar_Draw");


}

int CMiniGame::Update(void)
{
	
		
	if (m_bWin && m_dwTime + 2000 < GetTickCount())
	{
		CSceneMgr::Get_Instance()->Set_PlayWith(true);
		CSceneMgr::Get_Instance()->Scene_Change(SC_MINIROOM2);
		m_bWin = false;
		return 0;
	}

	if (m_dwTime + 1500 < GetTickCount() && !m_bCount)
	{
		m_bReady = false;
		m_bStart = true;
		m_bCount = true;
		m_dwTime = GetTickCount();
	}

	if (m_bStart && m_dwTime + 1000 < GetTickCount())
	{
		m_bGameStart = true;
		m_bStart = false;
		m_bTextOut = true;
	}

	if (m_bGameStart && !m_bReady && !m_bStart && !m_bWin)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('1'))
		{
			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"cursor.wav", PUZZLE_EFFECT, g_fSound);
			MyTurn = CAbstractFactory<CRockPaperScissor>::Create(400, 400);
			static_cast<CRockPaperScissor*>(MyTurn)->Set_MyOption(0);

		}
		else if (CKeyMgr::Get_Instance()->Key_Down('2'))
		{
			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"cursor.wav", PUZZLE_EFFECT, g_fSound);
			MyTurn = CAbstractFactory<CRockPaperScissor>::Create(400, 400);
			static_cast<CRockPaperScissor*>(MyTurn)->Set_MyOption(1);

		}
		else if (CKeyMgr::Get_Instance()->Key_Down('3'))
		{
			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"cursor.wav", PUZZLE_EFFECT, g_fSound);
			MyTurn = CAbstractFactory<CRockPaperScissor>::Create(400, 400);
			static_cast<CRockPaperScissor*>(MyTurn)->Set_MyOption(2);

		}
		else
		{
			return 0;
		}

		PCTurn = CAbstractFactory<CRockPaperScissor>::Create(400, 200);
		static_cast<CRockPaperScissor*>(PCTurn)->Set_PCver(true);

		m_bGameStart = false;
		m_bResult = true;
		m_dwLoadingTime = GetTickCount();
		m_bScoreCount = false;
	}

	
	if (m_bResult && m_dwLoadingTime + 2000 < GetTickCount())
	{
		m_eGameResult = END;
		Safe_Delete(MyTurn);
		Safe_Delete(PCTurn);
		m_bResult = false;
		m_bGameStart = true;
		m_dwLoadingTime = GetTickCount();
	}


	if (MyTurn == nullptr || PCTurn == nullptr)
		return 0;

	MyTurn->Update();
	PCTurn->Update();
}

void CMiniGame::Late_Update(void)
{
	if (m_bWin)
		return;

	if (MyTurn == nullptr || PCTurn == nullptr)
		return;

	MyTurn->Late_Update();
	PCTurn->Late_Update();

	if (!m_bScoreCount)
	{

		switch (static_cast<CRockPaperScissor*>(PCTurn)->Get_MyOption())
		{
		case 0: //주먹
			if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 0)
				m_eGameResult = DRAW;
			else if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 1)
				m_eGameResult = WIN;
			else if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 2)
			{
				m_iScore++;
				m_eGameResult = LOSE;
			}
				
			
			break;
		case 1:	//보자기
			if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 1)
				m_eGameResult = DRAW;
			else if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 2)
				m_eGameResult = WIN;
			else if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 0)
			{
				m_eGameResult = LOSE;
				m_iScore++;
			}
				
			break;
		case 2: //가위
			if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 2)
				m_eGameResult = DRAW;
			else if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 0)
				m_eGameResult = WIN;
			else if (static_cast<CRockPaperScissor*>(MyTurn)->Get_MyOption() == 1)
			{
				m_eGameResult = LOSE;
				m_iScore++;
			}
				
			break;
		default:
			break;
		}
		m_bScoreCount = true;
	}


	switch (m_eGameResult)
	{
	case CMiniGame::WIN:
		FrameKey = L"TextBar_Win";
		break;
	case CMiniGame::LOSE:
		FrameKey = L"TextBar_Lose";	
		break;
	case CMiniGame::DRAW:
		FrameKey = L"TextBar_Draw";
		break;
	default:
		break;
	}

	if (m_iScore >= 3)
	{
		CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSuccess.wav", PUZZLE_EFFECT, g_fSound);
		m_bWin = true;
		m_dwTime = GetTickCount();
		m_eGameResult = END;
	}

}

void CMiniGame::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniRoom2");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, WINCX, 613, hGroundDC, 0, 0, SRCCOPY);

	if (m_bWin)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"Text_Clear");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			100,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}
	else if (m_bReady)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"Text_Ready");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			100,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}
	else if (m_bStart)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"Text_Start");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			100,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}

	if (m_bTextOut)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBar_RockPaperScissor");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			500,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}

	if (MyTurn == nullptr || PCTurn == nullptr)
		return;
	

	MyTurn->Render(hDC);
	PCTurn->Render(hDC);

	if (!m_bGameStart)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(FrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			100,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}
}

void CMiniGame::Release(void)
{
}
