#pragma once
#include "Obj.h"
class CShieldBullet :
	public CObj
{
public:
	CShieldBullet();
	virtual ~CShieldBullet();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

private:
	DWORD dwTime;
	bool m_bCount;
};

