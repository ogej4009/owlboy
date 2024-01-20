#include "EditorCam.h"
#include "EnumData.h"
#include "ValueData.h"

CPtr<GameActor> EditorCam::CamActor = nullptr;

void EditorCam::Move(const CVector& _Dir, float _Speed)
{
	GetTrans()->WMove(_Dir * GameTime::DeltaTime(_Speed));
}

void EditorCam::Join(CPtr<GameTransform> _Parent)
{
}

void EditorCam::Withdraw()
{
}

void EditorCam::Init()
{
	m_Cam = GetActor()->FindComType<GameCamera>();
	m_Cam = GetScene()->MainCam();
	if (nullptr == m_Cam)
	{
		MSG_ASSERT_CODE(L"이 component는 actor가 null입니다.");
	}

	if (nullptr == GameInput::FindKey(L"ET_CAM_ZERO"))
	{
		GameInput::CreateKey(L"ET_CAM_ZERO", VK_NUMPAD0);
		GameInput::CreateKey(L"ET_CAM_L", VK_NUMPAD4);
		GameInput::CreateKey(L"ET_CAM_R", VK_NUMPAD6);
		GameInput::CreateKey(L"ET_CAM_U", VK_NUMPAD8);
		GameInput::CreateKey(L"ET_CAM_D", VK_NUMPAD2);
		GameInput::CreateKey(L"ET_CAM_F", VK_ADD);
		GameInput::CreateKey(L"ET_CAM_B", VK_SUBTRACT);
		GameInput::CreateKey(L"ET_CAMROT_P", VK_NUMPAD7); // 정시계
		GameInput::CreateKey(L"ET_CAMROT_M", VK_NUMPAD9); // 반시계
		GameInput::CreateKey(L"ET_CAM_SPEED_UP", VK_SELECT);
		GameInput::CreateKey(L"ET_CAM_SPEED_ZERO", VK_DECIMAL);
	}

	m_bCheck = false;
	m_Speed = EDITOR_CAM_SPEED;
	m_RotSpeed = EDITOR_CAM_ROT_SPEED;
	m_AccSpeed = EDITOR_CAM_ACCEL_SPEED;
}

void EditorCam::Update()
{
	if (true == GameInput::Press(L"ET_CAM_ZERO"))
	{
		GetTrans()->SetWPos({ 0.0f, 0.0f, -9.9f });
	}

	/*if (false == m_bCheck)
	{*/
		if (true == GameInput::Press(L"ET_CAM_L"))
		{
			Move(CVector::LEFT, m_Speed);
		}
		if (true == GameInput::Press(L"ET_CAM_R"))
		{
			Move(CVector::RIGHT, m_Speed);
		}
		if (true == GameInput::Press(L"ET_CAM_U"))
		{
			GetTrans()->WMove(CVector::UP * GameTime::DeltaTime(m_Speed));
		}
		if (true == GameInput::Press(L"ET_CAM_D"))
		{
			GetTrans()->WMove(CVector::DOWN * GameTime::DeltaTime(m_Speed));
		}
		if (true == GameInput::Press(L"ET_CAM_F"))
		{
			GetTrans()->WMove(CVector::FORWARD * GameTime::DeltaTime(m_Speed));
		}
		if (true == GameInput::Press(L"ET_CAM_B"))
		{
			GetTrans()->WMove(CVector::BACK * GameTime::DeltaTime(m_Speed));
		}
		if (true == GameInput::Press(L"ET_CAMROT_P"))
		{
			CVector DIR = GameInput::MouseDir3D();
			GetTrans()->WRotAddY(DIR.X * GameTime::DeltaTime(m_RotSpeed));
			GetTrans()->WRotAddX(-DIR.Y * GameTime::DeltaTime(m_RotSpeed));
		}
		else if (true == GameInput::Press(L"ET_CAMROT_M"))
		{

		}
	//}



}


CVector EditorCam::ScreenPos3DToWorldPos(const CVector& _ScreenPos)
{
	CVector WinScale = GameWin::MainObj()->Size();
	CVector ConPos;
	ConPos.X = _ScreenPos.X * GetCamSize().X / WinScale.X;
	ConPos.Y = _ScreenPos.Y * GetCamSize().Y / WinScale.Y;
	ConPos += GetActor()->GetTrans()->GetWPos2d();
	return ConPos;
}

EditorCam::EditorCam() {}
EditorCam::~EditorCam() {}