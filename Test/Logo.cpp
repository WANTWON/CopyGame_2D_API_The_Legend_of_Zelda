#include "stdafx.h"
#include "Logo.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

float		g_fSound = 0.5f;

CLogo::CLogo() : m_dwDrawTime(GetTickCount()), m_DrawEffectID(0), m_DrawUIID(0), m_dwButtonTime(GetTickCount())
{
	
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Field6.bmp", L"Field");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/Store3.bmp", L"Store");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/StoreRoom.bmp", L"StoreRoom");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/ShoeStore.bmp", L"ShoeStore");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/ShoeMiniGame.bmp", L"ShoeMiniGame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossStage/BossMap.bmp", L"BossStage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Dungeon/DunGeon.bmp", L"Dungeon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossStage/EndingStage.bmp", L"EndingStage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossStage/BonusBack2.bmp", L"BossBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/MiniRoad.bmp", L"MiniRoad");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/MiniWorld.bmp", L"MiniWorld");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/MiniRoom.bmp", L"MiniRoom");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/MiniRoom2.bmp", L"MiniRoom2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/MiniRoom3.bmp", L"MiniRoom3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/MiniChief.bmp", L"MiniChief");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/MiniWood.bmp", L"MiniWood");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/QuestClearText.bmp", L"QuestClearText");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title_Screen/BackGround.bmp", L"LOGO_BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title_Screen/Effect.bmp", L"LOGO_Effect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title_Screen/Sword.bmp", L"LOGO_Sword");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title_Screen/Title.bmp", L"LOGO_Title");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title_Screen/Nintendo.bmp", L"LOGO_Nintendo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title_Screen/Press_Start.bmp", L"LOGO_Press_Start");

	//CSoundMgr::Get_Instance()->PlaySound(L"../Sound/Logo/Logo.wav", SOUND_BGM, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySound(L"Success.wav", SOUND_BGM, g_fSound);
}

int CLogo::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Logo.wav", SOUND_BGM, g_fSound);

	

	return 0;
}

void CLogo::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

	if (m_dwDrawTime + 100 < GetTickCount())
	{
		++m_DrawEffectID;
		if (m_DrawEffectID == 4)
			m_DrawEffectID = 0;

		m_dwDrawTime = GetTickCount();
	}

	if (m_dwButtonTime + 500 < GetTickCount())
	{
		++m_DrawUIID;
		if (m_DrawUIID == 2)
			m_DrawUIID = 0;

		m_dwButtonTime = GetTickCount();
	}

	
}

void CLogo::Render(HDC hDC)
{
	HDC hBackGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_BackGround");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackGroundMemDC, 0, 0, SRCCOPY);

	HDC hEffectMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Effect");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		0,	// 2,3 인자 :  복사받을 위치 X, Y
		0,
		WINCX,				// 4,5 인자 : 복사받을 가로, 세로 길이
		WINCY,
		hEffectMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		(160 +3) * m_DrawEffectID,
		239,				// 복사할 비트맵의 가로, 세로 길이
		160,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

	HDC hSwordMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Sword");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		50,	// 2,3 인자 :  복사받을 위치 X, Y
		80,
		350,				// 4,5 인자 : 복사받을 가로, 세로 길이
		200,
		hSwordMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		(98 + 3) * m_DrawUIID,
		191,				// 복사할 비트맵의 가로, 세로 길이
		98,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

	HDC hTitleMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Title");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		150,	// 2,3 인자 :  복사받을 위치 X, Y
		100,
		500,				// 4,5 인자 : 복사받을 가로, 세로 길이
		300,
		hTitleMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		167,				// 복사할 비트맵의 가로, 세로 길이
		88,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

	HDC hStartMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Press_Start");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		250,	// 2,3 인자 :  복사받을 위치 X, Y
		450,
		300,				// 4,5 인자 : 복사받을 가로, 세로 길이
		60,
		hStartMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		89 * m_DrawUIID,
		89,				// 복사할 비트맵의 가로, 세로 길이
		18,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

	HDC hLogoMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Nintendo");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		250,	// 2,3 인자 :  복사받을 위치 X, Y
		550,
		300,				// 4,5 인자 : 복사받을 가로, 세로 길이
		30,
		hLogoMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0 ,
		133,				// 복사할 비트맵의 가로, 세로 길이
		16,
		RGB(112, 216, 248));			// 제거하고자 하는 색상

}

void CLogo::Release(void)
{
}
