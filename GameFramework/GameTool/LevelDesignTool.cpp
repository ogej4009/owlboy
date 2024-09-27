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

	// FOG에 관하여 
	PaperBurnTestCBuffer = CVector{ 0.0f, 0.0f ,0.0f ,3.0f };

	float BorderNear = 0.0f;
	float BorderFar = 50.0f;

	FogBufferData Data;
	Data.FogStart = BorderNear;
	Data.FogEnd = BorderFar;


	// COLLISION(충돌연결)
	GetScene()->ColLink(0,1); // 예시


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
		NewCam->SetMode(CAMMODE::PERS);
		m_FreeCamCom = NewActor->CreateCom<FreeCam>();
		m_FreeCamActor = NewActor;
		//m_DesignCamCom = NewActor->CreateCom<DesignCam>();
		//m_DesignCamActor = NewActor;
	} 



	/*
	* 
	WPTR<WGAMEACTOR> NewActor = SCENE()->CreateActor();
	NewActor->TRANS()->WPOS({ 0.0f, 9.0f, -9.0f });
	NewActor->TRANS()->WROT({ 45.0f,0.0f,0.0f });
	WPTR<WCAM> NewCam = NewActor->CreateCom<WCAM>(0, (int)0);
	NewCam->MODE(CAMMODE::PERS);
	NewCam->CAMSIZE({ 12.8f, 7.2f });
	m_LineFilter = NewCam->AddFilter<WOutLineFilter>(50);
	WPTR<WCOL> Test = NewActor->CreateCom<WCOL>(0);
	Test->IsMouse = true;
	Test->ColType(COLTYPE::RAY3D);
	Test->PushEnterFunc(this, &DOOEmpty::TestCol); 
	
	

	
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
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 5.0f });
		NewActor->GetTrans()->SetWScale({ 5.0f, 5.0f, 5.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(L"TestGrid.png", (UINT)eRENDER_ORDER::RO_ACTOR);
	}


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



	///그리드 추가 
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 20.0f, 20.0f, 10.0f });
		CPtr<GameRenderer> NewRender = NewActor->CreateCom<GameRenderer>(L"GridMesh", L"Grid"); // GRIDMESH
		NewRender->SetCBuffer(L"GridTransData", NewRender->PTransDataPlus(), CBUFMODE::CB_LINK);
		NewActor->GetTrans()->SetWScale({ 10000.0f, 10000.0f, 10000.0f });
	}









	{
		m_LightActor = GetScene()->CreateActor();
		float4 Dir = CVector(0.0f, 1.0f, -1.0f);
		Dir *= 10.0f;
		m_LightCom = m_LightActor->CreateCom<GameLight>(0);
		m_mapAllLight.insert(std::map<int, CPtr<GameLight>>::value_type(0, m_LightCom));
		CPtr<GameRenderer> NewRender = m_LightActor->CreateCom<GameRenderer>(L"SquarePyramid", L"DebugMesh");
		m_LightActor->GetTrans()->SetWPos(Dir);
		m_LightActor->GetTrans()->WRotAddX(45.0f);
	}



}

void LevelDesignTool::Update()
{
	InputUpdate(); // 마우스->인터페이스->액터컨트롤  
	RenderTargetUpdate(); // 랜더타겟으로 모니터링 
	TextInfoUpdate(); // 정보를 모두 본다. 
	FreeCamUpdate(); // 방향키 
	DesignCamUpdate(); // 방향키 
}

void LevelDesignTool::SceneChangeStart()
{
	
}

void LevelDesignTool::SceneChangeEnd()
{
	//File_Out();
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


	//
	//m_ScreenPos3DToWorldPos = m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D());

	//if (GameInput::Press(L"SELECT"))
	//{
	//	CVector POS = m_TileRenderCom->GetTrans()->GetWPos();
	//	CVector SCALE = m_TileRenderCom->GetTrans()->GetWScale();

	//	// 맵 범위를 넘지 마라. 
	//	// 스트라이프 범위를 넘지 마라. 

	//	if (m_DesignCamCom->GetTrans()->GetWPos().X - (m_DesignCamCom->GetCamSize().X * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//		m_DesignCamCom->GetTrans()->GetWPos().X + (m_DesignCamCom->GetCamSize().X * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).X ||
	//		m_DesignCamCom->GetTrans()->GetWPos().Y - (m_DesignCamCom->GetCamSize().Y * 0.5f) > m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y ||
	//		m_DesignCamCom->GetTrans()->GetWPos().Y + (m_DesignCamCom->GetCamSize().Y * 0.5f) < m_DesignCamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D()).Y)
	//	{
	//		int a = 0;
	//	}
	//	else
	//	{
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







	//
	//
	//	if (true == WGAMEINPUT::Down(L"PICK"))
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




//void WTOOLMAPSCENE::ToolColFunc(WCOL* _Mosue, WCOL* _Monster)
//{
//	if (true == WGAMEINPUT::Down(L"MONSTERDELETE"))
//	{
//		std::map<WGAMEACTOR*, MONSTERDATA>::iterator FindMonster = m_MonsterData.find(_Monster->ACTOR());
//
//		if (FindMonster == m_MonsterData.end())
//		{
//			AMSG(L"존재하지 않는 몬스터를 지우려고 했습니다.");
//		}
//		FindMonster->first->Death();
//		m_MonsterData.erase(FindMonster);
//		// _Monster->ACTOR()->Death();
//	}
//}





//
//
//void HTOOLMAPSCENE::CreateFBXObject(CActorBaseData _FbxObjectData)
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

















