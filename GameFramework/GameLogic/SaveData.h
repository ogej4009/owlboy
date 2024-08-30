#pragma once
#include <GameMath.h>
#include <GameString.h>

// ����-> ������ �����ͼ� �̰��� ��Ī�ϰ�, ������. ����ü�� �װ��� �ؼ� ������ �ؼ� ���� �ִ� �ʿ�����Ʈ �����Ϳ� �ϳ��� �����͸� ������ �ְ� �Ѵ�. 
// ���̾�� �翬�� int���� �Ѵ�. 

enum class SAVEMAPDIR
{
	L,
	R,
	T,
	B,
	MAX
};

class MapObjData
{
public:
	int Type;
	CVector Pos;
	GameString Name;
};

class SaveMapObjData
{
public:
	union
	{
		struct
		{
			bool ArrSaveDir[(int)SAVEMAPDIR::MAX];
		};
	};
	CVector ArrSaveMapDir[(int)SAVEMAPDIR::MAX];

	wchar_t BackSprite[256];
};


