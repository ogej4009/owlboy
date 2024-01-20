#include "GameSpriteRenderer.h"
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
#include "GameTexture.h"
#include "GameSprite.h"
#include "GameCamera.h"



void GameSpriteRenderer::Init(int _Order)
{
	// 부모의 함수 호출하는 방법.
	GameRenderer::Init(_Order);

	m_VSShaderName = L"Default.hlsl";
	if (nullptr == GameConstantBuffer::Find(L"_TRANSDATA")) // 이름중복제거 
	{
		GameConstantBuffer::Create<CTransformData>(L"_TRANSDATA");
		GameConstantBuffer::Create<CVector>(L"_CUTDATA");
		GameConstantBuffer::Create<CVector>(L"_COLOR");
		GameConstantBuffer::Create(L"_OPTION", 16); // 크기를 직접넣어주었다. 
	}
	SprColor = CVector::WHITE;
	Option[3] = Option[2] = Option[1] = Option[0] = 0;
}

/* Render()에서 모든 것을 해결하는 구조로 기획 */
void GameSpriteRenderer::Render(CPtr<GameCamera> _Cam)
{
	DebugCheck();

	if (nullptr == m_Spr)
	{
		MSG_ASSERT_CODE(L"스프라이트가 세팅되지 않았습니다");
	}

	CamUpdate(_Cam);

	CPtr<GameRasterizer> RS = GameRasterizer::Find(L"NONE");
	CPtr<GameDepthstencil> DS = GameDepthstencil::Find(L"DEFDEPTH");
	CPtr<GameBlend> BLEND = GameBlend::Find(L"AlphaBlend");

	RS->Setting();
	DS->Setting();
	BLEND->Setting();

	CPtr<GameSampler> SMP = GameSampler::Find(L"PWSMP");

	m_Spr->Tex()->Setting(SHADERTYPE::SHADER_PS, 0);
	SMP->Setting(SHADERTYPE::SHADER_PS, 0);

	CPtr<GameVtxShader> VTXS = GameVtxShader::Find(m_VSShaderName);
	CPtr<GamePixShader> ITXS = GamePixShader::Find(L"Default.hlsl");

	CPtr<GameConstantBuffer> CBTRANS = GameConstantBuffer::Find(L"_TRANSDATA");
	CPtr<GameConstantBuffer> CBCOLOR = GameConstantBuffer::Find(L"_COLOR");
	CPtr<GameConstantBuffer> CUTDATA = GameConstantBuffer::Find(L"_CUTDATA");
	CPtr<GameConstantBuffer> OPTION = GameConstantBuffer::Find(L"_OPTION");

	if (L"Default.hlsl" == m_VSShaderName)
	{
		CutData = m_Spr->SpriteData(m_SprIndex);
	}

	CBTRANS->DataChange(m_TD);
	CBCOLOR->DataChange(SprColor);
	CUTDATA->DataChange(CutData);
	OPTION->DataChange(Option);

	CBTRANS->Setting(SHADERTYPE::SHADER_VS, 0);
	CUTDATA->Setting(SHADERTYPE::SHADER_VS, 1);
	CBCOLOR->Setting(SHADERTYPE::SHADER_PS, 0);
	OPTION->Setting(SHADERTYPE::SHADER_PS, 1);

	VTXS->Setting();
	ITXS->Setting();

	CPtr<GameVtxBuffer> VB = GameVtxBuffer::Find(L"RECT2DCOLOR");
	CPtr<GameIdxBuffer> IB = GameIdxBuffer::Find(L"RECT2DCOLOR");

	VB->Setting();
	IB->Setting();

	GameDevice::MainObj()->Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GameDevice::MainObj()->Context()->DrawIndexed(IB->Count(), 0, 0);

}

GameSpriteRenderer::GameSpriteRenderer()
{
}

GameSpriteRenderer::~GameSpriteRenderer()
{
}

