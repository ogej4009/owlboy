#include "LevelDesignViewer.h"
#include <GameDebugPlus.h>
#include <DesignCam.h>
#include <GameLight.h>



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



