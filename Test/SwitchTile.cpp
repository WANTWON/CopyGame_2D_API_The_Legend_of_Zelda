#include "stdafx.h"
#include "SwitchTile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"

CSwitchTile::CSwitchTile() : m_bCount(false)
{
}


CSwitchTile::~CSwitchTile()
{
	Release();
}

void CSwitchTile::Initialize(void)
{
	m_eTiletype = TILE_SWITCH;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iOption = 0;
	m_iDrawID = 0;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/SwitchTile.bmp", L"SwitchTile");
}

int CSwitchTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSwitchTile::Late_Update(void)
{
	if (m_bEditorMode)
		return;

	float Width = 0;
	float Height = 0;

	if (CCollisionMgr::Check_Rect(CObjMgr::Get_Instance()->Get_Player(), this, &Width, &Height) && !m_bCount)
	{
		CSoundMgr::Get_Instance()->StopSound(TILE_EFFECT);
		m_iOption = 1;
		CTileMgr::Get_Instance()->Set_SolvedTile();
		CSoundMgr::Get_Instance()->PlaySound(L"SwitchTile2.wav", TILE_EFFECT, g_fSound);
		m_bCount = true;
	}
		
	//else
		//m_iOption = 0;

	if(m_iOption == 1)
		m_iDrawID = 1;
	else
		m_iDrawID = 0;
}

void CSwitchTile::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(L"SwitchTile");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hTileDC,							// 비트맵을 가지고 있는 DC
		16 * m_iDrawID,								// 비트맵 출력 시작 좌표, X,Y
		0,
		16,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(0, 255, 0));			// 제거하고자 하는 색상
}

void CSwitchTile::Release(void)
{
}
