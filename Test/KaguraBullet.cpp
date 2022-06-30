#include "stdafx.h"
#include "KaguraBullet.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BmpMgr.h"

CKaguraBullet::CKaguraBullet() : dwTime(GetTickCount()), PosX(0), PosY(0), m_bCount(false), m_bMiniFire(false)
{
}


CKaguraBullet::~CKaguraBullet()
{
	Release();
}

void CKaguraBullet::Initialize(void)
{
	m_tInfo.fCX = 100.f;
	m_eGroup = RENDER_EFFECT;
	m_tInfo.fCY = 100.f;
	m_eBulletType = BULLET_KAGURA;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.dwFrameSpeed = 100;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/KaguraBullet.bmp", L"KaguraBullet");
}

int CKaguraBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bMiniFire)
	{
		if (!m_bCount)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Fire.wav", PLAYER_EFFECT, g_fSound - 0.3f);
			m_bCount = true;
		}
		m_tInfo.fX += PosX*0.1f;
		m_tInfo.fY -= PosY*0.1f;
		m_tInfo.fCX = 10.f;
		m_tInfo.fCY = 10.f;
	}
	else
	{
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
		m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;
	}
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlaySound(L"KAGURA.wav", BUllET_EFFECT, g_fSound + 0.5f);
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CKaguraBullet::Late_Update(void)
{
	if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() != CPlayer::KAGURA)
		m_bDead = true;

	if (m_bMiniFire)
	{
		Move_Frame();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bDead = true;
	}
	
}

void CKaguraBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (m_bMiniFire)
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(L"KaguraBullet");

		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 25,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 25,
			int(m_tInfo.fCX) + 50,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 50,
			hItemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart *(100),								// 비트맵 출력 시작 좌표, X,Y
			0,
			100,				// 복사할 비트맵의 가로, 세로 길이
			100,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	
	
	
}

void CKaguraBullet::Release(void)
{
}
