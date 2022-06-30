#pragma once
#include "Include.h"
#include "Hp.h"
#include "CoinNumber.h"
#include "ItemRect.h"
#include "SkillRect.h"


class CObj;
class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	void Update_Hp(void);
	void Update_Coin(void);
	void Update_Key(void);

public:
	static CUIMgr*	 Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CUIMgr;

		return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CUIMgr*	m_pInstance;
	vector<CObj*>		m_HpList;
	vector<CObj*>		m_CoinList;
	vector<CObj*>		m_KeyList;


	CObj*				m_ItemRect;
	CObj*				m_ItemRect2;

	CObj*				m_SkillRect;
	CObj*				m_SkillRect2;
	CObj*				m_SkillRect3;

	int iFullHp;
	int iLastHp;
	int iPastFullHp;
	int iMaxHp;
	int iHpCount;
	int iPastHpCount;

	int iPreHp;
	int iPreCoin;
	int iPreKey;

	bool m_bCount;
	bool m_bZeroHeart;

	int iNumber;
};

