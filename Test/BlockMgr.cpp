#include "stdafx.h"
#include "BlockMgr.h"
#include "AbstractFactory.h"
#include "Block.h"
#include "ScrollMgr.h"
#include "Grass.h"
#include "Jar.h"
#include "ObjMgr.h"
#include "Player.h"
#include "TreasureChest.h"
#include "Mushroom.h"
#include "Fire.h"
#include "Wood.h"

CBlockMgr*	CBlockMgr::m_pInstance = nullptr;

CBlockMgr::CBlockMgr() : m_bChangeTileID(false), m_bCreated(false), m_iTileID(0), m_EditorMode(false), m_iBlockSolved(0), m_iSeedSolved(0)
{
	
}


CBlockMgr::~CBlockMgr()
{
	Release();
}

void CBlockMgr::Initialize(void)
{

}

void CBlockMgr::Update(void)
{
	int iEvent = 0;

	if (m_BlockList.empty())
		return;


	for (auto& iter = m_BlockList.begin(); iter != m_BlockList.end();)
	{
		iEvent = (*iter)->Update();

		if (iEvent == OBJ_DEAD)
		{
			iter = m_BlockList.erase(iter);
		}
		else
			++iter;
	}
		
}

void CBlockMgr::Late_Update(void)
{
	if (m_BlockList.empty())
		return;


	if (m_EditorMode)
	{
		for (auto& iter : m_BlockList)
			iter->Set_EditorMode(true);
	}

	if (!m_EditorMode)
	{
		float fMin_Distance = 999.f;
		CObj* Target_Jar = nullptr;

		if (CPlayer::PICKUP == static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State())
		{
			for (auto& iter : CBlockMgr::Get_Instance()->Get_Blocks())
			{
				if (static_cast<CBlock*>(iter)->Get_BlockType() != BLOCK_JAR)
					continue;

				float fWidth = fabsf(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - iter->Get_Info().fX);
				float fHeight = fabsf(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - iter->Get_Info().fY);
				float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

				if (fMin_Distance >= fDiagonal)
				{
					fMin_Distance = fDiagonal;
					Target_Jar = iter;

				}
			}

			if(fMin_Distance <= 50)
				static_cast<CJar*>(Target_Jar)->Set_BePicked();
		}
	}
	

	for (auto& iter : m_BlockList)
		iter->Late_Update();

}

void CBlockMgr::Render(HDC hDC)
{
	if (m_BlockList.empty())
		return;

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) -2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) -2;

	int	iCullCX = iMoveX + WINCX +2;
	int	iCullCY = iMoveY + WINCY +2;


	for (auto& iter : m_BlockList)
	{
		if (static_cast<CBlock*>(iter)->Get_BlockType() == BLOCK_JAR)
			continue;

		if (iter->Get_Info().fX < iCullCX && iter->Get_Info().fY < iCullCY &&
			iter->Get_Info().fX > iMoveX && iter->Get_Info().fY > iMoveY)
			iter->Render(hDC);
	}
}

void CBlockMgr::JarRender(HDC hDC)
{
	if (m_BlockList.empty())
		return;

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;


	for (auto& iter : m_BlockList)
	{
		if (static_cast<CBlock*>(iter)->Get_BlockType() == BLOCK_JAR)
		{

			if (iter->Get_Info().fX < iCullCX && iter->Get_Info().fY < iCullCY &&
				iter->Get_Info().fX > iMoveX && iter->Get_Info().fY > iMoveY)
				iter->Render(hDC);
		}
	}
}

void CBlockMgr::Release(void)
{
	if (m_BlockList.empty())
		return;

	for_each(m_BlockList.begin(), m_BlockList.end(), CDeleteObj());
	m_BlockList.clear();
}

void CBlockMgr::Picking_Block(POINT& _pt, BLOCKID _iBlockCategory)
{

	int iX = _pt.x - (_pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
	int iY = _pt.y - (_pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

	if (!m_BlockList.empty())
	{
		for (auto& iter : m_BlockList)
		{
			if (iter->Get_Info().fX == iX && iter->Get_Info().fY == iY)
			{
				dynamic_cast<CBlock*>(iter)->Change_Option();
				m_bChangeTileID = true;
				m_bCreated = true;
			}
				
		}
	}

	if (!m_bCreated)
	{
		CObj* pBlock;
		switch (_iBlockCategory)
		{
		case BLOCK_GRASS:
			pBlock = CAbstractFactory<CGrass>::Create((float)iX, (float)iY, OBJ_BLOCK);
			static_cast<CBlock*>(pBlock)->Set_BlockType(BLOCK_GRASS);
			break;
		case BLOCK_JAR:
			pBlock = CAbstractFactory<CJar>::Create((float)iX, (float)iY, OBJ_BLOCK);
			static_cast<CBlock*>(pBlock)->Set_BlockType(BLOCK_JAR);
			pBlock->Set_EditorMode(true);
			break;
		case BLOCK_CHEST:
			pBlock = CAbstractFactory<CTreasureChest>::Create((float)iX, (float)iY, OBJ_BLOCK);
			static_cast<CBlock*>(pBlock)->Set_BlockType(BLOCK_CHEST);
			pBlock->Set_EditorMode(true);
			break;
		case BLOCK_MUSHROOM:
			pBlock = CAbstractFactory<CMushroom>::Create((float)iX, (float)iY, OBJ_BLOCK);
			static_cast<CBlock*>(pBlock)->Set_BlockType(BLOCK_MUSHROOM);
			pBlock->Set_EditorMode(true);
			break;

		case BLOCK_FIRE:
			pBlock = CAbstractFactory<CFire>::Create((float)iX, (float)iY, OBJ_BLOCK);
			static_cast<CBlock*>(pBlock)->Set_BlockType(BLOCK_FIRE);
			pBlock->Set_EditorMode(true);
			break;

		case BLOCK_WOOD:
			pBlock = CAbstractFactory<CWood>::Create((float)iX, (float)iY, OBJ_BLOCK);
			static_cast<CWood*>(pBlock)->Set_BlockType(BLOCK_WOOD);
			pBlock->Set_EditorMode(true);
			break;
		default:
			break;
		}

		m_BlockList.push_back(pBlock);

	}

	m_bCreated = false;
	m_bChangeTileID = false;

}

void CBlockMgr::Add_Object( CObj* pObj)
{
	m_BlockList.push_back(pObj);
}


void CBlockMgr::Delete_Block(POINT & _pt, int _iDrawID, int _iOption)
{
	int iX = _pt.x - (_pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
	int iY = _pt.y - (_pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

	if (!m_BlockList.empty())
	{
		for (auto& iter = m_BlockList.begin(); iter != m_BlockList.end();)
		{
			if ((*iter)->Get_Info().fX == iX && (*iter)->Get_Info().fY == iY)
			{
				iter = m_BlockList.erase(iter);
			}
			else
				++iter;
		}
	}


}

void CBlockMgr::Save_Block(SCENEID eStage)
{

	HANDLE hFile = nullptr;

	switch (eStage)
	{
	case SC_STAGE_FIELD:
		hFile = CreateFile(L"../Data/Field/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_BOSS:
		hFile = CreateFile(L"../Data/Boss/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_ENDING:
		hFile = CreateFile(L"../Data/Ending/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_DUNGEON:
		hFile = CreateFile(L"../Data/Dungeon/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STORE:
		hFile = CreateFile(L"../Data/Store/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STOREROOM:
		hFile = CreateFile(L"../Data/StoreRoom/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROAD:
		hFile = CreateFile(L"../Data/MiniRoad/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWORLD:
		hFile = CreateFile(L"../Data/MiniWorld/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_SHOESTORE:
		hFile = CreateFile(L"../Data/ShoeStore/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM:
		hFile = CreateFile(L"../Data/MiniRoom/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWOOD:
		hFile = CreateFile(L"../Data/MiniWood/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM2:
		hFile = CreateFile(L"../Data/MiniRoom2/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM3:
		hFile = CreateFile(L"../Data/MiniRoom3/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINICHIEF:
		hFile = CreateFile(L"../Data/MiniChief/Block.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	default:
		break;
	}


	if (INVALID_HANDLE_VALUE == hFile)
		return;

	
	DWORD dwByte = 0;
	int iDrawID = 0, iOption = 0;
	BLOCKID eBlockID = BLOCK_END;

	for (auto& iter : m_BlockList)
	{
		iDrawID = static_cast<CBlock*>(iter)->Get_DrawID();
		iOption = static_cast<CBlock*>(iter)->Get_Option();
		eBlockID = static_cast<CBlock*>(iter)->Get_BlockType();

		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &eBlockID, sizeof(BLOCKID), &dwByte, nullptr);
	}

	CloseHandle(hFile);

}

void CBlockMgr::Load_Block(SCENEID eStage)
{

	HANDLE hFile = nullptr;

	switch (eStage)
	{
	case SC_STAGE_FIELD:
		hFile = CreateFile(L"../Data/Field/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_BOSS:
		hFile = CreateFile(L"../Data/Boss/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_ENDING:
		hFile = CreateFile(L"../Data/Ending/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_DUNGEON:
		hFile = CreateFile(L"../Data/Dungeon/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STORE:
		hFile = CreateFile(L"../Data/Store/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_STOREROOM:
		hFile = CreateFile(L"../Data/StoreRoom/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROAD:
		hFile = CreateFile(L"../Data/MiniRoad/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWORLD:
		hFile = CreateFile(L"../Data/MiniWorld/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_STAGE_SHOESTORE:
		hFile = CreateFile(L"../Data/ShoeStore/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM:
		hFile = CreateFile(L"../Data/MiniRoom/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIWOOD:
		hFile = CreateFile(L"../Data/MiniWood/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM2:
		hFile = CreateFile(L"../Data/MiniRoom2/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINIROOM3:
		hFile = CreateFile(L"../Data/MiniRoom3/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	case SC_MINICHIEF:
		hFile = CreateFile(L"../Data/MiniChief/Block.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	default:
		break;
	}	

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	INFO	tInfo{};
	int		iDrawID = 0, iOption = 0;
	BLOCKID eBlockID = BLOCK_END;
	DWORD	dwByte = 0;

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &eBlockID, sizeof(BLOCKID), &dwByte, nullptr);

		if (0 == dwByte)
			break;


		CObj* pBlock = nullptr;
		switch (eBlockID)
		{
		case BLOCK_GRASS:
			pBlock = CAbstractFactory<CGrass>::Create(tInfo.fX, tInfo.fY, OBJ_BLOCK);
			break;
		case BLOCK_JAR:
			pBlock = CAbstractFactory<CJar>::Create(tInfo.fX, tInfo.fY, OBJ_BLOCK);
			break;
		case BLOCK_CHEST:
			pBlock = CAbstractFactory<CTreasureChest>::Create(tInfo.fX, tInfo.fY, OBJ_BLOCK);
			break;
		case BLOCK_MUSHROOM:
			pBlock = CAbstractFactory<CMushroom>::Create(tInfo.fX, tInfo.fY, OBJ_BLOCK);
			break;
		case BLOCK_FIRE:
			pBlock = CAbstractFactory<CFire>::Create(tInfo.fX, tInfo.fY, OBJ_BLOCK);
			break;
		case BLOCK_WOOD:
			pBlock = CAbstractFactory<CWood>::Create(tInfo.fX, tInfo.fY, OBJ_BLOCK);
			break;
		default:
			break;
		}
		
		static_cast<CBlock*>(pBlock)->Set_DrawID(iDrawID);
		static_cast<CBlock*>(pBlock)->Set_Option(iOption);
		static_cast<CBlock*>(pBlock)->Set_BlockType(eBlockID);

		m_BlockList.push_back(pBlock);
	}
	CloseHandle(hFile);


}


