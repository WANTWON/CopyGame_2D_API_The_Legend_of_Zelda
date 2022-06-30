#include "stdafx.h"
#include "CollisionMgr.h"
#include "Tile.h"
#include "Block.h"
#include "Player.h"
#include "Jar.h"
#include "Monster.h"
#include "Bullet.h"
#include "TileMgr.h"


RECT rc = {};

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Collsion_Rect(list<CObj*> vecList, CObj * pObj)
{
	for (auto& iter : vecList)
	{
		float fWidth = 0;
		float fHeight = 0;

		if (Check_Rect(pObj, iter, &fWidth, &fHeight))
		{
			if (iter->Get_ID() == OBJ_MONSTER)
			{
				if (static_cast<CMonster*>(iter)->Get_CurState() == CMonster::DEAD)
					return false;
			}
			return true;
		}

	}
	return false;
}

bool CCollisionMgr::Collsion_Tile(vector<CObj*> vecList, CObj * pObj)
{

	for (auto& iter : vecList)
	{
		float fWidth = 0;
		float fHeight = 0;

		if (Check_Rect(pObj, iter, &fWidth, &fHeight) && 
			static_cast<CTile*>(iter)->Get_Option() == 0)
		{
			if (fWidth > fHeight)	//상하충돌
			{
				if (pObj->Get_Info().fY < iter->Get_Info().fY) //상충돌
					pObj->Set_PosY(-fHeight);
				else
					pObj->Set_PosY(fHeight); //하충돌

				return true;
			}
			else
			{
				if (pObj->Get_Info().fX < iter->Get_Info().fX) //좌충돌
					pObj->Set_PosX(-fWidth);
				else
					pObj->Set_PosX(fWidth);//우충돌


				return true;
			}
		}
		else if (Check_Rect(pObj, iter, &fWidth, &fHeight) &&
			static_cast<CTile*>(iter)->Get_Option() == 1 && pObj->Get_ID() == OBJ_PLAYER)
		{
			if (static_cast<CPlayer*>(pObj)->Get_State() != CPlayer::MINIMODE)
				static_cast<CPlayer*>(pObj)->Set_State(CPlayer::FALL_WATER);
			else
				static_cast<CPlayer*>(pObj)->Set_FallWater();
		}
		else if (Check_Rect(pObj, iter, &fWidth, &fHeight) &&
			(static_cast<CTile*>(iter)->Get_Option() == 4)&& pObj->Get_ID() == OBJ_PLAYER)
		{
			if (static_cast<CPlayer*>(pObj)->Get_State() == CPlayer::FLY)
				return true;

			static_cast<CPlayer*>(pObj)->Set_State(CPlayer::FALLING);
		}
		else if (Check_Rect(pObj, iter, &fWidth, &fHeight) &&
			(static_cast<CTile*>(iter)->Get_Option() == 2) && pObj->Get_ID() == OBJ_PLAYER)
		{
			if (static_cast<CPlayer*>(pObj)->Get_State() == CPlayer::FLY
				|| CTileMgr::Get_Instance()->Get_SolvedTiles() != 0)
				return true;
				static_cast<CPlayer*>(pObj)->Set_State(CPlayer::FALLING);		
		}

	}

	return false;
}

bool CCollisionMgr::Collsion_Block(list<CObj*> BlockList, CObj * pObj)
{
	for (auto& iter : BlockList)
	{
		float fWidth = 0;
		float fHeight = 0;

		if (static_cast<CBlock*>(iter)->Get_BlockType() == BLOCK_WOOD)
			continue;

		if (Check_Rect(pObj, iter, &fWidth, &fHeight) &&
			static_cast<CBlock*>(iter)->Get_DrawID() == 0)
		{
			if (fWidth > fHeight)	//상하충돌
			{
				if (pObj->Get_Info().fY < iter->Get_Info().fY) //상충돌
					pObj->Set_PosY(-fHeight);
				else
					pObj->Set_PosY(fHeight); //하충돌
			}
			else
			{
				if (pObj->Get_Info().fX < iter->Get_Info().fX) //좌충돌
					pObj->Set_PosX(-fWidth);
				else
					pObj->Set_PosX(fWidth);//우충돌
			}

			return true;
		}
	}
	return false;
}

bool CCollisionMgr::Collsion_Wood(list<CObj*> BlockList, CObj * pObj)
{
	for (auto& iter : BlockList)
	{
		float fWidth = 0;
		float fHeight = 0;

		if (Check_Rect(pObj, iter, &fWidth, &fHeight) &&
			static_cast<CBlock*>(iter)->Get_Option() == 5)
		{
			

			return true;
		}
	}
	return false;
}

bool CCollisionMgr::Collsion_Bullets(list<CObj*> BulletList, CObj* pObj)
{
	if (BulletList.empty())
		return false;

	if (pObj->Get_ID() == OBJ_PLAYER)
	{
		for (auto& iter = BulletList.begin(); iter != BulletList.end(); ++iter)
		{
			if (OBJ_MONSTER == (*iter)->Get_ID() && IntersectRect(&rc, &(pObj->Get_Rect()), &((*iter)->Get_Rect()))) //몬스터의 총알에 맞았을 때
			{
				
				static_cast<CPlayer*>(pObj)->Set_BeAttacked();

				if(static_cast<CBullet*>(*iter)->Get_BulletType() != BULLET_LASER)
					(*iter)->Set_Dead();
			}
		}
	}
	else
	{
		for (auto& iter = BulletList.begin(); iter != BulletList.end(); ++iter)
		{
			if (OBJ_PLAYER == (*iter)->Get_ID() && IntersectRect(&rc, &(pObj->Get_Rect()), &((*iter)->Get_Rect()) ))
			{
				if (OBJ_MONSTER == pObj->Get_ID()) //피격 대상이 몬스터일 때
				{
					//pObj->Minus_Hp();

					if (static_cast<CBullet*>(*iter)->Get_BulletType() == BULLET_THUNDER)
					{
							static_cast<CMonster*>(pObj)->Set_BeCritical();
					}
					else if (static_cast<CBullet*>(*iter)->Get_BulletType() == BULLET_KAGURA)
					{
							static_cast<CMonster*>(pObj)->Set_m_bMegaCritical();
					}
					else
						static_cast<CMonster*>(pObj)->Set_BeAttack();
				}
				else if (OBJ_BLOCK ==  pObj->Get_ID()) //피격 대상이 블록일 때
				{
					BLOCKID eBlocktype = static_cast<CBlock*>(pObj)->Get_BlockType();

					switch (eBlocktype)
					{
					case BLOCK_GRASS:
						CSoundMgr::Get_Instance()->PlaySoundW(L"Cut_Grass.wav", ITEM_EFFECT, g_fSound);
						dynamic_cast<CBlock*>(pObj)->Set_DrawID(1);
						break;
					case BLOCK_JAR:
						dynamic_cast<CJar*>(pObj)->Break_Jar();
						break;
					case BLOCK_CHEST:
						dynamic_cast<CBlock*>(pObj)->Set_DrawID(1);
						break;
					case BLOCK_FIRE:
					{
						if (static_cast<CBullet*>(*iter)->Get_BulletType() == BUllET_FIRE)
						{
							dynamic_cast<CBlock*>(pObj)->Set_Option(1);
						}
							
						break;
					}
					case BLOCK_SEED:
						if (static_cast<CBullet*>(*iter)->Get_BulletType() == BULLET_MAGIC)
							return true;
						break;
					default:
						break;
					}
					
				}
			}
		}
	}
	return false;
}

bool CCollisionMgr::Check_Rect(CObj * pObj, CObj * pTarget, float* _fWidth , float* _fHeight )
{
	float	fWidth = abs(pObj->Get_Info().fX - pTarget->Get_Info().fX);
	float	fHeight = abs(pObj->Get_Info().fY - pTarget->Get_Info().fY);

	float fRadiusX = (pObj->Get_Info().fCX + pTarget->Get_Info().fCX)*0.5f;
	float fRadiusY = (pObj->Get_Info().fCY + pTarget->Get_Info().fCY)*0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*_fWidth = fRadiusX - fWidth;
		*_fHeight = fRadiusY - fHeight;

		return true;
	}


	return false;
}
