#pragma once
#include "Obj.h"
class CHp :
	public CObj
{
public:
	CHp();
	virtual ~CHp();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_DrawID(int number) { m_DrawID = number; }
	const int& Get_DrawID(void) const { return m_DrawID; }

public:
	int m_DrawID;
	int m_Option;

};

