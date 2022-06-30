#include "stdafx.h"
#include "MiniRoom.h"
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

CMiniRoom::CMiniRoom() : m_bCount(false)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
}


CMiniRoom::~CMiniRoom()
{
	Release();
}

void CMiniRoom::Initialize(void)
{
	CTileMgr::Get_Instance()->Load_Tile(SC_MINIROOM);
	CBlockMgr::Get_Instance()->Load_Block(SC_MINIROOM);

	CObj* pObj9 = CAbstractFactory<CNpc>::Create(440, 300);
	static_cast<CNpc*>(pObj9)->Set_NPCType(MINI_NPC);
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


		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 345);

	}

	CObj* pObj = CAbstractFactory<CTreasureChest>::Create(400, 300, OBJ_BLOCK);
	static_cast<CTreasureChest*>(pObj)->Set_Chest_Item(ITEM_STRANGEMAN);
	CBlockMgr::Get_Instance()->Add_Object(pObj);

}

int CMiniRoom::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CMiniRoom::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Portal().empty())
		m_bCount = false;

	


	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(396, 481);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_MINIWORLD);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		m_bCount = true;
	}

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
}

void CMiniRoom::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniRoom");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, WINCX, 613, hGroundDC, 0, 0, SRCCOPY);

	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	//CTileMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CMiniRoom::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();
}
