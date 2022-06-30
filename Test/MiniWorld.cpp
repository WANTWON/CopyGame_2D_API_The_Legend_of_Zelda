#include "stdafx.h"
#include "MiniWorld.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "TileMgr.h"
#include "BlockMgr.h"
#include "UIMgr.h"
#include "Portal.h"
#include "Block.h"
#include "SceneMgr.h"
#include "Door.h"
#include "MenuObjMgr.h"

CMiniWorld::CMiniWorld() : m_bCount(false), m_textOut(false), m_dwTime(GetTickCount()), m_QuestdwTime(GetTickCount()), m_bQuest(false)
{
}


CMiniWorld::~CMiniWorld()
{
	Release();
}

void CMiniWorld::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopAll();

	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
	CTileMgr::Get_Instance()->Load_Tile(SC_MINIWORLD);
	CBlockMgr::Get_Instance()->Load_Block(SC_MINIWORLD);
	CObjMgr::Get_Instance()->Load_Monster(SC_MINIWORLD);

	if (CSceneMgr::Get_Instance()->Get_InvenOut())
	{
		CObjMgr::Get_Instance()->Load_Player();
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(CSceneMgr::Get_Instance()->Get_PlayerPos().fX, CSceneMgr::Get_Instance()->Get_PlayerPos().fY);
		CSceneMgr::Get_Instance()->Set_InvenOut(false);
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_WeaponType(CSceneMgr::Get_Instance()->Get_PlayerWeapon());
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Second_WeaponType(CSceneMgr::Get_Instance()->Get_PlayerSecondWeapon());

	}
	else if (CSceneMgr::Get_Instance()->Get_QuestOut())
	{
		CObjMgr::Get_Instance()->Load_Player();
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(CSceneMgr::Get_Instance()->Get_PlayerPos().fX, CSceneMgr::Get_Instance()->Get_PlayerPos().fY);
		CSceneMgr::Get_Instance()->Set_QuestOut(false);
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_WeaponType(CSceneMgr::Get_Instance()->Get_PlayerWeapon());
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Second_WeaponType(CSceneMgr::Get_Instance()->Get_PlayerSecondWeapon());

	}
	else
	{
		CSoundMgr::Get_Instance()->StopAll();
		CObjMgr::Get_Instance()->Load_Player();
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(775, 1338);
	}
}

int CMiniWorld::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"MiniWorld.wav", SOUND_BGM, g_fSound - 0.3f);

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CMiniWorld::Late_Update(void)
{
	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(887, 81);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_STAGE_DUNGEON);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		CObj* pObj2 = CAbstractFactory<CPortal>::Create(532, 622);
		static_cast<CPortal*>(pObj2)->Set_PortalType(SC_MINIROOM);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj2);

		CObj* pObj3 = CAbstractFactory<CPortal>::Create(1320, 900);
		static_cast<CPortal*>(pObj3)->Set_PortalType(SC_MINIWOOD);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj3);

		CObj* pObj4 = CAbstractFactory<CPortal>::Create(1297, 784);
		static_cast<CPortal*>(pObj4)->Set_PortalType(SC_MINIWOOD);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj4);

		CObj* pObj5 = CAbstractFactory<CPortal>::Create(110, 824);
		static_cast<CPortal*>(pObj5)->Set_PortalType(SC_MINIROOM2);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj5);

		CObj* pObj6 = CAbstractFactory<CPortal>::Create(725, 1020);
		static_cast<CPortal*>(pObj6)->Set_PortalType(SC_MINIROOM3);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj6);

		CObj* pObj7 = CAbstractFactory<CPortal>::Create(175, 146);
		static_cast<CPortal*>(pObj7)->Set_PortalType(SC_MINICHIEF);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj7);
		m_bCount = true;
	}

	if (CSceneMgr::Get_Instance()->Get_MiniWorld() == true)
	{
		if (!m_bQuest)
		{
			m_QuestdwTime = GetTickCount();
			m_bQuest = true;
			m_textOut = true;
		}
			
		if (m_QuestdwTime + 3000 < GetTickCount())
		{
			CMenuObjMgr::Get_Instance()->Load_Quest();
			CMenuObjMgr::Get_Instance()->Set_QuestComplete(FIELD_QUEST);
			CMenuObjMgr::Get_Instance()->Update();
			CMenuObjMgr::Get_Instance()->Late_Update();
			CMenuObjMgr::Get_Instance()->Save_Quest();
			CSceneMgr::Get_Instance()->Set_MiniWorld(false);
			m_textOut = false;
		}
	}

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
}

void CMiniWorld::Render(HDC hDC)
{

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniWorld");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, iCullCX, iCullCY, hGroundDC, 0, 0, SRCCOPY);

	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CTileMgr::Get_Instance()->Render(hDC);

	if (m_textOut)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"QuestClearText");

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

	CUIMgr::Get_Instance()->Render(hDC);
}

void CMiniWorld::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	//CUIMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();
}
