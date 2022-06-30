#pragma once
#include "Block.h"
class CWood :
	public CBlock
{
public:
	CWood();
	virtual ~CWood();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

