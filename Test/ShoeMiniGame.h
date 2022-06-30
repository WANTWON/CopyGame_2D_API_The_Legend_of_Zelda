#pragma once
#include "Scene.h"
class CShoeMiniGame :
	public CScene
{
public:
	CShoeMiniGame();
	virtual ~CShoeMiniGame();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bReady;
	bool m_bStart;


	bool m_bCount;
	bool m_bWin;
	bool m_bShoesEmpty;
	bool m_bNext;
	size_t VecNum = 0;
	int m_iScore = 0;
	int m_iFinish = 0;

	DWORD m_dwTime;

	vector<CObj*> m_ShoesList;
};

