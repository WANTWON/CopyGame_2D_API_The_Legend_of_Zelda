#include "stdafx.h"
#include "OctopusBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "BlockMgr.h"


COctopusBullet::COctopusBullet()
{
}


COctopusBullet::~COctopusBullet()
{
}

void COctopusBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/MonsterBullet.bmp", L"MonsterBullet");
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_eGroup = RENDER_EFFECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fSpeed = 0.5f;
}

int COctopusBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void COctopusBullet::Late_Update(void)
{
	Move_Frame();

	if (m_bDead || this == nullptr)
		return;

	float TempX = 0;
	float TempY = 0;


	if ( CObjMgr::Get_Instance()->Get_Shields().empty() == false &&CCollisionMgr::Check_Rect(CObjMgr::Get_Instance()->Get_Shield(), this, &TempX, &TempY))
		m_bDead = true;

	if (CCollisionMgr::Collsion_Block(CBlockMgr::Get_Instance()->Get_Blocks(), this))
		m_bDead = true;
	if (CCollisionMgr::Collsion_Tile(CTileMgr::Get_Instance()->Get_EditTiles(), this))
		m_bDead = true;
	

	if (m_dwTime + 3000 < GetTickCount())
	{
		m_bDead = true;
		m_dwTime = GetTickCount();
	}
}

void COctopusBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonsterBullet");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (30),								// 비트맵 출력 시작 좌표, X,Y
		0,
		30,				// 복사할 비트맵의 가로, 세로 길이
		30,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void COctopusBullet::Release(void)
{
}

void COctopusBullet::Move(void)
{
	m_tInfo.fX += m_tMovePoint.x* m_fSpeed;
	m_tInfo.fY -= m_tMovePoint.y* m_fSpeed;
}

void COctopusBullet::Motion_Change(void)
{
}
