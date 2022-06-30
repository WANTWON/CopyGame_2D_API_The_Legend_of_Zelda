#pragma once
#include "Monster.h"
class COctopusMonster :
	public CMonster
{
public:
	COctopusMonster();
	virtual ~COctopusMonster();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

private:
	void Motion_Change(void);
	void IDLE_Motion(void);
	void Move(void);
	void Dead_Motion(void);

private:
	DWORD	m_dwTime;
	DWORD	m_dwAttackTime;

	DIRECTION m_ePreDir;
	bool m_bCount;

};

