#pragma once
#include "Obj.h"
class CShoe :
	public CObj
{
public:
	

public:
	CShoe();
	virtual ~CShoe();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	
	void Set_MyTurn(bool type) { m_bMyturn = type; }
	bool& Get_Myturn(void) { return m_bMyturn; }

private:
	int m_iOption;
	int m_iDrawID;
	
	bool m_bMyturn;
	
};

