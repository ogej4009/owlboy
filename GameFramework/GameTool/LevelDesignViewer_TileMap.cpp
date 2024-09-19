#include "LevelDesignViewer.h"
#include <GameCol.h>


void LevelDesignViewer::ClearMapObj()
{
	for (auto& Var : AllMapObjData)
	{
		Var.first->Death();
	}

	AllMapObjData.clear();
}

void LevelDesignViewer::AddSelMapObj(int _Select, CVector _Pos)
{
	MapObjData Data;

	CPtr<GameActor> NewActor = nullptr;

	Data.Type = _Select;

	switch (_Select)
	{
	case 0:
	{
		NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		NewActor->GetTrans()->SetWScale({ 1.28f, 1.28f, 1.0f });
	}
	
		// NewActor->CreateCom
		// <4가지유형의오브젝트가있다.>
		// (int를 줄거다.valuedata혹은 enumdata헤더에 이름을 int로 나열해놓았다. );

		break;
	default:
		break;
	}

	Data.Pos = _Pos;
	// Data.Name = _Name;

	AllMapObjData.insert(std::map<GameActor*, MapObjData>::value_type(NewActor, Data));

}

void LevelDesignViewer::ColDeleteMapObj(GameCol* _Cursor, GameCol* _Obj)
{
	if (true == GameInput::Down(L"DELETE"))
	{
		std::map<GameActor*, MapObjData>::iterator FindObj = AllMapObjData.find(_Obj->GetActor());

		if (FindObj == AllMapObjData.end())
		{
			MSG_ASSERT_CODE(L"존재하지 않는 몬스터를 지우려고 했습니다.");
		}

		FindObj->first->Death();
		AllMapObjData.erase(FindObj);
	}
}

