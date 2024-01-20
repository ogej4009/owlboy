#include "GameDevice.h"
#include "GameDevice.h"
#include <GameIO.h>
#include "GameVtxShader.h"
#include "GamePixShader.h"
#include "Vtx.h"


#pragma  warning( push )
#pragma  warning( disable : 26444 )

void GameDevice::ShaderInit()
{
	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"GameShader");

	{
		CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Default.hlsl"), L"VS2DIMAGE");
		VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->CreateLayout();
		GamePixShader::Load(m_Dir.CombineFileName(L"Default.hlsl"), L"PS2DIMAGE");
	}

	{
		CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Vertical.hlsl"), L"VS2DIMAGEC");
		VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->CreateLayout();
	}

	{
		CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Horizon.hlsl"), L"VS2DIMAGECC");
		VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->CreateLayout();
	}

	{
		CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Distortion.hlsl"), L"VS2DIMAGED");
		VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->CreateLayout();
	}

	{
		CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"Ghostburn.hlsl"), L"VS2DIMAGEG");
		VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->CreateLayout();
	}

	{
		CPtr<GameVtxShader> VTX = GameVtxShader::Load(m_Dir.CombineFileName(L"TileMap.hlsl"), L"VS_TILEMAP");
		VTX->AddLayout("SHA_INIT_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->AddLayout("SHA_INIT_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		VTX->CreateLayout();
		GamePixShader::Load(m_Dir.CombineFileName(L"TileMap.hlsl"), L"PS_TILEMAP");

	}



#pragma region VTX
	/*
		VS2DIMAGE를 인자로 넣는 이유
		하나의 쉐이더 안에 여러개의 함수가 있으니 인자값으로 넣어줄 때 하나 지정한다.
		VTX->AddLayout()
		VTX->AddLayout()
		VTX->AddLayout()
		VTX->CreateLayout()
	*/
#pragma endregion

}

#pragma warning( pop )