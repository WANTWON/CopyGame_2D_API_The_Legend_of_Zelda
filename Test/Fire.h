#pragma once
#include "Block.h"
class CFire :
	public CBlock
{
public:
	CFire();
	~CFire();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool	m_bCount;

	DWORD	m_dwtime;
};

