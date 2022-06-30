#include "stdafx.h"
#include "LaserBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Monster.h"


CLaserBullet::CLaserBullet() : m_dwTime(GetTickCount())
{
}


CLaserBullet::~CLaserBullet()
{
}

void CLaserBullet::Initialize(void)
{

	m_eBulletType = BULLET_LASER;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/LaserBullet.bmp", L"LaserBullet");
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 13.f;
	m_eGroup = RENDER_EFFECT;

	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	//m_fSpeed = 0.03f;
}

int CLaserBullet::Update(void)
{
	//CSoundMgr::Get_Instance()->PlaySound(L"LaserBullet", MONSTER_BULLET, g_fSound);
	CSoundMgr::Get_Instance()->PlaySound(L"Laser.wav", MONSTER_BULLET, g_fSound + 0.2f);
	if (m_bDead)
		return OBJ_DEAD;

	
	Update_Rect();
	Move();

	return OBJ_NOEVENT;
}

void CLaserBullet::Late_Update(void)
{

	if (m_bDead || m_pTarget == nullptr)
		return;

	
	if (m_tInfo.fX > WINCX || m_tInfo.fX < 0 || m_tInfo.fY > WINCY + 100 || m_tInfo.fY < 0 )
		m_bDead = true;

	if (static_cast<CMonster*>(m_pTarget)->Get_CurState() == CMonster::HIT)
		m_bDead = true;
}

void CLaserBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LaserBullet");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX) - 13,	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX) + 25 ,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (50),								// 비트맵 출력 시작 좌표, X,Y
		0,
		50,				// 복사할 비트맵의 가로, 세로 길이
		250,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CLaserBullet::Release(void)
{
}

void CLaserBullet::Move(void)
{

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tRect.top = m_pTarget->Get_Rect().bottom + 10;

	

	if (m_dwTime + 50 < GetTickCount())
	{
		m_tInfo.fCY += 30;
		m_tInfo.fY += 15;

		if (m_tRect.bottom >= WINCY)
		{
			m_tInfo.fCY -= 30;
			m_tInfo.fY -= 15;
		}
			

		m_dwTime = GetTickCount();
	}

	
	m_tInfo.fY = (m_tRect.top + m_tRect.bottom)*0.5f;
	
}


