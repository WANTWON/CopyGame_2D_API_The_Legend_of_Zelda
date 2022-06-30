#include "stdafx.h"
#include "EndingStage.h"
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

CEndingStage::CEndingStage() : m_bCount(false)
{
}


CEndingStage::~CEndingStage()
{
}

void CEndingStage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossStage/EndingObject.bmp", L"EndingObject");

	
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
	CTileMgr::Get_Instance()->Load_Tile(SC_STAGE_ENDING);
	CBlockMgr::Get_Instance()->Load_Block(SC_STAGE_ENDING);
	CObjMgr::Get_Instance()->Load_Monster(SC_STAGE_ENDING);
	
	

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
		//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(1620, 1080));
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 980);
	}
	//CUIMgr::Get_Instance()->Initialize();

}

int CEndingStage::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"EndingStage.wav", SOUND_BGM, g_fSound - 0.3f);

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CEndingStage::Late_Update(void)
{
	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();

	if ( !m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(400, 100);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_ENDING_LOGO);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);
		m_bCount = true;
	}

}

void CEndingStage::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"EndingStage");

	BitBlt(hDC, iScrollX, iScrollY, iCullCX, iCullCY, hGroundDC, 0, 0, SRCCOPY);

						
	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->JarRender(hDC);
	//CTileMgr::Get_Instance()->Render(hDC);

	HDC hObjectDC = CBmpMgr::Get_Instance()->Find_Image(L"EndingObject");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
		iScrollY,
		800,				// 4,5 인자 : 복사받을 가로, 세로 길이
		1040,
		hObjectDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		800,				// 복사할 비트맵의 가로, 세로 길이
		1040,
		RGB(244, 0, 244));			// 제거하고자 하는 색상

	CUIMgr::Get_Instance()->Render(hDC);
}

void CEndingStage::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Save_Player();
}
