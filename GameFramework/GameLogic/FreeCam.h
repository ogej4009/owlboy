#pragma once
#include "GameUnity.h"
#include <set>

#pragma comment(lib, "GameBase.lib")
#pragma comment(lib, "GameEngine.lib")


class FreeCam : public ActorComponent
{
	CPtr<GameCamera> m_Cam;
	float m_MoveSpeed;
	float m_HMoveSpeed;
	float m_RotSpeed;
	float m_HRotSpeed;
	CVector m_StartPos;
	CVector m_StartRot;
	float m_StartFov;
	CVector m_FixedPos;
	CVector m_FixedRot;
	float m_FixedFov;


public:
	void CamReset();
	void CamAccel();// 가속
	void CamDecel();// 감속 
	void CamZoomIn();
	void CamZoomOut();

public:
	void Init() override;
	void Update() override;

public:
	FreeCam();
	~FreeCam();

};

#define FREECAM_HMOVESPEED 0.5f
#define FREECAM_MOVESPEED 1.0f
#define FREECAM_ROTSPEED 200.0f
#define FREECAM_HROTSPEED 10.0f
#define FREECAM_FOV 60.0f
#define FREECAM_FOV_ARGU 0.1f
#define FREECAM_FOV_MIN 30.0f
#define FREECAM_FOV_MAX 99.9f
#define FREECAM_DEF_POS_Z -9.9f
#define FREECAM_DEF_ROT_X 45.0f
#define FREECAM_MOVESPEED_MAX 5.0f
#define FREECAM_MOVESPEED_MIN 1.0f
#define FREECAM_MOVESPEED_ARGU 0.1f