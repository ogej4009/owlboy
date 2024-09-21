#pragma once
#include "GameUnity.h"
#include <SaveData.h>


class MeshCreateData
{
public:
	GameString Name;
	int4	Index;
	CVector	Scale;
	CVector	Rot;
	CVector	Pos;
};

class MeshActorData
{
public:
	int4			Type;
	MeshCreateData	Data;
};

class LightCreateData
{
public:
	int4	Type;
	CVector	Scale;
	CVector	Rot;
	CVector	Pos;
	CVector	AmbColor;
	CVector	SpecPow;
	CVector	LightPower;
	CVector	LightDir;
	CVector	LIghtDirInv;
};


class GameActor;
class FreeCam;
class DesignCam;
class GameTileMap;
class GameTileRenderer;
class LevelDesignViewer : public SceneComponent // MapToolEditor
{
	friend class Dlg0;
	friend class Dlg1;
	friend class Dlg2;
	friend class Dlg3;
	friend class Dlg4;

public:
	static LevelDesignViewer* pViewer;

public:
	struct FogBufferData
	{
		float FogStart;
		float FogEnd;
		float Dummy1;
		float Dummy2;
	};
	CVector PaperBurnTestCBuffer;
	CPtr<GameActor> m_FogActor;


public:

	// 광원
	CPtr<GameActor> m_LightActor;
	CPtr<GameLight> m_LightCom;

	// 관리구조 
	std::map<GameActor*, MeshActorData> m_StaticActorData;
	std::map<GameActor*, MeshCreateData> m_AniMeshComData;
	std::vector<MeshCreateData> m_AllMeshData;
	std::map<int, LightCreateData> m_LightCreateMeshComData;
	std::map<int, CPtr<GameLight>> m_LightMeshComData;

	// 월드좌표 
	CVector m_ScreenPos3DToWorldPos;
	int m_Index;

	// 타일맵
	CPtr<GameActor> m_GridActor;
	CPtr<GameRenderer> m_GridRender;
	CPtr<GameActor> m_TileRenderActor;
	CPtr<GameTileRenderer> m_TileRenderCom;
	CPtr<GameActor> m_TileMapActor;
	CPtr<GameTileMap> m_TileMapCom;

	// 카메라
	CPtr<GameActor> m_CamActor;
	CPtr<GameCamera> m_CamCom;
	CPtr<GameActor> m_DesignCamActor;
	CPtr<DesignCam> m_DesignCamCom;
	CPtr<GameActor> m_FreeCamActor;
	CPtr<FreeCam> m_FreeCamCom;

	// 관리구조 
	static std::map<GameActor*, MapObjData> AllMapObjData;
	static std::map<GameString*, SaveMapObjData> AllSaveMapObjData;

public:
	// 타일맵함수 
	static void ClearMapObj();
	static void AddSelMapObj(int _Select, CVector _Pos);
	static void DeleteMapObj(GameCol* _Cursor, GameCol* _Obj);

	// 엔티티함수
	static void ClearEntity();
	static void AddSelEntity(int _Select, CVector _Pos);
	static void DeleteEntity(GameCol* _Cursor, GameCol* _Obj);

	// 백드롭함수 (옵션)
	static void ClearBackDrop();
	static void AddSelBackDrop(int _Select, CVector _Pos);
	static void DeleteBackDrop(GameCol* _Cursor, GameCol* _Obj);

public:
	void CtrlUpdate();
	void DebugTargetUpdate();
	
public:
	void CreateAnimationMesh();
	void CreateStaticMesh();
	void FillInAllLightValue();

public:
	void ViewDlg0();
	void ViewDlg1();
	void ViewDlg2();
	void ViewDlg3();
	void ViewDlg4();

public:
	void Progress();

public:
	void Init() override;
	void Update() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void DebugText();

public:
	void File_In();
	void File_Out();

public:
	LevelDesignViewer();
	~LevelDesignViewer();
};
