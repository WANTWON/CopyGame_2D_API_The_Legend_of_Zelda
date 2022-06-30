#include "stdafx.h"
#include "RockPaperScissor.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CRockPaperScissor::CRockPaperScissor() : m_iOption(0), m_iDrawID(0)
{
}


CRockPaperScissor::~CRockPaperScissor()
{
	Release();
}

void CRockPaperScissor::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Rock.bmp", L"Rock");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Paper.bmp", L"Paper");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Scissor.bmp", L"Scissor");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/PCRock.bmp", L"PCRock");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/PCPaper.bmp", L"PCPaper");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/PCScissor.bmp", L"PCScissor");

	m_tInfo.fCX = 200;
	m_tInfo.fCY = 200;

	m_iOption = rand() % 3;
}

int CRockPaperScissor::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CRockPaperScissor::Late_Update(void)
{

	if (m_bPC)
	{
		if (m_iOption == 0)
			m_pFrameKey = L"PCRock";
		else if (m_iOption == 2)
			m_pFrameKey = L"PCScissor";
		else if (m_iOption == 1)
			m_pFrameKey = L"PCPaper";
	}
	else
	{

		if (m_iOption == 0)
			m_pFrameKey = L"Rock";
		else if (m_iOption == 2)
			m_pFrameKey = L"Scissor";
		else if (m_iOption == 1)
			m_pFrameKey = L"Paper";
	}
}

void CRockPaperScissor::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart ,								// 비트맵 출력 시작 좌표, X,Y
		0,
		100,				// 복사할 비트맵의 가로, 세로 길이
		100,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CRockPaperScissor::Release(void)
{
}
