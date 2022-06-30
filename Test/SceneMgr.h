#pragma once

#include "Logo.h"
#include "MyMenu.h"
#include "MyEdit.h"
#include "Stage.h"
#include "EditMenu.h"
#include "BossStage.h"
#include "EndingStage.h"
#include "EndingLogo.h"
#include "Dungeon.h"
#include "Inventory.h"
#include "Store.h"
#include "StoreRoom.h"
#include "MiniRoad.h"
#include "MiniWorld.h"
#include "ShoeStore.h"
#include "ShoeMiniGame.h"
#include "MiniRoom.h"
#include "MiniRoom2.h"
#include "MiniRoom3.h"
#include "MiniWood.h"
#include "MiniChief.h"
#include "Quest.h"
#include "MiniGame.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eScene, SCENEID StageNum = SC_STAGE_FIELD);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	const SCENEID& Get_CurScene(void) const { return m_eCurScene; }
	const SCENEID& Get_PreScene(void) const { return m_ePreScene; }
	const INFO& Get_PlayerPos(void) const { return m_tPlayerINFO; }
	const bool& Get_InvenOut(void) const { return m_bInven_Out; }
	const bool& Get_QuestOut(void) const { return m_bQuest_Out; }
	const bool& Get_MiniWorld(void) const { return m_bMiniWorldIn; }
	const bool& Get_bCount(void) const { return m_bCount; }
	const bool& Get_bQuestCount(void) const { return m_bQuestCount; }
	const bool& Get_bShoseMake(void) const { return m_bShoesMake; }
	const bool& Get_bPlayWith(void) const { return m_bPlayWith; }
	const WEAPONID& Get_PlayerWeapon(void) const { return m_ePlayerWeapon; }
	const WEAPONID& Get_PlayerSecondWeapon(void) const { return m_ePlayerSecondWeapon; }
	const bool& Get_First_Start(void) const { return m_bFirst; }
	

	void Set_InvenOut(bool type) { m_bInven_Out = type; }
	void Set_QuestOut(bool type) { m_bQuest_Out = type; }
	void Set_MiniWorld(bool type) { m_bMiniWorldIn = type; }
	void Set_bCount(bool type) { m_bCount = type; }
	void Set_bQuestCount(bool type) { m_bQuestCount = type; }
	void Set_PlayerWeapon(WEAPONID type) { m_ePlayerWeapon = type; }
	void Set_PlayerWWeapon(WEAPONID type) { m_ePlayerSecondWeapon = type; }
	void Set_First_Start(bool type) { m_bFirst = type; }
	void Set_ShoesMake(bool type) { m_bShoesMake = type; }
	void Set_PlayWith(bool type) { m_bPlayWith = type; }
	void Set_SolvedQuestNumber(void) { m_iSolvedQuestNumber++; }

	const int& Get_SolvedQuestNumber(void) const { return m_iSolvedQuestNumber; }

public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static		CSceneMgr*		m_pInstance;
	CScene*						m_pScene;

	SCENEID						m_ePreScene;
	SCENEID						m_eCurScene;
	SCENEID						m_eInvenPreScene;

	INFO						m_tPlayerINFO;
	WEAPONID					m_ePlayerWeapon;
	WEAPONID					m_ePlayerSecondWeapon;

	bool	m_bInven_Out;
	bool	m_bQuest_Out;
	bool	m_bMiniWorldIn;

	bool	m_bCount;
	bool	m_bQuestCount;
	bool	m_bFirst;
	bool    m_bShoesMake;
	bool    m_bPlayWith;
	int m_iSolvedQuestNumber;
};

