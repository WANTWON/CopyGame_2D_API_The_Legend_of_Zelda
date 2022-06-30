#pragma once
#include "Obj.h"
#include "SoundMgr.h"
#include "Player.h"

class CItem :
	public CObj
{
public:

	CItem() : m_eItemType(ITEM_END), m_iDrawID(0), m_iOption(0)
	{
	}

	virtual ~CItem()
	{
	}

public:
	virtual void	Initialize(void) PURE;
	virtual int		Update(void) PURE;
	virtual void	Late_Update(void) PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release(void) PURE;

protected:
	ITEMID			m_eItemType;
	int				m_iDrawID;
	int				m_iOption;
};

