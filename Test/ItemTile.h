#pragma once
#include "MenuObj.h"
class CItemTile :
	public CMenuObj
{
public:
	CItemTile();
	virtual ~CItemTile();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Exist(bool type) {m_bExist = type;}
	void Set_WeaponType(WEAPONID type) { m_WeaponType = type; }
	void Set_beUsed(bool type) { if (!m_bExist)return;  m_bBeUsed = type; }
	void Set_DrawID(int i){ m_iDrawID = i; }
	void Set_WOption(bool type) { if(!m_bExist)return;  WOption = type; }

public:
	const bool& Get_Exist(void) { return m_bExist; }
	const bool& Get_Used(void) { return m_bBeUsed; }
	const int& Get_DrawID(void) { return m_iDrawID; }
	const WEAPONID& Get_Weapontype(void) { return m_WeaponType; }

private:
	bool  m_bExist;
	int  m_iDrawID;
	bool m_bBeUsed;


	bool WOption = false;
	WEAPONID m_WeaponType;
};

