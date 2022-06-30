#pragma once
#include "Item.h"
class CStoreWeapon :
	public CItem
{
public:
	enum Type { WEAPON, HP, PORTION};
public:
	CStoreWeapon();
	virtual ~CStoreWeapon();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

	void Set_Item_type(Type Itemtype, WEAPONID type = WEAPON_END) { m_eType = Itemtype; m_eWeapontype = type; }
	void Set_WeaponType(void);

private:
	float m_fTime = 0;
	bool  m_bCount;
	bool m_bTextout;
	bool m_bSuccessBuy;
	bool m_bShortage_Money;
	int  iCoin;

	DWORD m_dwTime;
	Type m_eType;
	WEAPONID m_eWeapontype;
	TCHAR* TextFrameKey;
};

