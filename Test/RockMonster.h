#pragma once
#include "Monster.h"
class CRockMonster :
	public CMonster
{
public:
	CRockMonster();
	virtual ~CRockMonster();

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
	void WakeUp_Motion(void);
	void IDLE_Move(void);
	void Dead_Motion(void);

private:
	DWORD	m_dwTime;
	DWORD m_dwJumpTime;
	DIRECTION m_ePreDir;
	bool m_bCount;
	bool m_bStop;

	float fWidth;
	float fHeight;
	float fDiagonal;
};

