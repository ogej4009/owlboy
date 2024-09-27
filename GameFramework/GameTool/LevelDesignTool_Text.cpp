#include "LevelDesignTool.h"
#include <GameDebugPlus.h>
#include <DesignCam.h>
#include <FreeCam.h>
#include <GameLight.h>



void LevelDesignTool::TextInfoUpdate()
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

	//swprintf_s(Arr, L"[CamPos] X : %f, Y : %f, Z : %f"
	//	, m_DesignCamActor->GetTrans()->GetWPos().X
	//	, m_DesignCamActor->GetTrans()->GetWPos().Y
	//	, m_DesignCamActor->GetTrans()->GetWPos().Z
	//);
	//GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,90 }, CVector::WHITE);

	//swprintf_s(Arr, L"[CamScreenSize] X : %f, Y : %f"
	//	, m_DesignCamCom->GetCamSize().X
	//	, m_DesignCamCom->GetCamSize().Y
	//);
	//GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,110 }, CVector::WHITE);

	swprintf_s(Arr, L"[CamPos] X : %f, Y : %f, Z : %f"
		, m_FreeCamActor->GetTrans()->GetWPos().X
		, m_FreeCamActor->GetTrans()->GetWPos().Y
		, m_FreeCamActor->GetTrans()->GetWPos().Z
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,90 }, CVector::WHITE);

	//swprintf_s(Arr, L"[CamScreenSize] X : %f, Y : %f"
	//	, m_FreeCamCom->GetCamSize().X
	//	, m_FreeCamCom->GetCamSize().Y
	//);
	//GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,110 }, CVector::WHITE);

	swprintf_s(Arr, L"[ScreenPos3DToWorldPos] X : %f, Y : %f, Z : %f"
		, m_ScreenPos3DToWorldPos.X
		, m_ScreenPos3DToWorldPos.Y
		, m_ScreenPos3DToWorldPos.Z
	);
	GameDebugPlus::DrawDebugText(Arr, 20.0f, { 0,130 }, CVector::WHITE);


	PaperBurnTestCBuffer.W = PaperBurnTestCBuffer.W - sin(GameTime::DeltaTime(0.5f));

	CVector CamPos = GetScene()->MainCam()->GetTrans()->GetWPos();
	CVector CamRot = GetScene()->MainCam()->GetTrans()->GetWRot();

	GameDebugPlus::DrawDebugText(L" [CamPos] X : %f, Y : %f, Z : %f, [CamRot] : X : %f, Y : %f, Z : %f"
		, CamPos.X, CamPos.Y, CamPos.Z
		, CamRot.X, CamRot.Y, CamRot.Z
	);

	GameDebugPlus::DrawDebugText(L" [Light AmbColor] X : %f, Y : %f, Z : %f "
		, m_LightCom->GetAmbColor().X
		, m_LightCom->GetAmbColor().Y
		, m_LightCom->GetAmbColor().Z
	);

}




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


