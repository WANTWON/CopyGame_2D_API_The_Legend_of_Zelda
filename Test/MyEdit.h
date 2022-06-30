#pragma once
#include "Scene.h"
class CMyEdit : public CScene
{
public:
	CMyEdit();
	~CMyEdit();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Key_Input(void);
	void Set_EditStage(SCENEID Stage) { m_iEditStage = Stage; }

private:
	SCENEID m_iEditStage;
};

