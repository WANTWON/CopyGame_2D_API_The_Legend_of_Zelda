#include "stdafx.h"
#include "Hp.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CHp::CHp() : m_DrawID(0), m_Option(0)
{
}


CHp::~CHp()
{
}

void CHp::Initialize(void)
{
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 30;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HUD/LinkHp.bmp", L"LinkHp");
}

int CHp::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CHp::Late_Update(void)
{
	

}

void CHp::Render(HDC hDC)
{
	HDC	hHpDC = CBmpMgr::Get_Instance()->Find_Image(L"LinkHp");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left ),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hHpDC,							// 비트맵을 가지고 있는 DC
		(30) * m_DrawID,								// 비트맵 출력 시작 좌표, X,Y
		0,
		30,				// 복사할 비트맵의 가로, 세로 길이
		30,
		RGB(255, 0, 255));			// 제거하고자 하는 색상
}

void CHp::Release(void)
{
}
