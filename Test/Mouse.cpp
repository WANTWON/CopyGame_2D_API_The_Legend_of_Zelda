#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_eGroup = RENDER_PLAYERUPOBJECT;
}

int CMouse::Update(void)
{
	POINT Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	m_tInfo.fX = (float)Pt.x;
	m_tInfo.fY = (float)Pt.y;

	Update_Rect();
	ShowCursor(false);


	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMouse::Release(void)
{
}
