#include "stdafx.h"
#include "Fire.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BlockMgr.h"

CFire::CFire() : m_bCount(false)
{
}


CFire::~CFire()
{
	Release();
}

void CFire::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX;
	m_tInfo.fCY = BLOCKCY;
	m_eGroup = RENDER_GAMEOBJECT;

	m_eBlockType = BLOCK_FIRE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwFrameSpeed = 70;
	m_iOption = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Fire.bmp", L"Block_Fire");

	m_pFrameKey = L"Block_Fire";
}

int CFire::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CFire::Late_Update(void)
{
	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);

	if (m_iOption == 1 && !m_bCount)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Fire.wav", SOUND_EFFECT, g_fSound);
		m_tFrame.iFrameEnd = 3;
		CBlockMgr::Get_Instance()->Set_BlockSolved();
		m_bCount = true;
	}
	Move_Frame();

}

void CFire::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hTileDC,							// 비트맵을 가지고 있는 DC
		(16) * m_tFrame.iFrameStart,								// 비트맵 출력 시작 좌표, X,Y
		16 * m_iOption,
		16,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(112, 216, 248));			// 제거하고자 하는 색상
}

void CFire::Release(void)
{
}
