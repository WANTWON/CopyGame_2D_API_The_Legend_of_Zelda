#pragma once
#include "MenuObj.h"
class CChoosePoint :
	public CMenuObj
{
public:
	CChoosePoint();
	virtual ~CChoosePoint();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Key_Input(void);

	void Set_UsedIndex(int i) { m_iUsedIndex = i; }
	void Set_SecondUsedIndex(int i) { m_iWUsedIndex = i; }
	void Set_Index(int i) { m_iWIndex = i; }
	void Set_SecondIndex(int i) { m_iIndex = i; }

	const int& Get_Index(void) { return m_iIndex; }
	const int& Get_UsedIndex(void) { return m_iUsedIndex; }
	const int& Get_WUsedIndex(void) { return m_iWUsedIndex; }

private:
	int m_iIndex;
	int m_iUsedIndex;

	WEAPONID m_WeaponID;


	int m_iWIndex;
	int m_iWUsedIndex;

	WEAPONID m_WWeaponID;
};

