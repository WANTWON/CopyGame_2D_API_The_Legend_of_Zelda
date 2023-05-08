#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "Tile.h"
#include "ScrollMgr.h"

CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr() : m_bChangeTileID(false), m_bCreated(false), m_iTileID(0), m_bEditMode(false), m_iSolvedTile(0)
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize(void)
{

}

void CTileMgr::Add_Tiles(TILEID eID, CObj* pObj)
{
	if (eID >= TILE_END || nullptr == pObj)
		return;

	m_vecTile[eID].push_back(pObj);
}

void CTileMgr::Update(void)
{
	for (size_t i = 0; i < TILE_END; ++i)
	{
		if (m_vecTile[i].empty())
			continue;

		for (auto& iter : m_vecTile[i])
			iter->Update();
	}
}

void CTileMgr::Late_Update(void)
{
	if (m_bEditMode)
		return;


	for (size_t i = 0; i < TILE_END; ++i)
	{
		if (m_vecTile[i].empty())
			continue;

		for (auto& iter : m_vecTile[i])
			iter->Late_Update();
	}
}

void CTileMgr::Render(HDC hDC)
{


	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY());

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;


	if (m_bEditMode)
	{
		for (size_t i = 0; i < TILE_END; ++i)
		{
			for (auto& iter : m_vecTile[i])
			{
				if (m_vecTile[i].empty())
					continue;

				if (iter->Get_Info().fX <= iCullCX && iter->Get_Info().fY <= iCullCY &&
					iter->Get_Info().fX >= iMoveX && iter->Get_Info().fY >= iMoveY)
					iter->Render(hDC);
			}
		}
	}
	else
	{
		for (size_t i = TILE_SWITCH; i < TILE_END; ++i)
		{
			for (auto& iter : m_vecTile[i])
			{
				if (m_vecTile[i].empty())
					continue;

				if (iter->Get_Info().fX <= iCullCX && iter->Get_Info().fY <= iCullCY &&
					iter->Get_Info().fX >= iMoveX && iter->Get_Info().fY >= iMoveY)
					iter->Render(hDC);
			}
		}
	}

}

void CTileMgr::Release(void)
{
	for (size_t i = 0; i < TILE_END; ++i)
	{
		if (m_vecTile[i].empty())
			return;

		for_each(m_vecTile[i].begin(), m_vecTile[i].end(), CDeleteObj());
		m_vecTile[i].clear();
	}
}

void CTileMgr::Picking_Tile(POINT& _pt, int _iDrawID, int _iOption, TILEID type = TILE_EDIT)
{

	int iX = int(_pt.x - (_pt.x % (TILECX)) + TILECX*0.5f);
	int iY = int(_pt.y - (_pt.y % (TILECY)) + TILECY*0.5f);

	for (size_t i = 0; i < TILE_END; ++i)
	{
		if (!m_vecTile[i].empty())
		{
			for (auto& iter : m_vecTile[i])
			{
				if (iter->Get_Info().fX == iX && iter->Get_Info().fY == iY) //타일 리스트중 해당 좌표에 타일이 있으면 
					m_bCreated = true;	//만들어져 있음 true
			}
		}
	}

	if (!m_bCreated) //만들어져 있지 않으면
	{
		switch (type)
		{
		case TILE_EDIT:
		{
			CObj* pTile = CAbstractFactory<CTile>::Create(float(iX), float(iY));
			Add_Tiles(TILE_EDIT, pTile);
			break;
		}
		case TILE_SWITCH:
		{
			CObj* pTile = CAbstractFactory<CSwitchTile>::Create(float(iX), float(iY));
			Add_Tiles(TILE_SWITCH, pTile);
			break;
		}
		default:
			break;
		}

	}

	m_bCreated = false;

}

void CTileMgr::Change_Tile(POINT & _pt, int _iDrawID, int _iOption)
{
	int iX = int(_pt.x - (_pt.x % (TILECX)) + TILECX*0.5f);
	int iY = int(_pt.y - (_pt.y % (TILECY)) + TILECY*0.5f);

	for (size_t i = 0; i < TILE_END; ++i)
	{
		if (!m_vecTile[i].empty())
		{
			for (auto& iter : m_vecTile[i])
			{
				if (iter->Get_Info().fX == iX && iter->Get_Info().fY == iY)
				{
					dynamic_cast<CTile*>(iter)->Change_DrawID();
					dynamic_cast<CTile*>(iter)->Change_Option();
					m_bChangeTileID = true;
				}
			}
		}
	}
	if (!m_bChangeTileID)
	{
		CObj* pTile = CAbstractFactory<CTile>::Create(float(iX), float(iY));
		Add_Tiles(TILE_EDIT, pTile);
	}

	m_bChangeTileID = false;
}

void CTileMgr::Delete_Tile(POINT & _pt, int _iDrawID, int _iOption)
{
	int iX = int(_pt.x - (_pt.x % (TILECX)) + TILECX*0.5f);
	int iY = int(_pt.y - (_pt.y % (TILECY)) + TILECY*0.5f);


	for (size_t i = 0; i < TILE_END; ++i)
	{
		if (!m_vecTile[i].empty())
		{
			for (auto& iter = m_vecTile[i].begin(); iter < m_vecTile[i].end();)
			{
				if ((*iter)->Get_Info().fX == iX && (*iter)->Get_Info().fY == iY)
				{
					iter = m_vecTile[i].erase(iter);
				}
				else
					++iter;
			}
		}
	}


}

void CTileMgr::Save_Tile(SCENEID eStage)
{

	HANDLE hFile = nullptr;

	switch (eStage)
	{
	case SC_STAGE_FIELD:
		hFile = CreateFile(L"../Data/Field/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_BOSS:
		hFile = CreateFile(L"../Data/Boss/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_ENDING:
		hFile = CreateFile(L"../Data/Ending/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_DUNGEON:
		hFile = CreateFile(L"../Data/Dungeon/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STORE:
		hFile = CreateFile(L"../Data/Store/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STOREROOM:
		hFile = CreateFile(L"../Data/StoreRoom/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROAD:
		hFile = CreateFile(L"../Data/MiniRoad/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWORLD:
		hFile = CreateFile(L"../Data/MiniWorld/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_SHOESTORE:
		hFile = CreateFile(L"../Data/ShoeStore/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM:
		hFile = CreateFile(L"../Data/MiniRoom/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM2:
		hFile = CreateFile(L"../Data/MiniRoom2/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM3:
		hFile = CreateFile(L"../Data/MiniRoom3/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWOOD:
		hFile = CreateFile(L"../Data/MiniWood/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINICHIEF:
		hFile = CreateFile(L"../Data/MiniChief/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	default:
		break;
	}


	if (INVALID_HANDLE_VALUE == hFile)
		return;

	int iDrawID = 0, iOption = 0;
	DWORD dwByte = 0;
	TILEID Tiletype = TILE_END;

	for (size_t i = 0; i < TILE_END; ++i)
	{
		for (auto& iter : m_vecTile[i])
		{
			iDrawID = static_cast<CTile*>(iter)->Get_DrawID();
			iOption = static_cast<CTile*>(iter)->Get_Option();
			Tiletype = static_cast<CTile*>(iter)->Get_TileType();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &Tiletype, sizeof(TILEID), &dwByte, nullptr);
		}
	}
	CloseHandle(hFile);

}

void CTileMgr::Load_Tile(SCENEID eStage)
{
	HANDLE hFile = nullptr;
	switch (eStage)
	{
	case SC_STAGE_FIELD:
		hFile = CreateFile(L"../Data/Field/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_BOSS:
		hFile = CreateFile(L"../Data/Boss/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_ENDING:
		hFile = CreateFile(L"../Data/Ending/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_DUNGEON:
		hFile = CreateFile(L"../Data/Dungeon/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STORE:
		hFile = CreateFile(L"../Data/Store/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STOREROOM:
		hFile = CreateFile(L"../Data/StoreRoom/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROAD:
		hFile = CreateFile(L"../Data/MiniRoad/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWORLD:
		hFile = CreateFile(L"../Data/MiniWorld/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_SHOESTORE:
		hFile = CreateFile(L"../Data/ShoeStore/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM:
		hFile = CreateFile(L"../Data/MiniRoom/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWOOD:
		hFile = CreateFile(L"../Data/MiniWood/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM2:
		hFile = CreateFile(L"../Data/MiniRoom2/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM3:
		hFile = CreateFile(L"../Data/MiniRoom3/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINICHIEF:
		hFile = CreateFile(L"../Data/MiniChief/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	default:
		break;
	}


	if (INVALID_HANDLE_VALUE == hFile)
		return;

	INFO	tInfo{};
	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;
	TILEID Tiletype = TILE_EDIT;

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &Tiletype, sizeof(TILEID), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj*	pTile = nullptr;
		switch (Tiletype)
		{
		case TILE_EDIT:
		{
			pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
			static_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
			static_cast<CTile*>(pTile)->Set_Option(iOption);
			static_cast<CTile*>(pTile)->Set_Tieletype(Tiletype);
			break;
		}

		case TILE_SWITCH:
		{
			pTile = CAbstractFactory<CSwitchTile>::Create(tInfo.fX, tInfo.fY);
			static_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
			static_cast<CTile*>(pTile)->Set_Option(iOption);
			static_cast<CTile*>(pTile)->Set_Tieletype(Tiletype);
			break;
		}
		}


		Add_Tiles(Tiletype, pTile);
	}
	CloseHandle(hFile);


}


