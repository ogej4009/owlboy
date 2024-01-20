#pragma once
#include "GameShader.h"

class GamePixShader : public GameShader, public GameFileMgr<GamePixShader>
{
public:
	static CPtr<GamePixShader> Load(const GameString& _Path, const GameString& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0)
	{
		CPtr<GamePixShader> Res = CreateAndInsertToFile(_Path);
		Res->Load(_FuncName, _VH, _VL);
		return Res;
	}

public:
	ID3D11PixelShader* m_ShaderPtr;

public:
	void Load(const GameString& _FuncName, unsigned int _VH = 5, unsigned int _VL = 0);
	void Setting();

public:
	GamePixShader() : m_ShaderPtr(nullptr)
	{
		m_Type = SHADERTYPE::SHADER_PS;
	}

	~GamePixShader()
	{
		m_ShaderPtr->Release();
	}
};