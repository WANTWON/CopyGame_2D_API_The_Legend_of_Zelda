#pragma once
typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;
}INFO;

typedef struct tagPoint
{
	float fX;
	float fY;

	tagPoint(void) { ZeroMemory(this, sizeof(tagPoint)); }
}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& tLeft, LINEPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight) {}

}LINE;

typedef struct tagFrame
{
	int iFrameStart;
	int iFrameEnd;
	int iMotion;

	DWORD dwFrameSpeed;
	DWORD dwFrameTime;
}FRAME;

typedef struct tagPlayer
{
	INFO tInfo;

	int			iHp;
	int			iMaxHp;
	int			iCoin;
	int			iKey;

}PLAYERINFO;