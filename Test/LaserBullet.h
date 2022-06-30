#pragma once
#include "Bullet.h"
class CLaserBullet :
	public CBullet
{
public:
	CLaserBullet();
	virtual ~CLaserBullet();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_MovePoint(POINT  point) { m_tMovePoint = point; }

private:
	void Move(void);

private:
	DWORD m_dwTime;
	POINT m_tMovePoint;

	float PosY = 0.f;
};

