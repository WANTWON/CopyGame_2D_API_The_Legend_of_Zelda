#include "stdafx.h"
#include "WhatThe.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CWhatThe::CWhatThe(): m_bGet_Effect(false), m_dwTime(GetTickCount()), m_bCount(false)
{
}


CWhatThe::~CWhatThe()
{
	Release();
}

void CWhatThe::Initialize(void)
{
	m_eItemType = ITEM_STRANGEMAN;
	m_tInfo.fCX = 25;
	m_tInfo.fCY = 50;
	m_fSpeed = 0.2f;
	m_eGroup = RENDER_PLAYERUPOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/WhatMan.bmp", L"WhatMan");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/TextBar_WhatThe.bmp", L"TextBar_WhatThe");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.dwFrameSpeed = 100;
	m_pFrameKey = L"WhatMan";
}

int CWhatThe::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Effect)
		Get_Effect();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CWhatThe::Late_Update(void)
{
	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this))
		m_bGet_Effect = true;

	Move_Frame();
}

void CWhatThe::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hItemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart *(16),								// 비트맵 출력 시작 좌표, X,Y
		0,
		16,				// 복사할 비트맵의 가로, 세로 길이
		32,
		RGB(128, 128, 128));			// 제거하고자 하는 색상


	if (m_bCount)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBar_WhatThe");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			500,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}
}

void CWhatThe::Release(void)
{
}

void CWhatThe::Get_Effect(void)
{
	if (!m_bCount)
	{
		m_dwTime = GetTickCount();
		m_bCount = true;
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::EFFECT);
		m_tInfo.fY -= 15;
	}

	if (m_dwTime + 3000 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", ITEM_EFFECT, g_fSound);
		m_bDead = true;

		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::IDLE);
	}

}
