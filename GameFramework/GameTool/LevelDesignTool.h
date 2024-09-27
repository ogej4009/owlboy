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
	// ����
	CPtr<GameActor> m_LightActor;
	CPtr<GameLight> m_LightCom;

	// �������� 
	std::map<GameActor*, CActorData> m_mapAllActorData;
	std::map<GameActor*, CActorBaseData> m_mapAllActorBaseData;
	std::vector<CActorBaseData> m_vecAllActorBaseData;
	std::map<int, CLightData> m_mapAllLightData;
	std::map<int, CPtr<GameLight>> m_mapAllLight;
	static std::map<GameActor*, MapObjData> AllMapObjData;
	static std::map<GameString*, SaveMapObjData> AllSaveMapObjData;

	// ������ǥ 
	CVector m_ScreenPos3DToWorldPos;
	int m_TileIndex;

	// Ÿ�ϸ�
	CPtr<GameActor> m_TileRenderActor;
	CPtr<GameTileRenderer> m_TileRenderCom;
	CPtr<GameActor> m_TileMapActor;
	CPtr<GameTileMap> m_TileMapCom;

	// ī�޶�
	CPtr<GameActor> m_CamActor;
	CPtr<GameCamera> m_CamCom;
	CPtr<GameActor> m_DesignCamActor;
	CPtr<DesignCam> m_DesignCamCom;
	CPtr<GameActor> m_FreeCamActor;
	CPtr<FreeCam> m_FreeCamCom;


public:
	// Ÿ�ϸ��Լ� 
	static void ClearMapObj();
	static void AddSelMapObj(int _Select, CVector _Pos);
	static void DelMapObj(GameCol* _Cursor, GameCol* _Obj);

	// ��ƼƼ�Լ�-�ִϸ��̼� �׽�Ʈ 
	static void ClearEntity();
	static void AddSelEntity(int _Select, CVector _Pos);
	static void DelEntity(GameCol* _Cursor, GameCol* _Obj);

	// �����Լ� (�ɼ�)
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
//1.���̾��
//2.��üĸ��
//3.Ÿ�ϸ�
//4.����Ʈ��

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


