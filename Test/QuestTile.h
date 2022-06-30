#pragma once
#include "MenuObj.h"
class CQuestTile :
	public CMenuObj
{
public:
	CQuestTile();
	virtual ~CQuestTile();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Exist(bool type) { m_bExist = type; }
	void Set_DrawID(int i) { m_iDrawID = i; }
	void Set_QuestType(QUESTID type) { m_QuestType = type; }

public:
	const bool& Get_Exist(void) { return m_bExist; }
	const int& Get_DrawID(void) { return m_iDrawID; }
	const QUESTID& Get_Questtype(void) { return m_QuestType; }

private:
	bool  m_bExist;
	int  m_iDrawID;

	QUESTID m_QuestType;
};

