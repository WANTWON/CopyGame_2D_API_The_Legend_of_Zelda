#include "stdafx.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SnakeMonster.h"
#include "BossMonster.h"
#include "OctopusMonster.h"
#include "MoblinMonster.h"
#include "RockMonster.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CTileMgr::Get_Instance()->Set_EditMode(true);
	CTileMgr::Get_Instance()->Initialize();
	CBlockMgr::Get_Instance()->Set_EditorMode(true);
	CObjMgr::Get_Instance()->Set_EditorMode(true);
	CBlockMgr::Get_Instance()->Initialize();
	
}

int CMyEdit::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CBlockMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	Key_Input();
	return 0;
}
void CMyEdit::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CBlockMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int	iMoveX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX()) - 2;
	int	iMoveY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY()) - 2;

	int	iCullCX = iMoveX + WINCX + 2;
	int	iCullCY = iMoveY + WINCY + 2;

	HDC hGroundDC;
	HDC hBackDC;

	switch (m_iEditStage)
	{
	case SC_STAGE_FIELD:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Field");
		BitBlt(hDC, iScrollX, iScrollY, 2500, 1706, hGroundDC, 0, 0, SRCCOPY);
		break;
	case SC_STAGE_BOSS:
		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"BossBack");
		BitBlt(hDC, iScrollX, iScrollY, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"BossStage");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			iScrollX,	// 2,3 인자 :  복사받을 위치 X, Y
			iScrollY + 50,
			WINCX,				// 4,5 인자 : 복사받을 가로, 세로 길이
			WINCY,
			hGroundDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			352,				// 복사할 비트맵의 가로, 세로 길이
			255,
			RGB(128, 128, 128));			// 제거하고자 하는 색상
		break;
	case SC_STAGE_ENDING:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"EndingStage");
		BitBlt(hDC, iScrollX, iScrollY, 800, 1040, hGroundDC, 0, 0, SRCCOPY);
		break;
	case SC_STAGE_DUNGEON:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Dungeon");
		BitBlt(hDC, iScrollX, iScrollY, 1500, 3611, hGroundDC, 0, 0, SRCCOPY);
		break;
	case SC_STAGE_STORE:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Store");
		BitBlt(hDC, iScrollX, iScrollY, 1500, 923, hGroundDC, 0, 0, SRCCOPY);
		break;
	case SC_STAGE_STOREROOM:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"StoreRoom");
		BitBlt(hDC, iScrollX, iScrollY, 800, 613, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_STAGE_SHOESTORE:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"ShoeStore");
		BitBlt(hDC, iScrollX, iScrollY, 800, 600, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_MINIROAD:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniRoad");
		BitBlt(hDC, iScrollX, iScrollY, 800, 2200, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_MINIWORLD:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniWorld");
		BitBlt(hDC, iScrollX, iScrollY, 1500, 1464, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_MINIROOM:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniRoom");
		BitBlt(hDC, iScrollX, iScrollY, 800, 600, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_MINIROOM2:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniRoom2");
		BitBlt(hDC, iScrollX, iScrollY, 800, 600, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_MINIROOM3:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniRoom3");
		BitBlt(hDC, iScrollX, iScrollY, 800, 600, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_MINIWOOD:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniWood");
		BitBlt(hDC, iScrollX, iScrollY, 800, 825, hGroundDC, 0, 0, SRCCOPY);
		break;

	case SC_MINICHIEF:
		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"MiniChief");
		BitBlt(hDC, iScrollX, iScrollY, 800, 600, hGroundDC, 0, 0, SRCCOPY);
		break;
	default:
		break;
	}
	

	CTileMgr::Get_Instance()->Render(hDC);
	CBlockMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

	TCHAR sztPoints[32] = L"";
	swprintf_s(sztPoints, L"1.Grass");
	TextOut(hDC, 0, 0, sztPoints, lstrlen(sztPoints));

	TCHAR sztPoints2[32] = L"";
	swprintf_s(sztPoints2, L"2. Jar");
	TextOut(hDC, 0, 15, sztPoints2, lstrlen(sztPoints2));

	TCHAR sztPoints3[32] = L"";
	swprintf_s(sztPoints3, L"3. Snake_Monster");
	TextOut(hDC, 0,  30, sztPoints3, lstrlen(sztPoints3));

	TCHAR sztPoints4[32] = L"";
	swprintf_s(sztPoints4, L"4. BossMonster");
	TextOut(hDC, 0, 45, sztPoints4, lstrlen(sztPoints4));

	TCHAR sztPoints5[32] = L"";
	swprintf_s(sztPoints5, L"5. OctopusMonster");
	TextOut(hDC, 0, 60, sztPoints5, lstrlen(sztPoints5));

	TCHAR sztPoints6[32] = L"";
	swprintf_s(sztPoints6, L"6. Treasure_Chest");
	TextOut(hDC, 0, 75, sztPoints6, lstrlen(sztPoints6));

	TCHAR sztPoints7[32] = L"";
	swprintf_s(sztPoints7, L"7. Mushroom");
	TextOut(hDC, 0, 90, sztPoints7, lstrlen(sztPoints7));

	TCHAR sztPoints8[32] = L"";
	swprintf_s(sztPoints8, L"8. SwitchTile");
	TextOut(hDC, 0, 105, sztPoints8, lstrlen(sztPoints8));

	TCHAR sztPoints9[32] = L"";
	swprintf_s(sztPoints9, L"9. Fire");
	TextOut(hDC, 0, 120, sztPoints9, lstrlen(sztPoints9));

	TCHAR sztPoints0[32] = L"";
	swprintf_s(sztPoints0, L"0. MoblinMonster");
	TextOut(hDC, 0, 135, sztPoints0, lstrlen(sztPoints0));

	TCHAR sztPointsF1[32] = L"";
	swprintf_s(sztPointsF1, L"Q. RockMonster");
	TextOut(hDC, 0, 135, sztPointsF1, lstrlen(sztPointsF1));

	TCHAR sztPointsF2[32] = L"";
	swprintf_s(sztPointsF2, L"W. Wood");
	TextOut(hDC, 0, 150, sztPointsF2, lstrlen(sztPointsF2));
}


void CMyEdit::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBlockMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
}

void CMyEdit::Key_Input(void)
{
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(10.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-10.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(10.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-10.f);


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON)) //한번 누르면 타일 종류가 바뀌게
	{
		CTileMgr::Get_Instance()->Change_Tile(pt, 1, 0);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON)) //꾹 누르면 타일 깔 수 있게
	{
		CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 0, TILE_EDIT);
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON)) //타일 또는 블럭 삭제
	{
		CTileMgr::Get_Instance()->Delete_Tile(pt, 1, 0);
		CBlockMgr::Get_Instance()->Delete_Block(pt, 1, 0);
		CObjMgr::Get_Instance()->Delete_Obj(pt, 1, 0);
	}
		

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CBlockMgr::Get_Instance()->Picking_Block(pt, BLOCK_GRASS);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CBlockMgr::Get_Instance()->Picking_Block(pt, BLOCK_JAR);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		int iX = pt.x - (pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
		int iY = pt.y - (pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

		CObj* pObj = CAbstractFactory<CSnakeMonster>::Create((float)iX, (float)iY);
		pObj->Set_EditorMode(true);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		int iX = pt.x - (pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
		int iY = pt.y - (pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

		CObj* pObj = CAbstractFactory<CBossMonster>::Create((float)iX, (float)iY);
		pObj->Set_EditorMode(true);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		int iX = pt.x - (pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
		int iY = pt.y - (pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

		CObj* pObj = CAbstractFactory<COctopusMonster>::Create((float)iX, (float)iY);
		pObj->Set_EditorMode(true);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('6'))
	{
		CBlockMgr::Get_Instance()->Picking_Block(pt, BLOCK_CHEST);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('7'))
	{
		CBlockMgr::Get_Instance()->Picking_Block(pt, BLOCK_MUSHROOM);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('8'))
	{
		CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 0, TILE_SWITCH);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('9'))
	{
		CBlockMgr::Get_Instance()->Picking_Block(pt, BLOCK_FIRE);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('0'))
	{
		int iX = pt.x - (pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
		int iY = pt.y - (pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

		CObj* pObj = CAbstractFactory<CMoblinMonster>::Create((float)iX, (float)iY);
		pObj->Set_EditorMode(true);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		int iX = pt.x - (pt.x % (BLOCKCX)) + int(BLOCKCX*0.5f);
		int iY = pt.y - (pt.y % (BLOCKCY)) + int(BLOCKCY*0.5f);

		CObj* pObj = CAbstractFactory<CRockMonster>::Create((float)iX, (float)iY);
		pObj->Set_EditorMode(true);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		CBlockMgr::Get_Instance()->Picking_Block(pt, BLOCK_WOOD);
	}





	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CTileMgr::Get_Instance()->Save_Tile(m_iEditStage);
		CBlockMgr::Get_Instance()->Save_Block(m_iEditStage);
		CObjMgr::Get_Instance()->Save_Monster(m_iEditStage);
	}


	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		CTileMgr::Get_Instance()->Load_Tile(m_iEditStage);
		CBlockMgr::Get_Instance()->Load_Block(m_iEditStage);
		CObjMgr::Get_Instance()->Load_Monster(m_iEditStage);
	}


}
