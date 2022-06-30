#pragma once
#include "Block.h"
class CSeed :
	public CBlock
{
public:
	CSeed();
	virtual ~CSeed();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	DWORD m_dwTime;
	bool m_bCount;
};

