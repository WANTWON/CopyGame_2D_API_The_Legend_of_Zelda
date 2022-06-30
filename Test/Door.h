#pragma once
#include "Block.h"
class CDoor :
	public CBlock
{
public:
	enum DOORSTATE { DOOR_1, DOOR_2, DOOR_3 };

public:
	CDoor();
	virtual ~CDoor();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_DoorType(DOORSTATE type) { m_eDoortype = type; }

private:
	DOORSTATE m_eDoortype;
};

