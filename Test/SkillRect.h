#pragma once
#include "Obj.h"
class CSkillRect :
	public CObj
{
public:
	CSkillRect();
	virtual ~CSkillRect();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_DrawID(int number) { m_DrawID = number; }

private:
	int m_DrawID;
};

