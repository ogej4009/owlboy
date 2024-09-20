#include "LevelDesignViewer.h"


void LevelDesignViewer::DebugTargetUpdate()
{
#pragma region DEBUGTEXTURE RENDERTARGET
	float Ratio = 2.0f;
	CVector Scale = { 128 * Ratio , 72 * Ratio };

	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(0), Scale, CVector{ (640.0f - Scale.X), 360, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(1), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(2), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y * 2, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(3), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y * 3, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(6), Scale, CVector{ (640.0f - Scale.X * 2.0F), 360 - Scale.Y * 3, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(7), Scale, CVector{ (640.0f - Scale.X), 360 - Scale.Y * 4, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_LightCom->ShadowTarget()->Texture(0), CVector{ Scale.X, Scale.X }, CVector{ (640.0f - Scale.X * 2.0f), (360 - Scale.Y * 4) + Scale.X - Scale.Y, 0.0f }, CVector::BLACK);
	////GameDebugPlus::DrawDebugTexture(m_BloomFilterCom->OutTarget->Texture(0), Scale, CVector{ (640.0f - Scale.X * 2.0f), 360, 0.0f }, CVector::BLACK);
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->DeferredLightTarget()->Texture(3), Scale, CVector{ (640.0f - Scale.X * 2.0f), 360 - Scale.Y * 1, 0.0f }, CVector::BLACK);

	// 포그 필터 
	// GameDebugPlus::DrawDebugTexture( ) 
#pragma endregion
}


