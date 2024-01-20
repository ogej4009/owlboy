#pragma once
#include "GameRenderer.h"
#include "GameSprite.h"

class GameSpriteRenderer : public GameRenderer
{
public:
	CVector SprColor;
	CVector SprScale;

public:
	GameString m_VSShaderName;

private:
	CVector CutData;
	CPtr<GameSprite> m_Spr;
	unsigned int m_SprIndex;
	int Option[4];
	GameString Name;

public:
	void SetNullSprite()
	{
		m_Spr = nullptr;
	}

	void VSShaderName(GameString _VSShaderName)
	{
		m_VSShaderName = _VSShaderName;
	}

	GameString GetSprName()
	{
		return Name;
	}

	void SetSprite(const GameString& _Name, unsigned int _SpriteIndex = 0)
	{
		m_Spr = GameSprite::Find(_Name);
		Name = _Name;
		SpriteIndex(_SpriteIndex);
	}

	CPtr<GameSprite> GetSprite()
	{
		return  m_Spr;
	}

	void SpriteIndex(unsigned int _SpriteIndex)
	{
		m_SprIndex = _SpriteIndex;
	}

	void SpriteIndexPlus(unsigned int _SpriteIndex)
	{
		m_SprIndex += _SpriteIndex;
	}

	void SpriteIndexMinus(unsigned int _SpriteIndex)
	{
		m_SprIndex -= _SpriteIndex;
	}

	void ColorMode(unsigned int _SpriteIndex)
	{
		Option[0] = _SpriteIndex;
	}

	void SetCutData(CVector _CutData)
	{
		CutData = _CutData;
	}

	int ColorMode()
	{
		return Option[0];
	}

public:
	void Init(int _Order = 0);
	void Render(CPtr<GameCamera> _Cam) override;

#pragma region Render의상황
	/*
		상속구조 :
		Transform > Renderer > SpriteRenderer
		(CamUpdate) ---------> [Render()]여기서 사용
	*/
#pragma endregion

public:
	void SetAlpha(float _Alpha)
	{
		SprColor.W = _Alpha;
	}

	float GetAlpha()
	{
		return SprColor.W;
	}

	void SetPlusAlpha(float _Alpha)
	{
		SprColor.W += _Alpha;
	}

	void SetMinusAlpha(float _Alpha)
	{
		SprColor.W -= _Alpha;
	}

	void SetColor(CVector _Color)
	{
		SprColor = _Color;
	}

	void SetScale(CVector _Scale)
	{
		SprScale.X = _Scale.X;
		SprScale.Y = _Scale.Y;
		SprScale.Z = 1.0f;
	}

public:
	GameSpriteRenderer();
	~GameSpriteRenderer();

};