#pragma once
#include "Monster.h"
class CGuideMonster :
	public CMonster
{
public:
	CGuideMonster();
	virtual ~CGuideMonster();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

private:
	void Move(void);
	void Dead_Motion(void);
	void Motion_Change(void);

	DWORD	m_dwTime;
	bool m_bCount;
	bool m_bSoundCount;

};

