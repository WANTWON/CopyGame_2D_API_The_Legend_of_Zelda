#include "stdafx.h"
#include "BooBullet.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "Player.h"

CBooBullet::CBooBullet()
{
}


CBooBullet::~CBooBullet()
{
	Release();
}

void CBooBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BooBullet.bmp", L"BooBullet");

	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_eGroup = RENDER_EFFECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fAnimSpeed = 7.f;
	m_fAnimTime = 0.f;
	m_fAnimAccel = 4.8f;
	m_fSpeed = 7.f;
}

int CBooBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBooBullet::Late_Update(void)
{
	RECT rc = {};

	BulletFrame();

	if (IntersectRect(&rc, &(CObjMgr::Get_Instance()->Get_Player()->Get_Rect()), &m_tRect))
	{
		m_bDead = true;
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Beboomerang();
	}
		
}

void CBooBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BooBullet");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX) - 25,	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY) - 25,
		int(m_tInfo.fCX) + 50,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY) + 50,
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (100),								// 비트맵 출력 시작 좌표, X,Y
		0,
		100,				// 복사할 비트맵의 가로, 세로 길이
		100,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CBooBullet::Release(void)
{
}

void CBooBullet::Move(void)
{
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fAnimSpeed * m_fAnimTime - (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
		m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;
		break;
	case DIR_UP:
		m_tInfo.fY -= m_fAnimSpeed * m_fAnimTime - (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;

		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fAnimSpeed * m_fAnimTime - (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
		m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;

		break;
	case DIR_DOWN:
		m_tInfo.fY += m_fAnimSpeed * m_fAnimTime - (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;

		break;
	}
	m_fAnimTime += 0.05f;

}



