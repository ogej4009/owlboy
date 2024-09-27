#include "Intro.h"
#include <ValueData.h>
#include <EnumData.h>
#include <GameTexture.h>
#include <GameSprite.h>
#include <GameSpriteRenderer.h>
#include <GameDebugPlus.h>
#include <RectFade.h>
#include <GameLight.h>
#include <GameRenderTarget.h>
#include <ScrollCam.h>



void Intro::Init()
{

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetLPos(ValueData::CAM_DEFAULT_POS);
		CPtr<GameCamera> NewCam = NewActor->CreateCom<GameCamera>(0
			, (UINT)eRENDER_ORDER::RO_ACTOR);
		NewCam->SetCamSize({ 12.8f * 2.0f, 7.2f * 2.0f });
		NewCam->SetMode(CAMMODE::ORTH);
		m_ScrollCamCom = NewActor->CreateCom<ScrollCam>();
		m_ScrollCamActor = NewActor;
	}
}

void Intro::Update()
{
	if (TRUE == GameInput::Down(L"NEXTPAGE"))
	{
		GameScene::ChangeScene(L"TUTOR");
	}
}

void Intro::SceneChangeStart()
{
	
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"Intro");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
		for (auto& _File : FileList)
		{
			GameSprite::Create(_File.FileName(), 1, 1);
		}
	}


	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 10.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(L"sprIntro_2782x1564.png", (UINT)eRENDER_ORDER::RO_ACTOR);
		NewRender->SetSrcSizeOfTexture(L"sprIntro_2782x1564.png");
	}

	{
		CPtr<GameActor> NewActor = GetScene()->CreateActor();
		NewActor->GetTrans()->SetWPos({ 0.0f, 0.0f, 0.0f });
		CPtr<GameSpriteRenderer> NewRender = NewActor->CreateCom<GameSpriteRenderer>(L"sprFadeBlack_32x32.png", (UINT)eRENDER_ORDER::RO_ACTOR);
		NewRender->SetWScale({ 100.0f, 100.0f, 1.0f });
		CPtr<RectFade> NewFade = NewActor->CreateCom<RectFade>();
		NewFade->FadeIn();
	}

	{
		m_LightActor = GetScene()->CreateActor();
		float4 Dir = CVector(0.0f, 1.0f, -1.0f);
		Dir *= 10.0f;
		m_LightCom = m_LightActor->CreateCom<GameLight>(0);
		m_mapAllLight.insert(std::map<int, CPtr<GameLight>>::value_type(0, m_LightCom));
		CPtr<GameRenderer> NewRender = m_LightActor->CreateCom<GameRenderer>(L"SquarePyramid", L"DebugMesh");
		m_LightActor->GetTrans()->SetWPos(Dir);
		m_LightActor->GetTrans()->WRotAddX(45.0f);
	}

	

}

void Intro::SceneChangeEnd()
{

	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Local");
		Dic.Move(L"Intro");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Delete(_File.FileName());
		}
		for (auto& _File : FileList)
		{
			GameSprite::Delete(_File.FileName());
		}
	}

}

Intro::Intro()
{
}

Intro::~Intro()
{
}

