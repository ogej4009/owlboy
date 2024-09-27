#include "LevelDesignTool.h"
#include <GameCol.h>



void LevelDesignTool::TileMapUpdate()
{

}

void LevelDesignTool::AnimationUpdate()
{

}

void LevelDesignTool::BackdropUpdate()
{
	
}

void LevelDesignTool::ClearMapObj()
{
	for (auto& Var : AllMapObjData)
	{
		Var.first->Death();
	}

	AllMapObjData.clear();
}

void LevelDesignTool::AddSelMapObj(int _Select, CVector _Pos)
{
	MapObjData Data;

	CPtr<GameActor> NewActor = nullptr;

	Data.Type = _Select;

	switch (_Select)
	{
	case 0:
	{
		//NewActor = GetScene()->CreateActor();
		//NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		//NewActor->GetTrans()->SetWScale({ 1.28f, 1.28f, 1.0f });	
	}

	// NewActor->CreateCom
	// <4���������ǿ�����Ʈ���ִ�.>
	// (int�� �ٰŴ�.valuedataȤ�� enumdata����� �̸��� int�� �����س��Ҵ�. );

	break;
	case 1:
	{

	}
	default:
		break;
	}

	Data.Pos = _Pos;
	// Data.Name = _Name;

	AllMapObjData.insert(std::map<GameActor*, MapObjData>::value_type(NewActor, Data));

}

void LevelDesignTool::DelMapObj(GameCol* _Cursor, GameCol* _Obj)
{
	if (true == GameInput::Down(L"DELETE"))
	{
		std::map<GameActor*, MapObjData>::iterator FindObj = AllMapObjData.find(_Obj->GetActor());

		if (FindObj == AllMapObjData.end())
		{
			MSG_ASSERT_CODE(L"�������� �ʴ� ���͸� ������� �߽��ϴ�.");
		}

		FindObj->first->Death();
		AllMapObjData.erase(FindObj);
	}
}

void LevelDesignTool::ClearEntity()
{

}

void LevelDesignTool::AddSelEntity(int _Select, CVector _Pos)
{

}

void LevelDesignTool::DelEntity(GameCol* _Cursor, GameCol* _Obj)
{

}

void LevelDesignTool::ClearBackDrop()
{

}

void LevelDesignTool::AddSelBackDrop(int _Select, CVector _Pos)
{

}

void LevelDesignTool::DelBackDrop(GameCol* _Cursor, GameCol* _Obj)
{

}


