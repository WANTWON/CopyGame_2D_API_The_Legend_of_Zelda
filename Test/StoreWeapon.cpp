#include "stdafx.h"
#include "StoreWeapon.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "MenuObjMgr.h"
#include "AbstractFactory.h"
#include "ItemTile.h"


CStoreWeapon::CStoreWeapon() : m_dwTime(GetTickCount()), m_bCount(false), m_bTextout(false), m_bSuccessBuy(false), m_bShortage_Money(false)
{
}


CStoreWeapon::~CStoreWeapon()
{
}

void CStoreWeapon::Initialize(void)
{
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 100;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Mage.bmp", L"Item_Mage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Boomerang.bmp", L"Item_Boomerang");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Bow.bmp", L"Item_Bow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Shield.bmp", L"Item_Shield");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Fire.bmp", L"Item_Fire");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Wand.bmp", L"Text_Wand");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Shield.bmp", L"Text_Shield");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Lanton.bmp", L"Text_Lanton");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Bow.bmp", L"Text_Bow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Boomerang.bmp", L"Text_Boomerang");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Hp.bmp", L"Text_Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Portion.bmp", L"Text_Portion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Purchase_success.bmp", L"Purchase_success");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Money_is_scarce.bmp", L"Money_is_scarce");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Portion.bmp", L"Item_Portion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Heart.bmp", L"Item_Heart");


	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 0;
	//m_tFrame.dwFrameSpeed = 100;
}

int CStoreWeapon::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CStoreWeapon::Late_Update(void)
{

	switch (m_eType)
	{
	case CStoreWeapon::WEAPON:
		Set_WeaponType();
		break;
	case CStoreWeapon::HP:
		m_pFrameKey = L"Item_Heart";
		TextFrameKey = L"Text_Hp";
		iCoin = 50;
		break;
	case CStoreWeapon::PORTION:
		m_pFrameKey = L"Item_Portion";
		TextFrameKey = L"Text_Portion";
		iCoin = 10;
		break;
	default:
		break;
	}
	RECT rc = {};

	if (IntersectRect(&rc, &(CObjMgr::Get_Instance()->Get_Player()->Get_Rect()), &m_tRect))
	{
		if (m_bSuccessBuy)
			m_bTextout = false;
		else
			m_bTextout = true;
		

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			if (iCoin > CObjMgr::Get_Instance()->Get_Player()->Get_Coin())
			{
				m_bShortage_Money = true;
				return;
			}


			if (m_eType == WEAPON)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Buy.wav", SOUND_EFFECT, g_fSound - 0.4f);
				m_bSuccessBuy = true;
				CMenuObjMgr::Get_Instance()->Load_Weapon();
				CMenuObjMgr::Get_Instance()->Add_Weapon(m_eWeapontype);
				CMenuObjMgr::Get_Instance()->Update();
				CMenuObjMgr::Get_Instance()->Late_Update();
				CMenuObjMgr::Get_Instance()->Save_Weapon();
				CObjMgr::Get_Instance()->Get_Player()->Set_Coin(-iCoin);
				
			}
			else if (m_eType == HP)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"HpUp.wav", SOUND_EFFECT, g_fSound + 0.5f);
				CObjMgr::Get_Instance()->Get_Player()->Set_MaxHp();
				CObjMgr::Get_Instance()->Get_Player()->Set_Coin(-iCoin);
			}
			else if (m_eType == PORTION)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"HpPortion.wav", SOUND_EFFECT, g_fSound + 0.5f);
				CObjMgr::Get_Instance()->Get_Player()->Set_Coin(-iCoin);
				CObjMgr::Get_Instance()->Get_Player()->Set_Hp();
			}
				
			m_dwTime = GetTickCount();
			m_bTextout = false;
			m_bShortage_Money = false;
		}		
		
	}
	else
	{
		m_bTextout = false;
	}
	
	if ((m_bSuccessBuy||m_bShortage_Money) && m_dwTime + 1000 < GetTickCount() )
	{
		m_bSuccessBuy = false;
		m_bShortage_Money = false;
		m_dwTime = GetTickCount();
	}
}

void CStoreWeapon::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	if (m_eType == HP)
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 10,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) + 25,
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) - 70,
			hItemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			8,				// 복사할 비트맵의 가로, 세로 길이
			7,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	else if (m_eType == PORTION)
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 10,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) + 20,
			int(m_tInfo.fCX) + 5,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) - 60,
			hItemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			14,				// 복사할 비트맵의 가로, 세로 길이
			16,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	else
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 10,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) + 20,
			int(m_tInfo.fCX) + 20,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) - 60,
			hItemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			78,				// 복사할 비트맵의 가로, 세로 길이
			57,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	

	if (m_bShortage_Money)
	{
		HDC hTextOutDC = CBmpMgr::Get_Instance()->Find_Image(L"Money_is_scarce");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			500,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextOutDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}
	else if (m_bSuccessBuy)
	{

		HDC hTextOutDC = CBmpMgr::Get_Instance()->Find_Image(L"Purchase_success");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			500,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextOutDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}
	else if (!m_bSuccessBuy && m_bTextout)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(TextFrameKey);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			500,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}

}

void CStoreWeapon::Release(void)
{
}

void CStoreWeapon::Set_WeaponType(void)
{
	
	switch (m_eWeapontype)
	{
	case WAND:
		m_pFrameKey = L"Item_Mage";
		TextFrameKey = L"Text_Wand";
		iCoin = 300;
		break;
	case ARROW:
		m_pFrameKey = L"Item_Bow";
		TextFrameKey = L"Text_Bow";
		iCoin = 70;
		break;
	case SHIELD:
		m_pFrameKey = L"Item_Shield";
		TextFrameKey = L"Text_Shield";
		iCoin = 100;
		break;
	case LANTON:
		m_pFrameKey = L"Item_Fire";
		TextFrameKey = L"Text_Lanton";
		iCoin = 100;
		break;
	case BOOMERANG:
		m_pFrameKey = L"Item_Boomerang";
		TextFrameKey = L"Text_Boomerang";
		iCoin = 100;
		break;
	}
}
