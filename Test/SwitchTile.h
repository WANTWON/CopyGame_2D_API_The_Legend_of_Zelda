#pragma once
#include "Tile.h"
class CSwitchTile :
	public CTile
{
public:
	CSwitchTile();
	virtual ~CSwitchTile();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bCount;
};

