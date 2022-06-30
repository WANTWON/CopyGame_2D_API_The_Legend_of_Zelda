#pragma once
#include "Obj.h"
class CRockPaperScissor :
	public CObj
{
public:
	CRockPaperScissor();
	virtual ~CRockPaperScissor();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Set_MyOption(int type) { m_iOption = type; }
	void Set_PCver(int type) { m_bPC = type; }
	int& Get_MyOption(void) { return m_iOption; }

private:
	int m_iOption;
	int m_iDrawID;

	bool m_bPC = false;
};

