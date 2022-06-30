#include "stdafx.h"
#include "ShoeMiniGame.h"
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
#include "StoreWeapon.h"
#include "Shoe.h"

CShoeMiniGame::CShoeMiniGame() : m_bCount(false), m_bWin(false), m_dwTime(GetTickCount()), m_bShoesEmpty(false), m_bNext(false), m_bReady(true), m_bStart(false)
{
	//ZeroMemory(&m_ShoesVec, sizeof(m_ShoesVec));
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
}


CShoeMiniGame::~CShoeMiniGame()
{
	Release();
}

void CShoeMiniGame::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/EditRect.bmp", L"EditRect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Ready.bmp", L"Text_Ready");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Start.bmp", L"Text_Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Clear.bmp", L"Text_Clear");
	

	//CObjMgr::Get_Instance()->Load_Player();
	//CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 400);
}

int CShoeMiniGame::Update(void)
{
	if (m_bWin && m_dwTime + 2000 < GetTickCount())
	{
		CSceneMgr::Get_Instance()->Set_ShoesMake(true);
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_SHOESTORE);
		m_bWin = false;
		return 0 ;
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
		m_bShoesEmpty = true;
		m_bStart = false;
	}


	if (m_bShoesEmpty && !m_bReady && !m_bStart && !m_bWin)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int i = 0; i < 5; ++i)
			{
				m_ShoesList.push_back(CAbstractFactory<CShoe>::Create(130 * (i + 1), 280 + (j*120)));
			}
		}
		m_bShoesEmpty = false;
	}

	//CObjMgr::Get_Instance()->Update();

	for (auto& iter : m_ShoesList)
	{
		iter->Update();
	}
	return 0;
}

void CShoeMiniGame::Late_Update(void)
{

	if (m_bWin)
		return;

	if (m_ShoesList.empty())
	{
		m_bShoesEmpty = true;
		return;
	}
		

	

	//CObjMgr::Get_Instance()->Late_Update();

	for (VecNum; VecNum < m_ShoesList.size();)
	{
		static_cast<CShoe*>(m_ShoesList[VecNum])->Set_MyTurn(true);
		(m_ShoesList[VecNum])->Late_Update();
		if (static_cast<CShoe*>(m_ShoesList[VecNum])->Get_Myturn() == false)
		{
			++m_iScore;
			++VecNum;
			if (VecNum == m_ShoesList.size())
				VecNum = m_ShoesList.size() - 1;
		}	
		else
			break;
		
	}
	
	if (m_iScore == 10)
	{
		for (auto& iter : m_ShoesList)
		{
			Safe_Delete(iter);
		}
		m_ShoesList.clear();
		VecNum = 0;
		m_iScore = 0;
		m_iFinish++;
	}

	if (m_iFinish == 3)
	{
		CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSuccess.wav", PUZZLE_EFFECT, g_fSound);
		m_bWin = true;
		m_dwTime = GetTickCount();
	}
		
}

void CShoeMiniGame::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"ShoeMiniGame");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, WINCX, 600, hGroundDC, 0, 0, SRCCOPY);


	HDC hRectDC = CBmpMgr::Get_Instance()->Find_Image(L"EditRect");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		50,	// 2,3 인자 :  복사받을 위치 X, Y
		200,
		700,				// 4,5 인자 : 복사받을 가로, 세로 길이
		300,
		hRectDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		228,				// 복사할 비트맵의 가로, 세로 길이
		124,
		RGB(128, 128, 128));			// 제거하고자 하는 색상


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
	else
	{
		for (auto& iter : m_ShoesList)
		{
			iter->Render(hDC);
		}
	}


	
	

	


	//CBlockMgr::Get_Instance()->Render(hDC);
	//CObjMgr::Get_Instance()->Render(hDC);

	//CTileMgr::Get_Instance()->Render(hDC);
	//CUIMgr::Get_Instance()->Render(hDC);
}

void CShoeMiniGame::Release(void)
{
	//CTileMgr::Get_Instance()->Destroy_Instance();
	//CBlockMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	//CObjMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Save_Player();

	for (auto& iter : m_ShoesList)
	{
		Safe_Delete(iter);
	}
	m_ShoesList.clear();
}
