#include "pch.h"
#include "LevelDesignViewer.h"
#include "RView.h"
// -------------------------------- BAS
// -------------------------------- ENG
#include <GameCol.h>
#include <GameDebugPlus.h>
#include <GameLight.h>
#include <GameRenderTarget.h>
#include <GameTileRenderer.h>
#include <GameTileMap.h>
#include <GameMesh.h>
#include <EnumData.h>
#include <ValueData.h>
#include <DesignCam.h>
#include <FreeCam.h>



int LevelDesignViewer::OneMapObj = 0;
LevelDesignViewer* LevelDesignViewer::pViewer = nullptr;
std::map<GameActor*, MapObjData> LevelDesignViewer::AllMapObjData;
std::map<GameString*, SaveMapObjData> LevelDesignViewer::AllSaveMapObjData;

LevelDesignViewer::LevelDesignViewer()
{
	pViewer = this;
}

LevelDesignViewer::~LevelDesignViewer()
{
}


void LevelDesignViewer::ClearMapObj()
{
	//for (auto& Var : AllMapObjData)
	//{
	//	Var.first->Death();
	//}

	//AllMapObjData.clear();
}

void LevelDesignViewer::AddSelMapObj(int _Select, CVector _Pos)
{
	/*MapObjData Data;
	CPtr<GameActor> NewActor = nullptr;
	Data.Type = _Select;

	switch (_Select)
	{
	case 0:
	{
		NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		{
			NewActor->GetTrans()->SetWScale({ 1.28f, 1.28f, 1.0f });
		}
		NewActor->CreateCom<4가지유형의오브젝트가있다.>(int를 줄거다.valuedata혹은 enumdata헤더에 이름을 int로 나열해놓았다. );
	}
	break;
	default:
		break;
	}

	Data.Pos = _Pos;
	AllMapObjData.insert(std::map<GameActor*, MapObjData>::value_type(NewActor, Data));*/
}

void LevelDesignViewer::ColMapObj(GameCol* _Cursor, GameCol* _Obj)
{
	//if (true == GameInput::Down(L"DELETE"))
	//{
	//	std::map<GameActor*, MapObjData>::iterator FindObj = AllMapObjData.find(_Obj->GetActor());

	//	if (FindObj == AllMapObjData.end())
	//	{
	//		MSG_ASSERT_CODE(L"존재하지 않는 몬스터를 지우려고 했습니다.");
	//	}

	//	FindObj->first->Death();
	//	AllMapObjData.erase(FindObj);
	//}
}

void LevelDesignViewer::Progress()
{
	GameScene::Progress();
}

void LevelDesignViewer::Init()
{

#pragma region FOG에관하여 
	PaperBurnTestCBuffer = CVector{ 0.0f,0.0f ,0.0f ,3.0f };
	FogBufferData DATA;

	float BorderNear = 0.0f;
	float BorderFar = 50.0f;

	DATA.FogStart = BorderNear;
	DATA.FogEnd = BorderFar;
#pragma endregion

#pragma region COLLISION(충돌연결)
	GetScene()->ColLink(0,1); // 예시
#pragma endregion

	SEL_TILESPR_INDEX = 0;

	if (nullptr == GameInput::FindKey(L"SELECT"))
	{
		GameInput::CreateKey(L"SELECT", VK_LBUTTON);
		GameInput::CreateKey(L"DELETE", VK_RBUTTON);
		GameInput::CreateKey(L"CLEAR", 'C');
		GameInput::CreateKey(L"AMB_UP", 'V');
		GameInput::CreateKey(L"AMB_DOWN", 'B');
	}

	FileCreate();

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetLPos(ValueData::CAM_DEF_POS);
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0
			, (UINT)RENDER_ORDER::RO_ACTOR
			, (UINT)RENDER_ORDER::RO_COL_LEVEL);
		NewCam->SetCamSize({ 12.8f, 7.2f });
		NewCam->SetMode(CAMMODE::ORTH);
		//m_FreeCamCom = NewActor->CreateCom<FreeCam>(10.0f);
		//m_FreeCamActor = NewActor;
		m_DesignCamCom = NewActor->CreateCom<DesignCam>();
		m_DesignCamActor = NewActor;
	} 


	{
		TILERENDERER = GetScene()->CreateActor();
		TILERENDERCOM = TILERENDERER->CreateCom<GameTileRenderer>(80, 46, L"ColLevel2.png", 0);
		TILERENDERCOM->SetMapSize({ 12.80f, 7.20f, 1.0f });
		TILERENDERER->GetTrans()->SetWScale({ TILE_INTERVAL_A, TILE_INTERVAL_A, 1.0f }); // 맵 사이즈 커스텀 
	}

	/*{
		m_TileMapActor = GetScene()->CreateActor();
		m_TileMapCom = m_TileMapActor->CreateCom<GameTileMap>(80, 46, L"ColLevel2.png", 4);
		m_TileMapActor->GetTrans()->SetWScale({ 12.80f, 7.20f, 1.0f });
	}*/


	//{
	//	CPtr<GameActor> NewActor = GetScene()->CreateActor();
	//	CPtr<GameRenderer> NewRender = NewActor->CreateCom<GameRenderer>(L"Grid", L"Grid"); //  메쉬, 메테리얼
	//	NewRender->SetCBuffer(L"TransDataPlus", NewRender->PTransDataPlus(), CBUFMODE::CB_LINK);
	//	NewActor->GetTrans()->SetWScale({ 12.80f, 7.20f, 1.0f });
	//}


	//{
	//	GridActor = GetScene()->CreateActor();
	//	GridRender = GridActor->CreateCom<GameRenderer>(L"GridMesh", L"Grid");
	//	GridActor->GetTrans()->SetWScale({ 10000.0f, 10000.0f, 10000.0F });
	//	GridRender->SetCBuffer(L"CAMDATA", &GridRender->GetTransDataPlus());
	//}


	//{
	//	CPtr<GameActor> NewActor = GetScene()->CreateActor();
	//	//NewActor->GetTrans()->SetLScale({ 12.8f * 10.0f, 7.2f * 10.0f, 3.0f });
	//	NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, -8.0f });
	//	CPtr<GameSpriteRenderer> NewRender = 
	//		NewActor->CreateCom<GameSpriteRenderer>(L"TestGrid.png", (int)RENDER_ORDER::RO_ACTOR);
	//	NewRender->SetSprite(L"TestGrid.png", 0);
	//	NewRender->SetSrcSizeOfTexture(L"TestGrid.png");
	//}

	/* 
	{
		WPTR<WGAMEACTOR> NewActor = SCENE()->CreateActor();
		WPTR<WRENDERER> NewRender = NewActor->CreateCom<WRENDERER>(L"GRIDMESH", L"GRID");
		NewRender->CBUFFER(L"WWTRANSDATA", NewRender->PTRANSDATANEEDS(), CBUFFERMODE::CB_LINK);
		NewActor->TRANS()->WSCALE({ 10000.0F, 10000.0F, 10000.0F });
	}
	*/



#pragma region SPHERE
	/*{
		WPTR<WGAMEACTOR> NewActor = SCENE()->CreateActor();
		WPTR<WRENDERER> NewRender = NewActor->CreateCom<WRENDERER>(L"SPHERE", L"Defferd");
		NewActor->TRANS()->LPOS({ -2.0F, 2.0F, 2.0F });
		NewRender->ShadowOn();
	}
	{
		WPTR<WGAMEACTOR> NewActor = SCENE()->CreateActor();
		WPTR<WRENDERER> NewRender = NewActor->CreateCom<WRENDERER>(L"SPHERE", L"Foward");
		NewRender->GetRenderPlayer(0)->RenderOption.IsDifTexture = false;
		NewRender->GetRenderPlayer(0)->RenderOption.IsNormalTexture = true;
		NewRender->TEXTURE(L"NormalTexture", L"BumpTest.png");
		NewActor->TRANS()->LPOS({ 2.0F, 2.0F, 2.0F });
	}*/
#pragma endregion


#pragma region PLAYER 유저
	//{
	//	m_PlayerActor = SCENE()->CreateActor();
	//	m_PlayerActor->TRANS()->WPOS({ 0.0f, 0.0f , 0.0f });
	//	WPTR<WGAMEACTOR> PlayerActor = SCENE()->CreateActor();
	//	PlayerActor->TRANS()->WSCALE({ 0.01f, 0.01f , 0.01f });
	//	PlayerActor->TRANS()->PARENT(m_PlayerActor->TRANS());
	//	WPTR<WRENDERER> PlayerRender = PlayerActor->CreateCom<WRENDERER>();
	//	WPTR<WBoneAnimationComEx> BoneAniComEx = PlayerActor->CreateCom<WBoneAnimationComEx>();
	//	std::vector<WPTR<WRENDERPLAYER>> RpGroup1 = BoneAniComEx->MainFbx(L"AnimMan.FBX", L"Defferd", 0);
	//	//std::vector<WPTR<WRENDERPLAYER>> RpGroup2 = BoneAniComEx->MainFbx(L"AnimMan.FBX", L"OUTLINE", 0);
	//	//BoneAniComEx->FbxToPartRenderPlayer(L"AnimMan.FBX", L"OUTLINE", 0, 0, 0, 2);
	//	BoneAniComEx->FbxToPartRenderPlayer(L"AnimMan.FBX", L"Emission", 0, 0, 0, 2);
	//	BoneAniComEx->CreateAni(L"ALS_N_Run_RB.FBX", L"RunBack");
	//	BoneAniComEx->CreateAni(L"ALS_N_Run_F.FBX", L"Run");
	//	BoneAniComEx->ChangeAni(L"RunBack");
	//	PlayerRender->ShadowOn();
	//}
#pragma endregion




#pragma region LIGHT 
	{
		m_LightActor = GetScene()->CreateActor();
		float4 Dir = CVector(0.0f, 1.0f, -1.0f);
		Dir *= 10.0f;
		m_LightCom = m_LightActor->CreateCom<GameLight>(0);
		m_LightMeshComData.insert(std::map<int, CPtr<GameLight>>::value_type(0, m_LightCom));
		CPtr<GameRenderer> NewRender = m_LightActor->CreateCom<GameRenderer>(L"SquarePyramid", L"DebugMesh");
		m_LightActor->GetTrans()->SetWPos(Dir);
		m_LightActor->GetTrans()->WRotAddX(45.0f);
	}
#pragma endregion






}

void LevelDesignViewer::Update()
{

#pragma region LIGHT CONTROLLER
	InteractionUpdate();
	TextDebugUpdate();
	TargetDebugUpdate();
#pragma endregion
	SceneDebugDisplay();

	//////////////////////////////////////////////////////

	/* 
	< 디자인 >
	맵 범위를 넘지 않는 클릭 이미지 스트라이프 추가 
	또한 스트라이프 범위 체크해서 딱 그곳으로 클릭할 수 있다. 


	
	*/



}

void LevelDesignViewer::SceneChangeStart()
{
	

}

void LevelDesignViewer::SceneChangeEnd()
{
	//FileDelete();
}

void LevelDesignViewer::SceneDebugDisplay()
{
	wchar_t Arr[256];

	swprintf_s(Arr
		, L"[MousePos] X : %f, Y : %f"
		, GameWin::MainObj()->MousePos().X
		, GameWin::MainObj()->MousePos().Y
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,10 }, CVector::WHITE);

	swprintf_s(Arr
		, L"[MousePos3D] X : %f, Y : %f, Z : %f"
		, GameWin::MainObj()->MousePosVec3D().X
		, GameWin::MainObj()->MousePosVec3D().Y
		, GameWin::MainObj()->MousePosVec3D().Z
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,30 }, CVector::WHITE);

	swprintf_s(Arr
		, L"[MouseScreenOrth] X : %f, Y : %f"
		, GetScene()->MainCam()->CamOrthMousePos2d().X
		, GetScene()->MainCam()->CamOrthMousePos2d().Y
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,50 }, CVector::WHITE);

	swprintf_s(Arr
		, L"[MouseWorldOrth] X : %f, Y : %f"
		, GetScene()->MainCam()->OrthWorldMousePos2d().X
		, GetScene()->MainCam()->OrthWorldMousePos2d().Y
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,70 }, CVector::WHITE);

	swprintf_s(Arr, L"[CamPos] X : %f, Y : %f, Z : %f"
		, m_DesignCamActor->GetTrans()->GetWPos().X
		, m_DesignCamActor->GetTrans()->GetWPos().Y
		, m_DesignCamActor->GetTrans()->GetWPos().Z
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,90 }, CVector::WHITE);

	swprintf_s(Arr, L"[CamScreenSize] X : %f, Y : %f"
		, m_DesignCamCom->GetCamSize().X
		, m_DesignCamCom->GetCamSize().Y);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,110 }, CVector::WHITE);

	swprintf_s(Arr, L"[ScreenPos3DToWorldPos] X : %f, Y : %f, Z : %f"
		, m_ScreenPos3DToWorldPos.X
		, m_ScreenPos3DToWorldPos.Y
		, m_ScreenPos3DToWorldPos.Z
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,130 }, CVector::WHITE);

}



void LevelDesignViewer::InteractionUpdate()
{
	
	m_ScreenPos3DToWorldPos = m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D());

	if (GameInput::Press(L"SELECT"))
	{
		CVector POS = TILERENDERCOM->GetTrans()->GetWPos();
		CVector SCALE = TILERENDERCOM->GetTrans()->GetWScale();

		// 전체 사이즈 

		// 스트라이프 사이즈 

		if (m_DesignCamCom->GetTrans()->GetWPos().X - (m_DesignCamCom->GetCamSize().X * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			m_DesignCamCom->GetTrans()->GetWPos().X + (m_DesignCamCom->GetCamSize().X * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			m_DesignCamCom->GetTrans()->GetWPos().Y - (m_DesignCamCom->GetCamSize().Y * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
			m_DesignCamCom->GetTrans()->GetWPos().Y + (m_DesignCamCom->GetCamSize().Y * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
		{
			int a = 0;
		}
		else
		{
			TILERENDERCOM->TileAdd(
				m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D())
				, 5
			);
		}

	}

	if (GameInput::Press(L"DELETE"))
	{
		if (m_DesignCamCom->GetTrans()->GetWPos().X - (m_DesignCamCom->GetCamSize().X * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			m_DesignCamCom->GetTrans()->GetWPos().X + (m_DesignCamCom->GetCamSize().X * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			m_DesignCamCom->GetTrans()->GetWPos().Y - (m_DesignCamCom->GetCamSize().Y * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
			m_DesignCamCom->GetTrans()->GetWPos().Y + (m_DesignCamCom->GetCamSize().Y * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
		{
			int a = 0;
		}
		else
		{
			//m_TileMapCom->TileRemove(m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()), SEL_TILESPR_INDEX);
		}

	}

	if (GameInput::Press(L"CLEAR"))
	{
		//m_TileMapRD->TileClear();
	}


	if (GameInput::Press(L"AMB_DOWN"))
	{
		m_LightCom->SetAmbColor({
			m_LightCom->GetAmbColor().X - GameTime::DeltaTime(1.0F),
			m_LightCom->GetAmbColor().Y - GameTime::DeltaTime(1.0F),
			m_LightCom->GetAmbColor().Z - GameTime::DeltaTime(1.0F) });
	}


	if (GameInput::Press(L"AMB_UP"))
	{
		m_LightCom->SetAmbColor({
			m_LightCom->GetAmbColor().X + GameTime::DeltaTime(1.0F),
			m_LightCom->GetAmbColor().Y + GameTime::DeltaTime(1.0F),
			m_LightCom->GetAmbColor().Z + GameTime::DeltaTime(1.0F) });
	}
}

void LevelDesignViewer::TextDebugUpdate()
{
	//GameDebugPlus::DrawDebugText(L"PLAYER POS : %f %f %f"
	//	, m_PlayerActor->GetTrans()->GetWPos().X
	//	, m_PlayerActor->GetTrans()->GetWPos().Y
	//	, m_PlayerActor->GetTrans()->GetWPos().Z);

	PaperBurnTestCBuffer.W = PaperBurnTestCBuffer.W - sin(GameTime::DeltaTime(0.5f));

	CVector DEBUG_POS = GetScene()->MainCam()->GetTrans()->GetWPos();
	CVector DEBUG_ROT = GetScene()->MainCam()->GetTrans()->GetWRot();

	GameDebugPlus::DrawDebugText(L"X %f, Y %f, Z %f, ROT_X %f, ROT_Y %f, ROT_Z %f"
		, DEBUG_POS.X
		, DEBUG_POS.Y
		, DEBUG_POS.Z
		, DEBUG_ROT.X
		, DEBUG_ROT.Y
		, DEBUG_ROT.Z
	);

	GameDebugPlus::DrawDebugText(L" LIGHT AMB X : %f, LIGHT AMB Y %f, LIGHT AMB Z %f"
		, m_LightCom->GetAmbColor().X
		, m_LightCom->GetAmbColor().Y
		, m_LightCom->GetAmbColor().Z
	);

}

void LevelDesignViewer::TargetDebugUpdate()
{
#pragma region DEBUGTEXTURE RENDERTARGET
	float Ratio = 2.0f;
	CVector Scale = { 128 * Ratio , 72 * Ratio };

	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(0), Scale, CVector{ (640.0f - Scale.X), 360, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(1), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(2), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y * 2, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(3), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y * 3, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(6), Scale, CVector{ (640.0f - Scale.X * 2.0F), 360 - Scale.Y * 3, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(7), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y * 4, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_LightCom->ShadowTarget()->Texture(0), CVector{ Scale.X, Scale.X }, CVector{ (640.0f - Scale.X * 2.0f), (360 - Scale.Y * 4) + Scale.X - Scale.Y, 0.0f }, CVector::BLACK);
	////GameDebugPlus::DrawDebugTexture(m_BloomFilterCom->OutTarget->Texture(0), Scale, CVector{ (640.0f - Scale.X * 2.0f), 360, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->DeferredLightTarget()->Texture(3), Scale, CVector{ (640.0f - Scale.X * 2.0f), 360 - Scale.Y * 1, 0.0f }, CVector::BLACK);
	
	// 포그 필터 
	// GameDebugPlus::DrawDebugTexture( ) 
#pragma endregion
}



void LevelDesignViewer::CreateAnimationMesh()
{

	

}
void LevelDesignViewer::CreateStaticMesh() 
{
	//NewActor = nullptr;

	//WGAMESTRING _Str = std::to_wstring(_FbxObjectData.m_MeshData.m_Index.x);

	////////////////////// 스케일값은 고정한다. 
	//if (_FbxObjectData.m_ActorType.x == (int)MESHDATATYPE::PROP_cablepack_goingdown_long)
	//{
	//	NewActor = SCENE()->CreateActor();
	//	NewActor->CreateComName<PROP_cablepack_goingdown_long>(_Str);
	//	// 
	//}
	//else if (_FbxObjectData.m_ActorType.x == (int)MESHDATATYPE::PROP_cables_flow_4)
	//{
	//	NewActor = SCENE()->CreateActor();
	//	NewActor->CreateComName<PROP_cables_flow_4>(_Str);
	//	// 
	//}


	//m_StaticActorData.insert(std::map<WGAMEACTOR*, MeshActorData>::value_type(NewActor, _FbxObjectData));

}


void LevelDesignViewer::FillInAllLightValue()
{
	LightCreateData LightObjData;

	for (int i = 0; i < m_LightMeshComData.size(); i++)
	{
		std::map<int, CPtr<GameLight>>::iterator Find;
		
		Find = m_LightMeshComData.find(i);
		
		if (m_LightMeshComData.end() == Find)
		{
			return;
		}

		LightObjData.m_Type.x = i;
		LightObjData.m_Scale = Find->second->GetActor()->GetTrans()->GetWScale();
		LightObjData.m_Rot = Find->second->GetActor()->GetTrans()->GetWRot();
		LightObjData.m_Pos = Find->second->GetActor()->GetTrans()->GetWPos();
		LightObjData.m_AmbColor = Find->second->GetAmbColor();
		LightObjData.m_SpecPow = Find->second->GetSpecPow();
		LightObjData.m_LightPower = Find->second->GetLightPower();
		LightObjData.m_LightDir = Find->second->GetLightDir();
		LightObjData.m_LIghtDirInv = Find->second->GetLightDirInv();

		m_LightCreateMeshComData.insert(std::map<int, LightCreateData>::value_type(i, LightObjData));
	}

}