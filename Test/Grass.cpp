#include "stdafx.h"
#include "Grass.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CGrass::CGrass()
{
}


CGrass::~CGrass()
{
}

void CGrass::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX;
	m_tInfo.fCY = BLOCKCY;

	m_eBlockType = BLOCK_GRASS;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_iOption = 0;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Thicket.bmp", L"Thicket");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Grass.bmp", L"Grass");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Twig.bmp", L"Twig");

	m_pFrameKey = L"Thicket";
}

int CGrass::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CGrass::Late_Update(void)
{
	

	if (m_iOption == 0)
		m_pFrameKey = L"Thicket";
	else if (m_iOption == 1)
		m_pFrameKey = L"Grass";
	else if (m_iOption == 2)
		m_pFrameKey = L"Twig";

	if (m_bEditorMode)
		return;

	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);
}

void CGrass::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hTileDC,							// ��Ʈ���� ������ �ִ� DC
		(16 + 6) * m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		16,				// ������ ��Ʈ���� ����, ���� ����
		16,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����
}

void CGrass::Release(void)
{
}
