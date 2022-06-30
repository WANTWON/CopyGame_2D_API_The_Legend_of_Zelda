#pragma once
#include "Include.h"
#include "ObjMgr.h"
#include "Obj.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual		void	Initialize(void) PURE;
	virtual		int		Update(void)	PURE;
	virtual		void	Late_Update(void) PURE;
	virtual		void	Render(HDC hDC) PURE;
	virtual		void	Release(void) PURE;

public:
	void Save_PlayerPos(INFO m_tInfo) { m_tPlayerINFO = m_tInfo; }

protected:

	INFO m_tPlayerINFO;
};

