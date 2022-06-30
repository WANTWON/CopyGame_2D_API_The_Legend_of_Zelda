#pragma once
#include "Include.h"

class CObj;
class CBlockMgr
{
private:
	CBlockMgr();
	~CBlockMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void JarRender(HDC hDC);
	void Release(void);

public:
	void Picking_Block(POINT& _pt, BLOCKID _iBlockCategory);
	void Delete_Block(POINT& _pt, int _iDrawID, int _iOption);
	void Set_EditorMode(bool mode) { m_EditorMode = mode; }
	void Set_BlockSolved(void) { ++m_iBlockSolved; }
	void Set_SeedSolved(void) { ++m_iSeedSolved; }

	void Save_Block(SCENEID eStage);
	void Load_Block(SCENEID eStage);

	void Add_Object(CObj* pObj);

public:
	const list<CObj*>& Get_Blocks(void) const { return m_BlockList; }
	const int&		   Get_iSolvedBlock(void) { return m_iBlockSolved; }
	const int&		   Get_iSolvedSeed(void) { return m_iSeedSolved; }

public:
	static		CBlockMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBlockMgr;

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
	static		CBlockMgr*		m_pInstance;
	list<CObj*>				m_BlockList;

	bool m_bChangeTileID;
	bool m_bCreated;

	int m_iTileID;
	int m_iBlockSolved;
	int m_iSeedSolved;

	bool m_EditorMode;
};


