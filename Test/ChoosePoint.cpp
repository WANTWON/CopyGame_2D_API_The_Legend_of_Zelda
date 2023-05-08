#include "stdafx.h"
#include "ChoosePoint.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "MenuObjMgr.h"
#include "ItemTile.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SceneMgr.h"


CChoosePoint::CChoosePoint() : m_iIndexQ(0), m_iUsedIndex(0), m_iIndexW(0), m_iWUsedIndex(0)
{
}


CChoosePoint::~CChoosePoint()
{
	Release();
}

void CChoosePoint::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Choose_Item.bmp", L"Choose_Item");

	m_tInfo.fCX = 90;
	m_tInfo.fCY = 70;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwFrameTime = GetTickCount();
	m_WeaponID = SWORD;

	
	
}

int CChoosePoint::Update(void)
{
	Key_Input();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CChoosePoint::Late_Update(void)
{
	Move_Frame();
}

void CChoosePoint::Render(HDC hDC)
{
	HDC hPhotoDC = CBmpMgr::Get_Instance()->Find_Image(L"Choose_Item");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		m_tRect.left,	// 2,3 ���� :  ������� ��ġ X, Y
		m_tRect.top,
		m_tInfo.fCX,				// 4,5 ���� : ������� ����, ���� ����
		m_tInfo.fCY,
		hPhotoDC,							// ��Ʈ���� ������ �ִ� DC
		(28 + 2) * m_tFrame.iFrameStart ,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		28,				// ������ ��Ʈ���� ����, ���� ����
		24,
		RGB(192, 192, 255));			// �����ϰ��� �ϴ� ����
}

void CChoosePoint::Release(void)
{
	m_iIndexQ = 0;
}

void CChoosePoint::Key_Input(void)
{

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
	{
		
		
		--m_iIndexQ;
		--m_iIndexW;
		if (m_iIndexQ <= 0)
		{
			m_iIndexW = 0;
			m_iIndexQ = 0;
		}
				
		
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
	{
		++m_iIndexQ;
		++m_iIndexW;
		if (m_iIndexQ >= 11)
		{
			m_iIndexQ = 11;
			m_iIndexW = 11;
		}
				
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		
		if (m_iIndexQ / 4 < 2)
		{
			m_iIndexQ += 4;
			m_iIndexW += 4;
		}
			
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{

		if (m_iIndexQ / 4 > 0)
		{
			m_iIndexQ -= 4;
			m_iIndexW -= 4;
		}
			
	}

	m_tInfo.fX = CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexQ]->Get_Info().fX;
	m_tInfo.fY = CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexQ]->Get_Info().fY;



	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"ItemSelect.wav", SOUND_EFFECT, g_fSound);

		if (static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexQ])->Get_Exist() == false)
			return;

		static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexQ])->Set_beUsed(true);
		static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexQ])->Set_WOption(false); //Q�� �Ķ���
		m_WeaponID = static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexQ])->Get_Weapontype();
		CSceneMgr::Get_Instance()->Set_PlayerWeapon(m_WeaponID);

		if (m_iUsedIndex != m_iIndexQ) //���� ���ǰ� �ִ� Q����ĭ�� ���� ������ �����۰� �ٸ���
		{
			// ������ �������� �������� ���� ���� ��Ų��.
			static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iUsedIndex])->Set_beUsed(false);
			static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iUsedIndex])->Set_DrawID(0);
			m_iUsedIndex = m_iIndexQ;
		}
			
	}

	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"ItemSelect.wav", SOUND_EFFECT, g_fSound);

		if (static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexW])->Get_Exist() == false)
			return;

		static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexW])->Set_beUsed(true);
		static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexW])->Set_WOption(true); //W�� ������
		m_WWeaponID = static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndexW])->Get_Weapontype();
		

		CSceneMgr::Get_Instance()->Set_PlayerWWeapon(m_WWeaponID);

		if (m_iWUsedIndex != m_iIndexW)
		{
			static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iWUsedIndex])->Set_beUsed(false);
			static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iWUsedIndex])->Set_DrawID(0);
			m_iWUsedIndex = m_iIndexW;
		}

	}
}
