#include "stdafx.h"
#include "BossMonster.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "BossBullet.h"
#include "GuideMonster.h"
#include "LaserMonster.h"

CBossMonster::CBossMonster()
	: m_bCount(false), m_dwTime(GetTickCount()), m_eLevel(LEVEL_1), m_bDeadCount(false),
	m_bMove(true), m_bAttack(false), m_dwAttackTime(GetTickCount()), m_dwBulletTime(GetTickCount()),
	m_iTime(5000), m_iLaserMonsterCount(0), m_bPause(false), m_bPauseCount(false), m_bStart(false), m_dwTelePortTime(GetTickCount())
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 100.f, 150.f };

	m_fSpeed = 0.5f;
	m_fDistance = m_tInfo.fCX;
	m_eDir = DIR_LEFT;
	m_eGroup = RENDER_MONSTER;

	m_eMonsterType = BOSS_MONSTER;
	m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();

	m_iHp = 100;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/Boss.bmp", L"Boss");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/BossDead.bmp", L"BossDead");

	m_pFrameKey = L"Boss";
}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eCurState != DEAD && m_eCurState != HIT && !m_bAttack)
		Move();
	else if (m_bAttack && m_eCurState != HIT && m_eCurState != DEAD)
		Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(void)
{
	Motion_Change();

	if (m_bEditorMode)
		return;

	if (m_eCurState == DEAD)
	{
		Dead_Motion();
		return;
	}

	if (TELEPORT != m_eCurState)
		Move_Frame();
	else
		TelePort_Motion();

	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);
	CCollisionMgr::Collsion_Tile(CTileMgr::Get_Instance()->Get_EditTiles(), this);
	CCollisionMgr::Collsion_Block(CBlockMgr::Get_Instance()->Get_Blocks(), this);

	if ( m_beAttacked && m_eCurState != DEAD)
	{
		m_eCurState = HIT;

		if (!m_bCount)
		{
			CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Boss_Hurt.wav", MONSTER_EFFECT, g_fSound + 0.2f);
			
			if (m_bMegaCritical)
				m_iHp -= 5;
			else if (m_bCritical)
				m_iHp -= 3;
			else if (m_bAttack)
				--m_iHp;
			
			m_dwTime = GetTickCount();
			m_bCount = true;
		}

		if (m_dwTime + 200 < GetTickCount())
		{
			m_beAttacked = false;
			if(m_eLevel != LEVEL_3)
				m_eCurState = IDLE;
			else
				m_eCurState = TELEPORT;
			m_bCount = false;
		}

	}

	if (m_iHp <= 0)
	{
		m_pFrameKey = L"BossDead";
		m_eCurState = DEAD;
	}	
	else if (m_iHp < 30)
	{
		m_eLevel = LEVEL_3;
		m_fSpeed = 3.f;
		m_iDrawID = 2;
	}

	else  if (m_iHp < 70)
	{
		m_eLevel = LEVEL_2;
		m_iDrawID = 1;
		m_fSpeed = 0.01f;
		m_iTime = 6000;
	}

	if (m_dwAttackTime + m_iTime < GetTickCount() && (m_eLevel == LEVEL_1 || m_eLevel == LEVEL_2))
	{
		if (m_bAttack)
			m_bAttack = false;
		else
			m_bAttack = true;

		m_dwAttackTime = GetTickCount();
	}

}

void CBossMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	 if (m_eCurState == DEAD)
	{

		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 20,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 70,
			int(m_tInfo.fCX) + 40,
			int(m_tInfo.fCY) + 130,
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (50),								// 비트맵 출력 시작 좌표, X,Y
			0,
			50,				// 복사할 비트맵의 가로, 세로 길이
			100,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	else if (m_eCurState == HIT)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 80,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 80,
			int(m_tInfo.fCX) + 160,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 160,
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (300),								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion  * 300,
			300,				// 복사할 비트맵의 가로, 세로 길이
			300,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX) - 80,	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY) - 80,
			int(m_tInfo.fCX) + 160,				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY) + 160,
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (300),								// 비트맵 출력 시작 좌표, X,Y
			(m_tFrame.iMotion + (m_iDrawID * 4)) * 300,
			300,				// 복사할 비트맵의 가로, 세로 길이
			300,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
	}
	
}

void CBossMonster::Release(void)
{
}

void CBossMonster::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CBossMonster::LASER_ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CBossMonster::BUllET_ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 26;
			m_tFrame.iMotion = 2;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CBossMonster::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CBossMonster::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 12;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CBossMonster::TELEPORT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 26;
			m_tFrame.iMotion = 3;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case CBossMonster::DEAD:
			m_pFrameKey = L"BossDead";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 32;
			m_tFrame.iMotion = 0;

			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBossMonster::Move(void)
{
	if (m_bEditorMode)
		return;

	switch (m_eLevel)
	{
	case CBossMonster::LEVEL_1:
		Level1_Move();
		break;
	case CBossMonster::LEVEL_2:
		Level2_Move();
		break;
	case CBossMonster::LEVEL_3:
		Level3_Move();
		break;
	default:
		break;
	}
}

void CBossMonster::Attack(void)
{
	if (m_bEditorMode)
		return;

	switch (m_eLevel)
	{
	case CBossMonster::LEVEL_1:
		Level1_Attack();
		break;
	case CBossMonster::LEVEL_2:
		Level2_Attack();
		break;
	case CBossMonster::LEVEL_3:
		Level3_Attack();
		break;
	default:
		break;
	}
}

void CBossMonster::Dead_Motion(void)
{
	if (!m_bDeadCount)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Boss_Dead.wav", MONSTER_EFFECT, g_fSound + 0.5f);
		m_bDeadCount = true;
	}
	
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_bDead = true;
			CObjMgr::Get_Instance()->Get_Player()->Set_StageClear();
			CSoundMgr::Get_Instance()->PlaySound(L"Boom.wav", SOUND_EFFECT, g_fSound + 0.5f);

		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}

void CBossMonster::TelePort_Motion(void)
{
	if (m_eCurState != TELEPORT)
		return;
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount() && !m_bPause && !m_bAttack)
	{
		++m_tFrame.iFrameStart;

		
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_bAttack = true;
			m_dwTelePortTime = GetTickCount();
		}

		m_tFrame.dwFrameTime = GetTickCount();
	}
}

void CBossMonster::Level1_Move(void)
{
	m_eCurState = IDLE;

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed*3;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed*3;
		break;
	default:
		break;
	}

	if (m_tInfo.fX < 300)
		m_eDir = DIR_RIGHT;
	else if (m_tInfo.fX > 500)
		m_eDir = DIR_LEFT;

}

void CBossMonster::Level2_Move(void)
{

	m_eCurState = BUllET_ATTACK;

	float fWidth = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - m_tInfo.fX);
	float fHeight = (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - m_tInfo.fY);
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	m_fAngle = acosf(fWidth / fDiagonal);
	if (m_tInfo.fY < CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY)
		m_fAngle *= -1;

	m_tInfo.fX += fDiagonal*cos(m_fAngle)*m_fSpeed;
	m_tInfo.fY -= fDiagonal*sin(m_fAngle)*m_fSpeed;
	
	++m_fAngle;
		
	POINT  Posin;
	Posin.x = long(m_fDistance*cos(m_fAngle));
	Posin.y = long(m_fDistance*sin(m_fAngle));


	if (m_dwBulletTime + 1100 < GetTickCount() && (m_iLaserMonsterCount < 5))
	{
		CObj* pObj = CAbstractFactory<CLaserMonster>::Create(m_tInfo.fX + Posin.x, m_tInfo.fY - Posin.y);
		pObj->Set_Target(this);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
		++m_iLaserMonsterCount;
		m_dwBulletTime = GetTickCount();
	}

}

void CBossMonster::Level3_Move(void)
{

	if (!m_bStart)
	{
		m_eCurState = TELEPORT;
		m_bStart = true;
	}

	if (m_bPause)
	{
		if (!m_bPauseCount)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Teleport.wav", MONSTER_EFFECT, g_fSound + 0.1f);
			m_dwPauseTime = GetTickCount();
			m_bPauseCount = true;
		}

		if (m_dwPauseTime + 2000 < GetTickCount())
		{
			m_bPause = false;
			m_bPauseCount = false;
			m_eCurState = TELEPORT;
		}
	}

	if (m_eCurState == TELEPORT)
	{
		if (m_tFrame.iFrameStart > 9 && m_tFrame.iFrameStart < 19)
		{
			m_tInfo.fX = -100;
			m_tInfo.fY = -100;
			m_tInfo.fCX = 0;
			m_tInfo.fCY = 0;
		}
		else if (m_tFrame.iFrameStart == 19)
		{
			m_tInfo.fX = rand() % 400 + 200.f;
			m_tInfo.fY = rand() % 100 + 200.f;
			m_tInfo.fCX = 100;
			m_tInfo.fCY = 150;
		}
	}
	
	
	
}

void CBossMonster::Level1_Attack(void)
{
	m_eCurState = BUllET_ATTACK;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	float fWidth = (m_pTarget->Get_Info().fX - m_tInfo.fX);
	float fHeight = (m_pTarget->Get_Info().fY - m_tInfo.fY);
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	m_fAngle = acosf(fWidth / fDiagonal);
	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1;

	POINT  Posin;
	Posin.x = long(m_fDistance*cos(m_fAngle));
	Posin.y = long(m_fDistance*sin(m_fAngle));

	if (m_dwBulletTime + 500 < GetTickCount())
	{
		CObj* pObj = CAbstractFactory<CBossBullet>::Create(m_tInfo.fX + Posin.x, m_tInfo.fY - Posin.y, OBJ_MONSTER);
		static_cast<CBossBullet*>(pObj)->Set_MovePoint(Posin);

		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);

		Posin.x = long(m_fDistance*cos(m_fAngle + 10));
		Posin.y = long(m_fDistance*sin(m_fAngle + 10));

		 pObj = CAbstractFactory<CBossBullet>::Create(m_tInfo.fX + Posin.x, m_tInfo.fY - Posin.y, OBJ_MONSTER);
		static_cast<CBossBullet*>(pObj)->Set_MovePoint(Posin);

		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);

		Posin.x = long(m_fDistance*cos(m_fAngle - 90));
		Posin.y = long(m_fDistance*sin(m_fAngle - 90));

		 pObj = CAbstractFactory<CBossBullet>::Create(m_tInfo.fX + Posin.x, m_tInfo.fY - Posin.y, OBJ_MONSTER);
		static_cast<CBossBullet*>(pObj)->Set_MovePoint(Posin);

		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pObj);


		m_dwBulletTime = GetTickCount();
	}
	


}

void CBossMonster::Level2_Attack(void)
{

	m_eCurState = LASER_ATTACK;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	float fWidth = (m_pTarget->Get_Info().fX - m_tInfo.fX);
	float fHeight = (m_pTarget->Get_Info().fY - m_tInfo.fY);
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	m_fAngle = acosf(fWidth / fDiagonal);
	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1;

	POINT  Posin;
	Posin.x = long(m_fDistance*cos(m_fAngle));
	Posin.y = long(m_fDistance*sin(m_fAngle));

	if (m_dwBulletTime + 2000 < GetTickCount())
	{
		CObj* pObj = CAbstractFactory<CGuideMonster>::Create(m_tInfo.fX + Posin.x, m_tInfo.fY - Posin.y);
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);

		m_dwBulletTime = GetTickCount();
	}

}

void CBossMonster::Level3_Attack(void)
{
	m_eCurState = LASER_ATTACK;
	
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	default:
		break;
	}

	if (m_tInfo.fX <= CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX)
		m_eDir = DIR_RIGHT;
	else 
		m_eDir = DIR_LEFT;

	++m_fAngle;

	POINT  Posin;
	Posin.x = long(m_fDistance*cos(m_fAngle));
	Posin.y = long(m_fDistance*sin(m_fAngle));


	if (m_dwBulletTime + 1100 < GetTickCount() && (m_iLaserMonsterCount < 5))
	{
		CObj* pObj = CAbstractFactory<CLaserMonster>::Create(m_tInfo.fX + Posin.x, m_tInfo.fY - Posin.y);
		pObj->Set_Target(this);
		static_cast<CLaserMonster*>(pObj)->Set_LaserMode(true);


		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
		++m_iLaserMonsterCount;
		m_dwBulletTime = GetTickCount();
	}


	if (m_dwTelePortTime + 5000 < GetTickCount())
	{
		m_bAttack = false;
		m_bPause = true;
		

		m_dwTelePortTime = GetTickCount();
	}

}
