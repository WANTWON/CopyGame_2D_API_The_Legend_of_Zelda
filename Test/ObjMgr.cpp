#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Monster.h"
#include "SnakeMonster.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "BossMonster.h"
#include "OctopusMonster.h"
#include "Player.h"
#include "MoblinMonster.h"
#include "RockMonster.h"
#include "BlockMgr.h"

CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr() : m_bEditorMode(false)
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(iter->Get_Info().fX - pObj->Get_Info().fX);
		float	fHeight = abs(iter->Get_Info().fY - pObj->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (!pTarget || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);

	if (OBJ_BULLET != eID)
		m_ObjList[eID].back()->Set_ID(eID);
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

int CObjMgr::Update(void)
{
	int	iEvent = 0;

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (i == 9)
			break;

		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return iEvent;
}

void CObjMgr::Late_Update(void)
{
	if (m_bEditorMode)
	{
		for (size_t i = 0; i != OBJ_END; ++i)
		{
			for (auto& iter : m_ObjList[i])
			{
				iter->Set_EditorMode(true);

				if (m_ObjList[i].empty())
					break;
			}
		}
	}

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (i == OBJ_BLOCK)
		{
			for (auto& iter : m_ObjList[OBJ_BLOCK])
			{
				RENDERID eID = iter->Get_RenderID();
				m_RenderSort[eID].push_back(iter);

			}
			break;
		}
			

		for (auto& iter : m_ObjList[i])
		{
			
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID eID = iter->Get_RenderID();
			m_RenderSort[eID].push_back(iter);

		}
	}

}

void CObjMgr::Render(HDC hDC)
{
	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) -100;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) -100;

	int	iCullCX = iMoveX + WINCX + 100;
	int	iCullCY = iMoveY + WINCY + 100;

	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
		{
			if (iter->Get_Info().fX < iCullCX && iter->Get_Info().fY < iCullCY &&
				iter->Get_Info().fX > iMoveX && iter->Get_Info().fY > iMoveY)
				iter->Render(hDC);
		}

		m_RenderSort[i].clear();
	}


	/*for (size_t i = 0; i < OBJ_END; ++i)
	{
	for (auto& iter : m_ObjList[i])
	{
	if (iter->Get_Info().fX < iCullCX && iter->Get_Info().fY < iCullCY &&
	iter->Get_Info().fX > iMoveX && iter->Get_Info().fY > iMoveY)
	iter->Render(hDC);
	}

	}*/

}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (i == 9)
			break;
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_Obj(POINT & _pt, int _iDrawID, int _iOption)
{
	int iX = _pt.x - (_pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
	int iY = _pt.y - (_pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (!m_ObjList[i].empty())
		{
			for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
			{
				if ((*iter)->Get_Info().fX == iX && (*iter)->Get_Info().fY == iY)
				{
					iter = m_ObjList[i].erase(iter);
				}
				else
					++iter;
			}
		}
	}


}

void CObjMgr::Save_Monster(SCENEID eStage)
{

	HANDLE hFile = nullptr;

	switch (eStage)
	{
	case SC_STAGE_FIELD:
		hFile = CreateFile(L"../Data/Field/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_BOSS:
		hFile = CreateFile(L"../Data/Boss/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_ENDING:
		hFile = CreateFile(L"../Data/Ending/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_DUNGEON:
		hFile = CreateFile(L"../Data/Dungeon/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STORE:
		hFile = CreateFile(L"../Data/Store/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STOREROOM:
		hFile = CreateFile(L"../Data/StoreRoom/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROAD:
		hFile = CreateFile(L"../Data/MiniRoad/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWORLD:
		hFile = CreateFile(L"../Data/MiniWorld/Monster.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	default:
		break;
	}


	if (INVALID_HANDLE_VALUE == hFile)
		return;


	DWORD dwByte = 0;
	MONSTERID eMonsterID = MONSTER_END;

	for (auto& iter : m_ObjList[OBJ_MONSTER])
	{
		eMonsterID = static_cast<CMonster*>(iter)->Get_MonsterType();

		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &eMonsterID, sizeof(MONSTERID), &dwByte, nullptr);
	}

	CloseHandle(hFile);
}

void CObjMgr::Load_Monster(SCENEID eStage)
{

	HANDLE hFile = nullptr;

	switch (eStage)
	{
	case SC_STAGE_FIELD:
		hFile = CreateFile(L"../Data/Field/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_BOSS:
		hFile = CreateFile(L"../Data/Boss/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_ENDING:
		hFile = CreateFile(L"../Data/Ending/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_DUNGEON:
		hFile = CreateFile(L"../Data/Dungeon/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STORE:
		hFile = CreateFile(L"../Data/Store/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STOREROOM:
		hFile = CreateFile(L"../Data/StoreRoom/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROAD:
		hFile = CreateFile(L"../Data/MiniRoad/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWORLD:
		hFile = CreateFile(L"../Data/MiniWorld/Monster.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	default:
		break;
	}


	if (INVALID_HANDLE_VALUE == hFile)
		return;

	INFO	tInfo{};

	DWORD dwByte = 0;
	MONSTERID eMonsterID = MONSTER_END;

	for_each(m_ObjList[OBJ_MONSTER].begin(), m_ObjList[OBJ_MONSTER].end(), CDeleteObj());
	m_ObjList[OBJ_MONSTER].clear();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &eMonsterID, sizeof(MONSTERID), &dwByte, nullptr);

		if (0 == dwByte)
			break;


		CObj* pMonster = nullptr;
		switch (eMonsterID)
		{
		case SNAKE_MONSTER:
			pMonster = CAbstractFactory<CSnakeMonster>::Create(tInfo.fX, tInfo.fY, OBJ_MONSTER);
			break;
		case OCTOPUS_MONSTER:
			pMonster = CAbstractFactory<COctopusMonster>::Create(tInfo.fX, tInfo.fY, OBJ_MONSTER);
			break;
		case BOSS_MONSTER:
			pMonster = CAbstractFactory<CBossMonster>::Create(tInfo.fX, tInfo.fY, OBJ_MONSTER);
			break;
		case MOBLIN_MONSTER:
			pMonster = CAbstractFactory<CMoblinMonster>::Create(tInfo.fX, tInfo.fY, OBJ_MONSTER);
			break;
		case ROCK_MONSTER:
			pMonster = CAbstractFactory<CRockMonster>::Create(tInfo.fX, tInfo.fY, OBJ_MONSTER);
		default:
			break;
		}
		Add_Object(OBJ_MONSTER, pMonster);
	}
	CloseHandle(hFile);
}

void CObjMgr::Save_Player(void)
{
	HANDLE hFile = CreateFile(L"../Data/Player.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;


	DWORD dwByte = 0;
	PLAYERINFO tInfo = {};
	WEAPONID WeaponType = WEAPON_END;
	WEAPONID Second_WeaponType = WEAPON_END;

	tInfo.tInfo = m_ObjList[OBJ_PLAYER].front()->Get_Info(); 
	tInfo.iHp = m_ObjList[OBJ_PLAYER].front()->Get_Hp();
	tInfo.iMaxHp = m_ObjList[OBJ_PLAYER].front()->Get_MaxHp();
	tInfo.iCoin = m_ObjList[OBJ_PLAYER].front()->Get_Coin();
	tInfo.iKey = m_ObjList[OBJ_PLAYER].front()->Get_Key();
	WeaponType = static_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_WeaponType();
	Second_WeaponType = static_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Get_Second_WeaponType();

	WriteFile(hFile, &tInfo, sizeof(PLAYERINFO), &dwByte, nullptr);
	WriteFile(hFile, &WeaponType, sizeof(WEAPONID), &dwByte, nullptr);
	WriteFile(hFile, &Second_WeaponType, sizeof(WEAPONID), &dwByte, nullptr);
		
	CloseHandle(hFile);
}

void CObjMgr::Load_Player(void)
{
	HANDLE hFile = CreateFile(L"../Data/Player.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	DWORD dwByte = 0;
	PLAYERINFO tInfo = {};
	WEAPONID WeaponType = WEAPON_END;
	WEAPONID Second_WeaponType = WEAPON_END;

	for_each(m_ObjList[OBJ_PLAYER].begin(), m_ObjList[OBJ_PLAYER].end(), CDeleteObj());
	m_ObjList[OBJ_PLAYER].clear();

	ReadFile(hFile, &tInfo, sizeof(PLAYERINFO), &dwByte, nullptr);
	ReadFile(hFile, &WeaponType, sizeof(WEAPONID), &dwByte, nullptr);
	ReadFile(hFile, &Second_WeaponType, sizeof(WEAPONID), &dwByte, nullptr);

	CObj* pPlayer = CAbstractFactory<CPlayer>::Create();
	pPlayer->Load_Coin(tInfo.iCoin);
	pPlayer->Load_Hp(tInfo.iHp);
	pPlayer->Load_MaxHp(tInfo.iMaxHp);
	pPlayer->Load_Key(tInfo.iKey);
	static_cast<CPlayer*>(pPlayer)->Set_WeaponType(WeaponType);
	static_cast<CPlayer*>(pPlayer)->Set_Second_WeaponType(Second_WeaponType);
	Add_Object(OBJ_PLAYER, pPlayer);
	
	CloseHandle(hFile);
}
