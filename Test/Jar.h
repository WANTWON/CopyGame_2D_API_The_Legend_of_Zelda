#pragma once
#include "Block.h"
class CJar :
	public CBlock
{
public:
	CJar();
	virtual ~CJar();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Break_Jar(void);
	void Follow_Player_Top(void);
	void Be_Picked(void);
	void Be_Thrown(void);

public:
	void Set_BePicked(void) { m_bPicked = true; }

private:
	bool m_bPicked;
	bool m_bThrow;
	bool m_bBreak;


	float m_fTime;
	bool m_bCount;

};



