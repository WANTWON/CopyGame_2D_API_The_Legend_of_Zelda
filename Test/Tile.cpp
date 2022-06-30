#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "WalkTile.h"
#include "AbstractFactory.h"

CTile::CTile() : m_bCount(false)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_eTiletype = TILE_EDIT;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iOption = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile2.bmp", L"Tile");
	m_pFrameKey = L"Tile";
}

int CTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
	if (m_iOption == 2 && !m_bCount && CTileMgr::Get_Instance()->Get_SolvedTiles() != 0)
	{
		CTileMgr::Get_Instance()->Add_Tiles(TILE_WALK, CAbstractFactory<CWalkTile>::Create(m_tInfo.fX, m_tInfo.fY));
		m_bCount = true;
	}
}

void CTile::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hTileDC,							// 비트맵을 가지고 있는 DC
		30 * m_iDrawID,								// 비트맵 출력 시작 좌표, X,Y
		0,
		30,				// 복사할 비트맵의 가로, 세로 길이
		30,
		RGB(0, 255, 0));			// 제거하고자 하는 색상
}

void CTile::Release(void)
{
}
