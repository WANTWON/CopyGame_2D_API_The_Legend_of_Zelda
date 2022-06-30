#include "stdafx.h"
#include "ShoeStore.h"
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
#include "MenuObjMgr.h"

CShoeStore::CShoeStore() : m_bCount(false), m_bShoesMakeCount(false)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
}


CShoeStore::~CShoeStore()
{
	Release();
}

void CShoeStore::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Shoe.bmp", L"Shoe");


	CTileMgr::Get_Instance()->Load_Tile(SC_STAGE_SHOESTORE);
	CBlockMgr::Get_Instance()->Load_Block(SC_STAGE_SHOESTORE);
	CObjMgr::Get_Instance()->Load_Monster(SC_STAGE_SHOESTORE);

	CObj* pObj9 = CAbstractFactory<CNpc>::Create(350,260);
	static_cast<CNpc*>(pObj9)->Set_NPCType(SHOE_NPC);
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
		if (CSceneMgr::Get_Instance()->Get_bShoseMake())
		{
			CObjMgr::Get_Instance()->Get_Player()->Set_Pos(345, 300);
		}	
		else
			CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 500);

	}
}

int CShoeStore::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CShoeStore::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Portal().empty())
		m_bCount = false;

	if (CSceneMgr::Get_Instance()->Get_bShoseMake() && !m_bShoesMakeCount)
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::EFFECT);
		m_bShoesMakeCount = true;
		CMenuObjMgr::Get_Instance()->Load_Quest();
		CMenuObjMgr::Get_Instance()->Set_QuestComplete(STORE_QUEST);
		CMenuObjMgr::Get_Instance()->Update();
		CMenuObjMgr::Get_Instance()->Late_Update();
		CMenuObjMgr::Get_Instance()->Save_Quest();

		CMenuObjMgr::Get_Instance()->Load_Weapon();
		CMenuObjMgr::Get_Instance()->Add_Weapon(HORSE);
		CMenuObjMgr::Get_Instance()->Update();
		CMenuObjMgr::Get_Instance()->Late_Update();
		CMenuObjMgr::Get_Instance()->Save_Weapon();
		m_dwTime = GetTickCount();
	}

	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(400, 600);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_STAGE_STORE);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		m_bCount = true;
	}

	if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() == CPlayer::EFFECT && m_dwTime + 2000 < GetTickCount())
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::IDLE);
		CSceneMgr::Get_Instance()->Set_ShoesMake(false);
	}
		

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
}

void CShoeStore::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"ShoeStore");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, WINCX, 600, hGroundDC, 0, 0, SRCCOPY);

	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	//CTileMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);

	if (CSceneMgr::Get_Instance()->Get_bShoseMake())
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shoe");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			330,	// 2,3 인자 :  복사받을 위치 X, Y
			250,
			30,				// 4,5 인자 : 복사받을 가로, 세로 길이
			20,
			hItemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			11,				// 복사할 비트맵의 가로, 세로 길이
			8,
			RGB(128, 128, 128));			// 제거하고자 하는 색상

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
}

void CShoeStore::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();
}
