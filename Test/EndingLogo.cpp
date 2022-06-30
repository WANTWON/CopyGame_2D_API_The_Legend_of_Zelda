#include "stdafx.h"
#include "EndingLogo.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CEndingLogo::CEndingLogo() : m_dwDrawTime(GetTickCount()), m_DrawEffectID(0), m_DrawUIID(0), m_dwButtonTime(GetTickCount())
, m_DrawPhotoID(0), m_dwPhotoTime(GetTickCount())
{
}


CEndingLogo::~CEndingLogo()
{
	Release();
}

void CEndingLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending/BackGround.bmp", L"Ending_Background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending/Ending.bmp", L"Ending_Photo");

}

int CEndingLogo::Update(void)
{
	if (m_dwDrawTime + 100 < GetTickCount())
	{
		++m_DrawEffectID;
		if (m_DrawEffectID == 4)
			m_DrawEffectID = 0;

		m_dwDrawTime = GetTickCount();
	}

	if (m_dwButtonTime + 500 < GetTickCount())
	{
		++m_DrawUIID;
		if (m_DrawUIID == 2)
			m_DrawUIID = 0;

		m_dwButtonTime = GetTickCount();
	}

	return 0;
}

void CEndingLogo::Late_Update(void)
{

	if (m_dwPhotoTime + 1000 < GetTickCount())
	{
		++m_DrawPhotoID;

		if (m_DrawPhotoID > 7)
			m_DrawPhotoID = 0;

		m_dwPhotoTime = GetTickCount();
	}
}

void CEndingLogo::Render(HDC hDC)
{
	HDC hBackGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending_Background");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackGroundMemDC, 0, 0, SRCCOPY);

	HDC hSwordMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Sword");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		50,	// 2,3 인자 :  복사받을 위치 X, Y
		180,
		175,				// 4,5 인자 : 복사받을 가로, 세로 길이
		100,
		hSwordMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		(98 + 3) * m_DrawUIID,
		191,				// 복사할 비트맵의 가로, 세로 길이
		98,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

	HDC hTitleMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Title");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		150,	// 2,3 인자 :  복사받을 위치 X, Y
		200,
		250,				// 4,5 인자 : 복사받을 가로, 세로 길이
		150,
		hTitleMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		167,				// 복사할 비트맵의 가로, 세로 길이
		88,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

	HDC hLogoMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Nintendo");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		250,	// 2,3 인자 :  복사받을 위치 X, Y
		550,
		300,				// 4,5 인자 : 복사받을 가로, 세로 길이
		30,
		hLogoMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		133,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

	HDC hPhotoDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending_Photo");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		450,	// 2,3 인자 :  복사받을 위치 X, Y
		100,
		240,				// 4,5 인자 : 복사받을 가로, 세로 길이
		320,
		hPhotoDC,							// 비트맵을 가지고 있는 DC
		120 * m_DrawPhotoID,								// 비트맵 출력 시작 좌표, X,Y
		0,
		120,				// 복사할 비트맵의 가로, 세로 길이
		160,
		RGB(112, 216, 248));			// 제거하고자 하는 색상
}

void CEndingLogo::Release(void)
{
}
