#pragma once
#include "Obj.h"
class CItemRect :
	public CObj
{
public:
	CItemRect();
	virtual ~CItemRect();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	void Set_DrawID(int number) { m_DrawID = number; }
	const int& Get_DrawID(void) const { return m_DrawID; }
	void Set_WeaponID(WEAPONID type) { m_eWeaponType = type; }
	void Set_TypeNumber(int i) { TypeNumber = i; }

public:
	int m_DrawID;
	int m_Option;

	int TypeNumber;
	WEAPONID m_eWeaponType;
};

