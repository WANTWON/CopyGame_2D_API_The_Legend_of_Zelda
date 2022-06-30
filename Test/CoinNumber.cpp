#include "stdafx.h"
#include "CoinNumber.h"
#include "BmpMgr.h"


CCoinNumber::CCoinNumber()
{
}


CCoinNumber::~CCoinNumber()
{
	Release();
}

void CCoinNumber::Initialize(void)
{
	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HUD/Number.bmp", L"Number");
}

int CCoinNumber::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoinNumber::Late_Update(void)
{
	if (m_DrawID > 4)
	{
		m_Option = 1;
		m_DrawID -= 5;
	}
	else
	{
		m_Option = 0;
	}
}

void CCoinNumber::Render(HDC hDC)
{
	HDC	hHpDC = CBmpMgr::Get_Instance()->Find_Image(L"Number");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hHpDC,							// 비트맵을 가지고 있는 DC
		(8) * m_DrawID,								// 비트맵 출력 시작 좌표, X,Y
		(8) * m_Option,
		7,				// 복사할 비트맵의 가로, 세로 길이
		7,
		RGB(244, 0, 244));			// 제거하고자 하는 색상
}

void CCoinNumber::Release(void)
{
}
