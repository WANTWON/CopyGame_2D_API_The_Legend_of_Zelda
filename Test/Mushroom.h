#pragma once
#include "Block.h"
class CMushroom :
	public CBlock
{
public:
	CMushroom();
	virtual ~CMushroom();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Direction_Change(void);
	void Motion_Change(void);
	void Be_Pull_Motion(void);

public:
	void Set_BePull(bool m_bool) { m_bBePull = m_bool; }
	void Set_Pullend(bool m_bool) { m_bPullend = m_bool; }


private:
	bool m_bBePull;
	bool m_bPullend;
	bool m_bCount;

	DIRECTION m_ePreDIR;

};

