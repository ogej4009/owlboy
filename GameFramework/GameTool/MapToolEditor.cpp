#include "pch.h"
#include "MapToolEditor.h"
#include <EnumData.h>
#include <ValueData.h>
#include <GameCol.h>
#include <GameDebugPlus.h>
#include <EditorCam.h>
#include <GameTileRenderer.h>
#include "RView.h"


MapToolEditor* MapToolEditor::MainMapToolEditor = nullptr;
std::map<GameActor*, EntityData> MapToolEditor::TotalEntityData;

GameTileRenderer* MapToolEditor::TileMapCom = nullptr;



MapToolEditor::MapToolEditor()
{
	MainMapToolEditor = this;
	Trigger = false;
}

MapToolEditor::~MapToolEditor()
{
}


void MapToolEditor::TileInit(int _Idx)
{
	Index = _Idx;
}

void MapToolEditor::TileTrigger(bool _Trigger)
{
	Trigger = _Trigger;
}

void MapToolEditor::TileUpdate()
{

	if (true == Trigger)
	{
		TileMapCom->AddTile(GetScene()->MainCam()->OrthWorldMousePos2d(), Index);
		/*TileMapCom->AddTile(m_CamCom->ScreenPos3DToWorldPos(GameWin::MainObj()->MousePosVec3D())
			, Index);*/
		Trigger = false;
		int a = 0;
	}

	/*if (true == GameInput::Down(L"DELETE"))
	{
		TileMapCom->AddTile(GetScene()->MainCam()->OrthWorldMousePos2d().X
			, GetScene()->MainCam()->OrthWorldMousePos2d().Y, Index);
	}

	if (true == GameInput::Down(L"CLEAR"))
	{
		TileMapCom->Clear();
	}*/

}

void MapToolEditor::Progress()
{
	GameScene::Progress();
}

void MapToolEditor::Init()
{
	
	// Key Setting..
	if (nullptr == GameInput::FindKey(L"CLEAR"))
	{
		GameInput::CreateKey(L"CLEAR", 'V');
		GameInput::CreateKey(L"SELECT", VK_LBUTTON);
		GameInput::CreateKey(L"DELETE", VK_RBUTTON);
	}
}

void MapToolEditor::Update()
{
	// Tile CamKey..
	TileMapCom->CamKey(m_CamActor->GetTrans()->GetWPos2d());



	if (true == GameInput::Down(L"SELECT"))
	{
		float CamX = m_CamCom->GetCamSize().X * 0.5f + m_CamActor->GetTrans()->GetWPos().X;		
		float CamY = m_CamCom->GetCamSize().Y * 0.5f - m_CamActor->GetTrans()->GetWPos().Y;

		float MouseX = GetScene()->MainCam()->OrthWorldMousePos2d().X;
		float MouseY = -GetScene()->MainCam()->OrthWorldMousePos2d().Y;

		TileUpdate();

		if (CamX < MouseX || -CamX > MouseX)
		{
			return;
		}
		
		if (CamY < MouseY || -CamY > MouseY)
		{
			return;
		}

		if (-1 == RView::SelEntity)
		{
			return;
		}

		// Tile Setting.. 

		// Entity..
		CreateEntity(RView::SelEntity, GetScene()->MainCam()->OrthWorldMousePos2d(), RView::EntityName);


	}

	SceneDebugDisplay();

}

void MapToolEditor::SceneChangeStart()
{
	// File Setting.. 
	FileCreate();

	// Camera Setting..
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos(ValueData::CAMERA_DEFAULT_POS);
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0,
			(UINT)RENDER_ORDER::RO_ACTOR,
			(UINT)RENDER_ORDER::RO_COL_LEVEL);
		NewCam->SetCamSize({ 6.4f, 3.6f });
		NewCam->SetMode(CAMMODE::ORTH);
		m_CamCom = NewActor->CreateCom<EditorCam>();
		m_CamActor = NewActor;
	}

	// Grid-Frame-Test Setting..
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 50.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>((UINT)RENDER_ORDER::RO_COL_LEVEL);
		NewRender->SetSprite(L"__GRID_FRAME_1280x720.png");
		NewRender->SetSrcSizeOfTexture(L"__GRID_FRAME_1280x720.png");
	}

	// Col-Level Setting..
	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 10.0f });
		NewActor->GetTrans()->SetWScale({ 1.0f, 1.0f, 1.0f });
		TileMapCom = NewActor->CreateCom<GameTileRenderer>();
		TileMapCom->SetSprite(L"ColLevel1.png");
	}

}

void MapToolEditor::SceneChangeEnd()
{
	// File Delete..
	FileDelete();
}

void MapToolEditor::SceneDebugDisplay()
{
	wchar_t Arr[256];

	swprintf_s(Arr, L"[MousePos] X : %f, Y : %f"
		, GameWin::MainObj()->MousePos().X
		, GameWin::MainObj()->MousePos().Y);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,10 }, CVector::WHITE);

	swprintf_s(Arr, L"[MousePos3D] X : %f, Y : %f, Z : %f"
		, GameWin::MainObj()->MousePosVec3D().X
		, GameWin::MainObj()->MousePosVec3D().Y
		, GameWin::MainObj()->MousePosVec3D().Z);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,30 }, CVector::WHITE);

	swprintf_s(Arr, L"[MouseScreenOrth] X : %f, Y : %f"
		, GetScene()->MainCam()->CamOrthMousePos2d().X
		, GetScene()->MainCam()->CamOrthMousePos2d().Y);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,50 }, CVector::WHITE);

	swprintf_s(Arr, L"[MouseWorldOrth] X : %f, Y : %f"
		, GetScene()->MainCam()->OrthWorldMousePos2d().X
		, GetScene()->MainCam()->OrthWorldMousePos2d().Y);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,70 }, CVector::WHITE);

	swprintf_s(Arr, L"[CamPos] X : %f, Y : %f"
		, m_CamActor->GetTrans()->GetWPos().X
		, m_CamActor->GetTrans()->GetWPos().Y);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,90 }, CVector::WHITE);

	swprintf_s(Arr, L"[CamScreenSize] X : %f, Y : %f"
		, m_CamCom->GetCamSize().X
		, m_CamCom->GetCamSize().Y);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,110 }, CVector::WHITE);

}

void MapToolEditor::SceneValueDataInit()
{
}
































void MapToolEditor::ClearEntity()
{
	for (auto& Var : TotalEntityData)
	{
		Var.first->Death();
	}
	TotalEntityData.clear();
}

void MapToolEditor::CreateEntity(int _Index, CVector _Pos, GameString _Name)
{
	EntityData Data;
	CPtr<GameActor> NewActor = nullptr;
	Data.Type = _Index;

	if (_Index < 0)
	{
		_Index = 0;
	}

	switch (_Index)
	{
	case 0:
	{
		NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(
			(int)RENDER_ORDER::RO_ACTOR); // 그리드? 
		NewRender->SetSprite(L"0.png", 0);
	}
	break;
	case 1:
	{
		NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(
			(int)RENDER_ORDER::RO_ACTOR); // 그리드? 
		NewRender->SetSprite(L"1.png", 0);
	}
	break;
	case 2:
	{
		NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(
			(int)RENDER_ORDER::RO_ACTOR); // 그리드? 
		NewRender->SetSprite(L"2.png", 0);
	}
	break;
	case 3:
	{
		NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(
			(int)RENDER_ORDER::RO_ACTOR); // 그리드? 
		NewRender->SetSprite(L"3.png", 0);
	}
	break;
	case 4:
	{
		NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos2d(_Pos, -1.0f);
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(
			(int)RENDER_ORDER::RO_ACTOR); // 그리드? 
		NewRender->SetSprite(L"4.png", 0);
	}
	break;
	default:
		break;
	}

	NewActor->CreateCom<GameCol>((int)COLLISION_ORDER::CO_BACKDROP);
	Data.Pos = _Pos;
	Data.Name = _Name;
	// m_Data.push_back(NewData);
	// m_Actor.push_back(NewActor);

	TotalEntityData.insert(std::map<GameActor*, EntityData>::value_type(NewActor, Data));
}

void MapToolEditor::EntityFunc(GameCol* _Mouse, GameCol* _Entity)
{
	if (true == GameInput::Down(L"DELETE"))
	{
		std::map<GameActor*, EntityData>::iterator FindMonster = TotalEntityData.find(_Entity->GetActor());

		if (FindMonster == TotalEntityData.end())
		{
			MSG_ASSERT_CODE(L"존재하지 않는 엔티티를 지우려고 시도합니다. ");
		}
		FindMonster->first->Death();
		TotalEntityData.erase(FindMonster);
		// _Entity->GetActor()->Death();
	}
}


/* 


void HSSTAGECOM::Update()
{
	m_Map->CamKey(MCam->Trans()->LPOS());
	m_CamPos = MCam->Trans()->LPOS();
	m_MapCave->CamKey(MCam->Trans()->LPOS());

	if (10.0f > MCam->Trans()->LPOS().x)
	{
		m_CamPos.x = 10.0f;
		MCam->Trans()->LPOS(m_CamPos);
	}

	if (true == HSGAMEINPUT::Press(L"LMove") && 10.0f < m_CamPos.x && MCam->Trans()->WPOS().x > Player->Trans()->WPOS().x)
	{
		HS1STAGESKY::m_Map->Trans()->LMoveToTimeSpeed(HSVEC4::LEFT, LOGICVAR::Speed);
		MCam->Trans()->LMoveToTimeSpeed(HSVEC4::LEFT, LOGICVAR::Speed);
		m_MapTree->Trans()->LMoveToTimeSpeed(HSVEC4::LEFT, LOGICVAR::Speed);
	}

	if (true == HSGAMEINPUT::Press(L"RMove") && 10.0f <= m_CamPos.x && MCam->Trans()->WPOS().x < Player->Trans()->WPOS().x)
	{
		HSVEC4 Check = Player->Trans()->WPOS();
		HSVEC4 Add = { 0.6f, 0.0f, 0.0f };
		HS1STAGESKY::m_Map->Trans()->LMoveToTimeSpeed(HSVEC4::RIGHT, LOGICVAR::Speed);
		MCam->Trans()->LMoveToTimeSpeed(HSVEC4::RIGHT, LOGICVAR::Speed);
		m_MapTree->Trans()->LMoveToTimeSpeed(HSVEC4::RIGHT, LOGICVAR::Speed);
	}


}





*/