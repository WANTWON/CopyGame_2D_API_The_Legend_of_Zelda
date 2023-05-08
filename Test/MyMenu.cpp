#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "MenuObjMgr.h"
#include "MenuObj.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CMyMenu::CMyMenu() : m_dwDrawTime(GetTickCount()), m_iDrawID(0)
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Quit.bmp", L"Quit");

	CObj*	pObj = CAbstractFactory<CMyButton>::Create(100.f, 100.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(100.f, 200.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(100.f, 300.f);
	pObj->Set_FrameKey(L"Quit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

}

int CMyMenu::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Menu.wav", SOUND_BGM, g_fSound - 0.3f);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (m_dwDrawTime + 200 < GetTickCount())
	{
		m_iDrawID += Temp;
		if (m_iDrawID == 4 || m_iDrawID == 0)
			Temp *= -1;

			m_dwDrawTime = GetTickCount();
	}
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");


	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		0,	// 2,3 ���� :  ������� ��ġ X, Y
		0,
		WINCX,				// 4,5 ���� : ������� ����, ���� ����
		WINCY,
		hMenuDC,							// ��Ʈ���� ������ �ִ� DC
		(240 + 1) * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		240,				// ������ ��Ʈ���� ����, ���� ����
		160,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����

	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
