#pragma once
#include "Bullet.h"
class CArrowBullet :
	public CBullet
{
public:
	CArrowBullet();
	virtual ~CArrowBullet();

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
};

