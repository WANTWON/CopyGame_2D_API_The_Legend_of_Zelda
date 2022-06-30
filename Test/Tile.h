#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }
	void		Set_Tieletype(TILEID _iOption) { m_eTiletype = _iOption; }

	void		Change_DrawID() { ++m_iDrawID; if (m_iDrawID > 4)m_iDrawID = 0; }
	void		Change_Option() { ++m_iOption; if (m_iOption > 4)m_iOption = 0; }

	const int&	Get_DrawID(void) { return m_iDrawID; }
	const int&	Get_Option(void) { return m_iOption; }
//	const bool&	Get_Solved(void) { return m_bSolved; }
	const TILEID&	Get_TileType(void) { return m_eTiletype; }

protected:
	int		m_iDrawID;
	int		m_iOption;

	bool	m_bCount;


	TILEID  m_eTiletype;
};

