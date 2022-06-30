#pragma once
#include "Block.h"
class CTreasureChest :
	public CBlock
{
public:

public:
	CTreasureChest();
	virtual ~CTreasureChest();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Chest_Item(ITEMID type) { m_eITemType = type; }

private:
	bool m_bThrow;
	bool m_bBreak;


	float m_fTime;
	bool m_bCount;

	ITEMID m_eITemType;
};

