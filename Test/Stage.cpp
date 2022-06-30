#include "stdafx.h"
#include "Stage.h"
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
#include "SoundMgr.h"
#include "Npc.h"


CStage::CStage() : m_bCount(false)
{

}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CTileMgr::Get_Instance()->Set_EditMode(false);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PORTAL);
	CTileMgr::Get_Instance()->Load_Tile(SC_STAGE_FIELD);
	CBlockMgr::Get_Instance()->Load_Block(SC_STAGE_FIELD);
	CObjMgr::Get_Instance()->Load_Monster(SC_STAGE_FIELD);
	
	if (CSceneMgr::Get_Instance()->Get_First_Start())
	{
		CSoundMgr::Get_Instance()->StopAll();
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(1620, 1080));
		CSceneMgr::Get_Instance()->Set_First_Start(false);
	}
	else if (CSceneMgr::Get_Instance()->Get_InvenOut())
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
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1240, 300);
	}

	
	CObj* pObj9 = CAbstractFactory<CNpc>::Create(1519, 1090);
	static_cast<CNpc*>(pObj9)->Set_NPCType(FIELD_NPC);
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, pObj9);

	CUIMgr::Get_Instance()->Initialize();
}

int CStage::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Field.wav", SOUND_BGM, g_fSound-0.3f);

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
	return 0;
}

void CStage::Late_Update(void)
{


	if (CObjMgr::Get_Instance()->Get_Portal().empty())
		m_bCount = false;

	if (!m_bCount)
	{
		CObj* pObj = CAbstractFactory<CPortal>::Create(1250, 0);
		static_cast<CPortal*>(pObj)->Set_PortalType(SC_STAGE_STORE);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj);

		CObj* pObj2 = CAbstractFactory<CPortal>::Create(2450, 290);
		static_cast<CPortal*>(pObj2)->Set_PortalType(SC_STAGE_DUNGEON);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj2);

		CObj* pObj3 = CAbstractFactory<CPortal>::Create(178, 1111);
		static_cast<CPortal*>(pObj3)->Set_PortalType(SC_MINIROAD);
		CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, pObj3);
		m_bCount = true;
	}

	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	
	CUIMgr::Get_Instance()->Late_Update();

}

void CStage::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Field");
	
	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	BitBlt(hDC, iScrollX, iScrollY, iCullCX, iCullCY, hGroundDC, 0, 0, SRCCOPY);

	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->JarRender(hDC);
	//CTileMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);

}

void CStage::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	//CUIMgr::Get_Instance()->Destroy_Instance();
	//CObjMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
	CObjMgr::Get_Instance()->Save_Player();
	

}
