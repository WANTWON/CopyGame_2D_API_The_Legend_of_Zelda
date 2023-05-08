#include "stdafx.h"
#include "MoblinMonster.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "BlockMgr.h"
#include "Coin.h"
#include "SoundMgr.h"

CMoblinMonster::CMoblinMonster() : m_dwTime(GetTickCount()), m_bCount(false), m_ePreDir(DIR_END)
{
}


CMoblinMonster::~CMoblinMonster()
{
	Release();
}

void CMoblinMonster::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 40.f, 40.f };

	m_fSpeed = 0.005f;
	m_fDistance = 100.f;
	m_eDir = DIR_DOWN;
	m_eGroup = RENDER_PLAYER;

	m_eMonsterType = MOBLIN_MONSTER;
	m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iHp = 10;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Moblin.bmp", L"Moblin");
	m_pFrameKey = L"Moblin";
}

int CMoblinMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState == IDLE)
		Move();
	else if (m_eCurState == ATTACK)
		Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMoblinMonster::Late_Update(void)
{
	if (m_bEditorMode)
		return;

	Motion_Change();

	if (m_eCurState == DEAD)
	{
		Dead_Motion();
		return;
	}
	else if (m_eCurState == IDLE)
		IDLE_Motion();

	if (m_eCurState != HIT)
		Move_Frame();

	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);
	CCollisionMgr::Collsion_Tile(CTileMgr::Get_Instance()->Get_EditTiles(), this);
	CCollisionMgr::Collsion_Block(CBlockMgr::Get_Instance()->Get_Blocks(), this);
	CCollisionMgr::Collsion_Block(CObjMgr::Get_Instance()->Get_Shields(), this);


	if (m_beAttacked )
	{
		m_eCurState = HIT;

		if (!m_bCount)
		{
			CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"MoblinHit.wav", MONSTER_EFFECT, g_fSound + 0.5f);
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
	if (m_iHp <= 0)
		m_eCurState = DEAD;
}

void CMoblinMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX) - 100,	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY) - 100,
		int(m_tInfo.fCX) + 200,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY) + 200,
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (300),								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * 300,
		300,				// 복사할 비트맵의 가로, 세로 길이
		300,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CMoblinMonster::Release(void)
{
}

void CMoblinMonster::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CMoblinMonster::HIT:
			if (m_eDir == DIR_UP)
				m_tFrame.iMotion = 10;
			else if (m_eDir == DIR_LEFT)
				m_tFrame.iMotion = 8;
			else if (m_eDir == DIR_RIGHT)
				m_tFrame.iMotion = 9;
			else if (m_eDir == DIR_DOWN)
				m_tFrame.iMotion = 7;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameStart = 0;
			//m_tFrame.iMotion = 5;

			m_tFrame.dwFrameSpeed = 10;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CMoblinMonster::DEAD:
			m_tFrame.iFrameStart = 0;
			if (m_eDir == DIR_UP)
				m_tFrame.iMotion = 10;
			else if (m_eDir == DIR_LEFT)
				m_tFrame.iMotion = 8;
			else if (m_eDir == DIR_RIGHT)
				m_tFrame.iMotion = 9;
			else if (m_eDir == DIR_DOWN)
				m_tFrame.iMotion = 7;
			m_tFrame.iFrameEnd = 17;

			m_tFrame.dwFrameSpeed = 70;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CMoblinMonster::IDLE:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CMoblinMonster::ATTACK:
			CSoundMgr::Get_Instance()->PlaySound(L"MoblinAttack.wav", MONSTER_EFFECT, g_fSound + 0.5f);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			if (m_eDir == DIR_UP)
				m_tFrame.iMotion = 6;
			else if (m_eDir == DIR_LEFT)
				m_tFrame.iMotion = 3;
			else if (m_eDir == DIR_RIGHT)
				m_tFrame.iMotion = 5;
			else if (m_eDir == DIR_DOWN)
				m_tFrame.iMotion = 1;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CMoblinMonster::IDLE_Motion(void)
{
	if (m_eCurState != IDLE && m_eDir == m_ePreDir)
		return;

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tFrame.iMotion = 2;
		break;
	case DIR_UP:
		m_tFrame.iMotion = 6;
		break;
	case DIR_RIGHT:
		m_tFrame.iMotion = 4;
		break;
	case DIR_DOWN:
		m_tFrame.iMotion = 0;
		break;
	default:
		break;
	}
	m_ePreDir = m_eDir;
}

void CMoblinMonster::Move(void)
{
	if (m_bEditorMode)
		return;

	fWidth = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX);
	fHeight = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY);
	fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	if (abs(fWidth) < abs(fHeight)) //상하로 더 가까운 경우
	{
		if (fHeight <= 0)
			m_eDir = DIR_UP;
		else
			m_eDir = DIR_DOWN;
	}
	else //좌우로 더 가까운 경우
	{
		if (fWidth >= 0)
			m_eDir = DIR_RIGHT;
		else
			m_eDir = DIR_LEFT;
	}

	m_fAngle = acosf(fWidth / fDiagonal);
	if (m_tInfo.fY < CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY)
		m_fAngle *= -1;

	if (fDiagonal > 600)
		return;

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX += fDiagonal*cos(m_fAngle)*m_fSpeed;

		break;
	case DIR_UP:
		m_tInfo.fY -= fDiagonal*sin(m_fAngle)*m_fSpeed;

		break;
	case DIR_RIGHT:
		m_tInfo.fX += fDiagonal*cos(m_fAngle)*m_fSpeed;

		break;
	case DIR_DOWN:
		m_tInfo.fY -= fDiagonal*sin(m_fAngle)*m_fSpeed;

		break;
	default:
		break;
	}


	if (fDiagonal < 150 )
	{
		m_eCurState = ATTACK;
	}
	else
		m_eCurState = IDLE;

}

void CMoblinMonster::Attack(void)
{
	m_tInfo.fX += fDiagonal*cos(m_fAngle)*m_fSpeed*2;
	m_tInfo.fY -= fDiagonal*sin(m_fAngle)*m_fSpeed*2;


	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX += fDiagonal*cos(m_fAngle)*m_fSpeed*2;

		break;
	case DIR_UP:
		m_tInfo.fY -= fDiagonal*sin(m_fAngle)*m_fSpeed*2;

		break;
	case DIR_RIGHT:
		m_tInfo.fX += fDiagonal*cos(m_fAngle)*m_fSpeed*2;

		break;
	case DIR_DOWN:
		m_tInfo.fY -= fDiagonal*sin(m_fAngle)*m_fSpeed*2;

		break;
	default:
		break;
	}
	fWidth = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX);
	fHeight = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY);
	float fTempDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	if (fTempDiagonal < 200)
	{
		m_eCurState = ATTACK;
	}
	else
		m_eCurState = IDLE;
}

void CMoblinMonster::Dead_Motion(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Moblin_Dead.wav", MONSTER_EFFECT, g_fSound + 0.5f);

	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			CObj* pObj = CAbstractFactory<CCoin>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);

			m_bDead = true;
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}
