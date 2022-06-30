#pragma once

#include "Include.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(void);
	void	Release(void);

private:
	HDC m_hDC;

	DWORD m_dwTime;
	int m_iFPS;
	TCHAR m_szFPS[32];
};

