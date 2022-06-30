#include "stdafx.h"
#include "Dungeon.h"
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
#include "RockMonster.h"

CDungeon::CDungeon() : m_bCount(false)
{
}


CDungeon::~CDungeon()
{
}

void CDungeon::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopAll();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Dungeon/DunGeonObject.bmp", L"DunGeonObject");

	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
	CTileMgr::Get_Instance()->Load_Tile(SC_STAGE_DUNGEON);
	CBlockMgr::Get_Instance()->Load_Block(SC_STAGE_DUNGEON);
	CObjMgr::Get_Instance()->Load_Monster(SC_STAGE_DUNGEON);

	CObj* DoorObj = CAbstractFactory<CDoor>::Create(750, 2455);
	static_cast<CDoor*>(DoorObj)->Set_DoorType(CDoor::DOOR_1);
	CBlockMgr::Get_Instance()->Add_Object( DoorObj);

	CObj* DoorOb2j = CAbstractFactory<CDoor>::Create(750, 1480);
	static_cast<CDoor*>(DoorOb2j)->Set_DoorType(CDoor::DOOR_2);
	CBlockMgr::Get_Instance()->Add_Object(DoorOb2j);

	CObj* DoorObj3 = CAbstractFactory<CDoor>::Create(750, 890);
	static_cast<CDoor*>(DoorObj3)->Set_DoorType(CDoor::DOOR_3);
	CBlockMgr::Get_Instance()->Add_Object(DoorObj3);

	
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
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(650, 3450);
	}

	static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MinusKey();

}

int CDungeon::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"DunGeon.wav", SOUND_BGM, g_fSound - 0.3f);

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CDungeon::Late_Update(void)
{
	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(750, 130);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_STAGE_BOSS);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		CObj* pObj2 = CAbstractFactory<CPortal>::Create(750, 3575);
		static_cast<CPortal*>(pObj2)->Set_PortalType(SC_STAGE_FIELD);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj2);

		CObj* Monster = CAbstractFactory<CRockMonster>::Create(750, 1110);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, Monster);


		m_bCount = true;
	}

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
}

void CDungeon::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Dungeon");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, iCullCX, iCullCY, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	

	HDC hObjectDC = CBmpMgr::Get_Instance()->Find_Image(L"DunGeonObject");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
		iScrollY,
		1500,				// 4,5 인자 : 복사받을 가로, 세로 길이
		3611,
		hObjectDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		1500,				// 복사할 비트맵의 가로, 세로 길이
		3611,
		RGB(128, 128, 128));			// 제거하고자 하는 색상

	CUIMgr::Get_Instance()->Render(hDC);
}


void CDungeon::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	//CUIMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();
	
}
