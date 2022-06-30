#pragma once
#include "Obj.h"
class CNpc :
	public CObj
{
public:
	CNpc();
	virtual ~CNpc();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

	void	Set_NPCType(NPCID Type) { m_eNpcType = Type; }

private:
	NPCID	m_eNpcType;

	TCHAR*	m_pTextKey;
	bool m_bTextout;
	bool m_bUpgrade;

	DWORD m_dwTime;
};

