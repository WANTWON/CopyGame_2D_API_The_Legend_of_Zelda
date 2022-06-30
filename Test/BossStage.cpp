#include "stdafx.h"
#include "BossStage.h"
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


CBossStage::CBossStage() : m_bCount(false)
{
}


CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize(void)
{

	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL); 
	CTileMgr::Get_Instance()->Load_Tile(SC_STAGE_BOSS);
	CBlockMgr::Get_Instance()->Load_Block(SC_STAGE_BOSS);

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
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400, 500);
	}
	CObjMgr::Get_Instance()->Load_Monster(SC_STAGE_BOSS);
}

int CBossStage::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	return 0;
}

void CBossStage::Late_Update(void)
{
	RECT rc{};
	CSoundMgr::Get_Instance()->PlaySound(L"Boss.wav", SOUND_BGM, g_fSound - 0.3f);

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();

	CUIMgr::Get_Instance()->Late_Update();

	if (CObjMgr::Get_Instance()->Get_Player()->Get_StageClear() && !m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(400, 200);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_STAGE_ENDING);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);
		m_bCount = true;
	}

}

void CBossStage::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BossBack");

	BitBlt(hDC, iScrollX, iScrollY, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"BossStage");

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
		iScrollY +50,
		WINCX,				// 4,5 인자 : 복사받을 가로, 세로 길이
		WINCY,
		hGroundDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		352,				// 복사할 비트맵의 가로, 세로 길이
		255,
		RGB(128, 128, 128));			// 제거하고자 하는 색상

	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	//CTileMgr::Get_Instance()->Render(hDC);


	CUIMgr::Get_Instance()->Render(hDC);
}

void CBossStage::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	//CUIMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Save_Player();


}
