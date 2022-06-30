#include "stdafx.h"
#include "Shoe.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CShoe::CShoe() : m_iOption(0), m_iDrawID(0), m_bMyturn(false)
{
}


CShoe::~CShoe()
{
	Release();
}

void CShoe::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/Shoes.bmp", L"Shoes");

	m_tInfo.fCX = 100;
	m_tInfo.fCY = 100;
	int i = rand() % 4;

	if (i == 0)
		m_eDir = DIR_DOWN;
	else if (i == 1)
		m_eDir = DIR_LEFT;
	else if (i == 2)
		m_eDir = DIR_RIGHT;
	else if (i == 3)
		m_eDir = DIR_UP;

	m_iOption = rand() % 3;

}

int CShoe::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tFrame.iFrameStart = 1;
		break;
	case DIR_UP:
		m_tFrame.iFrameStart = 2;
		break;
	case DIR_RIGHT:
		m_tFrame.iFrameStart = 3;
		break;
	case DIR_DOWN:
		m_tFrame.iFrameStart = 0;
		break;
	}

	

	return OBJ_NOEVENT;
}

void CShoe::Late_Update(void)
{
	if (!m_bMyturn)
		return;



	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tFrame.iFrameStart = 1;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
		{
			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"cursor.wav", PUZZLE_EFFECT, g_fSound);
			m_iDrawID = 1;
			m_bMyturn = false;

		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT||VK_UP||VK_DOWN))
		{

			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"error.wav", PUZZLE_EFFECT, g_fSound);
		}
		break;
	case DIR_UP:
		m_tFrame.iFrameStart = 2;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
		{
			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"cursor.wav", PUZZLE_EFFECT, g_fSound);
			m_iDrawID = 1;
			m_bMyturn = false;

		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT || VK_LEFT || VK_DOWN))
		{

			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"error.wav", PUZZLE_EFFECT, g_fSound);
		}
		break;
	case DIR_RIGHT:
		m_tFrame.iFrameStart = 3;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
		{
			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"cursor.wav", PUZZLE_EFFECT, g_fSound);
			m_iDrawID = 1;
			m_bMyturn = false;

		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT || VK_UP || VK_DOWN))
		{

			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"error.wav", PUZZLE_EFFECT, g_fSound);
		}
		break;
	case DIR_DOWN:
		m_tFrame.iFrameStart = 0;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
		{
			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"cursor.wav", PUZZLE_EFFECT, g_fSound);
			m_iDrawID = 1;
			m_bMyturn = false;
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT || VK_UP || VK_LEFT))
		{

			CSoundMgr::Get_Instance()->StopSound(PUZZLE_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"error.wav", PUZZLE_EFFECT, g_fSound);
		}
		break;
	}

	
}

void CShoe::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shoes");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX) ,	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX) ,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart*100,								// 비트맵 출력 시작 좌표, X,Y
		(m_iOption)*200 + (m_iDrawID*100),
		100,				// 복사할 비트맵의 가로, 세로 길이
		100,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CShoe::Release(void)
{
}
