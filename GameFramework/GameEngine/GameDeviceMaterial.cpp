#include "GameDevice.h"
#include "GameMaterial.h"
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "GameBlend.h"
#include "GameRasterizer.h"
#include "GameDepthStencil.h"

#pragma warning( push )
#pragma warning( disable : 26444 )

void GameDevice::MaterialInit()
{
	

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"EmissionMap");
		MAT->SetVtxShader(L"VS_EmissionMap");
		MAT->SetPixShader(L"PS_EmissionMap");
		MAT->SetRasterizer(L"Front");
		MAT->SetDepthStencil(L"ZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"EmissionMapBloomCheck");
		MAT->SetVtxShader(L"VS_EmissionMapBloomCheck");
		MAT->SetPixShader(L"PS_EmissionMapBloomCheck");
		MAT->SetRasterizer(L"Front");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"EmissionMapBloom");
		MAT->SetVtxShader(L"VS_EmissionMapBloom");
		MAT->SetPixShader(L"PS_EmissionMapBloom");
		MAT->SetRasterizer(L"Front");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}


	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"Fog");
		MAT->SetVtxShader(L"VS_Fog");
		MAT->SetPixShader(L"PS_Fog");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"Shadow");
		MAT->SetVtxShader(L"VS_Shadow");
		MAT->SetPixShader(L"PS_Shadow");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"DefaultDepth");
		MAT->SetBlend(L"ShadowBlend");
	}
	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"HeightMap");
		MAT->SetVtxShader(L"VS_MapDeferredTexture");
		MAT->SetPixShader(L"PS_MapDeferredTexture");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"DefaultDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"OutLine");
		MAT->SetVtxShader(L"VS_OutLine");
		MAT->SetPixShader(L"PS_OutLine");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}
	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"OutLineDraw");
		MAT->SetVtxShader(L"VS_OutLineDraw");
		MAT->SetPixShader(L"PS_OutLineDraw");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"MotionBlur");
		MAT->SetVtxShader(L"VS_MotionBlur");
		MAT->SetPixShader(L"PS_MotionBlur");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"MotionBlurDraw");
		MAT->SetVtxShader(L"VS_MotionBlurDraw");
		MAT->SetPixShader(L"PS_MotionBlurDraw");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"EmissionBloomCheck");
		MAT->SetVtxShader(L"VS_EmissionBloomCheck");
		MAT->SetPixShader(L"PS_EmissionBloomCheck");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"EmissionBloom");
		MAT->SetVtxShader(L"VS_EmissionBloom");
		MAT->SetPixShader(L"PS_EmissionBloom");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"AlwaysZeroDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"Emission");
		MAT->SetVtxShader(L"VS_Emission");
		MAT->SetPixShader(L"PS_Emission");
		MAT->SetRasterizer(L"Back");
		MAT->SetDepthStencil(L"ZeroDepth"); 
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"StaticDeferredTexturePaperBurn");
		MAT->SetVtxShader(L"VS_StaticDeferredTexturePaperBurn");
		MAT->SetPixShader(L"PS_StaticDeferredTexturePaperBurn");
		MAT->SetRasterizer(L"Front");
		MAT->SetDepthStencil(L"DefaultDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> MAT = GameMaterial::Create(L"Sky");
		MAT->SetVtxShader(L"VS_Sky");
		MAT->SetPixShader(L"PS_Sky");
		MAT->SetRasterizer(L"Front");
		MAT->SetDepthStencil(L"DefaultDepth");
		MAT->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DebugMesh");
		Material->SetVtxShader(L"VS_DebugMesh");
		Material->SetPixShader(L"PS_DebugMesh");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetDebugBack");
		Material->SetVtxShader(L"VS_TargetDebugBack");
		Material->SetPixShader(L"PS_TargetDebugBack");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetDebug");
		Material->SetVtxShader(L"VS_TargetDebug"); 
		Material->SetPixShader(L"PS_TargetDebug");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredMerge");
		Material->SetVtxShader(L"VS_DeferredMerge");
		Material->SetPixShader(L"PS_DeferredMerge");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredLight");
		Material->SetVtxShader(L"VS_DeferredLight");
		Material->SetPixShader(L"PS_DeferredLight");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"OneBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Deferred");
		Material->SetVtxShader(L"VS_Deferred");
		Material->SetPixShader(L"PS_Deferred");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredStatic");
		Material->SetVtxShader(L"VS_DeferredStatic");
		Material->SetPixShader(L"PS_DeferredStatic");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Forward");
		Material->SetVtxShader(L"VS_Forward");
		Material->SetPixShader(L"PS_Forward");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{ // SkyBoxø° ¥Î«ÿ 
		CPtr<GameMaterial> Material = GameMaterial::Create(L"DeferredFront");
		Material->SetVtxShader(L"VS_DeferredFront");
		Material->SetPixShader(L"PS_DeferredFront");
		Material->SetRasterizer(L"Front");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	// ≈◊Ω∫∆Æ 

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Dash");
		Material->SetVtxShader(L"VS_Dash");
		Material->SetPixShader(L"PS_Dash");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Grid");
		Material->SetVtxShader(L"VS_Grid");
		Material->SetPixShader(L"PS_Grid");
		Material->SetRasterizer(L"None");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Fire");
		Material->SetVtxShader(L"VS_Fire");
		Material->SetPixShader(L"PS_Fire");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	//{
	//	CPtr<GameMaterial> Material = GameMaterial::Create(L"Particle");
	//	Material->SetVtxShader(L"VS_Particle");
	//	Material->SetGeoShader(L"GS_Particle");
	//	Material->SetPixShader(L"PS_Particle");
	//	Material->SetRasterizer(L"Back");
	//	Material->SetDepthStencil(L"DefaultDepth");
	//	Material->SetBlend(L"AlphaBlend");
	//}

	// ±‚∫ª 

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TileMap");
		Material->SetVtxShader(L"VS_TileMap");
		Material->SetPixShader(L"PS_TileMap");
		Material->SetRasterizer(L"None");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Sprite"); // UI&RECT 
		Material->SetVtxShader(L"VS_Sprite"); 
		Material->SetPixShader(L"PS_Sprite"); 
		//Material->SetRasterizer(L"Back"); //UI
		Material->SetRasterizer(L"None");
		//Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	// ¿Ã∆Â∆Æ 

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"ExGradien"); //ExGradien
		Material->SetVtxShader(L"VS_ExGradien");
		Material->SetPixShader(L"PS_ExGradien");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"YLight");
		Material->SetVtxShader(L"VS_YLight");
		Material->SetPixShader(L"PS_YLight");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Vertical");
		Material->SetVtxShader(L"VS_Vertical");
		Material->SetPixShader(L"PS_Vertical");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Horizon");
		Material->SetVtxShader(L"VS_Horizon");
		Material->SetPixShader(L"PS_Horizon");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"Distortion");
		Material->SetVtxShader(L"VS_Distortion");
		Material->SetPixShader(L"PS_Distortion");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"GhostBurn");
		Material->SetVtxShader(L"VS_GhostBurn");
		Material->SetPixShader(L"PS_GhostBurn");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"DefaultDepth");
		Material->SetBlend(L"AlphaBlend");
	}

	// ∑ª¥ı≈∏∞Ÿ 
	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetMergePlus"); 
		Material->SetVtxShader(L"VS_TargetMerge");
		Material->SetPixShader(L"PS_TargetMerge");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"OneBlend");
	}

	{
		CPtr<GameMaterial> Material = GameMaterial::Create(L"TargetMerge");
		Material->SetVtxShader(L"VS_TargetMerge");
		Material->SetPixShader(L"PS_TargetMerge");
		Material->SetRasterizer(L"Back");
		Material->SetDepthStencil(L"AlwaysDepth");
		Material->SetBlend(L"AlphaBlend");
	}
	
}


#pragma warning( pop )

