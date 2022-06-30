#include "stdafx.h"
#include "SwordBullet.h"
#include "ScrollMgr.h"


CSwordBullet::CSwordBullet()
	: dwTime(GetTickCount())
{
}


CSwordBullet::~CSwordBullet()
{
	Release();
}

void CSwordBullet::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_eGroup = RENDER_EFFECT;
	m_tInfo.fCY = 40.f;
}

int CSwordBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eBulletType == BULLET_THUNDER)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"ThunderBullet.wav", BUllET_EFFECT, g_fSound);

		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
	}
	else if (m_eBulletType != BUllET_FIRE)
	{
		int i = rand() % 4;
		switch (i)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySound(L"Sword_Sound (1).wav", BUllET_EFFECT, g_fSound - 0.3f);
			break;
		case 1:
			CSoundMgr::Get_Instance()->PlaySound(L"Sword_Sound (2).wav", BUllET_EFFECT, g_fSound - 0.3f);
			break;
		case 2:
			CSoundMgr::Get_Instance()->PlaySound(L"Sword_Sound (3).wav", BUllET_EFFECT, g_fSound - 0.3f);
			break;
		case 3:
			CSoundMgr::Get_Instance()->PlaySound(L"Sword_Sound (4).wav", BUllET_EFFECT, g_fSound - 0.3f);
			break;
		default:
			break;
		}
		
	}
		


	Update_Rect();

	return OBJ_NOEVENT;
}

void CSwordBullet::Late_Update(void)
{
	if (dwTime + 100 < GetTickCount())
	{
		m_bDead = true;
		dwTime = GetTickCount();
	}
}

void CSwordBullet::Render(HDC hDC)
{
	//int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CSwordBullet::Release(void)
{
}
