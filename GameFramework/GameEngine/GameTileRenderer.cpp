#include "GameTileRenderer.h"
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

CPtr<GameRasterizer> GameTileRenderer::TILE_RS = nullptr;
CPtr<GameDepthstencil> GameTileRenderer::TILE_DS = nullptr;
CPtr<GameBlend> GameTileRenderer::TILE_BLEND = nullptr;

CPtr<GameSampler> GameTileRenderer::TILE_SMP = nullptr;

CPtr<GameVtxShader> GameTileRenderer::TILE_VTXS = nullptr;
CPtr<GamePixShader> GameTileRenderer::TILE_ITXS = nullptr;

CPtr<GameConstantBuffer> GameTileRenderer::TILE_CBTRANS = nullptr;
CPtr<GameConstantBuffer> GameTileRenderer::TILE_CBCOLOR = nullptr;
CPtr<GameConstantBuffer> GameTileRenderer::TILE_CUTDATA = nullptr;
CPtr<GameConstantBuffer> GameTileRenderer::TILE_OPTION = nullptr;

CPtr<GameVtxBuffer> GameTileRenderer::TILE_VB = nullptr;
CPtr<GameIdxBuffer> GameTileRenderer::TILE_IB = nullptr;

void GameTileRenderer::Save(const GameString& _Path)
{
}

void GameTileRenderer::Load(const GameString& _Path)
{
}

void GameTileRenderer::Clear()
{
}

void GameTileRenderer::Init(int _Order)
{
	// 부모의 함수 호출하는 방법.
	GameRenderer::Init(_Order);
	
	m_VSTileShaderName = L"TileMap.hlsl";
	if (nullptr == GameConstantBuffer::Find(L"_TRANSDATA")) // 이름중복제거 
	{
		GameConstantBuffer::Create<CTransformData>(L"_TRANSDATA");
		GameConstantBuffer::Create<CVector>(L"_CUTDATA");
		GameConstantBuffer::Create<CVector>(L"_COLOR");
		GameConstantBuffer::Create(L"_OPTION", 16); // 크기를 직접넣어주었다. 
	}
	m_TileColor = CVector::WHITE;
	m_TileOption[3] = m_TileOption[2] = m_TileOption[1] = m_TileOption[0] = 0;
}

void GameTileRenderer::Render(CPtr<GameCamera> _Cam)
{
	DebugCheck();

	if (nullptr == m_TileSprite)
	{
		MSG_ASSERT_CODE(L"타일 스프라이트가 세팅되지 않았습니다");
	}

	CamUpdate(_Cam);

	CVector TilePos;



	for (auto& Tile : m_AllTileList)
	{
		if ((-0.08f + m_CamKey.X) > Tile->m_TileInfo.X
			|| (0.08f + m_CamKey.X) < Tile->m_TileInfo.X
			|| (-0.08f + m_CamKey.Y) > Tile->m_TileInfo.Y
			|| (0.08f + m_CamKey.Y) < Tile->m_TileInfo.Y)
		{
			continue;
		}

		Tile->m_TileTransData.WWORLD = GetTD().WWORLD;    

		TilePos.X = Tile->m_TileTransData.WWORLD.ArrV[3].X + (float)(Tile->m_TileInfo.X * Tile->m_TileTransData.WWORLD.ArrV[0].X);
		TilePos.Y = Tile->m_TileTransData.WWORLD.ArrV[3].Y + (float)(Tile->m_TileInfo.Y * Tile->m_TileTransData.WWORLD.ArrV[1].Y);
		TilePos.Z = Tile->m_TileTransData.WWORLD.ArrV[3].Z;

		Tile->m_TileTransData.WWORLD.ArrV[3] = TilePos;
		Tile->m_TileTransData.VIEW = _Cam->GetMrxView();
		Tile->m_TileTransData.PROJ = _Cam->GetMrxProj();
		Tile->m_TileTransData.WV = Tile->m_TileTransData.WWORLD * Tile->m_TileTransData.VIEW;
		Tile->m_TileTransData.VP = _Cam->GetMrxVP();
		Tile->m_TileTransData.WVP = Tile->m_TileTransData.WWORLD * Tile->m_TileTransData.VIEW * Tile->m_TileTransData.PROJ;
		Tile->m_TileTransData.CalTransData();

		if (false == this->GetActor()->IsUpdateObj())
		{
			continue;
		}

		RenderDataSetting();

		DrawSetting(Tile->m_TileTransData);
	}

}

void GameTileRenderer::RenderDataSetting()
{

	TILE_RS = GameRasterizer::Find(L"NONE");
	TILE_DS = GameDepthstencil::Find(L"DEFDEPTH");
	TILE_BLEND = GameBlend::Find(L"AlphaBlend");

	TILE_SMP = GameSampler::Find(L"PWSMP");
	
	TILE_VTXS = GameVtxShader::Find(m_VSTileShaderName);
	TILE_ITXS = GamePixShader::Find(L"TileMap.hlsl");

	TILE_CBTRANS = GameConstantBuffer::Find(L"_TRANSDATA");
	TILE_CBCOLOR = GameConstantBuffer::Find(L"_COLOR");
	TILE_CUTDATA = GameConstantBuffer::Find(L"_CUTDATA");
	TILE_OPTION = GameConstantBuffer::Find(L"_OPTION");

	TILE_VB = GameVtxBuffer::Find(L"RECT_TILE");
	TILE_IB = GameIdxBuffer::Find(L"RECT_TILE");

	if (L"TileMap.hlsl" == m_VSTileShaderName)
	{
		m_TileCutData = m_TileSprite->SpriteData(m_TileSprIndex);
	}
	
}

void GameTileRenderer::DrawSetting(const CTransformData& _TransData)
{

	TILE_CBTRANS->DataChange(_TransData);
	TILE_CBCOLOR->DataChange(m_TileColor);
	TILE_CUTDATA->DataChange(m_TileCutData);
	TILE_OPTION->DataChange(m_TileOption);

	TILE_RS->Setting();
	TILE_DS->Setting();
	TILE_BLEND->Setting();

	m_TileSprite->Tex()->Setting(SHADERTYPE::SHADER_PS, 0);
	TILE_SMP->Setting(SHADERTYPE::SHADER_PS, 0);

	TILE_CBTRANS->Setting(SHADERTYPE::SHADER_VS, 0);
	TILE_CUTDATA->Setting(SHADERTYPE::SHADER_VS, 1);
	TILE_CBCOLOR->Setting(SHADERTYPE::SHADER_PS, 0);
	TILE_OPTION->Setting(SHADERTYPE::SHADER_PS, 1);

	TILE_VTXS->Setting();
	TILE_ITXS->Setting();

	TILE_VB->Setting();
	TILE_IB->Setting();

	GameDevice::MainObj()->Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GameDevice::MainObj()->Context()->DrawIndexed(TILE_IB->Count(), 0, 0);
}
