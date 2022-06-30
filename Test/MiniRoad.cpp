#include "stdafx.h"
#include "MiniRoad.h"
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

CMiniRoad::CMiniRoad() :  m_bCount(false)
{
}


CMiniRoad::~CMiniRoad()
{
}

void CMiniRoad::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopAll();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Mini_UpGrass.bmp", L"Mini_UpGrass");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Mini_UnderGrass.bmp", L"Mini_UnderGrass");

	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
	CTileMgr::Get_Instance()->Load_Tile(SC_MINIROAD);
	CBlockMgr::Get_Instance()->Load_Block(SC_MINIROAD);
	CObjMgr::Get_Instance()->Load_Monster(SC_MINIROAD);

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
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 2100);
	}
}

int CMiniRoad::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CMiniRoad::Late_Update(void)
{
	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(400, 130);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_MINIWORLD);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		m_bCount = true;
	}

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();
}

void CMiniRoad::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniRoad");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, iCullCX, iCullCY, hGroundDC, 0, 0, SRCCOPY);

	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CTileMgr::Get_Instance()->Render(hDC);
	
	HDC hObjectDC = CBmpMgr::Get_Instance()->Find_Image(L"Mini_UnderGrass");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
		iScrollY*0.7f ,
		800,				// 4,5 인자 : 복사받을 가로, 세로 길이
		2200,
		hObjectDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		800,				// 복사할 비트맵의 가로, 세로 길이
		2200,
		RGB(128, 128, 128));			// 제거하고자 하는 색상

	HDC hObjectDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Mini_UpGrass");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
		iScrollY*0.8f,
		800,			// 4,5 인자 : 복사받을 가로, 세로 길이
		2200,
		hObjectDC2,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		800,				// 복사할 비트맵의 가로, 세로 길이
		2200,
		RGB(128, 128, 128));			// 제거하고자 하는 색상

	CUIMgr::Get_Instance()->Render(hDC);
}

void CMiniRoad::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	//CUIMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();
}
