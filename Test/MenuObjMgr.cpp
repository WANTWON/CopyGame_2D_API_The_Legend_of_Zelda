#include "stdafx.h"
#include "MenuObjMgr.h"
#include "ItemTile.h"
#include "ChoosePoint.h"
#include "AbstractFactory.h"
#include "QuestTile.h"
#include "SceneMgr.h"


CMenuObjMgr*		CMenuObjMgr::m_pInstance = nullptr;

CMenuObjMgr::CMenuObjMgr() 
{
	
}


CMenuObjMgr::~CMenuObjMgr()
{
	Release();
}


void CMenuObjMgr::Add_Object(MENUOBJID eID, CMenuObj * pObj)
{
	if (eID >= MENU_END || nullptr == pObj)
		return;

	m_MenuObjList[eID].push_back(pObj);

	m_MenuObjList[eID].back()->Set_ID(eID);
}

void CMenuObjMgr::Add_ItemTile(CMenuObj * pObj)
{
	m_pInvenVec.push_back(pObj);
}

void CMenuObjMgr::Add_QuestTile(CMenuObj * pObj)
{
	m_pQuestVec.push_back(pObj);
}

void CMenuObjMgr::Add_Weapon(WEAPONID eID,  bool Default)
{
	int i = 0;
	for (auto& iter : m_pInvenVec)
	{
		if (static_cast<CItemTile*>(iter)->Get_Exist() == false)
		{
			static_cast<CItemTile*>(iter)->Set_Exist(true);
			static_cast<CItemTile*>(iter)->Set_WeaponType(eID);

			if (Default)
				static_cast<CItemTile*>(iter)->Set_beUsed(true);
			
			return;
		}
		++i;
	}
}

void CMenuObjMgr::Add_Quest(QUESTID eID, bool Default)
{
	int i = 0;
	for (auto& iter : m_pQuestVec)
	{
		if (static_cast<CQuestTile*>(iter)->Get_Exist() == false)
		{
			static_cast<CQuestTile*>(iter)->Set_Exist(true);
			static_cast<CQuestTile*>(iter)->Set_QuestType(eID);
			return;
		}
		++i;
	}
}

void CMenuObjMgr::Set_QuestComplete(QUESTID type)
{
	for (auto& iter : m_pQuestVec)
	{
		if ( static_cast<CQuestTile*>(iter)->Get_Questtype() == type)
		{
			static_cast<CQuestTile*>(iter)->Set_DrawID(1);
			return;
		}
	}
}

void CMenuObjMgr::Delete_ID(MENUOBJID eID)
{
	for (auto& iter : m_MenuObjList[eID])
		Safe_Delete(iter);

	m_MenuObjList[eID].clear();
}

void CMenuObjMgr::Delete_Quest(void)
{
	for (size_t i = 0; i < m_pQuestVec.size(); ++i)
	{
		Safe_Delete<CMenuObj*>(m_pQuestVec[i]);
	}
	m_pQuestVec.clear();
}

void CMenuObjMgr::Initialize(void)
{
	for (size_t i = 0; i != MENU_END; ++i)
	{
		for (auto& iter : m_MenuObjList[i])
		{
			iter->Initialize();

			if (m_MenuObjList[i].empty())
				break;
		}
	}

	for (size_t i = 0; i < m_pInvenVec.size(); ++i)
	{
		m_pInvenVec[i]->Initialize();
	}
	for (size_t i = 0; i < m_pQuestVec.size(); ++i)
	{
		m_pQuestVec[i]->Initialize();
	}
}

int CMenuObjMgr::Update(void)
{
	int	iEvent = 0;

	for (size_t i = 0; i < MENU_END; ++i)
	{
		for (auto& iter = m_MenuObjList[i].begin();
			iter != m_MenuObjList[i].end();)
		{
			iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CMenuObj*>(*iter);
				iter = m_MenuObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	for (size_t i = 0; i < m_pInvenVec.size(); ++i)
	{
		m_pInvenVec[i]->Update();
	}
	for (size_t i = 0; i < m_pQuestVec.size(); ++i)
	{
		m_pQuestVec[i]->Update();
	}

	return iEvent;
}

void CMenuObjMgr::Late_Update(void)
{
	for (size_t i = 0; i != MENU_END; ++i)
	{
		for (auto& iter : m_MenuObjList[i])
		{
			iter->Late_Update();

			if (m_MenuObjList[i].empty())
				break;
		}
	}

	for (size_t i = 0; i < m_pInvenVec.size(); ++i)
	{
		m_pInvenVec[i]->Late_Update();
	}
	for (size_t i = 0; i < m_pQuestVec.size(); ++i)
	{
		m_pQuestVec[i]->Late_Update();
	}
}

void CMenuObjMgr::Render(HDC hDC)
{
	if (CSceneMgr::Get_Instance()->Get_CurScene() == SC_INVEN)
	{
		for (size_t i = 0; i < m_pInvenVec.size(); ++i)
		{
			m_pInvenVec[i]->Render(hDC);
		}

		for (size_t i = 0; i < MENU_END; ++i)
		{
			for (auto& iter : m_MenuObjList[i])
			{
				iter->Render(hDC);
			}

		}
	}
	else

	for (size_t i = 0; i < m_pQuestVec.size(); ++i)
	{
		m_pQuestVec[i]->Render(hDC);
	}

	
}

void CMenuObjMgr::Release(void)
{
	for (size_t i = 0; i < MENU_END; ++i)
	{
		for (auto& iter : m_MenuObjList[i])
			Safe_Delete<CMenuObj*>(iter);

		m_MenuObjList[i].clear();
	}

	for (size_t i = 0; i < m_pInvenVec.size(); ++i)
	{
		Safe_Delete<CMenuObj*>(m_pInvenVec[i]);

	}

	m_pInvenVec.clear();


	for (size_t i = 0; i < m_pQuestVec.size(); ++i)
	{
		Safe_Delete<CMenuObj*>(m_pQuestVec[i]);
	}
	m_pQuestVec.clear();
}

void CMenuObjMgr::Save_Weapon(void)
{
	HANDLE hFile = CreateFile(L"../Data/Weapon.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	


	if (INVALID_HANDLE_VALUE == hFile)
		return;


	DWORD dwByte = 0;
	INFO m_tInfo;
	bool  m_bExist;
	bool m_bBeUsed;
	int m_DrawID;


	WEAPONID m_WeaponType = WEAPON_END;

	for (auto& iter = m_pInvenVec.begin(); iter < m_pInvenVec.end() ;  ++iter)
	{
		m_tInfo = (*iter)->Get_Info();
		m_bExist = static_cast<CItemTile*>(*iter)->Get_Exist();
		m_bBeUsed = static_cast<CItemTile*>(*iter)->Get_Used();
		m_WeaponType = static_cast<CItemTile*>(*iter)->Get_Weapontype();
		m_DrawID = static_cast<CItemTile*>(*iter)->Get_DrawID();

		WriteFile(hFile, &((*iter)->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(m_bExist), sizeof(bool), &dwByte, nullptr);
		WriteFile(hFile, &(m_bBeUsed), sizeof(bool), &dwByte, nullptr);
		WriteFile(hFile, &m_WeaponType, sizeof(WEAPONID), &dwByte, nullptr);
		WriteFile(hFile, &m_DrawID, sizeof(int), &dwByte, nullptr);
	}

	CloseHandle(hFile);

}

void CMenuObjMgr::Load_Weapon(void)
{
	HANDLE hFile =  CreateFile(L"../Data/Weapon.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;
	INFO	tInfo;
	bool  m_bExist;
	bool m_bBeUsed;
	int m_DrawID;

	WEAPONID m_WeaponType = WEAPON_END;

	for (size_t i = 0; i < m_pInvenVec.size(); ++i)
	{
		Safe_Delete<CMenuObj*>(m_pInvenVec[i]);

	}

	m_pInvenVec.clear();

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			CMenuObjMgr::Get_Instance()->Add_ItemTile((CAbstractFactory<CItemTile>::Create_Menu(220.f + (j * 120), 180.f+ (i * 80))));
		}

	}

	for (auto& iter : m_pInvenVec)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_bExist, sizeof(bool), &dwByte, nullptr);
		ReadFile(hFile, &m_bBeUsed, sizeof(bool), &dwByte, nullptr);
		ReadFile(hFile, &m_WeaponType, sizeof(WEAPONID), &dwByte, nullptr);
		ReadFile(hFile, &m_DrawID, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;


		//iter->Set_Pos(tInfo.fX, tInfo.fY);
		static_cast<CItemTile*>(iter)->Set_Exist(m_bExist);
		static_cast<CItemTile*>(iter)->Set_beUsed(m_bBeUsed);
		static_cast<CItemTile*>(iter)->Set_WeaponType(m_WeaponType);
		static_cast<CItemTile*>(iter)->Set_DrawID(m_DrawID);
		static_cast<CItemTile*>(iter)->Initialize();
	}
	
	CloseHandle(hFile);
}

void CMenuObjMgr::Save_Quest(void)
{
	HANDLE hFile = CreateFile(L"../Data/Quest.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);



	if (INVALID_HANDLE_VALUE == hFile)
		return;


	DWORD dwByte = 0;
	INFO m_tInfo;
	bool  m_bExist;
	int m_DrawID;

	QUESTID m_QuestType = QUEST_END;

	for (auto& iter = m_pQuestVec.begin(); iter < m_pQuestVec.end(); ++iter)
	{
		m_tInfo = (*iter)->Get_Info();
		m_bExist = static_cast<CQuestTile*>(*iter)->Get_Exist();;
		m_QuestType = static_cast<CQuestTile*>(*iter)->Get_Questtype();
		m_DrawID = static_cast<CQuestTile*>(*iter)->Get_DrawID();

		WriteFile(hFile, &((*iter)->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(m_bExist), sizeof(bool), &dwByte, nullptr);
		WriteFile(hFile, &m_QuestType, sizeof(QUESTID), &dwByte, nullptr);
		WriteFile(hFile, &m_DrawID, sizeof(int), &dwByte, nullptr);
	}

	CloseHandle(hFile);
}

void CMenuObjMgr::Load_Quest(void)
{
	HANDLE hFile = CreateFile(L"../Data/Quest.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;
	INFO	tInfo;
	bool  m_bExist;
	int m_DrawID;

	QUESTID m_QuestType = QUEST_END;

	for (size_t i = 0; i < m_pQuestVec.size(); ++i)
	{
		Safe_Delete<CMenuObj*>(m_pQuestVec[i]);

	}

	m_pQuestVec.clear();

	for (int i = 0; i < 3; ++i)
	{
		CMenuObjMgr::Get_Instance()->Add_QuestTile(CAbstractFactory<CQuestTile>::Create_Menu(400, 200 + (i * 112)));
	}

	for (auto& iter : m_pQuestVec)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_bExist, sizeof(bool), &dwByte, nullptr);
		ReadFile(hFile, &m_QuestType, sizeof(WEAPONID), &dwByte, nullptr);
		ReadFile(hFile, &m_DrawID, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;


		//iter->Set_Pos(tInfo.fX, tInfo.fY);
		static_cast<CQuestTile*>(iter)->Set_Exist(m_bExist);
		static_cast<CQuestTile*>(iter)->Set_QuestType(m_QuestType);
		static_cast<CQuestTile*>(iter)->Set_DrawID(m_DrawID);
		static_cast<CQuestTile*>(iter)->Initialize();
	}

	CloseHandle(hFile);
}

void CMenuObjMgr::Save_ChoosePoint(void)
{
	HANDLE hFile = CreateFile(L"../Data/ChoosePoint.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);



	if (INVALID_HANDLE_VALUE == hFile)
		return;


	DWORD dwByte = 0;
	int m_iIndex;
	int m_iUsedIndex;
	int m_iSecondUsedIndex;


	m_iIndex = static_cast<CChoosePoint*>(m_MenuObjList[MENU_CHOOSE].front())->Get_Index();
	m_iUsedIndex = static_cast<CChoosePoint*>(m_MenuObjList[MENU_CHOOSE].front())->Get_UsedIndex();
	m_iSecondUsedIndex = static_cast<CChoosePoint*>(m_MenuObjList[MENU_CHOOSE].front())->Get_WUsedIndex();
	

		
	WriteFile(hFile, &(m_iIndex), sizeof(int), &dwByte, nullptr);
	WriteFile(hFile, &(m_iUsedIndex), sizeof(int), &dwByte, nullptr);
	WriteFile(hFile, &(m_iSecondUsedIndex), sizeof(int), &dwByte, nullptr);

	CloseHandle(hFile);
}

void CMenuObjMgr::Load_ChoosePoint(void)
{
	int i = 0;
	HANDLE hFile = CreateFile(L"../Data/ChoosePoint.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	if (INVALID_HANDLE_VALUE == hFile)
		return;


	DWORD dwByte = 0;
	int m_iIndex;
	int m_iUsedIndex;
	int m_iSecondUsedIndex;

	
		
	ReadFile(hFile, &m_iIndex, sizeof(int), &dwByte, nullptr);
	ReadFile(hFile, &m_iUsedIndex, sizeof(int), &dwByte, nullptr);
	ReadFile(hFile, &m_iSecondUsedIndex, sizeof(int), &dwByte, nullptr);

	static_cast<CChoosePoint*>(CMenuObjMgr::Get_ChoosePos())->Set_Index(m_iIndex);
	static_cast<CChoosePoint*>(CMenuObjMgr::Get_ChoosePos())->Set_SecondIndex(m_iIndex);
	static_cast<CChoosePoint*>(CMenuObjMgr::Get_ChoosePos())->Set_UsedIndex(m_iUsedIndex);
	static_cast<CChoosePoint*>(CMenuObjMgr::Get_ChoosePos())->Set_SecondUsedIndex(m_iSecondUsedIndex);

	static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iSecondUsedIndex])->Set_beUsed(true);
	static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iSecondUsedIndex])->Set_WOption(true);
	//static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndex])->Set_beUsed(true);
	static_cast<CItemTile*>(CMenuObjMgr::Get_Instance()->Get_Inven()[m_iIndex])->Set_WOption(false);

	CloseHandle(hFile);
}


