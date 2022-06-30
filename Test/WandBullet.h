#pragma once
#include "Bullet.h"
class CWandBullet :
	public CBullet
{
public:
	CWandBullet();
	virtual ~CWandBullet();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

private:
	void Animate(void);

private:
	DWORD dwTime;

	bool m_bBounce;
	float m_fAnimSpeed;
	float m_fAnimTime;
	float m_fAnimAccel;
};

