#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:

	CBullet() : m_eBulletType(BULLET_END)
	{
	}

	virtual ~CBullet()
	{
	}

public:
	virtual		void	Initialize(void) PURE;
	virtual		int		Update(void)	PURE;
	virtual		void	Late_Update(void) PURE;
	virtual		void	Render(HDC hDC) PURE;
	virtual		void	Release(void) PURE;

	void BulletFrame(void)
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;

			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart = 0;
			}


			m_tFrame.dwFrameTime = GetTickCount();
		}
	}

public:
	const BULLETID& Get_BulletType(void) const { return m_eBulletType; }
	void Set_BulletType(BULLETID type) { m_eBulletType = type; }

protected:
	BULLETID m_eBulletType;
};

