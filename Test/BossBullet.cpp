#include "stdafx.h"
#include "BossBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "BlockMgr.h"


CBossBullet::CBossBullet() : m_bCount(false)
{
}

CBossBullet::~CBossBullet()
{
	Release();
}

void CBossBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BossBullet.bmp", L"BossBullet");
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_eGroup = RENDER_EFFECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fSpeed = 0.03f;
}

int CBossBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	if (!m_bCount)
	{
		CSoundMgr::Get_Instance()->StopSound(MONSTER_BULLET);
		CSoundMgr::Get_Instance()->PlaySound(L"BossBullet.wav", MONSTER_BULLET, g_fSound - 0.4f);
		m_bCount = true;
	}

	Move();
	Update_Rect();
 	
	return OBJ_NOEVENT;
}

void CBossBullet::Late_Update(void)
{
	Move_Frame();

	if (m_bDead || this == nullptr)
		return;
	float TempX = 0;
	float TempY = 0;
	if (CCollisionMgr::Collsion_Block(CBlockMgr::Get_Instance()->Get_Blocks(), this))
		m_bDead = true;
	else if ( m_tInfo.fX > WINCX || m_tInfo.fX < 0 || m_tInfo.fY > WINCY || m_tInfo.fY < 0)
		m_bDead = true;
	if ( !(CObjMgr::Get_Instance()->Get_Shields().empty()) &&CCollisionMgr::Check_Rect(CObjMgr::Get_Instance()->Get_Shield(), this, &TempX, &TempY))
		m_bDead = true;
}

void CBossBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossBullet");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (50),								// 비트맵 출력 시작 좌표, X,Y
		0,
		50,				// 복사할 비트맵의 가로, 세로 길이
		50,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CBossBullet::Release(void)
{
}

void CBossBullet::Move(void)
{
	m_tInfo.fX += m_tMovePoint.x* m_fSpeed;
	m_tInfo.fY -= m_tMovePoint.y* m_fSpeed;
}

void CBossBullet::Motion_Change(void)
{
}
