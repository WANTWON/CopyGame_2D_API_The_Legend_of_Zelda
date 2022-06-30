#include "stdafx.h"
#include "MiniWood.h"
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
#include "Npc.h"
#include "TreasureChest.h"
#include "BlockMgr.h"
#include "Seed.h"
#include "MenuObjMgr.h"


CMiniWood::CMiniWood() : m_bCount(false), m_bAllSeedGrow(false), m_bChestCount(false), m_bTextOut(false), m_dwTime(GetTickCount())
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
}


CMiniWood::~CMiniWood()
{
	Release();
}

void CMiniWood::Initialize(void)
{
	CTileMgr::Get_Instance()->Load_Tile(SC_MINIWOOD);
	CBlockMgr::Get_Instance()->Load_Block(SC_MINIWOOD);

	CObj* pObj9 = CAbstractFactory<CNpc>::Create(519, 470);
	static_cast<CNpc*>(pObj9)->Set_NPCType(MINIWOOD_NPC);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, pObj9);

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
		CObjMgr::Get_Instance()->Load_Player();


		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 600);

	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			CObj* pObj = CAbstractFactory<CSeed>::Create(220 + (j*80), 120 + (i*80), OBJ_BLOCK);
			CBlockMgr::Get_Instance()->Add_Object(pObj);

			CObj* pObj2 = CAbstractFactory<CSeed>::Create(500 + (j * 80), 120 + (i * 80), OBJ_BLOCK);
			CBlockMgr::Get_Instance()->Add_Object(pObj2);
		}
	}


	
}

int CMiniWood::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CMiniWood::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Portal().empty())
		m_bCount = false;

	if (CBlockMgr::Get_Instance()->Get_iSolvedSeed() == 12)
	{
		m_bAllSeedGrow = true;
		
	}

	if (m_bAllSeedGrow && !m_bChestCount)
	{
		CMenuObjMgr::Get_Instance()->Load_Quest();
		CMenuObjMgr::Get_Instance()->Set_QuestComplete(MINIQUEST_FLOWER);
		CMenuObjMgr::Get_Instance()->Update();
		CMenuObjMgr::Get_Instance()->Late_Update();
		CMenuObjMgr::Get_Instance()->Save_Quest();
		CSoundMgr::Get_Instance()->PlaySound(L"Opendoor.wav", PUZZLE_EFFECT, g_fSound);
		CObj* pObj = CAbstractFactory<CTreasureChest>::Create(400, 300, OBJ_BLOCK);
		static_cast<CTreasureChest*>(pObj)->Set_Chest_Item(ITEM_KEY);
		CSceneMgr::Get_Instance()->Set_SolvedQuestNumber();
		CBlockMgr::Get_Instance()->Add_Object(pObj);
		m_bChestCount = true;
		m_bTextOut = true;
		m_dwTime = GetTickCount();
	}

	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(400, 800);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_MINIWORLD);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		m_bCount = true;
	}


	if (m_bTextOut && m_dwTime + 3000 < GetTickCount())
	{
		m_bTextOut = false;
		m_dwTime = GetTickCount();
	}

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
}

void CMiniWood::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniWood");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, WINCX, 825, hGroundDC, 0, 0, SRCCOPY);

	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	if (m_bTextOut)
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

	//CTileMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CMiniWood::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();
}
