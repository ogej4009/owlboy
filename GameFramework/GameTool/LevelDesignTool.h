#pragma once
#include "GameUnity.h"
#include <SaveData.h>



class CActorBaseData
{
public:
	GameString Name;
	int4 Index;
	CVector	Scale;
	CVector	Rot;
	CVector	Pos;
};

class CActorData
{
public:
	int4 Type;
	CActorBaseData	Data;
};

class CLightData
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
class LevelDesignTool : public SceneComponent 
{
	friend class Dlg0;
	friend class Dlg1;
	friend class Dlg2;
	friend class Dlg3;
	friend class Dlg4;

public:
	static LevelDesignTool* InstTool;

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
	std::map<GameActor*, CActorData> m_mapAllActorData;
	std::map<GameActor*, CActorBaseData> m_mapAllActorBaseData;
	std::vector<CActorBaseData> m_vecAllActorBaseData;
	std::map<int, CLightData> m_mapAllLightData;
	std::map<int, CPtr<GameLight>> m_mapAllLight;
	static std::map<GameActor*, MapObjData> AllMapObjData;
	static std::map<GameString*, SaveMapObjData> AllSaveMapObjData;

	// 월드좌표 
	CVector m_ScreenPos3DToWorldPos;
	int m_TileIndex;

	// 타일맵
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


public:
	// 타일맵함수 
	static void ClearMapObj();
	static void AddSelMapObj(int _Select, CVector _Pos);
	static void DelMapObj(GameCol* _Cursor, GameCol* _Obj);

	// 엔티티함수-애니메이션 테스트 
	static void ClearEntity();
	static void AddSelEntity(int _Select, CVector _Pos);
	static void DelEntity(GameCol* _Cursor, GameCol* _Obj);

	// 백드롭함수 (옵션)
	static void ClearBackDrop();
	static void AddSelBackDrop(int _Select, CVector _Pos);
	static void DelBackDrop(GameCol* _Cursor, GameCol* _Obj);

public:
	void DesignCamUpdate();
	void FreeCamUpdate();
	void InputUpdate();
	void RenderTargetUpdate();
	void TextInfoUpdate();
	
//0.BACKDROP
//1.레이어설정
//2.전체캡쳐
//3.타일맵
//4.라이트값

public:
	void TileMapUpdate();
	void AnimationUpdate();
	void BackdropUpdate();
	void LightValueUpdate();

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

public:
	void File_In();
	void File_Out();

public:
	LevelDesignTool();
	~LevelDesignTool();
};


