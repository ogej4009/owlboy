#include "pch.h"
#include "LevelDesignViewer.h"
#include "RView.h"
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



void LevelDesignViewer::Progress()
{
	GameScene::Progress();
}

void LevelDesignViewer::Init()
{

	// FOG에 관하여 
	PaperBurnTestCBuffer = CVector{ 0.0f, 0.0f ,0.0f ,3.0f };

	float BorderNear = 0.0f;
	float BorderFar = 50.0f;

	FogBufferData Data;
	Data.FogStart = BorderNear;
	Data.FogEnd = BorderFar;


	// COLLISION(충돌연결)
	GetScene()->ColLink(0,1); // 예시


	SEL_TILESPR_INDEX = 0;

	// 키설정  
	if (nullptr == GameInput::FindKey(L"SELECT"))
	{
		GameInput::CreateKey(L"SELECT", VK_LBUTTON);
		GameInput::CreateKey(L"DELETE", VK_RBUTTON);
		GameInput::CreateKey(L"CLEAR", 'C');
		GameInput::CreateKey(L"AMB_UP", 'V');
		GameInput::CreateKey(L"AMB_DOWN", 'B');
	}

	// 파일 오픈 
	File_In();

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetLPos(ValueData::CAM_DEFAULT_POS);
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0
			, (UINT)eRENDER_ORDER::RO_ACTOR
			, (UINT)eRENDER_ORDER::RO_COL_LEVEL);
		NewCam->SetCamSize({ 12.8f, 7.2f });
		NewCam->SetMode(CAMMODE::ORTH);
		//m_FreeCamCom = NewActor->CreateCom<FreeCam>(10.0f);
		//m_FreeCamActor = NewActor;
		m_DesignCamCom = NewActor->CreateCom<DesignCam>();
		m_DesignCamActor = NewActor;
	} 



	/*
	{
		WPTR<WGAMEACTOR> PTR = SCENE()->CreateActor();
		WPTR<WMOUSECURSOR> MOUSE = PTR->CreateCom<WMOUSECURSOR>();
		MOUSE->SetCursorImage(L"Mouse.png", (int)RENDERORDER::RENDERORDER_UI);
		MOUSE->SetSize({ 0.2F, 0.2F, 0.2F });
		WPTR<WCOL> MOUSECOL = PTR->CreateCom<WCOL>((int)COLORDER::COLORDER_MOUSE);

		MOUSECOL->PushStayFunc(ToolColFunc); // ★
	}

	{
		MAP_ACTOR = SCENE()->CreateActor(L"MAP");
		MAP_RENDER = MAP_ACTOR->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_MAP);
		RENDERCHANGE(L"01");
	}*/



	size_t Size = sizeof(ObjectLightData);
	int XX = 0;


	{
		m_TileRenderActor = GetScene()->CreateActor();
		m_TileRenderCom = m_TileRenderActor->CreateCom<GameTileRenderer>(80, 46, L"ColLevel2.png", 0);
		m_TileRenderCom->SetMapSize({ 12.80f, 7.20f, 1.0f });
		m_TileRenderActor->GetTrans()->SetWScale({ TILE_INTERVAL_A, TILE_INTERVAL_A, 1.0f }); // 맵 사이즈 커스텀 
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
	//		NewActor->CreateCom<GameSpriteRenderer>(L"TestGrid.png", (int)eRENDER_ORDER::RO_ACTOR);
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


	/* 
	{
		HPTR<HGAMEACTOR> ParticleActor = SCENE()->CreateActor();
		HPTR<HPaticleCompoent> ParticleCom = ParticleActor->CreateCom<HPaticleCompoent>();

	}
	*/

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


	InteractionUpdate();
	TextDebugUpdate();
	TargetDebugUpdate();
	DebugText();

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
	//File_Out();
}

void LevelDesignViewer::DebugText()
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
		, m_DesignCamCom->GetCamSize().Y
	);
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
		CVector POS = m_TileRenderCom->GetTrans()->GetWPos();
		CVector SCALE = m_TileRenderCom->GetTrans()->GetWScale();

		// 맵 범위를 넘지 마라. 
		// 스트라이프 범위를 넘지 마라. 

		if (m_DesignCamCom->GetTrans()->GetWPos().X - (m_DesignCamCom->GetCamSize().X * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			m_DesignCamCom->GetTrans()->GetWPos().X + (m_DesignCamCom->GetCamSize().X * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			m_DesignCamCom->GetTrans()->GetWPos().Y - (m_DesignCamCom->GetCamSize().Y * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
			m_DesignCamCom->GetTrans()->GetWPos().Y + (m_DesignCamCom->GetCamSize().Y * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
		{
			int a = 0;
		}
		else
		{
			int b = 0;
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

	// L"RENDEROPTION"
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

		LightObjData.Type.x = i;
		LightObjData.Scale = Find->second->GetActor()->GetTrans()->GetWScale();
		LightObjData.Rot = Find->second->GetActor()->GetTrans()->GetWRot();
		LightObjData.Pos = Find->second->GetActor()->GetTrans()->GetWPos();
		LightObjData.AmbColor = Find->second->GetAmbColor();
		LightObjData.SpecPow = Find->second->GetSpecPow();
		LightObjData.LightPower = Find->second->GetLightPower();
		LightObjData.LightDir = Find->second->GetLightDir();
		LightObjData.LIghtDirInv = Find->second->GetLightDirInv();

		m_LightCreateMeshComData.insert(std::map<int, LightCreateData>::value_type(i, LightObjData));
	}

}




//
//void WTOOLMAPSCENE::Update()
//{
//	W3DDEBUG::DrawDebugText(L"MouseX %f MouseY %f ", WGAMEWINDOW::MAINOBJ()->MousePos().X, WGAMEWINDOW::MAINOBJ()->MousePos().Y);
//	W3DDEBUG::DrawDebugText(L"MouseScreenOrthX %f MouseScreenOrthY %f ", SCENE()->MainCam()->CamOrthMousePos2D().X, SCENE()->MainCam()->CamOrthMousePos2D().Y);
//	W3DDEBUG::DrawDebugText(L"MouseWorldOrthX %f MouseWorldOrthY %f ", SCENE()->MainCam()->OrthWorldMousePos2D().X, SCENE()->MainCam()->OrthWorldMousePos2D().Y);
//
//	if (WRightView::number == L"" || m_ImageName == WRightView::number)
//	{
//
//	}
//	else
//	{
//		m_ImageName = WRightView::number;
//		RENDERCHANGE(m_ImageName);
//	}
//
//	/*if (true == WGAMEINPUT::Down(L"MAPONOFF"))
//	{
//		if (true == MAPRENDER->IsUpdate())
//		{
//			MAPRENDER->Off();
//		}
//		else
//		{
//			MAPRENDER->On();
//		}
//	}*/
//	if (true == WGAMEINPUT::Down(L"MAPONOFF"))
//	{
//		if (false == W3DDEBUG::Debug())
//		{
//			W3DDEBUG::DebugOn();
//			MAP_RENDER->SPRITE(m_ImageName + "_LINE.png");
//		}
//		else
//		{
//			W3DDEBUG::DebugOn();
//			MAP_RENDER->SPRITE(m_ImageName + ".png");
//		}
//	}
//
//
//	if (true == WGAMEINPUT::Down(L"MONSTERPICK"))
//	{
//		float CamX = Cam->CAMSIZE().X * 0.5f + CAMPTR->TRANS()->WPOS().X;
//		float MouseX = SCENE()->MainCam()->OrthWorldMousePos2D().X;
//
//		float CamY = Cam->CAMSIZE().Y * 0.5f - CAMPTR->TRANS()->WPOS().Y;
//		float MouseY = -SCENE()->MainCam()->OrthWorldMousePos2D().Y;
//		//CamX < MouseX || 0 > MouseX ||
//		if (CamX < MouseX || -CamX > MouseX)
//		{
//			return;
//		}
//		if (CamY < MouseY || -CamY > MouseY)
//		{
//			return;
//		}
//		if (-1 == WRightView::SelectMonster)
//		{
//			return;
//		}
//		CreateMonster(WRightView::SelectMonster, SCENE()->MainCam()->OrthWorldMousePos2D());
//	}
//	WVECTOR a = WLOGICVALUE::m_IMG_LINE->GetPixel({ 0,0 });
//
//
//}



/* 



void WTOOLMAPSCENE::CreateMonster(int _SelectIndex, WVECTOR _Pos)
{
	// 어떤 데이터
	MONSTERDATA Data;

	// 어떤 액터
	WPTR<WGAMEACTOR> NewMonster = nullptr;

	// 해당위치에 추가
	Data.Type = _SelectIndex;

	switch (_SelectIndex)
	{
	case 0:
	{
		// 몬스터 액터를 생성하고, 위치에 그냥 놓는다.
		//
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.28f,1.28f,1.0f });
		}
		// 어떤 몬스터를 생성한다.
		NewMonster->CreateCom<WBIGSKUILLMONSTER>();
	}
	break;

	case 1:
	{
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.0f,1.0f,1.0f });
			WPTR<WSPRITERENDERER> MONSTERRERRENDER = NewMonster->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_ACTOR);
			MONSTERRERRENDER->LPOS({ 0, 0, 0 });
		}
		NewMonster->CreateCom<WLITTLEGHOST>();
	}
	break;
	case 2:
	{
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.0f,1.0f,1.0f });
			WPTR<WSPRITERENDERER> MONSTERRERRENDER = NewMonster->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_ACTOR);
			MONSTERRERRENDER->LPOS({ 0, 0, 0 });
		}
		NewMonster->CreateCom<WBANSHMONSTER>();
	}
	break;
	case 3:
	{
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.0f,1.0f,1.0f });
			WPTR<WSPRITERENDERER> MONSTERRERRENDER = NewMonster->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_ACTOR);
			MONSTERRERRENDER->LPOS({ 0, 0, 0 });
		}
		NewMonster->CreateCom<WSKELDOG>();
	}
	break;

	case 4:
	{
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.0f,1.0f,1.0f });
			WPTR<WSPRITERENDERER> MONSTERRERRENDER = NewMonster->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_ACTOR);
			MONSTERRERRENDER->LPOS({ 0, 0, 0 });
		}
		NewMonster->CreateCom<WMINOTAURS>();
	}
	break;

	case 5:
	{
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.0f,1.0f,1.0f });
			WPTR<WSPRITERENDERER> MONSTERRERRENDER = NewMonster->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_ACTOR);
			MONSTERRERRENDER->LPOS({ 0, 0, 0 });
		}
		NewMonster->CreateCom<WSNAKE>();
	}
	break;

	case 6:
	{
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.0f,1.0f,1.0f });
			WPTR<WSPRITERENDERER> MONSTERRERRENDER = NewMonster->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_ACTOR);
			MONSTERRERRENDER->LPOS({ 0, 0, 0 });
		}
		NewMonster->CreateCom<WWYVERN>();
	}
	break;

	case 7:
	{
		NewMonster = SCENE()->CreateActor();
		NewMonster->TRANS()->WPOS2D(_Pos, -1.0F);
		{
			NewMonster->TRANS()->WSCALE({ 1.0f,1.0f,1.0f });
			WPTR<WSPRITERENDERER> MONSTERRERRENDER = NewMonster->CreateCom<WSPRITERENDERER>((int)RENDERORDER::RENDERORDER_ACTOR);
			MONSTERRERRENDER->LPOS({ 0, 0, 0 });
		}
		NewMonster->CreateCom<WGIANTBAT>();
	}
	break;

	default:
		break;
	}

	Data.Pos = _Pos;

	// 생성한 몬스터는 여기에 집어넣는다.
	m_MonsterData.insert(std::map<WGAMEACTOR*, MONSTERDATA>::value_type(NewMonster, Data));
}

*/






//
//
//void HTOOLMAPSCENE::PlayerUpdate()
//{
//	if (HGAMEINPUT::Press(L"L"))
//	{
//		PlayerActor->TRANS()->LROTADDY(360.0f * HGAMETIME::DeltaTime());
//
//		// PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WLEFT());
//	}
//
//	if (HGAMEINPUT::Press(L"R"))
//	{
//		PlayerActor->TRANS()->LROTADDY(-360.0f * HGAMETIME::DeltaTime());
//		// PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WRIGHT());
//	}
//
//	if (HGAMEINPUT::Press(L"F"))
//	{
//		PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WFORWARD() * HGAMETIME::DeltaTime(20.0F));
//	}
//
//	if (HGAMEINPUT::Press(L"B"))
//	{
//		PlayerActor->TRANS()->WMOVE(PlayerActor->TRANS()->WBACK() * HGAMETIME::DeltaTime(20.0F));
//	}
//
//	int2 Index = Map->Index(PlayerActor->TRANS()->WPOS());
//
//	H3DDEBUG::DrawDebugText(L"Index %d %d", Index.x, Index.y);
//
//
//	HVECTOR Pos = PlayerActor->TRANS()->WPOS();
//	Pos.y = Map->YHeight(PlayerActor->TRANS()->WPOS());
//	PlayerActor->TRANS()->WPOS(Pos);
//}


//
//void HTOOLMAPSCENE::Update()
//{
//	PlayerUpdate();
//
//	// H3DDEBUG::DrawDebugText(L"AAAA");
//	float Ratio = 2.0f;
//	HVECTOR Scale = { 128 * Ratio, 72 * Ratio };
//
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(0), Scale, HVECTOR{ (640.0f - Scale.x), 360, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(1), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(2), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 2, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(3), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 3, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(7), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 4, 0.0f }, HVECTOR::BLACK);
//
//	H3DDEBUG::DrawDebugTexture(LightCom->ShadowTarget()->Texture(0), HVECTOR{ Scale.x, Scale.x }, HVECTOR{ (640.0f - Scale.x * 2.0f), (360 - Scale.y * 4) + Scale.x - Scale.y, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(6), Scale, HVECTOR{ (640.0f - Scale.x * 2.0F), 360 - Scale.y * 3, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(m_BloomFilter->OutTarget->Texture(0), Scale, HVECTOR{ (640.0f - Scale.x * 2.0f), 360, 0.0f }, HVECTOR::BLACK);
//
//	H3DDEBUG::DrawDebugTexture(CamPtr->DefferdLightTarget()->Texture(3), Scale, HVECTOR{ (640.0f - Scale.x * 2.0f), 360 - Scale.y * 1, 0.0f }, HVECTOR::BLACK);
//
//	HRightView::View->PushFbxList();
//
//	if (nullptr == AniCom)
//	{
//		return;
//	}
//
//	if (AniCom->CurAni()->IsEnd())
//	{
//		CString Text;
//
//		HRightView::View->m_PlayBtn.GetWindowTextW(Text);
//
//		if (Text != L"다시 재생")
//		{
//			HRightView::View->m_PlayBtn.SetWindowTextW(L"다시 재생");
//		}
//		return;
//	}
//
//	HRightView::View->CurFrame(AniCom->CurAni()->m_CurFrame);
//
//}
//
//void HTOOLMAPSCENE::CreateFBXObject(MeshCreateData _FbxObjectData)
//{
//	HPTR<HFBX> TestFbx = HFBX::Find(_FbxObjectData.m_MeshName);
//	HPTR<HGAMEACTOR> NewActor = SCENE()->CreateActor();
//	NewActor->TRANS()->WSCALE({ 0.1F, 0.1F, 0.1F });
//
//	HPTR<HRENDERER> NewRenderer = NewActor->CreateCom<HRENDERER>(0);
//	NewRenderer->LROT({ 0.0F, -90.0F, 0.0F });
//
//
//	HPTR<HFBX> _Fbx = HFBX::Find(_FbxObjectData.m_MeshName);
//	HFBXANIDATA* Ani = _Fbx->FindAniData(_FbxObjectData.m_TakeName);
//
//	HRightView::View->RangeSetting((int)Ani->TimeStartCount, (int)Ani->TimeEndCount);
//
//	HRightView::View->m_PlayBtn.SetWindowTextW(L"정지");
//
//	AniCom = NewActor->CreateCom<HBoneAnimationCom>();
//	AniCom->CreateAni(_FbxObjectData.m_MeshName, _FbxObjectData.m_TakeName, L"Test", (int)Ani->TimeStartCount, (int)Ani->TimeEndCount, L"3DANIFORWARD"/*, 2.0f, true*/);
//	AniCom->ChangeAni(L"Test");
//}







//
//
//void WTOOLMAPSCENE::DebugTextUpdate()
//{
//	//W3DDEBUG::DrawDebugText(L"COL MAP POS : %f %f %f", m_ColMapActor->TRANS()->WPOS().x, m_ColMapActor->TRANS()->WPOS().y, m_ColMapActor->TRANS()->WPOS().z);
//	//W3DDEBUG::DrawDebugText(L"MAP POS : %f %f %f", m_MapActor->TRANS()->WPOS().x, m_MapActor->TRANS()->WPOS().y, m_MapActor->TRANS()->WPOS().z);
//	W3DDEBUG::DrawDebugText(L"PLAYER POS : %f %f %f", m_PlayerActor->TRANS()->WPOS().x, m_PlayerActor->TRANS()->WPOS().y, m_PlayerActor->TRANS()->WPOS().z);
//
//	PaperBurnTestCBuffer.w = PaperBurnTestCBuffer.w - sin(WGAMETIME::DeltaTime(0.5f));
//
//	WVECTOR DEBUG_POS = SCENE()->MainCam()->TRANS()->WPOS();
//	WVECTOR DEBUG_ROT = SCENE()->MainCam()->TRANS()->WROT();
//	W3DDEBUG::DrawDebugText(L"X %f, Y %f, Z %f, ROT_X %f, ROT_Y %f, ROT_Z %f", DEBUG_POS.x, DEBUG_POS.y, DEBUG_POS.z, DEBUG_ROT.x, DEBUG_ROT.y, DEBUG_ROT.z);
//	W3DDEBUG::DrawDebugText(L" LIGHT AMB X : %f, LIGHT AMB Y %f, LIGHT AMB Z %f", m_LightCom->GetAmbColor().x, m_LightCom->GetAmbColor().y, m_LightCom->GetAmbColor().z);
//
//}
//
//void WTOOLMAPSCENE::DebugTargetUdpate()
//{
//#pragma region DEBUGTEXTURE RENDERTARGET
//	float Ratio = 2.0f;
//	WVECTOR Scale = { 128 * Ratio, 72 * Ratio };
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(0), Scale, WVECTOR{ (640.0f - Scale.x), 360, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(1), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(2), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 2, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(3), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 3, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(6), Scale, WVECTOR{ (640.0f - Scale.x * 2.0F), 360 - Scale.y * 3, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(7), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 4, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_LightCom->ShadowTarget()->Texture(0), WVECTOR{ Scale.x, Scale.x }, WVECTOR{ (640.0f - Scale.x * 2.0f), (360 - Scale.y * 4) + Scale.x - Scale.y, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_BloomFilterCom->OutTarget->Texture(0), Scale, WVECTOR{ (640.0f - Scale.x * 2.0f), 360, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->DefferdLightTarget()->Texture(3), Scale, WVECTOR{ (640.0f - Scale.x * 2.0f), 360 - Scale.y * 1, 0.0f }, WVECTOR::BLACK);
//	// 포그 필터 
//	// W3DDEBUG::DrawDebugTexture( ) 
//#pragma endregion
//}
//
//
//void WTOOLMAPSCENE::CreateAnimationMesh(MeshCreateData _FbxObjectData)
//{
//	// 보류
//}
//
//
//void WTOOLMAPSCENE::CreateStaticMesh(MeshActorData _FbxObjectData)
//{
//	NewActor = nullptr;
//
//	WGAMESTRING _Str = std::to_wstring(_FbxObjectData.m_MeshData.m_Index.x);
//
//	//////////////////// 스케일값은 고정한다. 
//	if (_FbxObjectData.m_ActorType.x == (int)MESHDATATYPE::PROP_cablepack_goingdown_long)
//	{
//		NewActor = SCENE()->CreateActor();
//		NewActor->CreateComName<PROP_cablepack_goingdown_long>(_Str);
//		// 
//	}
//	else if (_FbxObjectData.m_ActorType.x == (int)MESHDATATYPE::PROP_cables_flow_4)
//	{
//		NewActor = SCENE()->CreateActor();
//		NewActor->CreateComName<PROP_cables_flow_4>(_Str);
//		// 
//	}
//}

//void WTOOLMAPSCENE::DeleteAnimationMesh(WGAMESTRING _Name)
//{
//	// 스위치문을 이용해서 이름을 비교하고 씬에 선언한 멤버변수를 지웁니다. 
//}
//
//
//
//void WTOOLMAPSCENE::DeleteStaticMesh(WGAMESTRING _Name)
//{
//	// 스위치문을 이용해서 이름을 비교하고 씬에 선언한 멤버변수를 지웁니다. 
//}
//
//
//
//void WTOOLMAPSCENE::FillInAllLightValue()
//{
//	LightCreateData LightObjData;
//
//	for (int i = 0; i < m_LightMeshComData.size(); i++)
//	{
//		std::map<int, WPTR<WLight>>::iterator Find;
//		Find = m_LightMeshComData.find(i);
//		if (m_LightMeshComData.end() == Find)
//		{
//			return;
//		}
//
//		LightObjData.m_Type.x = i;
//		LightObjData.m_Scale = Find->second->ACTOR()->TRANS()->WSCALE();
//		LightObjData.m_Rot = Find->second->ACTOR()->TRANS()->WROT();
//		LightObjData.m_Pos = Find->second->ACTOR()->TRANS()->WPOS();
//		LightObjData.m_AmbColor = Find->second->GetAmbColor();
//		LightObjData.m_SpecPow = Find->second->GetSpecPow();
//		LightObjData.m_LightPower = Find->second->GetLightPower();
//		LightObjData.m_LightDir = Find->second->GetLightDir();
//		LightObjData.m_LIghtDirInv = Find->second->GetLightDirInv();
//
//		m_LightCreateMeshComData.insert(std::map<int, LightCreateData>::value_type(i, LightObjData));
//	}
//
//}
//
//
//void WTOOLMAPSCENE::ActorComAll()
//{
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 여기서부터~
//
//#pragma region MAP
//	{
//		m_MapActor = SCENE()->CreateActor();
//		m_MapActor->CreateCom<TEST_MAP>();
//		m_MapActor->TRANS()->WPOS({ -22.35f, 0.0f, 13.6f });
//	}
//#pragma endregion
//	//
//	//#pragma region COLMAP
//	//	{
//	//		m_ColMapActor = SCENE()->CreateActor();
//	//		m_ColMapActor->CreateCom<TEST_COL_MAP>();
//	//	}
//	//#pragma endregion
//	//
//	//#pragma region PROP_cablepack_goingdown_long
//	//	{
//	//		WPTR<WGAMEACTOR> PROP_cablepack_goingdown_long_Actor = SCENE()->CreateActor();
//	//		PROP_cablepack_goingdown_long_Actor->CreateCom<PROP_cablepack_goingdown_long>();
//	//		PROP_cablepack_goingdown_long_Actor->TRANS()->WPOS({ 100.0f, 0.0f, 200.0f });
//	//		//PROP_cablepack_goingdown_long_Actor->TRANS()->WROT({ 90.0f, 0.0f, 0.0f });
//	//		PROP_cablepack_goingdown_long_Actor->TRANS()->WSCALE({ 0.1f, 0.1f, 0.1f });
//	//	}
//	//#pragma endregion
//	//
//	//#pragma region PROP_cables_flow_4
//	//	{
//	//		WPTR<WGAMEACTOR> PROP_cables_flow_4_Actor = SCENE()->CreateActor();
//	//		PROP_cables_flow_4_Actor->CreateCom<PROP_cables_flow_4>();
//	//		PROP_cables_flow_4_Actor->TRANS()->WPOS({ 100.0f, 0.0f, 200.0f });
//	//		//PROP_cables_flow_4_Actor->TRANS()->WROT({ 90.0f, 0.0f, 0.0f });
//	//		PROP_cables_flow_4_Actor->TRANS()->WSCALE({ 0.1f, 0.1f, 0.1f });
//	//	}
//	//#pragma endregion
//	//
//}

























