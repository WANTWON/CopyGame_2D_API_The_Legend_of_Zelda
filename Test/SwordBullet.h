#pragma once
#include "Bullet.h"
class CSwordBullet :
	public CBullet
{
public:
	CSwordBullet();
	virtual ~CSwordBullet();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

private:
	DWORD dwTime;

};

