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
#include "GameCamera.h"
#include <GameString.h>

void GameSpriteRenderer::Init()
{
	GameRenderer::Init(L"FrameRect", L"Sprite", 0);


}

void GameSpriteRenderer::Init(int Order)
{
	GameRenderer::Init(L"FrameRect", L"Sprite", Order);
	m_SprDrawColor = CVector::WHITE;
	//m_SprRenderOption[3] = m_SprRenderOption[2] = m_SprRenderOption[1] = m_SprRenderOption[0] = 0;
	
}

void GameSpriteRenderer::Init(const GameString& Name, int Order)
{
	GameRenderer::Init(L"FrameRect", L"Sprite", Order);

	m_SprDrawColor = CVector::WHITE;
	//m_SprRenderOption[3] = m_SprRenderOption[2] = m_SprRenderOption[1] = m_SprRenderOption[0] = 0;
	m_Sprite = GameSprite::Find(Name);

	if (m_Sprite != nullptr)
	{
		m_SprCutData = m_Sprite->SpriteData(0);
		SetTexture(L"Tex", m_Sprite->Tex());
		SetSampler(L"Smp", L"LWSMP");
		//SetCBuffer(L"TransData", m_Parent->GetPTransData(), CBUFMODE::CB_LINK);
		SetCBuffer(L"CutData", &m_SprCutData, CBUFMODE::CB_LINK);
		SetCBuffer(L"DrawColor", &m_SprDrawColor, CBUFMODE::CB_LINK);
		//SetCBuffer(L"RenderOption", &m_SprRenderOption, CBUFMODE::CB_LINK);
		//m_SprParent->CreateRenderPlayer(0)->m_RenderOption.IsDifTexture = false;
		//m_SprParent->CreateRenderPlayer(0)->m_RenderOption.IsNormalTexture = true;
	}

}

void GameSpriteRenderer::Update()
{
	m_SprCutData = m_Sprite->SpriteData(m_SprIndex);
}

void GameSpriteRenderer::Render(CPtr<GameCamera> _Cam)
{
	/*
	DebugCheck();
	if (nullptr == m_Sprite)
	{
		MSG_ASSERT_CODE(L"스프라이트가 세팅되지 않았습니다");
	}
	m_SprCutData = m_Sprite->SpriteData(m_SprIndex);
	SetCBuffer(L"TransData", m_Parent->GetPTransData(), CBUFMODE::CB_LINK);
	SetCBuffer(L"CutData", &m_SprCutData, CBUFMODE::CB_LINK);
	SetCBuffer(L"DrawColor", &m_SprDrawColor, CBUFMODE::CB_LINK);
	SetCBuffer(L"RenderOption", &m_SprRenderOption, CBUFMODE::CB_LINK);
	SetTexture(L"Tex", m_Sprite->Tex());
	SetSampler(L"Smp", L"PWSMP");
	*/
	//GameRenderer::Render(_Cam);

}

//void GameSpriteRenderer::RenderUpdate(CPtr<GameCamera> _Cam)
//{
//	//m_Sprite->Tex()->Setting(SHADERTYPE::SHADER_PS, 0);
//	/*
//	SetTexture(L"Tex", m_Sprite->Tex());
//	SetSampler(L"Smp", L"PWSMP");
//	*/
//}

GameSpriteRenderer::GameSpriteRenderer()
{
}

GameSpriteRenderer::~GameSpriteRenderer()
{
}

//
//void WFbxEx::LoadUserFormat(const WGAMESTRING& _AniName, const WGAMESTRING& _MainFBXName)
//{
//	std::wcout << L"Load START" << std::endl;
//
//
//	WGAMEDIRECTORY Dic;
//	Dic.MoveParent(L"Wah3DX");
//	Dic.Move(L"RES");
//	Dic.Move(L"MESH");
//	Dic.Move(_MainFBXName);
//
//	Dic.SetPath(Dic.PlusFileName(_AniName));
//	WGAMESTRING _Path = Dic.PCONSTWCHAR();
//	_Path.ChangeStr(L".FBX", L".WFBXEX");
//
//	WGAMEFILE LoadFile = WGAMEFILE(_Path, L"rb");
//
//	int Size;
//	LoadFile >> Size;
//
//	m_UserAniData.resize(Size);
//
//	for (size_t i = 0; i < m_UserAniData.size(); i++)
//	{
//		LoadFile >> m_UserAniData[i].AniName;
//		LoadFile >> m_UserAniData[i].StartTime;
//		LoadFile >> m_UserAniData[i].EndTime;
//		LoadFile >> m_UserAniData[i].TimeStartCount;
//		LoadFile >> m_UserAniData[i].TimeEndCount;
//		LoadFile >> m_UserAniData[i].FrameCount;
//		LoadFile >> m_UserAniData[i].TimeMode;
//		LoadFile >> m_UserAniData[i].FbxModeCount;
//		LoadFile >> m_UserAniData[i].FbxModeRate;
//
//		LoadFile >> Size;
//		m_UserAniData[i].m_AniFrameData.resize(Size);
//		for (size_t j = 0; j < m_UserAniData[i].m_AniFrameData.size(); j++)
//		{
//			LoadFile >> m_UserAniData[i].m_AniFrameData[j].BoneIndex;
//			LoadFile >> m_UserAniData[i].m_AniFrameData[j].BoneParentIndex;
//			LoadFile >> Size;
//			m_UserAniData[i].m_AniFrameData[j].m_Data.resize(Size);
//			for (size_t k = 0; k < m_UserAniData[i].m_AniFrameData[j].m_Data.size(); k++)
//			{
//				LoadFile >> m_UserAniData[i].m_AniFrameData[j].m_Data[k].S;
//				LoadFile >> m_UserAniData[i].m_AniFrameData[j].m_Data[k].Q;
//				LoadFile >> m_UserAniData[i].m_AniFrameData[j].m_Data[k].T;
//				LoadFile >> m_UserAniData[i].m_AniFrameData[j].m_Data[k].Time;
//				LoadFile >> m_UserAniData[i].m_AniFrameData[j].m_Data[k].FrameMat;
//				LoadFile >> m_UserAniData[i].m_AniFrameData[j].m_Data[k].GlobalAnimation;
//				LoadFile >> m_UserAniData[i].m_AniFrameData[j].m_Data[k].LocalAnimation;
//
//			}
//		}
//	}
//}
//void WFbxEx::SaveUserFormat(const WGAMESTRING& _AniName, const WGAMESTRING& _MainFBXName)
//{
//	std::wcout << L"SAVE START" << std::endl;
//
//	WGAMEDIRECTORY Dic;
//	Dic.MoveParent(L"Wah3DX");
//	Dic.Move(L"RES");
//	Dic.Move(L"MESH");
//	Dic.Move(_MainFBXName, true);
//
//	Dic.SetPath(Dic.PlusFileName(_AniName));
//	WGAMESTRING _Path = Dic.PCONSTWCHAR();
//	_Path.ChangeStr(L".FBX", L".WFBXEX");
//
//	WGAMEFILE SaveFile = WGAMEFILE(_Path, L"wb");
//
//
//
//	SaveFile << (int)m_UserAniData.size();
//	for (size_t i = 0; i < m_UserAniData.size(); i++)
//	{
//		SaveFile << m_UserAniData[i].AniName;
//		SaveFile << m_UserAniData[i].StartTime;
//		SaveFile << m_UserAniData[i].EndTime;
//		SaveFile << m_UserAniData[i].TimeStartCount;
//		SaveFile << m_UserAniData[i].TimeEndCount;
//		SaveFile << m_UserAniData[i].FrameCount;
//		SaveFile << m_UserAniData[i].TimeMode;
//		SaveFile << m_UserAniData[i].FbxModeCount;
//		SaveFile << m_UserAniData[i].FbxModeRate;
//
//		SaveFile << (int)m_UserAniData[i].m_AniFrameData.size();
//		for (size_t j = 0; j < m_UserAniData[i].m_AniFrameData.size(); j++)
//		{
//			SaveFile << m_UserAniData[i].m_AniFrameData[j].BoneIndex;
//			SaveFile << m_UserAniData[i].m_AniFrameData[j].BoneParentIndex;
//			SaveFile << (int)m_UserAniData[i].m_AniFrameData[j].m_Data.size();
//			for (size_t k = 0; k < m_UserAniData[i].m_AniFrameData[j].m_Data.size(); k++)
//			{
//				SaveFile << m_UserAniData[i].m_AniFrameData[j].m_Data[k].S;
//				SaveFile << m_UserAniData[i].m_AniFrameData[j].m_Data[k].Q;
//				SaveFile << m_UserAniData[i].m_AniFrameData[j].m_Data[k].T;
//				SaveFile << m_UserAniData[i].m_AniFrameData[j].m_Data[k].Time;
//				SaveFile << m_UserAniData[i].m_AniFrameData[j].m_Data[k].FrameMat;
//				SaveFile << m_UserAniData[i].m_AniFrameData[j].m_Data[k].GlobalAnimation;
//				SaveFile << m_UserAniData[i].m_AniFrameData[j].m_Data[k].LocalAnimation;
//
//			}
//		}
//	}
//	int a = 0;
//}
//
