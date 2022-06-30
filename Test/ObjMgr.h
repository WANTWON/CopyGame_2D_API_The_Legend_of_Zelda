#pragma once

#include "Include.h"

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	const list<CObj*>& Get_Bullets(void) const { return m_ObjList[OBJ_BULLET]; }
	const list<CObj*>& Get_Monsters(void) const { return m_ObjList[OBJ_MONSTER]; }
	const list<CObj*>& Get_Player_List(void) const { return m_ObjList[OBJ_PLAYER]; }
	const list<CObj*>& Get_Portal(void) const { return m_ObjList[OBJ_PORTAL]; }
	const list<CObj*>& Get_Shields(void) const { return m_ObjList[OBJ_SHIELD]; }
	CObj* Get_Shield(void) { return m_ObjList[OBJ_SHIELD].front(); }

	void Set_BlockList(list<CObj*> list) { m_ObjList[OBJ_BLOCK] = list; }

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Delete_ID(OBJID eID);

	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	void		Save_Monster(SCENEID eStage);
	void		Load_Monster(SCENEID eStage);
	void		Save_Player(void);
	void		Load_Player(void);

public:
	void		Set_EditorMode(bool mode) { m_bEditorMode = mode; }
	void		Delete_Obj(POINT & _pt, int _iDrawID, int _iOption);


public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

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
	static		CObjMgr*		m_pInstance;
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*> m_RenderSort[RENDER_END];

	bool m_bEditorMode;
};

