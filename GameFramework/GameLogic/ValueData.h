#pragma once
#include "GameUnity.h"


class CStaticData
{
public:
	int4 Index;
	CVector Scale;
	CVector Rot;
	CVector Pos;
};

class CStaticActorData
{
public:
	int4 ActorType;
	CStaticData MeshData;
};

class CAnimData
{
public:
	int4 Type;
	CVector Scale;
	CVector Rot;
	CVector Pos;
};


class ValueData
{
public:
	static CVector CAM_DEFAULT_POS;
	static float PIXEL_RATIO;
	static float PIXEL_SCALE;
	static GameString STAGE_NAME;
	static CVector STAGE_SCALE;
	static CVector HERO_DEFAULT_POS_INSTAGE;
	static float HERO_DEFAULT_Z_ORDER;
	static float COL_LEVEL_DEFAULT_Z_ORDER;
};

bool OverCheck(CVector Pos);

class DayCycle
{
	float DayTime;

};


//
//class ItemData
//{
//	std::wstring mName;
//	int mDamage = 0;
//	int mMaxDamage = 0;
//	int mArmor = 0;
//	int mMaxArmor = 0;
//	int mDurability = 0;
//	CHAR_STATS mRequire1 = CS_MAX;
//	CHAR_STATS mRequire2 = CS_MAX;
//	int mRequire1Amount = 0;
//	int mRequire2Amount = 0;
//	int mPrice = 0;
//	int mItemLevel = 0;
//	ITEM_TYPE mType = IT_MAX;
//	int mStr = 0;
//	int mDex = 0;
//	int mVit = 0;
//	int mMag = 0;
//	int X = 0;
//	int Y = 0;
//	int gold = 0;
//	float mDropRate = 0.f;
//	// Gold: 30.3%
//	// Item: 10.7%
//	// Nothing : 59.0%
//};


//class UnitData
//{
//public:
//	const wchar_t* name = {};
//	int dlevel = 1;
//	int mLevel = 1;
//	int mMaxHP = 0;
//	int mMaxMP = 0;
//	int armor = 0;
//	int toHit = 0;
//	int attackMin = 0;
//	int attackMax = 0;
//	int gold = 0;
//	int exp = 0;
//
//};