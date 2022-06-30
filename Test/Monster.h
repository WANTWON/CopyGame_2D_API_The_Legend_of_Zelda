#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	enum STATE { IDLE, HIT, ATTACK, BUllET_ATTACK, LASER_ATTACK, ROCK, TELEPORT, DEAD};
public:
	CMonster() : m_eMonsterType(MONSTER_END), m_eCurState(IDLE), m_ePreState(IDLE), 
		m_iDrawID(0), m_beAttacked(false), m_bCritical(false), m_bMegaCritical(false)
	{
	}
	virtual ~CMonster()
	{
	}

public:
	virtual void	Initialize(void) PURE;
	virtual int		Update(void) PURE;
	virtual void	Late_Update(void) PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release(void) PURE;

public:
	void Set_BeAttack(void) { m_beAttacked = true; }
	void Set_BeCritical(void) { m_bCritical = true;  m_beAttacked = true;}
	void Set_m_bMegaCritical(void) { m_bMegaCritical = true;  m_beAttacked = true;}
	const MONSTERID& Get_MonsterType(void) const { return m_eMonsterType; }
	const STATE& Get_CurState(void) const { return m_eCurState; }

protected:
	STATE				m_eCurState;
	STATE				m_ePreState;
	MONSTERID			m_eMonsterType;

	int					m_iDrawID;
	bool				m_beAttacked;
	bool				m_bCritical;
	bool				m_bMegaCritical;
};

