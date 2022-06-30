#pragma once
#include "Monster.h"
class CMoblinMonster :
	public CMonster
{
public:
	CMoblinMonster();
	virtual ~CMoblinMonster();

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
	void Attack(void);
	void Dead_Motion(void);

private:
	DWORD	m_dwTime;
	DIRECTION m_ePreDir;
	bool m_bCount;

	float fWidth;
	float fHeight;
	float fDiagonal;
};

