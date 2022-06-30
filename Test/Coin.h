#pragma once
#include "Item.h"
class CCoin :
	public CItem
{
public:
	CCoin();
	virtual ~CCoin();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Get_Effect(void);
	void Set_Coin(void) { m_iOption = 0; }
	void Set_Bonus_Coin(void) { m_iOption = 1; }


private:
	bool m_bGet_Effect;

	float m_fTime = 0;
	bool  m_bCount;
	DWORD m_dwTime;

};

