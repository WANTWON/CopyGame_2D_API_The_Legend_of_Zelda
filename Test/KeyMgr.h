#pragma once

#include "Include.h"

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool		Key_Pressing(int _Key);
	bool		Key_Up(int _Key);		// 누르고 있다가 뗐을 때
	bool		Key_Down(int _Key);		// 눌렀을 때

	void		Release(void);
public:
	static		CKeyMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyMgr;

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
	static		CKeyMgr*		m_pInstance;
	bool						m_bKeyState[VK_MAX];
};

