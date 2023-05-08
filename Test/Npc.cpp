#include "stdafx.h"
#include "Npc.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "MenuObjMgr.h"
#include "AbstractFactory.h"
#include "QuestTile.h"
#include "Player.h"

CNpc::CNpc() : m_eNpcType(NPC_END), m_bTextout(false), m_bUpgrade(false)
{
}


CNpc::~CNpc()
{
	Release();
}

void CNpc::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/StoreNPC.bmp", L"StoreNPC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/ShoeStoreNPC.bmp", L"ShoeStoreNPC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniNPC.bmp", L"MiniNPC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniNPC2.bmp", L"MiniNPC2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniNPC3.bmp", L"MiniNPC3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniChief.bmp", L"MiniChiefNPC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniWoodNPC.bmp", L"MiniWoodNPC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/FieldNPC.bmp", L"FiledNPC");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/Store_TextBar.bmp", L"Store_TextBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/Upgrade_Textbar.bmp", L"Upgrade_Textbar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/ShoeStore_TextBar.bmp", L"ShoeStore_TextBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniNPC_TextBar.bmp", L"MiniNPC_TextBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniNPC2_TextBar.bmp", L"MiniNPC2_TextBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniNPC3_TextBar.bmp", L"MiniNPC3_TextBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniChief_TextBar.bmp", L"MiniChief_TextBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/MiniWoodNPC_TextBar.bmp", L"MiniWoodNPC_TextBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/FieldNPC_TextBar.bmp", L"FiledNPC_TextBar");
	m_eGroup = RENDER_PLAYER;


	m_pFrameKey = L"StoreNPC";
	m_pTextKey = L"Store_TextBar";
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 100;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 16;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CNpc::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CNpc::Late_Update(void)
{
	if (m_dwTime + 3000 < GetTickCount())
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::IDLE);
		m_bUpgrade = false;
		m_dwTime = GetTickCount();

	}

	Move_Frame();

	switch (m_eNpcType)
	{
	case STORE_NPC:
		m_pFrameKey = L"StoreNPC";
		m_pTextKey = L"Store_TextBar";
		break;
	case SHOE_NPC:
		m_pFrameKey = L"ShoeStoreNPC";
		m_pTextKey = L"ShoeStore_TextBar";
		break;
	case MINI_NPC:
		m_pFrameKey = L"MiniNPC";
		m_pTextKey = L"MiniNPC_TextBar";
		m_tFrame.iFrameEnd = 8;
		break;

	case MINI_NPC2:
		m_pFrameKey = L"MiniNPC2";
		m_pTextKey = L"MiniNPC2_TextBar";
		m_tFrame.iFrameEnd = 9;
		break;

	case MINI_NPC3:
		m_pFrameKey = L"MiniNPC3";
		m_pTextKey = L"MiniNPC3_TextBar";
		m_tFrame.iFrameEnd = 8;
		break;
	case MINIWOOD_NPC:
		m_pFrameKey = L"MiniWoodNPC";
		m_pTextKey = L"MiniWoodNPC_TextBar";
		m_tFrame.iFrameEnd = 3;
		break;
	case FIELD_NPC:
		m_tInfo.fCY = 70;
		m_pFrameKey = L"FiledNPC";
		m_pTextKey = L"FiledNPC_TextBar";
		m_tFrame.iFrameEnd = 4;
		break;
	case MINI_CHIEF:
		m_pFrameKey = L"MiniChiefNPC";
		m_pTextKey = L"MiniChief_TextBar";
		m_tFrame.iFrameEnd = 8;
		break;
	case NPC_END:
		break;
	default:
		break;
	}


	RECT rc{};
	if (IntersectRect(&rc, &(CObjMgr::Get_Instance()->Get_Player()->Get_Rect()), &m_tRect))
	{
		m_bTextout = true;

		if (m_eNpcType == SHOE_NPC && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_SHOE_MINIGAME);
		}
		if (m_eNpcType == MINI_NPC2 && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_MINIGAME);
		}
		if (m_eNpcType == FIELD_NPC && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			CMenuObjMgr::Get_Instance()->Load_Quest();
			CMenuObjMgr::Get_Instance()->Add_Quest(FIELD_QUEST);
			CMenuObjMgr::Get_Instance()->Add_Quest(STORE_QUEST);
			CMenuObjMgr::Get_Instance()->Update();
			CMenuObjMgr::Get_Instance()->Late_Update();
			CMenuObjMgr::Get_Instance()->Save_Quest();
		}
		if (m_eNpcType == MINI_CHIEF && CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{

			if (CSceneMgr::Get_Instance()->Get_SolvedQuestNumber() < 3)
			{
				CMenuObjMgr::Get_Instance()->Load_Quest();
				CMenuObjMgr::Get_Instance()->Delete_Quest();
				for (int i = 0; i < 3; ++i)
				{
					CMenuObjMgr::Get_Instance()->Add_QuestTile(CAbstractFactory<CQuestTile>::Create_Menu(400, 200 + (i * 112)));
				}
				CMenuObjMgr::Get_Instance()->Add_Quest(MINIQUEST_KEY);
				CMenuObjMgr::Get_Instance()->Add_Quest(MINIQUEST_WRITER);
				CMenuObjMgr::Get_Instance()->Add_Quest(MINIQUEST_FLOWER);
				CMenuObjMgr::Get_Instance()->Update();
				CMenuObjMgr::Get_Instance()->Late_Update();
				CMenuObjMgr::Get_Instance()->Save_Quest();
			}
			else
			{
				m_dwTime = GetTickCount();
				m_bUpgrade = true;
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::UPGRADE);
			}
			
		}
	}
	else
		m_bTextout = false;

}

void CNpc::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC;
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	
		if (m_eNpcType == STORE_NPC || m_eNpcType == MINI_CHIEF)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
			GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
				int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
				int(m_tRect.top + iScrollY) - 90,
				int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY) - 25,
				hMemDC,							// ��Ʈ���� ������ �ִ� DC
				m_tFrame.iFrameStart * (25),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
				0,
				25,				// ������ ��Ʈ���� ����, ���� ����
				40,
				RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
		}
		else if (m_eNpcType == SHOE_NPC)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
			GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
				int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
				int(m_tRect.top + iScrollY) - 90,
				int(m_tInfo.fCX) + 15,				// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY),
				hMemDC,							// ��Ʈ���� ������ �ִ� DC
				m_tFrame.iFrameStart * (20),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
				0,
				20,				// ������ ��Ʈ���� ����, ���� ����
				40,
				RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
		}
		else if (m_eNpcType == MINI_NPC || m_eNpcType == MINI_NPC3)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
			GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
				int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
				int(m_tRect.top + iScrollY) - 40,
				int(m_tInfo.fCX) + 15,				// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY) -10,
				hMemDC,							// ��Ʈ���� ������ �ִ� DC
				m_tFrame.iFrameStart * (21),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
				0,
				21,				// ������ ��Ʈ���� ����, ���� ����
				40,
				RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
		}
		else if (m_eNpcType == MINI_NPC2)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
			GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
				int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
				int(m_tRect.top + iScrollY) - 70,
				int(m_tInfo.fCX)  + 30,				// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY) + 30,
				hMemDC,							// ��Ʈ���� ������ �ִ� DC
				m_tFrame.iFrameStart * (35),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
				0,
				35,				// ������ ��Ʈ���� ����, ���� ����
				80,
				RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
		}
		else if (m_eNpcType == MINIWOOD_NPC)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
			GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
				int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
				int(m_tRect.top + iScrollY) - 70,
				int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY),
				hMemDC,							// ��Ʈ���� ������ �ִ� DC
				m_tFrame.iFrameStart * (16),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
				0,
				16,				// ������ ��Ʈ���� ����, ���� ����
				40,
				RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
		}
		else if (m_eNpcType == FIELD_NPC)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
			GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
				int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
				int(m_tRect.top + iScrollY) - 30,
				int(m_tInfo.fCX) + 15,				// 4,5 ���� : ������� ����, ���� ����
				int(m_tInfo.fCY) + 30,
				hMemDC,							// ��Ʈ���� ������ �ִ� DC
				m_tFrame.iFrameStart * (25),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
				0,
				25,				// ������ ��Ʈ���� ����, ���� ����
				40,
				RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
		}
	
	if (m_bTextout)
	{
		HDC	hTextDC = CBmpMgr::Get_Instance()->Find_Image(m_pTextKey);
		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX) - 55,	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY) - 180,
			int(m_tInfo.fCX) + 100,				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY)  + 10,
			hTextDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			200,				// ������ ��Ʈ���� ����, ���� ����
			141,
			RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
	}

	if (m_bUpgrade)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"Upgrade_Textbar");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			150,	// 2,3 ���� :  ������� ��ġ X, Y
			500,
			500,				// 4,5 ���� : ������� ����, ���� ����
			50,
			hTextDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			600,				// ������ ��Ʈ���� ����, ���� ����
			61,
			RGB(192, 192, 255));			// �����ϰ��� �ϴ� ����
	}
}

void CNpc::Release(void)
{
}
