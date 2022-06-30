#pragma once
#include "Scene.h"
class CMiniWorld :
	public CScene
{
public:
	CMiniWorld();
	virtual ~CMiniWorld();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bCount;
	bool m_textOut;
	bool m_bQuest;

	DWORD m_dwTime;
	DWORD m_QuestdwTime;
};

