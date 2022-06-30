#pragma once
#include "Obj.h"
class CMyButton :
	public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		m_iDrawID = 0;

};

