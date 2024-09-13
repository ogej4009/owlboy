#pragma once
#include "GameUnity.h"
#include <SaveData.h>


class MeshCreateData
{
public:
	//	GameString  m_MeshName;
	int4		m_Index;
	CVector		m_Scale;
	CVector		m_Rot;
	CVector		m_Pos;
};

class MeshActorData
{
public:
	int4				m_ActorType;
	MeshCreateData		m_MeshData;
};


class LightCreateData
{
public:
	int4		m_Type;
	CVector		m_Scale;
	CVector		m_Rot;
	CVector		m_Pos;
	CVector		m_AmbColor;
	CVector		m_SpecPow;
	CVector		m_LightPower;
	CVector		m_LightDir;
	CVector		m_LIghtDirInv;
};


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
	struct FogBufferData
	{
		float FogStart;
		float FogEnd;
		float Dummy1;
		float Dummy2;
	};
	CVector PaperBurnTestCBuffer;

public:
	int SEL_TILESPR_INDEX;

public:
	CPtr<GameActor> m_TileMapActor;
	CPtr<GameActor> TILERENDERER;

	CPtr<GameActor> m_DesignCamActor;
	CPtr<GameActor> m_CamActor;
	CPtr<GameActor> m_LightActor;
	CPtr<GameActor> m_PlayerActor;
	CPtr<GameActor> m_ColMapActor;
	CPtr<GameActor> m_MapActor;
	CPtr<GameActor> m_FogActor;

	std::map<GameActor*, MeshActorData> m_StaticActorData;
	std::vector<MeshCreateData> m_AllMeshData;
	std::map<GameActor*, MeshCreateData> m_AniMeshComData;
	std::map<int, LightCreateData> m_LightCreateMeshComData;
	std::map<int, CPtr<GameLight>> m_LightMeshComData;

	CPtr<GameActor>		GridActor;
	CPtr<GameRenderer>	GridRender;

	CPtr<GameTileRenderer> TILERENDERCOM;
	CPtr<GameTileMap> m_TileMapCom;

	CPtr<DesignCam> m_DesignCamCom;
	CPtr<GameCamera> m_CamCom;
	CPtr<GameLight> m_LightCom;
	/*
	CPtr<GameBloomFilter> m_BloomFilterCom;
	CPtr<GameOutLineFilter> m_OutLineFilterCom;
	CPtr<GameBoneAnimationComEx> m_BoneAniComEx;
	CPtr<GameFogFilter> m_FogFilterCom;
	*/
	
	CVector m_ScreenPos3DToWorldPos;

public:
	CPtr<GameActor> m_FreeCamActor;
	CPtr<FreeCam>	m_FreeCamCom;

public:
	static int OneMapObj;
	static std::map<GameActor*, MapObjData> AllMapObjData;
	static std::map<GameString*, SaveMapObjData> AllSaveMapObjData;
	static LevelDesignViewer* pViewer;

public:
	static void ClearMapObj();
	static void AddSelMapObj(int _Select, CVector _Pos);
	static void ColMapObj(GameCol* _Cursor, GameCol* _Obj);

public:
	static LevelDesignViewer* G_pViewer()
	{
		return pViewer;
	}


public:
	void InteractionUpdate();
	void TextDebugUpdate();
	void TargetDebugUpdate();
	
public:
	void CreateAnimationMesh();
	void CreateStaticMesh();
	void FillInAllLightValue();

public:
	void Progress();

public:
	void Init() override;
	void Update() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void SceneDebugDisplay();

public:
	void FileCreate();
	void FileDelete();

public:
	LevelDesignViewer();
	~LevelDesignViewer();
};
