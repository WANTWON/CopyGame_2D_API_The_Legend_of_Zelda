#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0), m_fScrollY(0)
{
}


CScrollMgr::~CScrollMgr()
{


	
}

void CScrollMgr::Scroll_Lock(void)
{
	SCENEID eScene = CSceneMgr::Get_Instance()->Get_CurScene();


	switch (eScene)
	{
	case SC_STAGE_FIELD:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - 2500 > m_fScrollX)
			m_fScrollX = WINCX - 2500;


		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 1706 > m_fScrollY)
			m_fScrollY = WINCY - 1706;
		break;

	case SC_STAGE_BOSS:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - 800 > m_fScrollX)
			m_fScrollX = WINCX - 800;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - WINCY > m_fScrollY)
			m_fScrollY = WINCY - WINCY;
		break;

	case SC_STAGE_ENDING:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - 800 > m_fScrollX)
			m_fScrollX = WINCX - 800;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 1040 > m_fScrollY)
			m_fScrollY = WINCY - 1040;
		break;

	case SC_STAGE_DUNGEON:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - 1500 > m_fScrollX)
			m_fScrollX = WINCX - 1500;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 3611 > m_fScrollY)
			m_fScrollY = WINCY - 3611;
		break;

	case SC_STAGE_STORE:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - 1500 > m_fScrollX)
			m_fScrollX = WINCX - 1500;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 922 > m_fScrollY)
			m_fScrollY = WINCY - 922;
		break;

	case SC_STAGE_STOREROOM:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 613 > m_fScrollY)
			m_fScrollY = WINCY - 613;
		break;

	case SC_MINIROAD:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 2200 > m_fScrollY)
			m_fScrollY = WINCY - 2200;
		break;

	case SC_MINIWORLD:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - 1500 > m_fScrollX)
			m_fScrollX = WINCX - 1500;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 1464 > m_fScrollY)
			m_fScrollY = WINCY - 1464;
		break;

	case SC_STAGE_SHOESTORE:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 600 > m_fScrollY)
			m_fScrollY = WINCY - 600;
		break;

	case SC_SHOE_MINIGAME:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 600 > m_fScrollY)
			m_fScrollY = WINCY - 600;
		break;
	case SC_MINIROOM:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 600 > m_fScrollY)
			m_fScrollY = WINCY - 600;
		break;


	case SC_MINIROOM2:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 600 > m_fScrollY)
			m_fScrollY = WINCY - 600;
		break;

	case SC_MINIROOM3:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 600 > m_fScrollY)
			m_fScrollY = WINCY - 600;
		break;

	case SC_MINICHIEF:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 600 > m_fScrollY)
			m_fScrollY = WINCY - 600;
		break;
	case SC_MINIWOOD:
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (WINCX - WINCX > m_fScrollX)
			m_fScrollX = WINCX - WINCX;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (WINCY - 825 > m_fScrollY)
			m_fScrollY = WINCY - 825;
		break;


	default:
		break;
	}
	
}
