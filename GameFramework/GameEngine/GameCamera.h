#pragma once
#include "GameComponent.h"
#include <set>
#include <GameDebug.h>

#pragma region 카메라 정의 
/*
	카메라를 들고 있는 Actor의 위치가 곧 카메라가 보고 있는 위치이다.
*/
#pragma endregion

enum class CAMMODE
{
	ORTH, // 직교투영 == Orthographic Projection
	PERS, // 원근투영 == Perspective projection 
};

class GameRenderer;
class GameCamera : public ActorComponent
{
public:
	friend GameTransform;
	friend GameScene;

private:
	CAMMODE m_Mode;
	CMatrix m_View;
	CMatrix m_Proj;
	CMatrix m_VP;
	CVector m_CamSize;
	float m_CamNear;
	float m_CamFar;
	float m_CamFov;

public:
	CMatrix GetMrxView()
	{
		return m_View;
	}

	CMatrix GetMrxProj()
	{
		return m_Proj;
	}

	CMatrix GetMrxVP()
	{
		return m_VP;
	}
#pragma region 카메라-랜더그룹
	/*
		내가 바라보는 랜더러들의 그룹을 <카메라>가 알고 있어야 한다.
	*/
#pragma endregion
private:
	std::set<int> m_ViewRenderers;

public:
	CVector GetCamSize() { return m_CamSize; }
	float GetCamFov() { return m_CamFov; }
	float GetCamNear() { return m_CamNear; }
	float GetCamFar() { return m_CamFar; }

	void SetCamSize(const CVector _Value) { m_CamSize = _Value; }
	void SetCamFov(float _Value) { m_CamFov = _Value; }
	void SetCamNear(float _Value) { m_CamNear = _Value; }
	void SetCamFar(float _Value) { m_CamFar = _Value; }

private:
	void StartSetting(int _Order);

public:
	CAMMODE GetMode()
	{
		return m_Mode;
	}
	void SetMode(CAMMODE _MODE) { m_Mode = _MODE; }

public:
	template<typename ... REST>
	void Init(int _Order, REST ... _ARG)
	{
		StartSetting(_Order);
		AddRenderGroup(_ARG...);
	}

public:
	void AddRenderGroup() {}

	template<typename ... REST>
	void AddRenderGroup(int _GroupIndex, REST ... _ARG)
	{
		if (m_ViewRenderers.end() != m_ViewRenderers.find(_GroupIndex))
		{
			MSG_ASSERT_CODE(L"카메라가 같은 그룹을 두번 보려고 했습니다.");
		}

		m_ViewRenderers.insert(_GroupIndex);
		AddRenderGroup(_ARG...);
	}

	void AddRenderGroup(int _GroupIndex)
	{
		if (m_ViewRenderers.end() != m_ViewRenderers.find(_GroupIndex))
		{
			MSG_ASSERT_CODE(L"카메라가 같은 그룹을 두번 보려고 했습니다");
		}
		m_ViewRenderers.insert(_GroupIndex);
	}

public:
	void RenderPrev() override;

public:
	CVector ScreenPos3dToWorldPos(const CVector& _ScreenPos);

public:
	CVector CamOrthMousePos2d();
	CVector OrthWorldMousePos2d();

};
