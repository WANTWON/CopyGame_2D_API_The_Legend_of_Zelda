#pragma once
#include "Scene.h"
class CEndingLogo :
	public CScene
{
public:
	CEndingLogo();
	virtual ~CEndingLogo();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	DWORD m_dwDrawTime;
	DWORD m_dwPhotoTime;
	DWORD m_dwButtonTime;


	int m_DrawEffectID;
	int m_DrawUIID;
	int m_DrawPhotoID;
};

