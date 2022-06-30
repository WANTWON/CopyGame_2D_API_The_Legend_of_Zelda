#pragma once
#include "Item.h"
class CHeart :
	public CItem
{
public:
	CHeart();
	virtual ~CHeart();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Get_Effect(void);

private:
	bool m_bGet_Effect;

	float m_fTime = 0;
	bool  m_bCount;
	DWORD m_dwTime;
};

