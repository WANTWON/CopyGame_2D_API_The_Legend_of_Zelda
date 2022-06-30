#include "stdafx.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "MenuObjMgr.h"
#include "Obj.h"
#include "SoundMgr.h"


// STATE 패턴 (FSM : Finite State Machine 유한 상태 기계) :자신이 취할 수 있는 유한한 개수의 상태를 가지고, 그리고 그 중 반드시 하나의 상태만 가질 수 있다.

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_LOGO), m_eInvenPreScene(SC_END),
	m_bInven_Out(false), m_bCount(false), m_bFirst(true), m_bShoesMake(false), 
	m_bQuestCount(false), m_bQuest_Out(false), m_bMiniWorldIn(true), m_bPlayWith(false), m_iSolvedQuestNumber(0)
{

}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene, SCENEID StageNum)
{
	m_eCurScene = eScene;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete<CScene*>(m_pScene);		//

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_EDIT_MENU:
			m_pScene = new CEditMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			static_cast<CMyEdit*>(m_pScene)->Set_EditStage(StageNum);
			break;

		case SC_STAGE_FIELD:
			m_pScene = new CStage;
			break;

		case SC_STAGE_DUNGEON:
			m_pScene = new CDungeon;
			break;

		case SC_STAGE_BOSS:
			m_pScene = new CBossStage;
			break;

		case SC_STAGE_ENDING:
			m_pScene = new CEndingStage;
			break;

		case SC_ENDING_LOGO:
			m_pScene = new CEndingLogo;
			break;

		case SC_INVEN:
			m_pScene = new CInventory;
			break;

		case SC_STAGE_STORE:
			m_pScene = new CStore;
			break;

		case SC_STAGE_STOREROOM:
			m_pScene = new CStoreRoom;
			break;

		case SC_STAGE_SHOESTORE:
			m_pScene = new CShoeStore;
			break;

		case SC_MINIROAD:
			m_pScene = new CMiniRoad;
			break;

		case SC_MINIWORLD:
			m_pScene = new CMiniWorld;
			break;

		case SC_MINIROOM:
			m_pScene = new CMiniRoom;
			break;

		case SC_MINIROOM2:
			m_pScene = new CMiniRoom2;
			break;

		case SC_MINIROOM3:
			m_pScene = new CMiniRoom3;
			break;

		case SC_MINIWOOD:
			m_pScene = new CMiniWood;
			break;

		case SC_SHOE_MINIGAME:
			m_pScene = new CShoeMiniGame;
			break;

		case SC_MINICHIEF:
			m_pScene = new CMiniChief;
			break;

		case SC_QUEST:
			m_pScene = new CQuest;
			break;

		case SC_MINIGAME:
			m_pScene = new CMiniGame;
			break;

		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		g_fSound += 0.1f;

		if (g_fSound > 1.f)
			g_fSound = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
		return ;
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		g_fSound -= 0.1f;

		if (g_fSound < 0.f)
			g_fSound = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
		return ;
	}

	if (CKeyMgr::Get_Instance()->Key_Up('I'))
	{
		if (m_eCurScene != SC_INVEN)
		{
			if (m_eCurScene == SC_SHOE_MINIGAME || m_eCurScene == SC_QUEST)
				return;

			m_eInvenPreScene = m_eCurScene;
			CObjMgr::Get_Instance()->Save_Player();
			m_tPlayerINFO = CObjMgr::Get_Instance()->Get_Player()->Get_Info();
			CSceneMgr::Get_Instance()->Scene_Change(SC_INVEN);
			
		}	
		else
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOpen.wav", BUllET_EFFECT, g_fSound);
			m_bInven_Out = true;
			CMenuObjMgr::Get_Instance()->Save_Weapon();
			CMenuObjMgr::Get_Instance()->Save_ChoosePoint();
			CMenuObjMgr::Get_Instance()->Destroy_Instance();
			CSceneMgr::Get_Instance()->Scene_Change(m_eInvenPreScene);

		}
	}

	if (CKeyMgr::Get_Instance()->Key_Up('O'))
	{
		if (m_eCurScene != SC_QUEST)
		{
			if (m_eCurScene == SC_SHOE_MINIGAME || m_eCurScene == SC_INVEN)
				return;

			m_eInvenPreScene = m_eCurScene;
			CObjMgr::Get_Instance()->Save_Player();
			m_tPlayerINFO = CObjMgr::Get_Instance()->Get_Player()->Get_Info();
			CSceneMgr::Get_Instance()->Scene_Change(SC_QUEST);

		}
		else
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOpen.wav", BUllET_EFFECT, g_fSound);
			m_bQuest_Out = true;
			CMenuObjMgr::Get_Instance()->Save_Quest();
			CMenuObjMgr::Get_Instance()->Destroy_Instance();
			CSceneMgr::Get_Instance()->Scene_Change(m_eInvenPreScene);

		}
	}

 	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();

	
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete<CScene*>(m_pScene);
}

