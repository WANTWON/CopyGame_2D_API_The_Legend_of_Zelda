#include "stdafx.h"
#include "ItemTile.h"
#include "BmpMgr.h"


CItemTile::CItemTile() : m_bExist(false), m_iDrawID(0), m_WeaponType(WEAPON_END), m_bBeUsed(false)
{
}


CItemTile::~CItemTile()
{
}

void CItemTile::Initialize(void)
{
	m_tInfo.fCX = 90;
	m_tInfo.fCY = 60;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Empty.bmp", L"Item_Empty");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/InvenBoomerang.bmp", L"InvenBoomerang");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/InvenSword.bmp", L"InvenSword");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/InvenBow.bmp", L"InvenBow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/InvenFire.bmp", L"InvenFire");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/InvenMage.bmp", L"InvenMage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/InvenShield.bmp", L"InvenShield");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/InvenHorse.bmp", L"InvenHorse");

}

int CItemTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CItemTile::Late_Update(void)
{
	switch (m_WeaponType)
	{
	case SWORD:
		m_pFrameKey = L"InvenSword";
		break;
	case WAND:
		m_pFrameKey = L"InvenMage";
		break;
	case ARROW:
		m_pFrameKey = L"InvenBow";
		break;
	case SHIELD:
		m_pFrameKey = L"InvenShield";
		break;
	case LANTON:
		m_pFrameKey = L"InvenFire";
		break;
	case BOOMERANG:
		m_pFrameKey = L"InvenBoomerang";
		break;
	case HORSE:
		m_pFrameKey = L"InvenHorse";
		break;
	}

	if (m_bBeUsed)
	{
		if (WOption == true)
			m_iDrawID = 2;
		else
			m_iDrawID = 1;
	}	
	else
	{
		m_iDrawID = 0;
		//WOption = false;
	}
		
}

void CItemTile::Render(HDC hDC)
{

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	if (!m_bExist)
	{

		HDC hSwordMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Item_Empty");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			m_tRect.left,	// 2,3 인자 :  복사받을 위치 X, Y
			m_tRect.top,
			m_tInfo.fCX,				// 4,5 인자 : 복사받을 가로, 세로 길이
			m_tInfo.fCY,
			hSwordMemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			78,				// 복사할 비트맵의 가로, 세로 길이
			57,
			RGB(112, 216, 248));			// 제거하고자 하는 색상
	}
	else
	{
		HDC hSwordMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			m_tRect.left,	// 2,3 인자 :  복사받을 위치 X, Y
			m_tRect.top,
			m_tInfo.fCX,				// 4,5 인자 : 복사받을 가로, 세로 길이
			m_tInfo.fCY,
			hSwordMemDC,							// 비트맵을 가지고 있는 DC
			m_iDrawID* 78.f,								// 비트맵 출력 시작 좌표, X,Y
			0,
			78.f ,				// 복사할 비트맵의 가로, 세로 길이
			57.f,
			RGB(112, 216, 248));			// 제거하고자 하는 색상
	}
}

void CItemTile::Release(void)
{
}
