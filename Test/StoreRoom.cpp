#include "stdafx.h"
#include "StoreRoom.h"
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

CStoreRoom::CStoreRoom() : m_bCount(false)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
}


CStoreRoom::~CStoreRoom()
{
	Release();
}

void CStoreRoom::Initialize(void)
{
	CTileMgr::Get_Instance()->Load_Tile(SC_STAGE_STOREROOM);
	CBlockMgr::Get_Instance()->Load_Block(SC_STAGE_STOREROOM);
	CObjMgr::Get_Instance()->Load_Monster(SC_STAGE_STOREROOM);

	CObj* pObj2 = CAbstractFactory<CStoreWeapon>::Create(335, 150);
	static_cast<CStoreWeapon*>(pObj2)->Set_Item_type(CStoreWeapon::WEAPON, WAND);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj2);

	CObj* pObj3 = CAbstractFactory<CStoreWeapon>::Create(215, 150);
	static_cast<CStoreWeapon*>(pObj3)->Set_Item_type(CStoreWeapon::WEAPON, BOOMERANG);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj3);

	CObj* pObj4 = CAbstractFactory<CStoreWeapon>::Create(275, 150);
	static_cast<CStoreWeapon*>(pObj4)->Set_Item_type(CStoreWeapon::WEAPON, ARROW);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj4);

	CObj* pObj5 = CAbstractFactory<CStoreWeapon>::Create(155, 150);
	static_cast<CStoreWeapon*>(pObj5)->Set_Item_type(CStoreWeapon::WEAPON, SHIELD);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj5);

	CObj* pObj6 = CAbstractFactory<CStoreWeapon>::Create(155, 355);
	static_cast<CStoreWeapon*>(pObj6)->Set_Item_type(CStoreWeapon::HP);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj6);

	CObj* pObj7 = CAbstractFactory<CStoreWeapon>::Create(215, 355);
	static_cast<CStoreWeapon*>(pObj7)->Set_Item_type(CStoreWeapon::PORTION);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj7);

	CObj* pObj8 = CAbstractFactory<CStoreWeapon>::Create(275, 355);
	static_cast<CStoreWeapon*>(pObj8)->Set_Item_type(CStoreWeapon::WEAPON, LANTON);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj8);

	CObj* pObj9 = CAbstractFactory<CNpc>::Create(525, 410);
	static_cast<CNpc*>(pObj9)->Set_NPCType(STORE_NPC);
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
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 500);

	}


	//CUIMgr::Get_Instance()->Initialize();
}

int CStoreRoom::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CStoreRoom::Late_Update(void)
{
	

	if (CObjMgr::Get_Instance()->Get_Portal().empty())
		m_bCount = false;


	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(400, 600);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_STAGE_STORE);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		m_bCount = true;
	}

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();

}

void CStoreRoom::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"StoreRoom");

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

void CStoreRoom::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();
}
