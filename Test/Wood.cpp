#include "stdafx.h"
#include "Wood.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BlockMgr.h"
#include "Coin.h"
#include "AbstractFactory.h"
#include "Portion.h"

CWood::CWood()
{
}


CWood::~CWood()
{
	Release();
}

void CWood::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX*1.5f;
	m_tInfo.fCY = BLOCKCY*1.5f;

	m_eBlockType = BLOCK_WOOD;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 70;
	m_iOption = 5;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MIni/Wood.bmp", L"Wood");

	m_pFrameKey = L"Wood";
}

int CWood::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CWood::Late_Update(void)
{
	if (m_bEditorMode)
		return;
}

void CWood::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX) ,	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY) ,
		int(m_tInfo.fCX) ,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY) ,
		hTileDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		38,				// 복사할 비트맵의 가로, 세로 길이
		32,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CWood::Release(void)
{
}
