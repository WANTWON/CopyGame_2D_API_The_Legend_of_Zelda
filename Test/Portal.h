#pragma once
#include "Obj.h"
class CPortal :
	public CObj
{
public:
	CPortal();
	virtual ~CPortal();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_PortalType(SCENEID type) { m_eSceneType = type; }
	void EndingMotion(void);
	void RockMotion(void);

private:
	SCENEID  m_eSceneType;
	bool m_bOpenRock;
	bool m_bEnding;

	bool m_bCount;
};

