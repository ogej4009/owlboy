#include "LevelDesignTool.h"
#include <GameDebugPlus.h>
#include <FreeCam.h>
#include <GameLight.h>


void LevelDesignTool::RenderTargetUpdate()
{

	CVector CamScale = { 12.80f , 7.20f };

	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(0)
	// , CamScale, CVector{ (640.0f - CamScale.X), 360, 0.0f }, CVector::BLACK);
	// 
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(1)
	// , CamScale, CVector{ (640.0f - CamScale.X), 360 - CamScale.Y, 0.0f }, CVector::BLACK);
	// 
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(2)
	// , CamScale, CVector{ (640.0f - CamScale.X), 360 - CamScale.Y * 2, 0.0f }, CVector::BLACK);
	// 
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(3)
	// , CamScale, CVector{ (640.0f - CamScale.X), 360 - CamScale.Y * 3, 0.0f }, CVector::BLACK);
	// 
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(6)
	// , CamScale, CVector{ (640.0f - CamScale.X * 2.0F), 360 - CamScale.Y * 3, 0.0f }, CVector::BLACK);
	// 
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->GbufferTarget()->Texture(7)
	// , CamScale, CVector{ (640.0f - CamScale.X), 360 - CamScale.Y * 4, 0.0f }, CVector::BLACK);
	// 
	//GameDebugPlus::DrawDebugTexture(m_LightCom->ShadowTarget()->Texture(0)
	// , CVector{ CamScale.X, CamScale.X }
	// , CVector{ (640.0f - CamScale.X * 2.0f), (360 - CamScale.Y * 4) + CamScale.X - CamScale.Y, 0.0f }
	// , CVector::BLACK);
	// 
	////GameDebugPlus::DrawDebugTexture(m_BloomFilterCom->OutTarget->Texture(0)
	// , Scale, CVector{ (640.0f - Scale.X * 2.0f), 360, 0.0f }, CVector::BLACK);
	// 
	//GameDebugPlus::DrawDebugTexture(m_FreeCamCom->DeferredLightTarget()->Texture(3)
	// , CamScale, CVector{ (640.0f - CamScale.X * 2.0f), 360 - CamScale.Y * 1, 0.0f }, CVector::BLACK);


}




//void WTOOLMAPSCENE::DebugTargetUdpate()
//{
//#pragma region DEBUGTEXTURE RENDERTARGET
//	float Ratio = 2.0f;
//	WVECTOR Scale = { 128 * Ratio, 72 * Ratio };
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(0)
// , Scale, WVECTOR{ (640.0f - Scale.x), 360, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(1), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(2), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 2, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(3), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 3, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(6), Scale, WVECTOR{ (640.0f - Scale.x * 2.0F), 360 - Scale.y * 3, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->GbufferTarget()->Texture(7), Scale, WVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 4, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_LightCom->ShadowTarget()->Texture(0), WVECTOR{ Scale.x, Scale.x }, WVECTOR{ (640.0f - Scale.x * 2.0f), (360 - Scale.y * 4) + Scale.x - Scale.y, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_BloomFilterCom->OutTarget->Texture(0), Scale, WVECTOR{ (640.0f - Scale.x * 2.0f), 360, 0.0f }, WVECTOR::BLACK);
//	W3DDEBUG::DrawDebugTexture(m_CamCom->DefferdLightTarget()->Texture(3), Scale, WVECTOR{ (640.0f - Scale.x * 2.0f), 360 - Scale.y * 1, 0.0f }, WVECTOR::BLACK);
//	// 포그 필터 
//	// W3DDEBUG::DrawDebugTexture( ) 
//#pragma endregion
//}



//void HTOOLMAPSCENE::Update()
//{
//	PlayerUpdate();
//
//	// H3DDEBUG::DrawDebugText(L"AAAA");
//	float Ratio = 2.0f;
//	HVECTOR Scale = { 128 * Ratio, 72 * Ratio };
//
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(0), Scale, HVECTOR{ (640.0f - Scale.x), 360, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(1), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(2), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 2, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(3), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 3, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(7), Scale, HVECTOR{ (640.0f - Scale.x), 360 - Scale.y * 4, 0.0f }, HVECTOR::BLACK);
//
//	H3DDEBUG::DrawDebugTexture(LightCom->ShadowTarget()->Texture(0), HVECTOR{ Scale.x, Scale.x }, HVECTOR{ (640.0f - Scale.x * 2.0f), (360 - Scale.y * 4) + Scale.x - Scale.y, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(CamPtr->GbufferTarget()->Texture(6), Scale, HVECTOR{ (640.0f - Scale.x * 2.0F), 360 - Scale.y * 3, 0.0f }, HVECTOR::BLACK);
//	H3DDEBUG::DrawDebugTexture(m_BloomFilter->OutTarget->Texture(0), Scale, HVECTOR{ (640.0f - Scale.x * 2.0f), 360, 0.0f }, HVECTOR::BLACK);
//
//	H3DDEBUG::DrawDebugTexture(CamPtr->DefferdLightTarget()->Texture(3), Scale, HVECTOR{ (640.0f - Scale.x * 2.0f), 360 - Scale.y * 1, 0.0f }, HVECTOR::BLACK);
//
//	HRightView::View->PushFbxList();
//
//	if (nullptr == AniCom)
//	{
//		return;
//	}
//
//	if (AniCom->CurAni()->IsEnd())
//	{
//		CString Text;
//
//		HRightView::View->m_PlayBtn.GetWindowTextW(Text);
//
//		if (Text != L"다시 재생")
//		{
//			HRightView::View->m_PlayBtn.SetWindowTextW(L"다시 재생");
//		}
//		return;
//	}
//
//	HRightView::View->CurFrame(AniCom->CurAni()->m_CurFrame);
//
//}

