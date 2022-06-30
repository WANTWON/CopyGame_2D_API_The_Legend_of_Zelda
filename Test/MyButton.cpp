#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 130.f;
	m_tInfo.fCY = 60.f;
	m_eGroup = RENDER_GAMEOBJECT;
}

int CMyButton::Update(void)
{

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	
	POINT		Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (PtInRect(&m_tRect, Pt))
	{
		

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Menu_Button.wav", SOUND_EFFECT, g_fSound - 0.3f);
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_FIELD);

			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT, SC_MINIWORLD);
			else if (!lstrcmp(L"Quit", m_pFrameKey))
				DestroyWindow(g_hWnd);
			else if (!lstrcmp(L"Back", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

			return;
		}

		m_iDrawID = 1;
	}
	else
	{
		
		m_iDrawID = 0;
	}
		




}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),			// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		m_iDrawID * (21 + 4),
		56,				// 복사할 비트맵의 가로, 세로 길이
		25,
		RGB(244, 0, 244));			// 제거하고자 하는 색상


}

void CMyButton::Release(void)
{

}
