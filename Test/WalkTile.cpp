#include "stdafx.h"
#include "WalkTile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CWalkTile::CWalkTile()
{
}


CWalkTile::~CWalkTile()
{
	Release();
}

void CWalkTile::Initialize(void)
{
	m_eTiletype = TILE_WALK;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_eGroup = RENDER_GAMEOBJECT;

	m_iOption = 0;
	m_iDrawID = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/WalkTile.bmp", L"WalkTile");
}

int CWalkTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CWalkTile::Late_Update(void)
{
}

void CWalkTile::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(L"WalkTile");

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
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CWalkTile::Release(void)
{
}
