#pragma once
#include "Scene.h"

class CLogo : public CScene
{
public:
	CLogo();
	~CLogo();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	DWORD m_dwDrawTime;
	DWORD m_dwButtonTime;
	int m_DrawEffectID;
	int m_DrawUIID;
};

