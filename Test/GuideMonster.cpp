#include "stdafx.h"
#include "GuideMonster.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "BlockMgr.h"


CGuideMonster::CGuideMonster() : m_bCount(false), m_dwTime(GetTickCount()), m_bSoundCount(false)
{
}


CGuideMonster::~CGuideMonster()
{
	Release();
}

void CGuideMonster::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 45.f, 50.f };

	m_fSpeed = 0.01f;
	m_eGroup = RENDER_MONSTER;

	m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iHp = 5;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/GuideMonster.bmp", L"GuideMonster");
	m_pFrameKey = L"GuideMonster";
}

int CGuideMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState != DEAD && m_eCurState != HIT)
		Move();

	if (!m_bSoundCount)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"GuideMonster.wav", MONSTER_BULLET, g_fSound + 0.2f);
		m_bSoundCount = true;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CGuideMonster::Late_Update(void)
{
	Motion_Change();

	if (m_eCurState == DEAD)
	{
		Dead_Motion();
		return;
	}

	if (m_eCurState != HIT)
		Move_Frame();

	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);
	CCollisionMgr::Collsion_Tile(CTileMgr::Get_Instance()->Get_EditTiles(), this);
	CCollisionMgr::Collsion_Block(CBlockMgr::Get_Instance()->Get_Blocks(), this);

	if (m_beAttacked)
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
	if (m_iHp <= 0)
		m_eCurState = DEAD;

}

void CGuideMonster::Render(HDC hDC)
{

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (16 + 2),								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * 20,
		16,				// 복사할 비트맵의 가로, 세로 길이
		20,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CGuideMonster::Release(void)
{
}

void CGuideMonster::Move(void)
{
	if (m_bEditorMode)
		return;

	float fWidth = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX);
	float fHeight = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY);
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

		m_fAngle = acosf(fWidth / fDiagonal);
		if (m_tInfo.fY < CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY)
			m_fAngle *= -1;

		m_tInfo.fX += fDiagonal*cos(m_fAngle)*m_fSpeed;
		m_tInfo.fY -= fDiagonal*sin(m_fAngle)*m_fSpeed;
	
}

void CGuideMonster::Dead_Motion(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"large swing.wav", MONSTER_EFFECT, g_fSound + 0.2f);

	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tInfo.fCX -= 5;
		m_tInfo.fCY -= 5;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_bDead = true;
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}

void CGuideMonster::Motion_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CGuideMonster::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 1;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CGuideMonster::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CGuideMonster::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 2;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
