#include "stdafx.h"
#include "ItemRect.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"


CItemRect::CItemRect()
{
}


CItemRect::~CItemRect()
{
}

void CItemRect::Initialize(void)
{
	m_tInfo.fX = 100;
	m_tInfo.fY = 100;
	m_tInfo.fCX = 45;
	m_tInfo.fCY = 45;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Sword.bmp", L"UI_Sword");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Mage.bmp", L"UI_Mage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Shield.bmp", L"UI_Shield");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Fire.bmp", L"UI_Fire");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Bow.bmp", L"UI_Bow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Boomerang.bmp", L"UI_Boomerang");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Non.bmp", L"UI_Non");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Horse.bmp", L"UI_Horse");
}

int CItemRect::Update(void)
{

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItemRect::Late_Update(void)
{
	if(TypeNumber == 1)
		m_eWeaponType = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_WeaponType();
	if (TypeNumber == 2)
		m_eWeaponType = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Second_WeaponType();

	switch (m_eWeaponType)
	{
	case SWORD:
		m_pFrameKey = L"UI_Sword";
		break;
	case WAND:
		m_pFrameKey = L"UI_Mage";
		break;
	case ARROW:
		m_pFrameKey = L"UI_Bow";
		break;
	case SHIELD:
		m_pFrameKey = L"UI_Shield";
		break;
	case LANTON:
		m_pFrameKey = L"UI_Fire";
		break;
	case BOOMERANG:
		m_pFrameKey = L"UI_Boomerang";
		break;
	case HORSE:
		m_pFrameKey = L"UI_Horse";
		break;
	case WEAPON_END:
		m_pFrameKey = L"UI_Non";
		break;
	}
}

void CItemRect::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC	hHpDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left) - 10,	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX) + 20,				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hHpDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		78,				// 복사할 비트맵의 가로, 세로 길이
		57,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CItemRect::Release(void)
{
}
