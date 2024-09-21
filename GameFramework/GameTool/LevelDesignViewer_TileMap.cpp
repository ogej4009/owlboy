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

void LevelDesignViewer::DeleteMapObj(GameCol* _Cursor, GameCol* _Obj)
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

