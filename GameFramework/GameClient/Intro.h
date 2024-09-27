#pragma once
#include <GameUnity.h>


class ScrollCam;
class Intro : public SceneComponent
{
	CPtr<GameActor> m_ScrollCamActor;
	CPtr<ScrollCam> m_ScrollCamCom;
	CPtr<GameActor> m_LightActor;
	CPtr<GameLight> m_LightCom;
	std::map<int, CPtr<GameLight>> m_mapAllLight;

public:
	void Init() override;
	void Update() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;

public:
	Intro();
	~Intro();
};

