#include "stdafx.h"
#include "MenuObj.h"

CMenuObj::CMenuObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f), m_iHp(20), m_iCoin(0), m_iMaxHp(6),
m_fDistance(0.f), m_pFrameKey(L""), m_bEditorMode(false), m_bStageClear(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CMenuObj::~CMenuObj()
{
}




void CMenuObj::Update_Rect(void)
{
	m_tRect.left = int(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = int(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = int(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = int(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

}

void CMenuObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{

			m_tFrame.iFrameStart = 0;
		}


		m_tFrame.dwFrameTime = GetTickCount();
	}
}



