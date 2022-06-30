#pragma once
#include "Monster.h"
class CBossMonster :
	public CMonster
{
public : 	
	enum HP_STATE {LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_END};

public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Minus_LaserMonster(void) { --m_iLaserMonsterCount; }
	STATE& Get_State(void) { return m_eCurState; }

private:
	void Motion_Change(void);	
	void Move(void);
	void Attack(void);
	void Dead_Motion(void);
	void TelePort_Motion(void);

private:
	void Level1_Move(void);
	void Level2_Move(void);
	void Level3_Move(void);

	void Level1_Attack(void);
	void Level2_Attack(void);
	void Level3_Attack(void);

private:
	DWORD	m_dwTime;
	DWORD	m_dwAttackTime;
	DWORD   m_dwBulletTime;
	DWORD	m_dwPauseTime;
	DWORD	m_dwTelePortTime;

	DIRECTION m_ePreDir;
	bool m_bCount;
	bool m_bPauseCount;
	
	HP_STATE m_eLevel;

	bool m_bMove;
	bool m_bPause;
	bool m_bAttack;
	bool m_bStart;
	bool m_bDeadCount;


	int m_iTime;
	int m_iLaserMonsterCount;
};

