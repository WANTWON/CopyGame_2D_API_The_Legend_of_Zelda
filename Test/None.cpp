#include "stdafx.h"
#include "None.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CNone::CNone() : m_bGet_Effect(false), m_dwTime(GetTickCount()), m_bCount(false)
{
}


CNone::~CNone()
{
}

void CNone::Initialize(void)
{
	m_eItemType = ITEM_NOTHING;
	m_tInfo.fCX = 25;
	m_tInfo.fCY = 30;
	m_eGroup = RENDER_PLAYERUPOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/TextBar_Nothing.bmp", L"TextBar_Nothing");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwFrameSpeed = 100;
}

int CNone::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Effect)
		Get_Effect();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CNone::Late_Update(void)
{
	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this))
		m_bGet_Effect = true;
}

void CNone::Render(HDC hDC)
{
	if (m_bCount)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBar_Nothing");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			150,	// 2,3 인자 :  복사받을 위치 X, Y
			500,
			500,				// 4,5 인자 : 복사받을 가로, 세로 길이
			50,
			hTextDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			600,				// 복사할 비트맵의 가로, 세로 길이
			61,
			RGB(192, 192, 255));			// 제거하고자 하는 색상
	}
}

void CNone::Release(void)
{
}

void CNone::Get_Effect(void)
{
	if (!m_bCount)
	{
		m_dwTime = GetTickCount();
		m_bCount = true;
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::EFFECT);
		m_tInfo.fY -= 15;
	}

	if (m_dwTime + 3000 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", ITEM_EFFECT, g_fSound);
		m_bDead = true;

		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::IDLE);
	}
}
