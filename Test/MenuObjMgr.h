#pragma once
#include "MenuObj.h"

class CMenuObjMgr
{
public:
	CMenuObjMgr();
	~CMenuObjMgr();

public:
	void		Add_Object(MENUOBJID eID, CMenuObj* pObj);
	void		Add_QuestTile(CMenuObj* pObj);
	void		Add_ItemTile( CMenuObj* pObj);
	void		Add_Weapon(WEAPONID eID, bool Default = false);
	void		Add_Quest(QUESTID eID, bool Default = false);
	void		Set_QuestComplete(QUESTID type);
	
	void		Delete_ID(MENUOBJID eID);
	void		Delete_Quest(void);
	
public:
	vector<CMenuObj*> Get_Inven(void) { return m_pInvenVec; }
	CMenuObj* Get_ChoosePos(void) { return m_MenuObjList[MENU_CHOOSE].front(); }


	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Save_Weapon(void);
	void		Load_Weapon(void);

	void		Save_Quest(void);
	void		Load_Quest(void);

	void		Save_ChoosePoint(void);
	void		Load_ChoosePoint(void);

public:
	static		CMenuObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMenuObjMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:
	static		CMenuObjMgr*		m_pInstance;

	vector<CMenuObj*>				m_pInvenVec;
	vector<CMenuObj*>				m_pQuestVec;

	list<CMenuObj*>	m_MenuObjList[MENU_END];


	
};

