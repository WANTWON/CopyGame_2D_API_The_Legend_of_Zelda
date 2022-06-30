#pragma once
#include "Bullet.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

class CBooBullet :
	public CBullet
{
public:
	CBooBullet();
	virtual ~CBooBullet();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

private:
	void Move(void);

private:
	DWORD dwTime;
	float m_fAnimSpeed;
	float m_fAnimTime;
	float m_fAnimAccel;
};

