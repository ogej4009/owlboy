#include "LevelDesignViewer.h"


void LevelDesignViewer::CreateAnimationMesh()
{



}



void LevelDesignViewer::CreateStaticMesh()
{
	//NewActor = nullptr;

	//WGAMESTRING _Str = std::to_wstring(_FbxObjectData.MeshData.Index.x);

	////////////////////// 스케일값은 고정한다. 
	//if (_FbxObjectData.ActorType.x == (int)MESHDATATYPE::PROP_cablepack_goingdown_long)
	//{
	//	NewActor = SCENE()->CreateActor();
	//	NewActor->CreateComName<PROP_cablepack_goingdown_long>(_Str);
	//	// 
	//}
	//else if (_FbxObjectData.ActorType.x == (int)MESHDATATYPE::PROP_cables_flow_4)
	//{
	//	NewActor = SCENE()->CreateActor();
	//	NewActor->CreateComName<PROP_cables_flow_4>(_Str);
	//	// 
	//}


	//m_StaticActorData.insert(std::map<WGAMEACTOR*, MeshActorData>::value_type(NewActor, _FbxObjectData));

}




void LevelDesignViewer::ClearEntity()
{

}

void LevelDesignViewer::AddSelEntity(int _Select, CVector _Pos)
{

}

void LevelDesignViewer::DeleteEntity(GameCol* _Cursor, GameCol* _Obj)
{

}


void LevelDesignViewer::ClearBackDrop()
{

}

void LevelDesignViewer::AddSelBackDrop(int _Select, CVector _Pos)
{

}

void LevelDesignViewer::DeleteBackDrop(GameCol* _Cursor, GameCol* _Obj)
{

}