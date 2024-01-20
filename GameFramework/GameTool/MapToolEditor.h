#pragma once
#include "GameUnity.h"
#include <SaveData.h>

class EditorCam;
class GameTileRenderer;
class MapToolEditor : public SceneComponent
{
	friend class Dlg0;
	friend class Dlg1;
	friend class Dlg2;
	friend class Dlg3;
	friend class Dlg4;

	// 맵..
public:
	static MapToolEditor* MainMapToolEditor;

public:
	static MapToolEditor* GetMainMapToolEditor()
	{
		return MainMapToolEditor;
	}

	// 카메라..
public:
	CPtr<GameActor> m_CamActor;
	CPtr<EditorCam>	m_CamCom;

	// 충돌레벨..
public:
	//static TileMap* TileMapCom;
	static 	GameTileRenderer* TileMapCom;
	int Index;
	bool Trigger;
	// 엔티티..
public:
	static std::map<GameActor*, EntityData> TotalEntityData;

public:
	static std::vector<CPtr<GameActor>> EntityActor; 
	//static std::vector<EntityData> EntityData;


	// 엔티티..
public:
	void CreateEntity(int _Index, CVector _Pos, GameString _Name);
	static void ClearEntity();

public:
	static void EntityFunc(GameCol* _Mouse, GameCol* _Entity);

	// 충돌레벨..
public:
	void TileInit(int _Idx);
	void TileUpdate();
	void TileTrigger(bool _Trigger);

	// 기본..
public:
	void Progress();

public:
	void Init() override;
	void Update() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void SceneDebugDisplay();
	void SceneValueDataInit();

public:
	void FileCreate();
	void FileDelete();

public:
	MapToolEditor();
	~MapToolEditor();
};

