#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool Collsion_Rect(list<CObj*> vecList, CObj* pObj);
	static bool Collsion_Tile(vector<CObj*> vecList, CObj* pObj);
	static bool Collsion_Block(list<CObj*> BlockList, CObj* pObj);
	static bool Collsion_Bullets(list<CObj*> BulletList, CObj* pObj);

	static bool Check_Rect(CObj* pObj, CObj* pTarget, float* _fWidth, float* _fHeight);
	static bool Collsion_Wood(list<CObj*> BlockList, CObj * pObj);
};

