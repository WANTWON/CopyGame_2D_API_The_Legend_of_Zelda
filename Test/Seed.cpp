#include "stdafx.h"
#include "Seed.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "BlockMgr.h"

CSeed::CSeed() : m_dwTime(GetTickCount()), m_bCount(false)
{
}


CSeed::~CSeed()
{
}

void CSeed::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX;
	m_tInfo.fCY = BLOCKCY;

	m_eBlockType = BLOCK_SEED;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_iOption = 0;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Seed.bmp", L"Seed");
	m_iOption = rand() % 3;
	m_pFrameKey = L"Seed";
}

int CSeed::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSeed::Late_Update(void)
{
	if (m_bEditorMode)
		return;

	if ((CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this)) && m_dwTime + 50 < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			if (!m_bCount)
			{
				CBlockMgr::Get_Instance()->Set_SeedSolved();
				m_bCount = true;
			}
		}
			
		m_dwTime = GetTickCount();
	}
}

void CSeed::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hTileDC,							// 비트맵을 가지고 있는 DC
		(16) * m_tFrame.iFrameStart,								// 비트맵 출력 시작 좌표, X,Y
		m_iOption * 16,
		16,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(128, 128, 128));			// 제거하고자 하는 색상
}

void CSeed::Release(void)
{
}
