#pragma once
#include "Obj.h"
class CPlayer : public CObj
{
public:
	enum STATE { IDLE, WALK, Q_ATTACK, W_ATTACK, FALL_WATER, FALLING, SKILL_READY,SKILL_GO, SKILL_FIRE, KAGURA,
		PULL, FLY, ROLL, HIT, EFFECT, PICKUP, PICKUPWALK , MINICHANGE, MINIMODE, THROW, UPGRADE, END };
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_Roll(void) { m_bRoll = false; }
	void Set_Attack(void) { m_bAttack = false; }
	void Set_State(STATE state) { m_eCurState = state; }
	void Set_BeAttacked(void) { m_bBeAttacked = true; }
	void Set_WeaponType(WEAPONID type) { m_eWeaponType = type; }
	void Set_Second_WeaponType(WEAPONID type) { m_eSecondWeaponType = type; }
	void Set_Beboomerang(void) {  m_bBoomerang = false;}
	void Set_FallWater(void) { m_bFallWater = true; }

public:
	STATE& Get_State(void) { return m_eCurState; }
	WEAPONID& Get_WeaponType(void) { return m_eWeaponType; }
	WEAPONID& Get_Second_WeaponType(void) { return m_eSecondWeaponType; }
	bool& Get_Throw(void) { return m_bThrow; }
	

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		Offset(void);
	void		Motion_Change(void);
private:
	void		PickUp_Move_Frame(void);
	void		PickUp_Motion(void);
	void		Throw_Move_Frame(void);
	void	    MIniChange_Frame(void);
	void		Falling_Water(void);
	void		Falling(void);
	void		Flying(void);

private:
	void		Sword_Attack(void);
	void		KaguraAttack(void);
	void		Fire_Attack(void); 
	void		Thunder_Skill_Attack(void);
	void		Lanton_Attack(void);
	void		Wand_Attack(void);
	void		Boo_Attack(void);
	void		Arrow_Attack(void);
	void		Shield_Attack(void);
	void		Shield_Frame(void);

private:
	POINT				m_tPosin;
	bool				m_bJump;
	float				m_fJumpPower;
	float				m_fTime;

	STATE				m_ePreState;
	STATE				m_eCurState;

	bool				m_bRoll;
	bool				m_bKAGURA;
	bool				m_bStop;
	bool				m_bAttack;
	bool				m_bFallWater;
	
	bool				m_bCanPick;
	bool				m_bCanPull;

	bool				m_bPick;
	bool				m_bPickWalk;
	bool				m_bThrow;
	
	bool				m_bCount;
	bool				m_bBoomerang;
	bool				m_bShieldMode;

	bool				m_bBeAttacked;

	int					m_iDrawID;

	bool				m_bInvincible_mode;
	bool				m_bRidingMode;

	float				Sound;

	DWORD				m_dwTime;
	DWORD				m_dwWalkTime; 
	DWORD				m_dwKaguraTime;

	WEAPONID			m_eWeaponType;
	WEAPONID			m_eSecondWeaponType;

};

