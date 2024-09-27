#include "FreeCam.h"
#include <GameDebug.h> 


void FreeCam::CamReset()
{
	GetTrans()->SetWPos(m_FixedPos);
	GetTrans()->SetWRot(m_FixedRot);
	m_Cam->SetCamFov(m_FixedFov);
}

void FreeCam::CamAccel()
{
	m_MoveSpeed += FREECAM_MOVESPEED_ARGU;

	if (m_MoveSpeed >= FREECAM_MOVESPEED_MAX)
	{
		m_MoveSpeed = FREECAM_MOVESPEED_MAX;
	}
}

void FreeCam::CamDecel()
{
	m_MoveSpeed -= FREECAM_MOVESPEED_ARGU;

	if (m_MoveSpeed <= FREECAM_MOVESPEED_MIN)
	{
		m_MoveSpeed = FREECAM_MOVESPEED_MIN;
	}
}

void FreeCam::CamZoomIn()
{
	if (m_Cam->GetCamFov() <= FREECAM_FOV_MIN)
	{
		return;
	}

	m_Cam->SetCamFov(m_Cam->GetCamFov() - GameTime::DeltaTime(FREECAM_FOV_ARGU)); 
}

void FreeCam::CamZoomOut()
{
	if (m_Cam->GetCamFov() >= FREECAM_FOV_MAX)
	{
		return;
	}

	m_Cam->SetCamFov(m_Cam->GetCamFov() + GameTime::DeltaTime(FREECAM_FOV_ARGU)); 
}

void FreeCam::Init()
{
	if (nullptr == GetActor()->FindComType<GameCamera>())
	{
		MSG_ASSERT_CODE(L"캠이 존재하지 않는 곳에 프리캠을 넣어줄수 없습니다.");
	}

	m_Cam = GetActor()->FindComType<GameCamera>();

	m_MoveSpeed = FREECAM_MOVESPEED;
	m_RotSpeed = FREECAM_ROTSPEED;
	m_HMoveSpeed = FREECAM_HMOVESPEED;
	m_HRotSpeed = FREECAM_HROTSPEED;

	m_StartPos = GetTrans()->GetWPos();
	m_StartRot = GetTrans()->GetWRot();
	m_StartFov = m_Cam->GetCamFov();

	m_FixedPos = { 0.0f, 0.0f, FREECAM_DEF_POS_Z };
	m_FixedRot = { FREECAM_DEF_ROT_X, 0.0f, 0.0f };
	m_FixedFov = FREECAM_FOV; 

	if (nullptr == GameInput::FindKey(L"CAM_LEFT"))
	{
		GameInput::CreateKey(L"CAM_LEFT", VK_NUMPAD4);
		GameInput::CreateKey(L"CAM_RIGHT", VK_NUMPAD6);
		GameInput::CreateKey(L"CAM_UP", VK_NUMPAD8);
		GameInput::CreateKey(L"CAM_DOWN", VK_NUMPAD2);
		GameInput::CreateKey(L"CAM_FORWARD", VK_NUMPAD7);
		GameInput::CreateKey(L"CAM_BACK", VK_NUMPAD9);
		GameInput::CreateKey(L"CAM_ROT", VK_NUMPAD5);
		GameInput::CreateKey(L"CAM_RESET", VK_NUMPAD0);
		GameInput::CreateKey(L"CAM_ZOOM_IN", VK_NUMPAD1);
		GameInput::CreateKey(L"CAM_ZOOM_OUT", VK_NUMPAD3);
		GameInput::CreateKey(L"CAM_SPEED_ACC", VK_SHIFT);
		GameInput::CreateKey(L"CAM_SPEED_DEC", VK_CONTROL);
	}
	else
	{
		int Test = 0;
	}

}


void FreeCam::Update()
{

	GetTrans()->GetTransDataPlus().Pos =  GetTrans()->GetWPos();

	if (true == GameInput::Press(L"CAM_LEFT"))
	{
		GetTrans()->LMove(GetTrans()->WLeft() * GameTime::DeltaTime(m_HMoveSpeed));
	}

	if (true == GameInput::Press(L"CAM_RIGHT"))
	{
		GetTrans()->LMove(GetTrans()->WRight() * GameTime::DeltaTime(m_HMoveSpeed));
	}

	if (true == GameInput::Press(L"CAM_UP"))
	{
		GetTrans()->LMove(GetTrans()->WUp() * GameTime::DeltaTime(m_HMoveSpeed));
	}

	if (true == GameInput::Press(L"CAM_DOWN"))
	{
		GetTrans()->LMove(GetTrans()->WDown() * GameTime::DeltaTime(m_HMoveSpeed));
	}

	if (true == GameInput::Press(L"CAM_FORWARD"))
	{
		GetTrans()->LMove(GetTrans()->WForward() * GameTime::DeltaTime(m_HMoveSpeed));
	}

	if (true == GameInput::Press(L"CAM_BACK"))
	{
		GetTrans()->LMove(GetTrans()->WBack() * GameTime::DeltaTime(m_HMoveSpeed));
	}

	if (true == GameInput::Press(L"CAM_ROT") && GameInput::Press(L"CAM_UP"))
	{		
		CVector Dir;
		Dir = GameInput::MouseDir3D();
		GetTrans()->WRotAddX(-360.0f * GameTime::DeltaTime(m_HRotSpeed));
	}

	if (true == GameInput::Press(L"CAM_ROT") && GameInput::Press(L"CAM_DOWN"))
	{
		CVector Dir;
		Dir = GameInput::MouseDir3D();
		GetTrans()->WRotAddX(360.0f * GameTime::DeltaTime(m_HRotSpeed));
	}

	if (true == GameInput::Press(L"CAM_ROT") && GameInput::Press(L"CAM_LEFT"))
	{
		CVector Dir;
		Dir = GameInput::MouseDir3D();
		GetTrans()->WRotAddY(-GameTime::DeltaTime(m_HRotSpeed));
		GetTrans()->WRotAddX(GameTime::DeltaTime(m_HRotSpeed));
		// GetTrans()->WRotAddY(Dir.x * GameTime::DeltaTime(m_HRotSpeed));
		// GetTrans()->WRotAddX(-Dir.y * GameTime::DeltaTime(m_HRotSpeed));		
		// GetTrans()->LRotAddY(-360.0f * GameTime::DeltaTime(m_HRotSpeed));
	}

	if (true == GameInput::Press(L"CAM_ROT") && GameInput::Press(L"CAM_RIGHT"))
	{
		CVector Dir;
		Dir = GameInput::MouseDir3D();
		GetTrans()->WRotAddY(GameTime::DeltaTime(m_HRotSpeed));
		GetTrans()->WRotAddX(-GameTime::DeltaTime(m_HRotSpeed));
		// GetTrans()->WRotAddY(Dir.x * GameTime::DeltaTime(m_HRotSpeed));
		// GetTrans()->WRotAddX(-Dir.y * GameTime::DeltaTime(m_HRotSpeed));
		// GetTrans()->LRotAddY(360.0f * GameTime::DeltaTime(m_HRotSpeed));
	}

	if (true == GameInput::Down(L"CAM_RESET"))
	{
		CamReset();
	}

	if (true == GameInput::Press(L"CAM_ZOOM_IN"))
	{
		CamZoomIn();
	}

	if (true == GameInput::Press(L"CAM_ZOOM_OUT"))
	{
		CamZoomOut();
	}


}

FreeCam::FreeCam()
{
}

FreeCam::~FreeCam()
{
}


