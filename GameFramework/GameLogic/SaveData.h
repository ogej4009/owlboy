#pragma once
#include <GameMath.h>
#include <GameString.h>

// 엑셀-> 스펙을 가져와서 이것을 매칭하고, 만들어낸다. 구조체와 그것을 해서 포인터 해서 저기 있는 맵오브젝트 데이터에 하나의 포인터를 가지고 있게 한다. 
// 레이어는 당연히 int여야 한다. 

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


