#pragma once
#include "Monster.h"
class CLaserMonster :
	public CMonster
{
public:
	CLaserMonster();
	virtual ~CLaserMonster();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_LaserMode(bool type) { m_bLaserMode = type; }


private:
	void Move(void);
	void Dead_Motion(void);
	void Motion_Change(void);
	void LaserAttack_Frame(void);


	DWORD	m_dwTime;
	DWORD	m_dwAttackTime;

	bool m_bCount;
	bool m_bLaserMode;
	bool m_bLaserCount;

	bool m_bSoundCount;

};

