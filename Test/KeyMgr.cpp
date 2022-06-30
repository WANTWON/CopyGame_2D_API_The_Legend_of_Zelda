#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}


CKeyMgr::~CKeyMgr()
{
	Release();
}

bool CKeyMgr::Key_Pressing(int _Key)
{
	if (GetAsyncKeyState(_Key) & 0x8000)
		return true;

	
	return false;
}

bool CKeyMgr::Key_Up(int _Key)
{
	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
			m_bKeyState[_Key] = !m_bKeyState[_Key];
	}

	return false;
}

bool CKeyMgr::Key_Down(int _Key)
{
	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}

	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
		m_bKeyState[_Key] = !m_bKeyState[_Key];

	return false;
}

void CKeyMgr::Release(void)
{
}
