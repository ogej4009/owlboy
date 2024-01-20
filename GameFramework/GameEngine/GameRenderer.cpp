#include "GameRenderer.h"
#include "GameActor.h"
#include "GameScene.h"
#include "GameDevice.h"
#include "GameVtxBuffer.h"
#include "GameIdxBuffer.h"
#include "GameConstantBuffer.h"
#include "GameDepthstencil.h"
#include "GameBlend.h"
#include "GameRasterizer.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameSampler.h"
#include "GameSprite.h"
#include "GameCamera.h"

GameRenderer::GameRenderer() {}
GameRenderer::~GameRenderer() {}

void GameRenderer::Init(int _Order)
{
#pragma region 랜더러
	/*
		랜더러는 랜더러 이면서 트랜스폼이다.
		자신만의 위치와 크기를 가지고 있는 개념이다.

		부모 트랜스폼의 자식으로 정해진다.
		자식인것이 태어날 때부터 정해진 것이므로 따로 관리 안한다. 씬에 연관되지 않는다.
	*/
#pragma endregion

#pragma region 랜더러의 부모-자식 활용
	/*
		부모는 GameRenderer 이것이다.
		랜더러 자신이 트랜스폼이다.
		그러므로 가지고 있는 것들이 있다. m_TD
	*/
#pragma endregion
	SetParent(GetActor()->GetTrans());
	Order(_Order);
	GetActor()->GetScene()->PushRender(this);
}

void GameRenderer::Render(CPtr<GameCamera> _Cam) {}