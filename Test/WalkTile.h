#pragma once
#include "Tile.h"
class CWalkTile :
	public CTile
{
public:
	CWalkTile();
	virtual ~CWalkTile();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};


