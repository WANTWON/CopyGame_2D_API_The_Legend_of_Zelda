#include "stdafx.h"
#include "Coin.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CCoin::CCoin() : m_bGet_Effect(false), m_dwTime(GetTickCount()), m_bCount(false)
{
}


CCoin::~CCoin()
{
}

void CCoin::Initialize(void)
{
	m_eItemType = ITEM_COIN;
	m_tInfo.fCX = 20;
	m_tInfo.fCY = 35;
	m_eGroup = RENDER_PLAYERUPOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Coin.bmp", L"Coin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Bonus_Coin.bmp", L"Bonus_Coin");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.dwFrameSpeed = 100;
	
	m_iDrawID = rand() % 3;

}

int CCoin::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Effect)
		Get_Effect();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoin::Late_Update(void)
{
	
	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this))
		m_bGet_Effect = true;

	if (0 == m_iOption)
		m_pFrameKey = L"Coin";
	else if (1 == m_iOption)
	{
		m_pFrameKey = L"Bonus_Coin";	
	}

	Move_Frame();
}

void CCoin::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (m_pFrameKey == L"Coin")
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) ,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) ,
			int(m_tInfo.fCX) ,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hItemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (8 + 8),								// 비트맵 출력 시작 좌표, X,Y
			0,
			8,				// 복사할 비트맵의 가로, 세로 길이
			14,
			RGB(244, 0, 244));			// 제거하고자 하는 색상
	}
	else if (m_pFrameKey == L"Bonus_Coin")
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 10,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX) + 10,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hItemDC,							// 비트맵을 가지고 있는 DC
			m_iDrawID * (16 + 8),								// 비트맵 출력 시작 좌표, X,Y
			0,
			16,				// 복사할 비트맵의 가로, 세로 길이
			15,
			RGB(244, 0, 244));			// 제거하고자 하는 색상
	}
}

void CCoin::Release(void)
{
}

void CCoin::Get_Effect(void)
{
	if (!m_bCount)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", ITEM_EFFECT, g_fSound);
		m_dwTime = GetTickCount();
		m_bCount = true;
	}

	float m_fJumpPower = 12.f;
	m_tInfo.fY -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
	m_fTime += 0.1f;


	if (m_dwTime + 500 < GetTickCount())
	{
		m_bDead = true;
		int Coin = 1;
		if (m_iOption == 1)
		{
			switch (m_iDrawID)
			{
			case 0:
				Coin = 50;
				break;
			case 1:
				Coin = 100;
				break;
			case 2:
				Coin = 300;
				break;
			default:
				break;
			}
		}
		CObjMgr::Get_Instance()->Get_Player()->Set_Coin(Coin);
	}
		
	
}
