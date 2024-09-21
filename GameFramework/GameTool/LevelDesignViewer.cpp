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


	CtrlUpdate();
	DebugTargetUpdate();
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



void LevelDesignViewer::CtrlUpdate()
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







void LevelDesignViewer::AddSelMapObj(int _Select, CVector _Pos)
{
	MapObjData Data;

	CPtr<GameActor> NewActor = nullptr;

	Data.Type = _Select;

	switch (_Select)
	{
	case 0:
	{
		//NewActor = GetScene()->CreateActor();
		//NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		//NewActor->GetTrans()->SetWScale({ 1.28f, 1.28f, 1.0f });	
	}

	// NewActor->CreateCom
	// <4가지유형의오브젝트가있다.>
	// (int를 줄거다.valuedata혹은 enumdata헤더에 이름을 int로 나열해놓았다. );

	break;
	case 1:
	{

	}
	default:
		break;
	}

	Data.Pos = _Pos;
	// Data.Name = _Name;

	AllMapObjData.insert(std::map<GameActor*, MapObjData>::value_type(NewActor, Data));

}


