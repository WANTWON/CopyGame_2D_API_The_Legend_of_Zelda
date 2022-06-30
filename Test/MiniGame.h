#pragma once
#include "Scene.h"
class CMiniGame :
	public CScene
{
public:
	enum GAMESTATE { WIN, LOSE, DRAW, END};
public:
	CMiniGame();
	virtual ~CMiniGame();


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
	bool m_bGameStart;
	bool m_bResult;
	bool m_bTextOut;

	bool m_bScoreCount;

	int m_iScore = 0;

	DWORD m_dwTime;
	DWORD m_dwLoadingTime;
	TCHAR*  FrameKey;
	CObj* MyTurn;
	CObj* PCTurn;

	GAMESTATE m_eGameResult = END;
};

