#pragma once

#include "Include.h"
#include "SoundMgr.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

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
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void		Set_FrameKey(TCHAR* _pFramekey) { m_pFrameKey = _pFramekey; }
	void		Set_ID(OBJID ID) { m_eID = ID; }
	void		Set_EditorMode(bool mode) { m_bEditorMode = mode; }
	void		Load_Coin(int Coin) { m_iCoin = Coin; }
	void		Load_Hp(int Hp) { m_iHp = Hp; }
	void		Load_MaxHp(int Hp) { m_iMaxHp = Hp; }
	void		Load_Key(int Hp) { m_iKey = Hp; }
	void		Set_MaxHp(void) { m_iMaxHp += 1; }
	void		Set_Key(void) { m_iKey += 1; }
	void		Set_MinusKey(void) { m_iKey -= 1; }
	void		Set_Coin(int Coin) { m_iCoin += Coin; }
	void		Set_Hp(void) { m_iHp += 4; if (m_iHp > m_iMaxHp*4) m_iHp = m_iMaxHp*4; }
	void		Set_StageClear(void) { m_bStageClear = true; }

public:
	const bool&		Get_Dead(void) const { return m_bDead; }
	const int&		Get_Hp(void)  const { return m_iHp; }
	const int&		Get_Key(void)  const { return m_iKey; }
	const int&		Get_MaxHp(void)  const { return m_iMaxHp; }
	const int&		Get_Coin(void)  const { return m_iCoin; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
	const INFO&		Get_Info(void) const { return m_tInfo; }
	const OBJID&	Get_ID(void) const { return m_eID; }
	const CObj*		Get_Target(void) const { return m_pTarget; }
	const DIRECTION& Get_Direction(void) const { return m_eDir; }
	const bool& Get_StageClear(void) { return m_bStageClear; }
	const RENDERID	Get_RenderID(void) const { return m_eGroup; }

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
	int			m_iKey;

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	OBJID		m_eID;

	bool m_bEditorMode;

	bool m_bStageClear;

	RENDERID	m_eGroup = RENDER_END;
};


// 추상 팩토리 패턴(abstract factory pattern)
// : 생성 패턴의 한 방법으로 인스턴스를 만드는 절차를 추상화시키는 패턴

// 이터레이터 패턴(반복자 패턴)
// : 내부 표현 방식은 공개하지 않고 순차적인 접근 방법을 제공하는 패턴
// 동일한 부모를 갖는 오브젝트들을 하나의 컨테이너로 관리하고자 하는 목적 