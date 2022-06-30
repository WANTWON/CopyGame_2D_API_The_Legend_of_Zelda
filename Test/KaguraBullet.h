#pragma once
#include "Bullet.h"
class CKaguraBullet :
	public CBullet
{
public:
	CKaguraBullet();
	virtual ~CKaguraBullet();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_MiniFire(void) { m_bMiniFire = true; }
	void Set_FirePos(float FX, float FY) { PosX = FX; PosY = FY; }

private:
	DWORD dwTime;

	float PosX;
	float PosY;

	bool m_bCount;
	bool m_bMiniFire;
};

