#pragma once
#include "Obj.h"


class CBlock :
	public CObj
{
public:
	CBlock() : m_bCut(false), m_iOption(0), m_eBlockType(BLOCK_END) {}
	virtual ~CBlock() {}

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	void		Set_DrawID(int _iDrawID) { m_tFrame.iFrameStart = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }
	void		Set_BlockType(BLOCKID _BlockType) { m_eBlockType = _BlockType; }

	void		Change_DrawID() { ++m_tFrame.iFrameStart;  if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd )m_tFrame.iFrameStart = 0; }
	void		Change_Option() { ++m_iOption;  if (m_iOption > 2)m_iOption = 0; }

	const int&		Get_DrawID(void) { return m_tFrame.iFrameStart; }
	const int&		Get_Option(void) { return m_iOption; }
	const BLOCKID&	Get_BlockType(void) { return m_eBlockType; }

protected:
	int		m_iOption;
	bool	m_bCut;
	BLOCKID	 m_eBlockType;
};

