#pragma once
#include "GameUnity.h"

#pragma comment(lib, "GameBase.lib")
#pragma comment(lib, "GameEngine.lib")

class ScrollCam : public ActorComponent
{
	CPtr<GameCamera> m_Cam;
	float m_Speed;

public:
	void Move(const CVector& _Dir, float _Speed);
	void Join(CPtr<GameTransform> _Parent);
	void Withdraw();

public:
	void Init() override;
	void Update() override;

public:
	ScrollCam();
	~ScrollCam();
};