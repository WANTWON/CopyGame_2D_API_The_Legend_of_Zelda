#pragma once
#include "Include.h"

class CMenuObj
{
public:
	CMenuObj();
	~CMenuObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

public:
	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead(void) { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_FrameKey(TCHAR* _pFramekey) { m_pFrameKey = _pFramekey; }
	void		Set_ID(MENUOBJID ID) { m_eID = ID; }
	void		Set_EditorMode(bool mode) { m_bEditorMode = mode; }
	void		Load_Coin(int Coin) { m_iCoin = Coin; }
	void		Load_Hp(int Hp) { m_iHp = Hp; }
	void		Set_MaxHp(void) { m_iMaxHp += 1; }
	void		Set_Coin(int Coin) { m_iCoin += Coin; }
	void		Set_Hp(void) { m_iHp += 4; if (m_iHp > m_iMaxHp * 4) m_iHp = m_iMaxHp * 4; }
	void		Set_StageClear(void) { m_bStageClear = true; }

public:
	const bool&		Get_Dead(void) const { return m_bDead; }
	const int&		Get_Hp(void)  const { return m_iHp; }
	const int&		Get_MaxHp(void)  const { return m_iMaxHp; }
	const int&		Get_Coin(void)  const { return m_iCoin; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
	const INFO&		Get_Info(void) const { return m_tInfo; }
	const MENUOBJID&	Get_ID(void) const { return m_eID; }
	const DIRECTION& Get_Direction(void) const { return m_eDir; }
	const bool& Get_StageClear(void) { return m_bStageClear; }

public:

public:
	virtual		void	Initialize(void) PURE;
	virtual		int		Update(void)	PURE;
	virtual		void	Late_Update(void) PURE;
	virtual		void	Render(HDC hDC) PURE;
	virtual		void	Release(void) PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	FRAME		m_tFrame;

	float		m_fSpeed;
	bool		m_bDead;
	float		m_fAngle;
	float		m_fDistance;

	int			m_iHp;
	int			m_iMaxHp;
	int			m_iCoin;

	TCHAR*		m_pFrameKey;

	MENUOBJID		m_eID;

	bool m_bEditorMode;

	bool m_bStageClear;
};

