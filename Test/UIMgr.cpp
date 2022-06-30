#include "stdafx.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "AbstractFactory.h"
#include "Player.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
	: m_bCount(false), iFullHp(0), iLastHp(0), iNumber(0), m_bZeroHeart(false), iMaxHp(0)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HUD/Status.bmp", L"Status");
}


CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize(void)
{
	iHpCount = CObjMgr::Get_Instance()->Get_Player()->Get_Hp();
	iPastHpCount = iHpCount;
	iFullHp = iHpCount /4;
	iLastHp = iHpCount %4;
	iPastFullHp = iFullHp;
	iMaxHp = CObjMgr::Get_Instance()->Get_Player()->Get_MaxHp();
	
	float Col = 0;
	for (int i = 0; i < iMaxHp; ++i)
	{
		m_HpList.push_back(CAbstractFactory<CHp>::Create( 530 + ((i%8)*30.f), 60 + (Col * 30)));
		static_cast<CHp*>(m_HpList[i])->Set_DrawID(4);
		if (i % 8 == 7)
			++Col;		
	}

	for (int i = 0; i < iFullHp; ++i)
	{
		static_cast<CHp*>(m_HpList[i])->Set_DrawID(0);
	}

	if (iLastHp != 0)
	{
		if (3 == iLastHp % 4)
			static_cast<CHp*>(m_HpList[iFullHp -1])->Set_DrawID(1);
		else if (2 == iLastHp % 4)
			static_cast<CHp*>(m_HpList[iFullHp -1])->Set_DrawID(2);
		else if (1 == iLastHp % 4)
			static_cast<CHp*>(m_HpList[iFullHp -1])->Set_DrawID(3);
		else if (0 == iLastHp % 4)
		{
			if (iPastFullHp == iFullHp)
				static_cast<CHp*>(m_HpList[iFullHp-1])->Set_DrawID(0);

			else if (iPastFullHp > iFullHp)
			{
				static_cast<CHp*>(m_HpList[iFullHp-1])->Set_DrawID(4);
				iPastFullHp = iFullHp;
			}
		}
	}
	
	int iCoin = CObjMgr::Get_Instance()->Get_Player()->Get_Coin();
	iPreCoin = iCoin;
	int iShare = iCoin;

	float i = 0;

	while (true)
	{
		int iDivid = iShare % 10;

		m_CoinList.push_back(CAbstractFactory<CCoinNumber>::Create( 250 - (i * 20), 60.f));
		static_cast<CCoinNumber*>(m_CoinList.back())->Set_DrawID(iDivid);

		iShare = iShare / 10;
		++i;

		if (iShare == 0)
			break;
	}
	

	int iKey = CObjMgr::Get_Instance()->Get_Player()->Get_Key();
	iPreKey= iKey;
	int iKeyShare = iKey;

	float j = 0;

	while (true)
	{
		int iDivid = iKeyShare % 10;

		m_KeyList.push_back(CAbstractFactory<CCoinNumber>::Create(155 - (j * 20), 60.f));
		static_cast<CCoinNumber*>(m_KeyList.back())->Set_DrawID(iDivid);

		iKeyShare = iKeyShare / 10;
		++j;

		if (iKeyShare == 0)
			break;
	}

	
	m_ItemRect = CAbstractFactory<CItemRect>::Create(55, 43);
	static_cast<CItemRect*>(m_ItemRect)->Set_TypeNumber(1);
	m_ItemRect2 = CAbstractFactory<CItemRect>::Create(135, 43);
	static_cast<CItemRect*>(m_ItemRect2)->Set_TypeNumber(2);

	m_SkillRect = CAbstractFactory<CSkillRect>::Create(55, 550);
	static_cast<CSkillRect*>(m_SkillRect)->Set_DrawID(1);
	m_SkillRect2 = CAbstractFactory<CSkillRect>::Create(55, 490);
	static_cast<CSkillRect*>(m_SkillRect2)->Set_DrawID(2);
	m_SkillRect3 = CAbstractFactory<CSkillRect>::Create(55, 420);
	static_cast<CSkillRect*>(m_SkillRect3)->Set_DrawID(3);

}

void CUIMgr::Update(void)
{
	Update_Hp();

	for (auto& iter : m_HpList)
		iter->Update();

	Update_Coin();

	for (auto& iter : m_CoinList)
		iter->Update();

	Update_Key();

	for (auto& iter : m_KeyList)
		iter->Update();

	m_ItemRect->Update();
	m_ItemRect2->Update();

	m_SkillRect->Update();
	m_SkillRect2->Update();
	m_SkillRect3->Update();
}

void CUIMgr::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Player_List().empty())
		return;

	for (auto& iter : m_CoinList)
		iter->Late_Update();


	for (auto& iter : m_KeyList)
		iter->Late_Update();

	m_ItemRect->Late_Update();
	m_ItemRect2->Late_Update();

	m_SkillRect->Late_Update();
	m_SkillRect2->Late_Update();
	m_SkillRect3->Late_Update();
}

void CUIMgr::Render(HDC hDC)
{
	

	for (auto& iter : m_HpList)
		iter->Render(hDC);

	for (auto& iter : m_CoinList)
		iter->Render(hDC);

	for (auto& iter : m_KeyList)
		iter->Render(hDC);

	m_ItemRect->Render(hDC);
	m_ItemRect2->Render(hDC);

	m_SkillRect->Render(hDC);
	m_SkillRect2->Render(hDC);
	m_SkillRect3->Render(hDC);

	HDC hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"Status");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		0,	// 2,3 인자 :  복사받을 위치 X, Y
		0,
		WINCX,				// 4,5 인자 : 복사받을 가로, 세로 길이
		WINCY,
		hUIDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		256,				// 복사할 비트맵의 가로, 세로 길이
		224,
		RGB(244, 0, 244));			// 제거하고자 하는 색상
}

void CUIMgr::Release(void)
{
	for_each(m_HpList.begin(), m_HpList.end(), CDeleteObj());
	m_HpList.clear();

	for_each(m_CoinList.begin(), m_CoinList.end(), CDeleteObj());
	m_CoinList.clear();

	for_each(m_KeyList.begin(), m_KeyList.end(), CDeleteObj());
	m_KeyList.clear();

	Safe_Delete(m_ItemRect);
	Safe_Delete(m_ItemRect2);

	Safe_Delete(m_SkillRect);
	Safe_Delete(m_SkillRect2);
	Safe_Delete(m_SkillRect3);
}


void CUIMgr::Update_Hp(void)
{

	if (CObjMgr::Get_Instance()->Get_Player_List().empty())
		return;

	if (m_bZeroHeart)
		return;

	iHpCount = CObjMgr::Get_Instance()->Get_Player()->Get_Hp();

	for_each(m_HpList.begin(), m_HpList.end(), CDeleteObj());
	m_HpList.clear();

	iPastHpCount = iHpCount;
	iMaxHp = CObjMgr::Get_Instance()->Get_Player()->Get_MaxHp();
	
	iFullHp = iHpCount / 4;
	iLastHp = iHpCount % 4;

	if (!m_bCount)
	{
		iNumber = m_HpList.size() - 1;
		m_bCount = true;
	}

	float Col = 0;
	for (int i = 0; i < iMaxHp; ++i)
	{
		m_HpList.push_back(CAbstractFactory<CHp>::Create(530 + ((i % 8)*30.f), 60 + (Col * 30)));
		static_cast<CHp*>(m_HpList[i])->Set_DrawID(4);
		if (i % 8 == 7)
			++Col;
	}

	for (int i = 0; i < iFullHp; ++i)
	{
		static_cast<CHp*>(m_HpList[i])->Set_DrawID(0);
	}

	if (iLastHp != 0)
	{
		if (3 == iLastHp % 4)
			static_cast<CHp*>(m_HpList[iFullHp])->Set_DrawID(1);
		else if (2 == iLastHp % 4)
			static_cast<CHp*>(m_HpList[iFullHp])->Set_DrawID(2);
		else if (1 == iLastHp % 4)
			static_cast<CHp*>(m_HpList[iFullHp])->Set_DrawID(3);
		else if (0 == iLastHp % 4)
		{
			if (iPastFullHp == iFullHp)
				static_cast<CHp*>(m_HpList[iFullHp])->Set_DrawID(0);

			else if (iPastFullHp > iFullHp)
			{
				static_cast<CHp*>(m_HpList[iFullHp])->Set_DrawID(4);
				iPastFullHp = iFullHp;
			}
		}
	}
}

void CUIMgr::Update_Coin(void)
{
	if (m_CoinList.empty())
		return;

	int iCoin = CObjMgr::Get_Instance()->Get_Player()->Get_Coin();

	iPreCoin = iCoin;

	for_each(m_CoinList.begin(), m_CoinList.end(), CDeleteObj());
	m_CoinList.clear();


	int iShare = iCoin;

	float i = 0;

	while (true)
	{
		int iDivid = iShare % 10;

		m_CoinList.push_back(CAbstractFactory<CCoinNumber>::Create(310 - (i * 20), 60.f));
		static_cast<CCoinNumber*>(m_CoinList.back())->Set_DrawID(iDivid);

		iShare = iShare / 10;
		++i;

		if (iShare == 0)
			break;
	}
}

void CUIMgr::Update_Key(void)
{
	if (m_KeyList.empty())
		return;

	int iKey = CObjMgr::Get_Instance()->Get_Player()->Get_Key();

	iPreKey = iKey;

	for_each(m_KeyList.begin(), m_KeyList.end(), CDeleteObj());
	m_KeyList.clear();


	int iShare = iKey;

	float i = 0;

	while (true)
	{
		int iDivid = iShare % 10;

		m_KeyList.push_back(CAbstractFactory<CCoinNumber>::Create(455 - (i * 20), 60.f));
		static_cast<CCoinNumber*>(m_KeyList.back())->Set_DrawID(iDivid);

		iShare = iShare / 10;
		++i;

		if (iShare == 0)
			break;
	}
}
