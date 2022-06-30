#pragma once
#include "Scene.h"
class CMiniRoom2 :
	public CScene
{
public:
	CMiniRoom2();
	virtual ~CMiniRoom2();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bCount;

	bool m_bPlay = false;
	DWORD m_dwTime = GetTickCount();

};

