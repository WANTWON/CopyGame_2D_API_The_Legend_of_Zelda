#include "stdafx.h"
#include "LaserMonster.h"
#include "BmpMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "BossMonster.h"
#include "LaserBullet.h"
#include "AbstractFactory.h"



CLaserMonster::CLaserMonster() : m_bCount(false), m_dwTime(GetTickCount()), 
m_dwAttackTime(GetTickCount()), m_bLaserMode(false), m_bLaserCount(false), m_bSoundCount(false)
{
}


CLaserMonster::~CLaserMonster()
{
	Release();
}

void CLaserMonster::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 30.f, 30.f };
	m_eGroup = RENDER_MONSTER;

	m_fSpeed = 0.01f;
	m_fDistance = 100.f;

	m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 2;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iHp = 5;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/LaserMonster.bmp", L"LaserMonster");
	m_pFrameKey = L"LaserMonster";
}

int CLaserMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState != DEAD && m_eCurState != HIT)
		Move();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CLaserMonster::Late_Update(void)
{
	
	if ( static_cast<CMonster*>(m_pTarget)->Get_CurState() == CMonster::DEAD)
	{
		m_eCurState = DEAD;
		return;
	}

	Motion_Change();


	if (!m_bSoundCount)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"thunder.wav", MONSTER_BULLET, g_fSound + 0.2f);
		m_bSoundCount = true;
	}

	if (m_eCurState == DEAD)
	{
		Dead_Motion();
		return;
	}

	if (m_eCurState != HIT && m_eCurState != LASER_ATTACK)
		Move_Frame();
	else if (m_eCurState == LASER_ATTACK)
		LaserAttack_Frame();

	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);

	if (m_beAttacked )
	{
		m_eCurState = HIT;

		if (!m_bCount)
		{
			if (m_bMegaCritical)
				m_iHp -= 5;
			else if (m_bCritical)
				m_iHp -= 3;
			else if (m_beAttacked)
				--m_iHp;
			m_dwTime = GetTickCount();
			m_bCount = true;
		}

		if (m_dwTime + 200 < GetTickCount())
		{
			m_beAttacked = false;
			m_eCurState = IDLE;
			m_bCount = false;
		}

	}
	if (m_iHp <= 0 || static_cast<CBossMonster*>(m_pTarget)->Get_State() == TELEPORT)
		m_eCurState = DEAD;

	if (m_bLaserMode)
	{
		if (m_dwAttackTime + 1000 < GetTickCount())
		{
			m_eCurState = LASER_ATTACK;

			m_dwAttackTime = GetTickCount();
		}
		
	}
	else if (m_eCurState != HIT && m_eCurState != DEAD)
		m_eCurState = IDLE;
}

void CLaserMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX) - 15,	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY) - 10 ,
		int(m_tInfo.fCX) + 30,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY) + 30,
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (20),								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * 20,
		20,				// 복사할 비트맵의 가로, 세로 길이
		20,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CLaserMonster::Release(void)
{
}

void CLaserMonster::Move(void)
{
	if (m_pTarget == nullptr)
		return;

		m_fAngle++;

		m_tInfo.fX = float(m_pTarget->Get_Info().fX + m_fDistance*cos(m_fAngle*RADIAN));
		m_tInfo.fY = float(m_pTarget->Get_Info().fY - m_fDistance*sin(m_fAngle*RADIAN));
	
}

void CLaserMonster::Dead_Motion(void)
{

	m_tFrame.iFrameStart = 0;

	m_tInfo.fCX -= 3;
	m_tInfo.fCY -= 3;

	if (m_tInfo.fCX <= 0 )
	{
		m_bDead = true;
		static_cast<CBossMonster*>(m_pTarget)->Minus_LaserMonster();
	}

}

void CLaserMonster::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CLaserMonster::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 2;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CLaserMonster::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 1;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CLaserMonster::LASER_ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CLaserMonster::LaserAttack_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;

			if (!m_bLaserCount)
			{
				CObj* pObj = CAbstractFactory<CLaserBullet>::Create(m_tInfo.fX, m_tInfo.fY, OBJ_MONSTER);
				pObj->Set_Target(this);
				CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
				m_bLaserCount = true;
			}
			
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}
