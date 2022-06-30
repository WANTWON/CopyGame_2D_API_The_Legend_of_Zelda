#pragma once
#include "Scene.h"
#include "MenuObj.h"


class CInventory :
	public CScene
{
public:
	CInventory();
	virtual ~CInventory();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:

	CMenuObj* m_pChoose;
	bool m_bCount = false;
	
};


