#include "stdafx.h"
#include "Jar.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BlockMgr.h"
#include "Coin.h"
#include "AbstractFactory.h"
#include "Portion.h"



CJar::CJar() : m_bPicked(false), m_fTime(0), m_bThrow(false), m_bBreak(false), m_bCount(false)
{
}


CJar::~CJar()
{
}

void CJar::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX;
	m_tInfo.fCY = BLOCKCY;

	m_eBlockType = BLOCK_JAR;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 70;
	m_iOption = 0;
	m_eGroup = RENDER_PLAYERUPOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Jar.bmp", L"Jar");

	m_pFrameKey = L"Jar";
}

int CJar::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Be_Thrown();
	Follow_Player_Top();
	if(m_bBreak)
		Break_Jar();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CJar::Late_Update(void)
{
	m_eGroup = RENDER_PLAYERUPOBJECT;

	if (m_bEditorMode)
		return;
	
	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);
		
	Be_Picked();

	
}

void CJar::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hTileDC,							// 비트맵을 가지고 있는 DC
		(16) * m_tFrame.iFrameStart,								// 비트맵 출력 시작 좌표, X,Y
		0,
		16,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(112, 216, 248));			// 제거하고자 하는 색상
}

void CJar::Release(void)
{
}

void CJar::Break_Jar(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"Break_Jar.wav", ITEM_EFFECT, g_fSound);

	m_bBreak = true;

	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			int Random = rand() % 2;
			if (Random == 1)
			{
				CObj* pObj = CAbstractFactory<CCoin>::Create(m_tInfo.fX, m_tInfo.fY);
				static_cast<CCoin*>(pObj)->Set_Bonus_Coin();
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
			}
			else if(Random == 0)
			{
				CObj* pObj = CAbstractFactory<CPortion>::Create(m_tInfo.fX, m_tInfo.fY);
				CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
			}
			m_bDead = true;
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}

void CJar::Follow_Player_Top(void)
{
	if (!m_bPicked)
		return;

	if (m_tInfo.fY <= m_pTarget->Get_Rect().top)
	{
		m_tInfo.fY = m_pTarget->Get_Rect().top - m_tInfo.fCY*0.5f;
		m_tInfo.fX = m_pTarget->Get_Info().fX;
	}	
	else
	{
		m_tInfo.fY += ((m_pTarget->Get_Rect().top - m_tInfo.fCY*0.5f) - m_tInfo.fY)*0.1f;
		m_tInfo.fX += (m_pTarget->Get_Info().fX - m_tInfo.fX)*0.1f;
	}
		

}

void CJar::Be_Picked(void)
{
	RECT rc = {};


	


	if (CPlayer::THROW == static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() && m_bPicked)
	{
		m_bPicked = false;
		m_bThrow = true;
	}
	else if (CPlayer::PICKUP == static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() 
		|| CPlayer::PICKUPWALK == static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State()
		&& m_bPicked)
	{
			Set_Target(CObjMgr::Get_Instance()->Get_Player());
	}
	else
	{
		m_bPicked = false;
	}
}

void CJar::Be_Thrown(void)
{
	if (!m_bThrow)
		return;

	float m_fJumpPower = 7.f;

	if (!m_bCount)
	{
		m_eDir = m_pTarget->Get_Direction();
		m_bCount = true;
	}
		
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fY -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_tInfo.fX -= m_fJumpPower * m_fTime - (3.5f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.06f;
		break;
	case DIR_UP:
		m_fJumpPower = 15.f;
		m_tInfo.fY -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.03f;
		break;
	case DIR_RIGHT:
		m_tInfo.fY -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_tInfo.fX += m_fJumpPower * m_fTime - (3.5f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.06f;
		break;
	case DIR_DOWN:
		m_fJumpPower = 15.f;
		m_tInfo.fY += m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.03f;
		break;
	default:
		break;
	}

	
	
	float fWidth = fabsf(m_pTarget->Get_Info().fX - m_tInfo.fX);
	float fHeight = fabsf(m_pTarget->Get_Info().fY - m_tInfo.fY);
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	if (fDiagonal > 200)
	{
		m_bThrow = false;
		m_bCount = false;
		Break_Jar();
	}
		
}
