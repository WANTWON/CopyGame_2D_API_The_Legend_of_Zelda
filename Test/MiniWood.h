#pragma once
#include "Scene.h"
class CMiniWood :
	public CScene
{
public:
	CMiniWood();
	virtual ~CMiniWood();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bCount;
	bool m_bAllSeedGrow;
	bool m_bChestCount;

	bool m_bTextOut;

	DWORD m_dwTime;
};

