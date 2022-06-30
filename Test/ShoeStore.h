#pragma once
#include "Scene.h"
class CShoeStore :
	public CScene
{
public:
	CShoeStore();
	virtual ~CShoeStore();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bCount;
	bool m_bShoesMakeCount;

	DWORD m_dwTime;
};

