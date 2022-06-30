#pragma once
#include "Include.h"
#include "Tile.h"
#include "SwitchTile.h"

class CObj;
class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Add_Tiles(TILEID eID, CObj* pObj);
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	void Picking_Tile(POINT& _pt, int _iDrawID, int _iOption, TILEID type);
	void Change_Tile(POINT& _pt, int _iDrawID, int _iOption);
	void Delete_Tile(POINT& _pt, int _iDrawID, int _iOption);
	void Save_Tile(SCENEID eStage);
	void Load_Tile(SCENEID eStage);

public:
	const vector<CObj*>& Get_EditTiles(void) const { return m_vecTile[TILE_EDIT]; }
	const vector<CObj*>& Get_SwitchTiles(void) const { return m_vecTile[TILE_SWITCH]; }
	const int&			 Get_SolvedTiles(void) const { return m_iSolvedTile; }

public:
	void Set_EditMode(bool type) { m_bEditMode = type; }
	void Set_SolvedTile(void) { ++m_iSolvedTile; }

public:
	static		CTileMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileMgr;

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
	static		CTileMgr*		m_pInstance;
	vector<CObj*>				m_vecTile[TILE_END];

	bool m_bChangeTileID;
	bool m_bCreated;
	bool m_bEditMode;
	int m_iTileID;

	int m_iSolvedTile;
};

