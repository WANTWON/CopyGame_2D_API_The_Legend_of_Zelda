#include "stdafx.h"
#include "MyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// 우선 getDC로 불러온 뒤, CreateCompatibleDC로 호환되는 dc를 할당한다.
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);


	m_hBitMap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들, 이미지는 프로그램에서 얻어오는 것이 아니라 파일로부터 읽어 들이기 때문에 NULL값
		pFilePath,  // 파일 경로
		IMAGE_BITMAP, // 어떤 타입을 읽을 것인가
		0,			// 가로, 세로 사이즈
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// LR_LOADFROMFILE : 파일에서 이미지를 불러오는 옵션, LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

												// 1. LoadImage는 비트맵의 현재 정보를 가지고 있는 상태이지만 그리고 있지는 않다.
												// 2. 비트맵을 그리기 위해서는 m_hMemDC를 준비했지만, 현재 선택된 gdi 오브젝트 값은 디폴트 상태이다.
												// 3. 준비한 dc의 gdi 오브젝트에 불러온 비트맵을 선택하기 위한 함수가 SelectObject이다.
												// 4. SelectObject는 gdi 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환한다.

	m_hOldMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
