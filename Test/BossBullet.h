#pragma once
#include "Bullet.h"
class CBossBullet :
	public CBullet
{
public:
	CBossBullet();
	virtual ~CBossBullet();

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
	void Motion_Change(void);

private:
	DWORD m_dwTime;

	POINT m_tMovePoint;

	bool m_bCount;

};

