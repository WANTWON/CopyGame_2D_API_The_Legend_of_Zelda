#pragma once
#include "Scene.h"
class CDungeon :
	public CScene
{
public:
	CDungeon();
	virtual ~CDungeon();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bCount;

};

