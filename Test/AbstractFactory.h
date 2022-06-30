#pragma once

#include "Obj.h"
#include "MenuObj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		pInstance->Set_Angle(_fAngle);

		return pInstance;
	}

	static CObj*		Create(float _fX, float _fY, OBJID _ObjID = OBJ_END)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);

		if(_ObjID != OBJ_END)
			pInstance->Set_ID(_ObjID);

		return pInstance;
	}

	static CMenuObj*		Create_Menu(float _fX, float _fY)
	{
		CMenuObj*		pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		return pInstance;
	}

public:
	CAbstractFactory() {	}
	~CAbstractFactory() { }
};

