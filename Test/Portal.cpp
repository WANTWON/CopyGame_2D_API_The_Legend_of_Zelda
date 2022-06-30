#include "stdafx.h"
#include "Portal.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "Player.h"

CPortal::CPortal() : m_eSceneType(SC_END) , m_bEnding(false), m_bOpenRock(false), m_bCount(false)
{
}


CPortal::~CPortal()
{
}

void CPortal::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending/Zelda/Zelda.bmp", L"Zelda");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending/Portal.bmp", L"Portal");
	m_pFrameKey = L"Portal";

	m_tInfo = { 400.f, 300.f, 40.f, 40.f };

	m_tFrame.iFrameStart = 4;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 1;
	m_eGroup = RENDER_GAMEOBJECT;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPortal::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPortal::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Portal().empty() || this == nullptr)
		return;


	if (m_bEnding)
		EndingMotion();
	else if (m_bOpenRock)
		RockMotion();

	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this) && !m_bCount)
	{
		switch (m_eSceneType)
		{
		case SC_STAGE_FIELD:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_FIELD);
			break;
		case SC_STAGE_BOSS:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_BOSS);
			break;
		case SC_STAGE_DUNGEON:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_DUNGEON);
			break;
		case SC_STAGE_ENDING:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_ENDING);
			break;
		case SC_STAGE_STORE:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_STORE);
			break;
		case SC_STAGE_STOREROOM:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_STOREROOM);
			break;
		case SC_STAGE_SHOESTORE:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_SHOESTORE);
			break;
		case SC_ENDING_LOGO:
			m_bOpenRock = true;
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 0;
			break;
		case SC_MINIROAD:
			if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() == CPlayer::MINIMODE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_MINIROAD);
			}
			break;
		case SC_MINIWORLD:
			CSceneMgr::Get_Instance()->Scene_Change(SC_MINIWORLD);
			break;
		case SC_MINIROOM:
			CSceneMgr::Get_Instance()->Scene_Change(SC_MINIROOM);
			break;

		case SC_MINIROOM2:
			CSceneMgr::Get_Instance()->Scene_Change(SC_MINIROOM2);
			break;

		case SC_MINIROOM3:
			CSceneMgr::Get_Instance()->Scene_Change(SC_MINIROOM3);
			break;

		case SC_MINIWOOD:
			CSceneMgr::Get_Instance()->Scene_Change(SC_MINIWOOD);
			break;

		case SC_MINICHIEF:
			CSceneMgr::Get_Instance()->Scene_Change(SC_MINICHIEF);
			break;
		default:
			break;
		}

		m_bCount = true;
	}
}

void CPortal::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eSceneType == SC_ENDING_LOGO)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Zelda");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 60,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 65,
			int(m_tInfo.fCX) + 120,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 115,
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (200),								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * 200,
			200,				// 복사할 비트맵의 가로, 세로 길이
			200,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	else if (m_eSceneType == SC_STAGE_ENDING)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 60,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 65,
			int(m_tInfo.fCX) + 120,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 115,
			hMemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			80,				// 복사할 비트맵의 가로, 세로 길이
			57,
			RGB(128, 128, 128));			// 제거하고자 하는 색상

		
	}
	else
	{
		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	}
	
}

void CPortal::Release(void)
{
}

void CPortal::EndingMotion(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_ENDING_LOGO);
			CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}

void CPortal::RockMotion(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		--m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
		{
			m_bEnding = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 2;
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}
