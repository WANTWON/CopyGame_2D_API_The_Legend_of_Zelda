#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "BlockMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SwordBullet.h"
#include "WandBullet.h"
#include "ArrowBullet.h"
#include "BooBullet.h"
#include "Block.h"
#include "Mushroom.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ShieldBullet.h"
#include "KaguraBullet.h"
#include "FireBullet.h"

bool g_MiniMode = false;

CPlayer::CPlayer()
	: m_bJump(false), m_fTime(0.f), m_fJumpPower(0.f), m_ePreState(END), m_eCurState(IDLE), m_bRoll(false), m_eWeaponType(SWORD), m_eSecondWeaponType(WEAPON_END),
	m_bPick(false), m_bThrow(false), m_bCount(false), m_bBeAttacked(false), m_dwTime(GetTickCount()), m_bInvincible_mode(false),
	m_bPickWalk(false), m_bCanPick(false), m_bCanPull(false), m_bStop(false), m_bAttack(false), m_bBoomerang(false), m_bRidingMode(false),
	m_bShieldMode(false), m_iDrawID(0), m_bFallWater(false), m_dwWalkTime(GetTickCount()), m_bKAGURA(false), m_dwKaguraTime(GetTickCount())
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 40.f, 40.f };

	m_fSpeed = 5.f;
	m_fDistance = 100.f;
	m_fJumpPower = 15.f;
	m_eDir = DIR_DOWN;
	m_iHp = 20;
	m_iCoin = 1000;
	m_eGroup = RENDER_PLAYER;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LinkFront.bmp", L"LinkFront");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LinkLeft.bmp", L"LinkLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LinkRight.bmp", L"LinkRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LinkBack.bmp", L"LinkBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_FALL.bmp", L"Player_FALL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fire.bmp", L"Player_KAGURA");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DOWN/Player_PICKUP.bmp", L"Player_DOWN_PICKUP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DOWN/Player_FALLWATER.bmp", L"Player_DOWN_FALLWATER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/UP/Player_PICKUP.bmp", L"Player_UP_PICKUP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/UP/Player_FALLWATER.bmp", L"Player_UP_FALLWATER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LEFT/Player_PICKUP.bmp", L"Player_LEFT_PICKUP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LEFT/Player_FALLWATER.bmp", L"Player_LEFT_FALLWATER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RIGHT/Player_PICKUP.bmp", L"Player_RIGHT_PICKUP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RIGHT/Player_FALLWATER.bmp", L"Player_RIGHT_FALLWATER");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RIGHT/Player_PICKUP_WALK.bmp", L"Player_RIGHT_PICKUP_WALK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LEFT/Player_PICKUP_WALK.bmp", L"Player_LEFT_PICKUP_WALK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DOWN/Player_PICKUP_WALK.bmp", L"Player_DOWN_PICKUP_WALK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/UP/Player_PICKUP_WALK.bmp", L"Player_UP_PICKUP_WALK");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RIGHT/Player_PULL.bmp", L"Player_RIGHT_PULL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LEFT/Player_PULL.bmp", L"Player_LEFT_PULL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DOWN/Player_PULL.bmp", L"Player_DOWN_PULL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/UP/Player_PULL.bmp", L"Player_UP_PULL");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RIGHT/Player_FLY.bmp", L"Player_RIGHT_FLY");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LEFT/Player_FLY.bmp", L"Player_LEFT_FLY");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DOWN/Player_FLY.bmp", L"Player_DOWN_FLY");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/UP/Player_FLY.bmp", L"Player_UP_FLY");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RIGHT/Player_HIT.bmp", L"Player_RIGHT_HIT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LEFT/Player_HIT.bmp", L"Player_LEFT_HIT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DOWN/Player_HIT.bmp", L"Player_DOWN_HIT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/UP/Player_HIT.bmp", L"Player_UP_HIT");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_MiniChange.bmp", L"Player_MiniChange");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Effect.bmp", L"Player_Effect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Player_Mini.bmp", L"Player_Mini");

	m_pFrameKey = L"LinkFront";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fDistance = 0;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState == FALL_WATER || m_bFallWater)
		Falling_Water();
	else if (m_eCurState == FALLING)
		Falling();
	else if (m_eCurState == FLY)
		Flying();
	else if (m_eCurState != MINICHANGE && m_eCurState != EFFECT &&  m_eCurState !=  UPGRADE && m_eCurState != HIT)
		Key_Input();

	Offset();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (this == nullptr)
		return;

	if (m_eWeaponType != HORSE && m_eSecondWeaponType != HORSE)
		m_bRidingMode = false;

	if (m_bRidingMode)
		m_fSpeed = 10.f;
	else if (m_eCurState == MINIMODE)
		m_fSpeed = 3.f;
	else
		m_fSpeed = 5.f;


	Motion_Change();

	if (m_eCurState == MINIMODE)
	{
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tFrame.iMotion = 2;
			break;
		case DIR_UP:
			m_tFrame.iMotion = 6;
			break;
		case DIR_RIGHT:
			m_tFrame.iMotion = 4;
			break;
		case DIR_DOWN:
			m_tFrame.iMotion = 0;
			break;
		}

		if(m_bFallWater)
			m_tFrame.iMotion = 8;
	}

	if (m_eCurState == MINIMODE && m_bRoll)
	{
		m_tFrame.iFrameEnd = 4;
	}

	if (m_eCurState == PICKUP && !m_bPickWalk)
		PickUp_Move_Frame();
	else if (m_eCurState == THROW)
		Throw_Move_Frame();
	else if (m_bShieldMode || m_eCurState == EFFECT || m_eCurState == SKILL_READY || m_eCurState == UPGRADE || m_eCurState == SKILL_FIRE)
		Shield_Frame();
	else if (m_eCurState == MINICHANGE)
		MIniChange_Frame();
	else
		Move_Frame();

	if (CCollisionMgr::Collsion_Wood(CBlockMgr::Get_Instance()->Get_Blocks(), this) && (CKeyMgr::Get_Instance()->Key_Down('C')))
	{
		g_MiniMode = true;
		m_pFrameKey = L"Player_MiniChange";
		m_eCurState = MINICHANGE;
	}

	CCollisionMgr::Collsion_Tile(CTileMgr::Get_Instance()->Get_EditTiles(), this);

	if (!m_bShieldMode && m_eCurState != KAGURA)
		CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);

	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Monsters(), this))
	{
		if (!m_bShieldMode && m_eCurState != KAGURA)
			m_bBeAttacked = true;
	}

	if (m_eCurState != PICKUP && m_eCurState != THROW && m_eCurState != FLY)
		CCollisionMgr::Collsion_Block(CBlockMgr::Get_Instance()->Get_Blocks(), this);
	

	if (m_bBeAttacked && !m_bRidingMode )
	{
		if (!m_bInvincible_mode)
		{
			m_eCurState = HIT;

			switch (m_eDir)
			{
			case DIR_LEFT:
				m_pFrameKey = L"Player_LEFT_HIT";
				m_tInfo.fX += 5.f;
				break;
			case DIR_UP:
				m_pFrameKey = L"Player_UP_HIT";
				m_tInfo.fY += 5.f;
				break;
			case DIR_RIGHT:
				m_pFrameKey = L"Player_RIGHT_HIT";
				m_tInfo.fX -= 5.f;
				break;
			case DIR_DOWN:
				m_pFrameKey = L"Player_DOWN_HIT";
				m_tInfo.fY -= 5.f;
				break;
			}
		}
	
		

		if (!m_bCount)
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Link_Hit.wav", PLAYER_EFFECT, g_fSound);
			if(! m_bInvincible_mode)
				--m_iHp;
			m_dwTime = GetTickCount();
			m_bCount = true;
		}

		if (m_dwTime + 500 < GetTickCount())
		{
			m_bBeAttacked = false;
			m_eCurState = IDLE;
			m_bCount = false;
			m_dwTime = GetTickCount();
		}
	}


}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

//	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	if (PICKUP == m_eCurState || FALL_WATER == m_eCurState || THROW == m_eCurState
		|| PICKUPWALK == m_eCurState || FALLING == m_eCurState || PULL == m_eCurState || FLY == m_eCurState 
		|| MINICHANGE == m_eCurState || EFFECT == m_eCurState || HIT == m_eCurState)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 5,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 20,
			int(m_tInfo.fCX) + 10,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 20,
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (20 + 10),								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			20,				// 복사할 비트맵의 가로, 세로 길이
			25,
			RGB(244, 0, 244));			// 제거하고자 하는 색상
	}
	else if(m_eCurState == MINIMODE)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 25,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 50 ,
			int(m_tInfo.fCX) + 50,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY)  + 50,
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (20),								// 비트맵 출력 시작 좌표, X,Y
			(m_tFrame.iMotion + m_iDrawID) * (20),
			20,				// 복사할 비트맵의 가로, 세로 길이
			20,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 60,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 65,
			int(m_tInfo.fCX) + 120,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 115,
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (200),								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * 200,
			200,				// 복사할 비트맵의 가로, 세로 길이
			200,
			RGB(244, 0, 244));			// 제거하고자 하는 색상
	}

	if (m_eCurState == KAGURA)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_KAGURA");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 100,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 100,
			int(m_tInfo.fCX) + 200,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 200,
			hMemDC,							// 비트맵을 가지고 있는 DC
			150* m_tFrame.iFrameStart,								// 비트맵 출력 시작 좌표, X,Y
			0,
			150,				// 복사할 비트맵의 가로, 세로 길이
			150,
			RGB(255, 0, 255));			// 제거하고자 하는 색상
	}


	if (m_bInvincible_mode)
	{
		TCHAR sztPoints[32] = L"";
		swprintf_s(sztPoints, L"Invincible_mode");
		TextOut(hDC, 675, 580, sztPoints, lstrlen(sztPoints));
	}
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	if (m_eCurState == PICKUP || PICKUPWALK == m_eCurState)
	{
		PickUp_Motion();
		return;
	}

	if (m_bShieldMode && (CKeyMgr::Get_Instance()->Key_Down('Q') || CKeyMgr::Get_Instance()->Key_Down('W')))
	{
		m_bShieldMode = false;
		CObjMgr::Get_Instance()->Delete_ID(OBJ_SHIELD);
	}
	else if (m_bShieldMode)
	{
		return;
	}
		
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F11))
	{
		if (m_bInvincible_mode)
			m_bInvincible_mode = false;
		else
			m_bInvincible_mode = true;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		//if (CSceneMgr::Get_Instance()->Get_SolvedQuestNumber() < 3)
		//	return;

		if (m_eCurState == MINIMODE)
			return;

		KaguraAttack();
		
		m_eCurState = KAGURA;
		m_bAttack = true;

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{

			m_eDir = DIR_UP;
			m_tInfo.fY -= m_fSpeed;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{

			m_eDir = DIR_DOWN;
			m_tInfo.fY += m_fSpeed;
		}
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{

			m_eDir = DIR_RIGHT;
			m_tInfo.fX += m_fSpeed;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{

			m_eDir = DIR_LEFT;
			m_tInfo.fX -= m_fSpeed;
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{

		m_eDir = DIR_LEFT;
		m_tInfo.fX -= m_fSpeed;

		if (m_eCurState != MINIMODE)
		{
			m_pFrameKey = L"LinkLeft";
			m_eCurState = WALK;
			
		}

		if (m_dwWalkTime + 300 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"land.wav", PLAYER_EFFECT, g_fSound);
			m_dwWalkTime = GetTickCount();
		}
		

		if (CKeyMgr::Get_Instance()->Key_Pressing('R') || m_bRoll)
		{
			if (m_eCurState == MINIMODE)
			{
				m_iDrawID = 1;
				m_bRoll = true;
				m_tInfo.fX -= 1.f;

			}
			else
			{
				m_bRoll = true;
				m_tInfo.fX -= 1.f;
				m_eCurState = ROLL;
				m_iDrawID = 0;
			}
		}
	
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_eDir = DIR_RIGHT;
		m_tInfo.fX += m_fSpeed;
		
		if (m_eCurState != MINIMODE)
		{
			m_pFrameKey = L"LinkRight";
			m_eCurState = WALK;
		}
		if (m_dwWalkTime + 300 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"land.wav", PLAYER_EFFECT, g_fSound);
			m_dwWalkTime = GetTickCount();
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing('R') || m_bRoll)
		{
			if (m_eCurState == MINIMODE)
			{
				m_iDrawID = 1;
				m_bRoll = true;
				m_tInfo.fX += 1.f;
			}
			else
			{
				m_bRoll = true;
				m_tInfo.fX += 1.f;
				m_eCurState = ROLL;
				m_iDrawID = 0;
			}
			
		}
		

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{

		m_eDir = DIR_DOWN;
		m_tInfo.fY += m_fSpeed;

		if (m_eCurState != MINIMODE)
		{
			m_eCurState = WALK;
			m_pFrameKey = L"LinkFront";
		}
		if (m_dwWalkTime + 300 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"land.wav", PLAYER_EFFECT, g_fSound);
			m_dwWalkTime = GetTickCount();
		}


		if (CKeyMgr::Get_Instance()->Key_Pressing('R') || m_bRoll)
		{
			if (m_eCurState == MINIMODE)
			{
				m_iDrawID = 1;
				m_bRoll = true;
				m_tInfo.fY += 1.f;
			}
			else
			{
				m_bRoll = true;
				m_tInfo.fY += 1.f;
				m_eCurState = ROLL;
				m_iDrawID = 0;
			}
		}
		
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{

		m_eDir = DIR_UP;
		m_tInfo.fY -= m_fSpeed;

		if (m_eCurState != MINIMODE)
		{
			m_eCurState = WALK;
			m_pFrameKey = L"LinkBack";
		}
		if (m_dwWalkTime + 300 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"land.wav", PLAYER_EFFECT, g_fSound);
			m_dwWalkTime = GetTickCount();
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing('R') || m_bRoll)
		{
			if (m_eCurState == MINIMODE)
			{
				m_iDrawID = 1;
				m_bRoll = true;
				m_tInfo.fY -= 1.f;
			}
			else
			{
				m_bRoll = true;
				m_tInfo.fY -= 1.f;
				m_eCurState = ROLL;
				m_iDrawID = 0;
			}
			
		}
	
	}
	else if (CKeyMgr::Get_Instance()->Key_Up('A'))
	{
		//if (CSceneMgr::Get_Instance()->Get_SolvedQuestNumber() < 3)
			//return;

		if (m_eCurState == MINIMODE)
			return;
		Thunder_Skill_Attack();
		m_eCurState = SKILL_GO;
		m_bAttack = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		//if (CSceneMgr::Get_Instance()->Get_SolvedQuestNumber() < 3)
			//return;

		if (m_eCurState == MINIMODE)
			return;
		CSoundMgr::Get_Instance()->PlaySound(L"ThunderOn.wav", BUllET_EFFECT, g_fSound - 0.3f);
		m_eCurState = SKILL_READY;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		//if (CSceneMgr::Get_Instance()->Get_SolvedQuestNumber() < 3)
			//return;

		if (m_eCurState == MINIMODE)
			return;
		CSoundMgr::Get_Instance()->PlaySound(L"Boom.wav", BUllET_EFFECT, g_fSound - 0.3f);
		m_eCurState = SKILL_FIRE;
		Fire_Attack();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Q')) //공격
	{
		if (m_eCurState == MINIMODE)
			return;

		m_eCurState = Q_ATTACK;
		m_bAttack = true;

		switch (m_eWeaponType)
		{
		case SWORD:
			Sword_Attack();
			break;
		case WAND:
			Wand_Attack();
			break;
		case ARROW:
			Arrow_Attack();
			break;
		case SHIELD:
			Shield_Attack();
			break;
		case LANTON:
			Lanton_Attack();
			break;
		case BOOMERANG:
			if (m_bBoomerang)
				return;
			Boo_Attack();
			break;
		case HORSE:
			if(m_bRidingMode)
				m_bRidingMode = false;
			else
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Horse.wav", BUllET_EFFECT, g_fSound);
				m_bRidingMode = true;
			}
				

			break;
		default:
			break;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('W')) //공격
	{
		if (m_eCurState == MINIMODE)
			return;

		m_eCurState = W_ATTACK;
		m_bAttack = true;

		switch (m_eSecondWeaponType)
		{
		case SWORD:
			Sword_Attack();
			break;
		case WAND:
			Wand_Attack();
			break;
		case ARROW:
			Arrow_Attack();
			break;
		case SHIELD:
			
			Shield_Attack();
			break;
		case LANTON:
			Lanton_Attack();
			break;
		case BOOMERANG:
			if (m_bBoomerang)
				return;
			Boo_Attack();
			break;
		case HORSE:
			if (m_bRidingMode)
				m_bRidingMode = false;
			else
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Horse.wav", BUllET_EFFECT, g_fSound);
				m_bRidingMode = true;
			}
			break;
		default:
			break;
		}
	}
	
	else if (CKeyMgr::Get_Instance()->Key_Down('X')) //줍기
	{

		if (m_eCurState == MINIMODE)
			return;

		if (CBlockMgr::Get_Instance()->Get_Blocks().empty())
			return;

		for (auto& iter : CBlockMgr::Get_Instance()->Get_Blocks())
		{
			if (static_cast<CBlock*>(iter)->Get_BlockType() == BLOCK_JAR)
			{
				float fWidth = fabsf(m_tInfo.fX - iter->Get_Info().fX);
				float fHeight = fabsf(m_tInfo.fY - iter->Get_Info().fY);
				float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

				if (fDiagonal <= 50)
					m_bCanPick = true;
			}

		}

		if (!m_bCanPick)
			return;

		if (!m_bPick)
		{
			m_bPick = true;
			CSoundMgr::Get_Instance()->PlaySoundW(L"PickUpJar.wav", PLAYER_EFFECT, g_fSound);
			m_eCurState = PICKUP;

			switch (m_eDir)
			{
			case DIR_LEFT:
				m_pFrameKey = L"Player_LEFT_PICKUP";
				break;
			case DIR_UP:
				m_pFrameKey = L"Player_UP_PICKUP";
				break;
			case DIR_RIGHT:
				m_pFrameKey = L"Player_RIGHT_PICKUP";
				break;
			case DIR_DOWN:
				m_pFrameKey = L"Player_DOWN_PICKUP";
				break;
			default:
				break;
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('R') || m_bRoll) //구르기
	{
		if (m_eCurState != MINIMODE)
		{
			m_bRoll = true;
			m_eCurState = ROLL;
		}

		m_bRoll = true;
		m_iDrawID = 1;
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= m_fSpeed;
			break;
		case DIR_UP:
			m_tInfo.fY -= m_fSpeed;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += m_fSpeed;
			break;
		case DIR_DOWN:
			m_tInfo.fY += m_fSpeed;
			break;
		default:
			break;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Up('E'))
	{
		if (m_eCurState == MINIMODE)
			return;

		if (m_pTarget == nullptr)
			return;

		m_eCurState = FLY;
		static_cast<CMushroom*>(m_pTarget)->Set_BePull(false);
		static_cast<CMushroom*>(m_pTarget)->Set_Pullend(true);
		m_pTarget = nullptr;
		m_bCanPull = false;
		m_bStop = false;
		m_fDistance = 0;

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('E'))
	{
		if (CBlockMgr::Get_Instance()->Get_Blocks().empty())
			return;

		for (auto& iter : CBlockMgr::Get_Instance()->Get_Blocks())
		{
			if (static_cast<CBlock*>(iter)->Get_BlockType() == BLOCK_MUSHROOM)
			{
				float fWidth = fabsf(m_tInfo.fX - iter->Get_Info().fX);
				float fHeight = fabsf(m_tInfo.fY - iter->Get_Info().fY);
				float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

				if (fDiagonal <= 50)
				{
					m_bCanPull = true;
					static_cast<CMushroom*>(iter)->Set_BePull(true);
					m_pTarget = iter;
				}

			}

		}

		if (!m_bCanPull)
			return;

		m_eCurState = PULL;

		switch (m_eDir)
		{
		case DIR_LEFT:
			m_pFrameKey = L"Player_RIGHT_PULL";

			if (!m_bStop)
				m_tInfo.fX += 1;
			break;
		case DIR_UP:
			m_pFrameKey = L"Player_UP_PULL";
			if (!m_bStop)
				m_tInfo.fY += 1;
			break;
		case DIR_RIGHT:
			m_pFrameKey = L"Player_LEFT_PULL";
			if (!m_bStop)
				m_tInfo.fX -= 1;
			break;
		case DIR_DOWN:
			m_pFrameKey = L"Player_DOWN_PULL";
			if (!m_bStop)
				m_tInfo.fY -= 1;
			break;
		default:
			break;
		}

		++m_fDistance;

		if (m_fDistance >= 45)
		{
			m_bStop = true;
		}
		else
		{
			m_bStop = false;
		}

	}
	else if (!m_bRoll && !m_bPick && !m_bThrow
		&& m_eCurState != FLY && !m_bAttack 
		&& !m_bBeAttacked && !m_bRidingMode) //누른 키값이 없을 때
	{
		m_iDrawID = 0;
		if (m_eCurState == MINIMODE)
			return;
		CSoundMgr::Get_Instance()->StopSound(BUllET_EFFECT);

		m_bKAGURA = false;
		m_eCurState = IDLE;
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_pFrameKey = L"LinkLeft";
			break;
		case DIR_UP:
			m_pFrameKey = L"LinkBack";
			break;
		case DIR_RIGHT:
			m_pFrameKey = L"LinkRight";
			break;
		case DIR_DOWN:
			m_pFrameKey = L"LinkFront";
			break;
		default:
			break;
		}
	}
}

void CPlayer::Jumping(void)
{
	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_fTime += 0.15f;
	}
}

void CPlayer::Offset(void)
{
	int iOffsetMinX = 300;
	int iOffsetMaxX = 500;

	int iOffsetMinY = 200;
	int iOffsetMaxY = 400;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (0 > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(WINCX);

	if (WINCX <= m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-WINCX);

	if (0 > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(WINCY);

	if (WINCY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-WINCY);




	// 플레이어가 왼쪽을 향하는 경우
	if (iOffsetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetMaxX <= m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffsetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::FLY:
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Jump.wav", PLAYER_EFFECT, g_fSound);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::WALK:
			if (m_bRidingMode)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 15;
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.iMotion = 1;
			}
			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::MINICHANGE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 19;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::MINIMODE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			
			
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount() ;
			break;

		case CPlayer::SKILL_FIRE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 16;


			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::EFFECT:
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Change.wav", PLAYER_EFFECT, g_fSound);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_pFrameKey = L"Player_Effect";

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::UPGRADE:
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Change.wav", PLAYER_EFFECT, g_fSound);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 14;
			m_pFrameKey = L"LinkFront";

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::Q_ATTACK:

			switch (m_eWeaponType)
			{
			case SWORD:
				m_tFrame.iMotion = 3;
				m_tFrame.iFrameEnd = 7;
				break;
			case WAND:
				m_tFrame.iMotion = 6;
				m_tFrame.iFrameEnd = 10;
				break;
			case ARROW:
				m_tFrame.iMotion = 5;
				m_tFrame.iFrameEnd = 7;
				break;
			case SHIELD:
				m_tFrame.iMotion = 4;
				m_tFrame.iFrameEnd = 5;
				
				break;
			case LANTON:
				m_tFrame.iMotion = 9;
				m_tFrame.iFrameEnd = 9;
				break;
			case BOOMERANG:
				m_tFrame.iMotion = 7;
				m_tFrame.iFrameEnd = 5;
				break;
			default:
				break;
			}
			m_tFrame.iFrameStart = 0;



			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::SKILL_READY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 11;


			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::KAGURA:
			m_pFrameKey = L"LinkFront";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 13;


			m_tFrame.dwFrameSpeed = 30;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::SKILL_GO:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 12;


			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::W_ATTACK:

			switch (m_eSecondWeaponType)
			{
			case SWORD:
				m_tFrame.iMotion = 3;
				m_tFrame.iFrameEnd = 7;
				break;
			case WAND:
				m_tFrame.iMotion = 6;
				m_tFrame.iFrameEnd = 10;
				break;
			case ARROW:
				m_tFrame.iMotion = 5;
				m_tFrame.iFrameEnd = 7;
				break;
			case SHIELD:
				m_tFrame.iMotion = 4;
				m_tFrame.iFrameEnd = 5;

				break;
			case LANTON:
				m_tFrame.iMotion = 9;
				m_tFrame.iFrameEnd = 9;
				break;
			case BOOMERANG:
				m_tFrame.iMotion = 7;
				m_tFrame.iFrameEnd = 5;
				break;
			case WEAPON_END:
				break;
			default:
				break;
			}
			m_tFrame.iFrameStart = 0;



			m_tFrame.dwFrameSpeed = 40;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		case CPlayer::FALL_WATER:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::ROLL:
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Link_Roll.wav", PLAYER_EFFECT, g_fSound);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 2;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::PICKUP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::PICKUPWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::THROW:
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::FALLING:
			Sound = 1.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CPlayer::PULL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}



void CPlayer::PickUp_Move_Frame(void)
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		m_bCount = true;
	}
	else if (!m_bCount)
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			m_tFrame.iFrameStart++;
			m_tFrame.dwFrameTime = GetTickCount();
		}

	}
	else
	{
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
	}
}

void CPlayer::PickUp_Motion(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_eCurState = PICKUPWALK;
		m_bPickWalk = true;
		m_pFrameKey = L"Player_LEFT_PICKUP_WALK";
		m_eDir = DIR_LEFT;
		m_tInfo.fX -= m_fSpeed;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_eCurState = PICKUPWALK;
		m_pFrameKey = L"Player_RIGHT_PICKUP_WALK";
		m_eDir = DIR_RIGHT;
		m_tInfo.fX += m_fSpeed;
		m_bPickWalk = true;

	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_eCurState = PICKUPWALK;
		m_bPickWalk = true;
		m_eDir = DIR_DOWN;
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_DOWN_PICKUP_WALK";
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_eCurState = PICKUPWALK;
		m_pFrameKey = L"Player_UP_PICKUP_WALK";
		m_eDir = DIR_UP;
		m_tInfo.fY -= m_fSpeed;
		m_bPickWalk = true;

	}
	else if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Throw.wav", PLAYER_EFFECT, g_fSound);
		m_bCount = false;
		m_bPickWalk = false;
		m_bPick = false;
		m_bCanPick = false;
		m_bThrow = true;
		m_eCurState = THROW;
	}
	else  //누른 키값이 없을 때
	{
		m_eCurState = PICKUP;
		m_bPickWalk = false;
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_pFrameKey = L"Player_LEFT_PICKUP";
			break;
		case DIR_UP:
			m_pFrameKey = L"Player_UP_PICKUP";
			break;
		case DIR_RIGHT:
			m_pFrameKey = L"Player_RIGHT_PICKUP";
			break;
		case DIR_DOWN:
			m_pFrameKey = L"Player_DOWN_PICKUP";
			break;
		default:
			break;
		}
	}
}

void CPlayer::Throw_Move_Frame(void)
{
	if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;

		if (m_tFrame.dwFrameTime + 250 < GetTickCount() && m_bThrow)
			m_bThrow = false;
	}
	else
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			m_tFrame.iFrameStart++;
			m_tFrame.dwFrameTime = GetTickCount();
		}
	}
}

void CPlayer::MIniChange_Frame(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"MiniChange.wav", PLAYER_EFFECT, g_fSound);

	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			m_tInfo.fCX -= 1;
			m_tInfo.fCY -= 1;
		}

		if (m_tInfo.fCX <= 10)
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Change.wav", PLAYER_EFFECT, g_fSound);
			m_tInfo.fCX = 10;
			m_tInfo.fCY = 10;
			m_fSpeed = 2.f;
			m_eCurState = MINIMODE;
			m_pFrameKey = L"Player_Mini";
		}
			

		m_tFrame.dwFrameTime = GetTickCount();
	}
	
}

void CPlayer::Falling_Water(void)
{
	int i = rand() % 2;
	switch (i)
	{
	case 0:
		//CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"WaterFalling.wav", PLAYER_EFFECT, g_fSound);
		break;

	case 1:
		//CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"WaterFalling2.wav", PLAYER_EFFECT, g_fSound);
		break;
	}

	if (!m_bCount && m_eCurState == MINIMODE)
	{
		m_tFrame.iMotion = 8;
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= 10;
			break;
		case DIR_UP:
			m_tInfo.fY -= 10;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += 10;
			break;
		case DIR_DOWN:
			m_tInfo.fY += 10;
			break;
		}
		m_dwTime = GetTickCount();
		m_bCount = true;
	}
	else if (!m_bCount)
	{
		m_iHp--;
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= 10;
			m_pFrameKey = L"Player_LEFT_FALLWATER";
			break;
		case DIR_UP:
			m_tInfo.fY -= 10;
			m_pFrameKey = L"Player_UP_FALLWATER";
			break;
		case DIR_RIGHT:
			m_tInfo.fX += 10;
			m_pFrameKey = L"Player_RIGHT_FALLWATER";
			break;
		case DIR_DOWN:
			m_tInfo.fY += 10;
			m_pFrameKey = L"Player_DOWN_FALLWATER";
			break;
		default:
			break;
		}
		m_dwTime = GetTickCount();
		m_bCount = true;
	}


	if (m_dwTime + 2000 < GetTickCount())
	{
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX += 30;
			break;
		case DIR_UP:
			m_tInfo.fY += 30;
			break;
		case DIR_RIGHT:
			m_tInfo.fX -= 30;
			break;
		case DIR_DOWN:
			m_tInfo.fY -= 30;
			break;
		default:
			break;
		}
		if(m_eCurState != MINIMODE)
			m_eCurState = IDLE;
		else
		{
			m_eCurState = MINIMODE;
			m_tFrame.iMotion = 0;
		}
		m_bCount = false;
		m_bFallWater = false;
	}
}

void CPlayer::Falling(void)
{
	
	if (!m_bCount)
	{
		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Falling.wav", PLAYER_EFFECT, g_fSound - 0.2f);
		m_pFrameKey = L"Player_FALL";
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= 10;
			break;
		case DIR_UP:
			m_tInfo.fY -= 10;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += 10;
			break;
		case DIR_DOWN:
			m_tInfo.fY += 10;
			break;
		default:
			break;
		}
		m_iHp--;
		m_dwTime = GetTickCount();
		m_bCount = true;
	}

	//Sound -= 0.05f;
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		switch (m_eDir)
		{
		case DIR_LEFT:
			m_tInfo.fX += 30;
			break;
		case DIR_UP:
			m_tInfo.fY += 30;
			break;
		case DIR_RIGHT:
			m_tInfo.fX -= 30;
			break;
		case DIR_DOWN:
			m_tInfo.fY -= 30;
			break;
		default:
			break;
		}

		m_eCurState = IDLE;
		m_bCount = false;
	}
}

void CPlayer::Flying(void)
{
	

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_pFrameKey = L"Player_LEFT_FLY";

		break;
	case DIR_UP:
		m_tInfo.fY -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_pFrameKey = L"Player_UP_FLY";

		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_pFrameKey = L"Player_RIGHT_FLY";

		break;
	case DIR_DOWN:
		m_tInfo.fY += m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
		m_pFrameKey = L"Player_DOWN_FLY";

		break;
	}

	m_fTime += 0.05f;


	if (m_fTime > 2.f)
	{
		m_fTime = 0;
		m_eCurState = IDLE;
	}
}

void CPlayer::Sword_Attack(void)
{
	int i = rand() % 3;
	switch (i)
	{
	case 0:
		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Link_Attack.wav", PLAYER_EFFECT, g_fSound);
		break;

	case 1:
		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Link_Attack2.wav", PLAYER_EFFECT, g_fSound);
		break;

	case 2:
		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Link_Attack3.wav", PLAYER_EFFECT, g_fSound);
		break;

	default:
		break;
	}
	
	switch (m_eDir)
	{
	case DIR_LEFT:
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER));
		break;
	case DIR_UP:
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY, OBJ_PLAYER));
		break;
	case DIR_RIGHT:
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER));
		break;
	case DIR_DOWN:
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY, OBJ_PLAYER));
		break;
	default:
		break;
	}
}

void CPlayer::KaguraAttack(void)
{
	if (!m_bKAGURA)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory <CKaguraBullet>::Create(m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER));
		m_bKAGURA = true;
	}

	m_fAngle += 5;

	if (m_fAngle > 360)
		m_fAngle -= 360;


	float PosX = cosf(m_fAngle*RADIAN) * 70;
	float PosY = sinf(m_fAngle*RADIAN) * 70;

	if (m_dwKaguraTime + 200 < GetTickCount())
	{
		CObj* pObj = CAbstractFactory <CKaguraBullet>::Create(m_tInfo.fX + PosX, m_tInfo.fY - PosY, OBJ_PLAYER);
		static_cast<CKaguraBullet*>(pObj)->Set_MiniFire();
		static_cast<CKaguraBullet*>(pObj)->Set_FirePos(PosX, PosY);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		m_dwKaguraTime = GetTickCount();
	}

}

void CPlayer::Fire_Attack(void)
{
	if (m_bKAGURA)
		return;


	CObj* pObj = nullptr;

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		switch (m_eDir)
		{
		case DIR_LEFT:
			pObj = CAbstractFactory <CFireBullet>::Create(m_tInfo.fX - (m_tInfo.fCX*2.2f), m_tInfo.fY -16, OBJ_PLAYER);
			static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
			break;
		case DIR_UP:
			pObj = CAbstractFactory <CFireBullet>::Create(m_tInfo.fX -5, m_tInfo.fY - m_tInfo.fCY*2.5f, OBJ_PLAYER);
			static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
			break;
		case DIR_RIGHT:
			pObj = CAbstractFactory <CFireBullet>::Create(m_tInfo.fX + m_tInfo.fCX*2.2f, m_tInfo.fY - 16, OBJ_PLAYER);
			static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
			break;
		case DIR_DOWN:
			pObj = CAbstractFactory <CFireBullet>::Create(m_tInfo.fX + 8, m_tInfo.fY + m_tInfo.fCY * 2 - 2, OBJ_PLAYER);
			static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
			break;
		default:
			break;
		}

		m_bKAGURA = true;
	}
	

	
}

void CPlayer::Thunder_Skill_Attack(void)
{
	
	CSoundMgr::Get_Instance()->StopSound(BUllET_EFFECT);
	CObj* pObj = nullptr;
	switch (m_eDir)
	{
	case DIR_LEFT:
		pObj = CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_UP:
		pObj = CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_RIGHT:
		pObj = CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_DOWN:
		pObj = CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BULLET_THUNDER);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	default:
		break;
	}
}

void CPlayer::Lanton_Attack(void)
{
	

	CObj* pObj = nullptr;
	switch (m_eDir)
	{
	case DIR_LEFT:
		pObj =  CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BUllET_FIRE);

		break;
	case DIR_UP:
		pObj = CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BUllET_FIRE);


		break;
	case DIR_RIGHT:
		pObj = CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BUllET_FIRE);

		break;
	case DIR_DOWN:
		pObj = CAbstractFactory <CSwordBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY, OBJ_PLAYER);
		static_cast<CBullet*>(pObj)->Set_BulletType(BUllET_FIRE);

		break;
	default:
		break;
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
}

void CPlayer::Wand_Attack(void)
{
	int i = rand() % 2;
	switch (i)
	{
	case 0:
		CSoundMgr::Get_Instance()->StopSound(BUllET_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"magic powder 1.wav", BUllET_EFFECT, g_fSound + 0.5f);
		break;

	case 1:
		CSoundMgr::Get_Instance()->StopSound(BUllET_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"magic powder 2.wav", BUllET_EFFECT, g_fSound + 0.5f);
		break;
	}

	CObj* pObj;
	switch (m_eDir)
	{
	case DIR_LEFT:
		pObj = CAbstractFactory <CWandBullet>::Create(m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_LEFT);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_UP:
		pObj = CAbstractFactory <CWandBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_UP);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_RIGHT:
		pObj = CAbstractFactory <CWandBullet>::Create(m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_RIGHT);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_DOWN:
		pObj = CAbstractFactory <CWandBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_DOWN);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	default:
		break;
	}
}

void CPlayer::Boo_Attack(void)
{

	if (m_bBoomerang)
		return;
	CSoundMgr::Get_Instance()->StopSound(BUllET_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"boomerang.wav", BUllET_EFFECT, g_fSound + 0.5f);

	CObj* pObj;
	switch (m_eDir)
	{
	case DIR_LEFT:
		pObj = CAbstractFactory <CBooBullet>::Create(m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_LEFT);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_UP:
		pObj = CAbstractFactory <CBooBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_UP);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_RIGHT:
		pObj = CAbstractFactory <CBooBullet>::Create(m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_RIGHT);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_DOWN:
		pObj = CAbstractFactory <CBooBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_DOWN);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	default:
		break;
	}

	m_bBoomerang = true;
}

void CPlayer::Arrow_Attack(void)
{
	int i = rand() % 2;
	switch (i)
	{
	case 0:
		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Link_Arrow.wav", PLAYER_EFFECT, g_fSound+0.5f);
		break;

	case 1:
		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Link_Arrow2.wav", PLAYER_EFFECT, g_fSound+0.5f);
		break;
	}
	CObj* pObj;
	switch (m_eDir)
	{
	case DIR_LEFT:
		pObj = CAbstractFactory <CArrowBullet>::Create(m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_LEFT);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_UP:
		pObj = CAbstractFactory <CArrowBullet>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_UP);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_RIGHT:
		pObj = CAbstractFactory <CArrowBullet>::Create(m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_RIGHT);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	case DIR_DOWN:
		pObj = CAbstractFactory <CArrowBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY, OBJ_PLAYER);
		pObj->Set_Dir(DIR_DOWN);
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);
		break;
	default:
		break;
	}
}

void CPlayer::Shield_Attack(void)
{

	if (m_bShieldMode)
		return;

	

	CObj* pObj = CAbstractFactory <CShieldBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD, pObj);


	m_bShieldMode = true;
}

void CPlayer::Shield_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			
		}


		m_tFrame.dwFrameTime = GetTickCount();
	}
}
