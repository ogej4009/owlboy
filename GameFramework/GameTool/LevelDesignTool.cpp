#include "pch.h"
#include "LevelDesignTool.h"
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




LevelDesignTool* LevelDesignTool::InstTool = nullptr;
std::map<GameActor*, MapObjData> LevelDesignTool::AllMapObjData;
std::map<GameString*, SaveMapObjData> LevelDesignTool::AllSaveMapObjData;



LevelDesignTool::LevelDesignTool()
{
	InstTool = this;
}

LevelDesignTool::~LevelDesignTool()
{
}

void LevelDesignTool::Progress()
{
	GameScene::Progress();
}

void LevelDesignTool::Init()
{

	// COLLISION(충돌연결)
	GetScene()->ColLink(0,1); 

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
		NewCam->SetCamSize({ 12.80f * 0.5f, 7.20f * 0.5f });
		NewCam->SetMode(CAMMODE::ORTH);
		//m_FreeCamCom = NewActor->CreateCom<FreeCam>();
		//m_FreeCamActor = NewActor;
		m_DesignCamCom = NewActor->CreateCom<DesignCam>();
		m_DesignCamActor = NewActor;
		//CPtr<GameCol> R_Col = NewActor->CreateCom<GameCol>(0);
		//R_Col->IsMouse = true;
		//R_Col->ColType(COLTYPE::RAY3D);
		//R_Col->PushEnterFunc(this, &LevelDesignTool::RayColFunc);
		// 필터를 어떻게 적용할 것인가? m_LineFilter = NewCam->AddFilter<GameOutLineFilter>(50);
	} 

	//{
	//	CPtr<GameActor> NewActor = GetScene()->CreateActor();
	//	CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>((int)eRENDER_ORDER::RO_COL_LEVEL);
	//	//RENDERCHANGE(L"01");
	//}
	

	/*{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 15.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(L"TestGrid.png", (UINT)eRENDER_ORDER::RO_ACTOR);
		NewRender->GetTrans()->SetWScale({ TILE_INTERVAL_A * 80, TILE_INTERVAL_A * 46, 3.0f });
	}*/

	{
		m_TileRenderActor = GetScene()->CreateActor();
		m_TileRenderActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 10.0f });
		m_TileRenderActor->GetTrans()->SetWScale({ TILE_INTERVAL_A * 80, TILE_INTERVAL_A * 46, 1.0f });
		m_TileRenderCom = m_TileRenderActor->CreateCom<GameTileRenderer>(80, 46
			, L"ColLevel2.png"
			, (UINT)eRENDER_ORDER::RO_COL_LEVEL
		);
		m_TileRenderCom->SetMapSize({ TILE_INTERVAL_A * 80, TILE_INTERVAL_A * 46 });
		//m_TileRenderCom->Off();
	}

	//{
	//	m_TileMapActor = GetScene()->CreateActor();
	//	m_TileMapActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 1.0f });
	//	m_TileMapActor->GetTrans()->SetWScale({ 12.80f, 7.20f, 1.0f });
	//	m_TileMapCom = m_TileMapActor->CreateCom<GameTileMap>(80, 46, L"ColLevel2.png", (UINT)eRENDER_ORDER::RO_COL_LEVEL);
	//}

	///////////////////////////////////////////////////////////////////////////////////////////////

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 20.0f, 20.0f, 10.0f });
		CPtr<GameRenderer> NewRender = NewActor->CreateCom<GameRenderer>(L"GridMesh", L"Grid"); // GRIDMESH
		NewRender->SetCBuffer(L"GridTransData", NewRender->PTransDataPlus(), CBUFMODE::CB_LINK);
		NewActor->GetTrans()->SetWScale({ 10000.0f, 10000.0f, 10000.0f });
	}

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 20.0f, -20.0f, 10.0f });
		CPtr<GameRenderer> NewRender = NewActor->CreateCom<GameRenderer>(L"GridMesh", L"Grid"); // GRIDMESH
		NewRender->SetCBuffer(L"GridTransData", NewRender->PTransDataPlus(), CBUFMODE::CB_LINK);
		NewActor->GetTrans()->SetWScale({ 10000.0f, 10000.0f, 10000.0f });
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	size_t Size = sizeof(ObjectLightData);
	{
		m_LightActor = GetScene()->CreateActor();
		float4 Dir = CVector(0.0f, 1.0f, -1.0f);
		Dir *= 10.0f;
		m_LightCom = m_LightActor->CreateCom<GameLight>(0);
		m_mapAllLight.insert(std::map<int, CPtr<GameLight>>::value_type(0, m_LightCom));
		CPtr<GameRenderer> NewRender = m_LightActor->CreateCom<GameRenderer>(L"SquarePyramid", L"DebugMesh");
		m_LightActor->GetTrans()->SetWPos(Dir);
		m_LightActor->GetTrans()->WRotAddX(60.0f);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

}

void LevelDesignTool::Update()
{
	InputUpdate();			// 마우스->인터페이스->액터컨트롤  
	RenderTargetUpdate();	// 랜더타겟으로 모니터링 
	TextInfoUpdate();		// 정보를 모두 본다. 
	FreeCamUpdate();		// 방향키 
	DesignCamUpdate();		// 방향키 
}

void LevelDesignTool::SceneChangeStart()
{
	
}

void LevelDesignTool::SceneChangeEnd()
{
	//File_Out();
}

void LevelDesignTool::RayColFunc(GameCol* _This, GameCol* _Other)
{
	
}

void LevelDesignTool::DesignCamUpdate()
{
}

void LevelDesignTool::FreeCamUpdate()
{
}

void LevelDesignTool::InputUpdate()
{
	// 방향키 컨트롤 
	// 양자택일
	DesignCamUpdate();
	FreeCamUpdate();

	// 맵 범위를 넘지 마라. 
	// 스트라이프 범위를 넘지 마라. 

	/*
		CVector POS = m_TileRenderCom->GetTrans()->GetWPos();
		CVector SCALE = m_TileRenderCom->GetTrans()->GetWScale();
	
		float RIGHT = POS.X + (0.5f * SCALE.X);
		float LEFT = POS.X - (0.5f * SCALE.X);
		float TOP = POS.Y + (0.5f * SCALE.Y);
		float BOT = POS.Y - (0.5f * SCALE.Y);
	
		float A = m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X;
		float B = m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y;
	
		if (RIGHT < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			LEFT > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
			TOP < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
			BOT > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
		{
			int XAA = 0; // 넘어갔다. 
		}
		else
		{
			int XAA2 = 0; // 영역안이다. 
		}
	*/

	//CVector MAPPOS = m_TileRenderCom->GetTrans()->GetWPos();
	//CVector MAPSIZE = m_TileRenderCom->GetMapSize();

	//float MR = MAPPOS.X + (0.5f * MAPSIZE.X);
	//float ML = MAPPOS.X - (0.5f * MAPSIZE.X);
	//float MT = MAPPOS.Y + (0.5f * MAPSIZE.Y);
	//float MB = MAPPOS.Y - (0.5f * MAPSIZE.Y);

	//if (MR < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//	ML > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//	MT < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
	//	MB > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
	//{
	//	int XAB = 0; // 넘어갔다. 
	//}
	//else
	//{
	//	int XAB2 = 0; // 영역안이다. 
	//}

	//m_ScreenPos3DToWorldPos = m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D());

	//if (GameInput::Press(L"SELECT"))
	//{

	//	if (m_DesignCamCom->GetTrans()->GetWPos().X - (m_DesignCamCom->GetCamSize().X * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//		m_DesignCamCom->GetTrans()->GetWPos().X + (m_DesignCamCom->GetCamSize().X * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//		m_DesignCamCom->GetTrans()->GetWPos().Y - (m_DesignCamCom->GetCamSize().Y * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
	//		m_DesignCamCom->GetTrans()->GetWPos().Y + (m_DesignCamCom->GetCamSize().Y * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
	//	{
	//		int a = 0;

	//	}
	//	else
	//	{
	//		m_TileRenderCom->TileAdd(m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()), 5);

	//		int b = 0;
	//	}

	//}

	//if (GameInput::Press(L"DELETE"))
	//{
	//	if (m_DesignCamCom->GetTrans()->GetWPos().X - (m_DesignCamCom->GetCamSize().X * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//		m_DesignCamCom->GetTrans()->GetWPos().X + (m_DesignCamCom->GetCamSize().X * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//		m_DesignCamCom->GetTrans()->GetWPos().Y - (m_DesignCamCom->GetCamSize().Y * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
	//		m_DesignCamCom->GetTrans()->GetWPos().Y + (m_DesignCamCom->GetCamSize().Y * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
	//	{
	//		int a = 0;
	//	}
	//	else
	//	{
	//		//m_TileMapCom->TileRemove(m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()), SEL_TILESPR_INDEX);
	//	}
	//}

	if (GameInput::Press(L"CLEAR"))
	{
		
	}

	if (GameInput::Press(L"AMB_DOWN"))
	{
		m_LightCom->SetAmbColor({
			m_LightCom->GetAmbColor().X - GameTime::DeltaTime(1.0f),
			m_LightCom->GetAmbColor().Y - GameTime::DeltaTime(1.0f),
			m_LightCom->GetAmbColor().Z - GameTime::DeltaTime(1.0f) });
	}

	if (GameInput::Press(L"AMB_UP"))
	{
		m_LightCom->SetAmbColor({
			m_LightCom->GetAmbColor().X + GameTime::DeltaTime(1.0f),
			m_LightCom->GetAmbColor().Y + GameTime::DeltaTime(1.0f),
			m_LightCom->GetAmbColor().Z + GameTime::DeltaTime(1.0f) });
	}


}


void LevelDesignTool::LightValueUpdate()
{
	CLightData LightObjData;

	for (int i = 0; i < m_mapAllLight.size(); i++)
	{
		std::map<int, CPtr<GameLight>>::iterator Find;
		
		Find = m_mapAllLight.find(i);
		
		if (m_mapAllLight.end() == Find)
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

		m_mapAllLightData.insert(std::map<int, CLightData>::value_type(i, LightObjData));
	}

}


//void LevelDesignTool::ToolColFunc(GameCol* _This, GameCol* _Other)
//{
//	if (true == GameInput::Down(L"SELECT"))
//	{
//		std::map<GameActor*, MapObjData>::iterator Find_Data = AllMapObjData.find(_This->GetActor());
//
//		if (Find_Data == AllMapObjData.end())
//		{
//			MSG_ASSERT_CODE(L"존재하지 않는 몬스터를 지우려고 했습니다.");
//		}
//
//		Find_Data->first->Death();
//		AllMapObjData.erase(Find_Data);
//	}
//}


