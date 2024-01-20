#pragma once
#include "GameRenderer.h"
#include "GameSprite.h"
#include <list>

class GameRasterizer;
class GameDepthstencil;
class GameBlend;

class GameSampler;
class GameTexture;
class GameConstantBuffer;

class GameVtxShader;
class GamePixShader;

class GameVtxBuffer;
class GameIdxBuffer;

class GameRenderer;
class GameTileRenderer : public GameRenderer
{

public:
	class TILEKEY
	{
	public:
		union
		{
			struct
			{
				__int64 X;
				__int64 Y;
			};

			struct
			{
				__int64 TileKey;
			};
		};

	public:
		TILEKEY& operator+=(const TILEKEY& _Other)
		{
			X += _Other.X;
			Y += _Other.Y;
			return *this;
		}

		TILEKEY() : X(0), Y(0)
		{
		}

		TILEKEY(int _X, int _Y) : X(_X), Y(_Y)
		{
		}
	}; 

public:
	class TILE //: public CRef
	{
	public:
		TILEKEY			m_TileInfo;
		CTransformData	m_TileTransData;
		unsigned int	m_TileIndex;
		
		TILE() {}
		~TILE() {}
	};

public:
	CPtr<GameSprite> m_TileSprite;
	GameString m_VSTileShaderName;
	GameString m_TileSprName;
	int m_TileSprIndex;

private:
	CVector m_TileCutData;
	int m_TileOption[4];

public:
	CVector m_TileColor;
	CVector m_TileScale;

public:
	std::map<__int64, TILE*> m_AllTile;
	std::list<TILE*> m_AllTileList;


public:
	TILEKEY m_UserKey;
	TILEKEY m_CamKey;

public:
	void UserKey(CVector _Pos)
	{
		m_UserKey.TileKey = AddKey((int)std::roundf(_Pos.X), (int)std::roundf(_Pos.Y));
	}

	void CamKey(CVector _Pos)
	{
		m_CamKey.TileKey = AddKey((int)std::roundf(_Pos.X), (int)std::roundf(_Pos.Y));
	}

public:
	bool IsTile(CVector _Pos)
	{
		if (m_AllTile.end() != m_AllTile.find(AddKey((int)std::roundf(_Pos.X), (int)std::roundf(_Pos.Y))))
		{
			return true;
		}

		return false;
	}

	TILEKEY IsTileIndex(CVector _Pos)
	{
		std::map<__int64, TILE*>::iterator Iter = m_AllTile.find(AddKey((int)std::roundf(_Pos.X), (int)std::roundf(_Pos.Y)));
		
		if (m_AllTile.end() != Iter)
		{
			TILEKEY Key;

			Key.TileKey = Iter->second->m_TileIndex;

			return  Key;
		}

		TILEKEY FalseKey;

		return FalseKey;
	}

public:
	__int64 AddKey(int _X, int _Y)
	{
		TILEKEY Key = TILEKEY(_X, _Y);

		return Key.TileKey;
	}

	void DeleteTile(CVector _Pos, unsigned int _Index)
	{
		DeleteTile((int)std::roundf(_Pos.X), (int)std::roundf(_Pos.Y), _Index);
	}

	void DeleteTile(int _X, int _Y, unsigned int _Index)
	{
		DeleteTile(AddKey(_X, _Y), _Index);
	}

	void DeleteTile(__int64 _Key, unsigned int _Index)
	{
		__int64 Key = _Key;

		std::map<__int64, TILE*>::iterator Iter = m_AllTile.find(Key);

		if (m_AllTile.end() == Iter)
		{
			return;
		}

		m_AllTileList.remove(Iter->second);
		//Iter->second->RD->Death();
		delete Iter->second;
		m_AllTile.erase(Iter);

	}

	void AddTile(CVector _Pos, unsigned int _Index)
	{
		AddTile((int)std::roundf(_Pos.X), (int)std::roundf(_Pos.Y), _Index);
	}

	void AddTile(int _X, int _Y, unsigned int _Index)
	{
		AddTile(AddKey(_X, _Y), _Index);
	}

	void AddTile(__int64 _Key, unsigned int _Index)
	{
		__int64 Key = _Key;

		std::map<__int64, TILE*>::iterator Iter = m_AllTile.find(Key);
		
		if (m_AllTile.end() != Iter)
		{
			DeleteTile(_Key, _Index);

			TILE* NewTile = new TILE();

			NewTile->m_TileInfo.TileKey = Key;
			NewTile->m_TileIndex = _Index;

			m_AllTile.insert(std::map<__int64, TILE*>::value_type(Key, NewTile));
			
			m_AllTileList.push_back(NewTile);



			RenderDataSetting();
			DrawSetting(NewTile->m_TileTransData);
			//int a = 0;
			/* */
			/*HSRENDERDATA* RD = CreateRenderData(L"2DRECT", L"2DSPRITE", NewTile->m_TileTransData);
			RD->SMP(L"LSMP", L"LSMP");
			RD->SMP(L"PSMP", L"PSMP");
			RD->CB(L"TEXCOLOR", m_Color, true);
			RD->TEX(L"SpriteTex", m_Sprite->Tex());
			NewTile->RD = RD;
			NewTile->m_Index = _Index;
			NewTile->RD->CB(L"TEXCUT", m_Sprite->CutData(NewTile->m_Index));*/

			return;
		}

		TILE* NewTile = new TILE();

		NewTile->m_TileInfo.TileKey = Key;
		NewTile->m_TileIndex = _Index;
		

		m_AllTile.insert(std::map<__int64, TILE*>::value_type(Key, NewTile));

		m_AllTileList.push_back(NewTile);

		RenderDataSetting();

	}

public:
	void SetSprite(const GameString& _Name, unsigned int _SpriteIndex = 0)
	{
		m_TileSprite = GameSprite::Find(_Name);

		if (nullptr == m_TileSprite)
		{
			MSG_ASSERT_CODE(L"원하는 스프라이트가 존재하지 않습니다.");
		}

		m_TileSprName = _Name;

		SpriteIndex(_SpriteIndex);
	}

	size_t GetSpriteCutSize(const GameString& _Name)
	{
		m_TileSprite = GameSprite::Find(_Name);

		if (nullptr == m_TileSprite)
		{
			MSG_ASSERT_CODE(L"원하는 스프라이트가 존재하지 않습니다.");
			return 0;
		}

		return m_TileSprite->Count();
	}

	CPtr<GameSprite> GetSprite()
	{
		return m_TileSprite;
	}

public:
	void SetNullSprite()
	{
		m_TileSprite = nullptr;
	}

	void VSShaderName(GameString _VSShaderName)
	{
		m_VSTileShaderName = _VSShaderName;
	}

	GameString GetSprName()
	{
		return m_TileSprName;
	}

	void SpriteIndex(unsigned int _SpriteIndex)
	{
		m_TileSprIndex = _SpriteIndex;
	}

	void SpriteIndexPlus(unsigned int _SpriteIndex)
	{
		m_TileSprIndex += _SpriteIndex;
	}

	void SpriteIndexMinus(unsigned int _SpriteIndex)
	{
		m_TileSprIndex -= _SpriteIndex;
	}

	void ColorMode(unsigned int _SpriteIndex)
	{
		m_TileOption[0] = _SpriteIndex;
	}

	void SetCutData(CVector _CutData)
	{
		m_TileCutData = _CutData;
	}

	int ColorMode()
	{
		return m_TileOption[0];
	}

public:
	void SetAlpha(float _Alpha)
	{
		m_TileColor.W = _Alpha;
	}

	float GetAlpha()
	{
		return m_TileColor.W;
	}

	void SetPlusAlpha(float _Alpha)
	{
		m_TileColor.W += _Alpha;
	}

	void SetMinusAlpha(float _Alpha)
	{
		m_TileColor.W -= _Alpha;
	}

	void SetColor(CVector _Color)
	{
		m_TileColor = _Color;
	}

	void SetScale(CVector _Scale)
	{
		m_TileScale.X = _Scale.X;
		m_TileScale.Y = _Scale.Y;
		m_TileScale.Z = 1.0f;
	}

public:
	static CPtr<GameRasterizer> TILE_RS;
	static CPtr<GameDepthstencil> TILE_DS;
	static CPtr<GameBlend> TILE_BLEND;

	static CPtr<GameSampler> TILE_SMP;

	static CPtr<GameVtxShader> TILE_VTXS;
	static CPtr<GamePixShader> TILE_ITXS;

	static CPtr<GameConstantBuffer> TILE_CBTRANS;
	static CPtr<GameConstantBuffer> TILE_CBCOLOR;
	static CPtr<GameConstantBuffer> TILE_CUTDATA;
	static CPtr<GameConstantBuffer> TILE_OPTION;

	static CPtr<GameVtxBuffer> TILE_VB;
	static CPtr<GameIdxBuffer> TILE_IB;

public:
	void Save(const GameString& _Path);
	void Load(const GameString& _Path);
	void Clear();

public:
	void Init(int _Order = 0);
	void Render(CPtr<GameCamera> _Cam) override;
	void RenderDataSetting();
	void DrawSetting(const CTransformData& _TransData);

};


//private:
//	static std::map<__int64, CPtr<TileData>>::iterator TileStart;
//	static std::map<__int64, CPtr<TileData>>::iterator TileEnd;
//	static std::map<__int64, CPtr<TileData>> m_AllTile;
//	static std::list<CPtr<TileData>> m_AllTileList;

//public:
//	void AddTile(CVector _Pos, unsigned int _SpriteIndex);
//	void AddTile(int _X, int _Y, unsigned int _SpriteIndex);
//	void AddTile(__int64 _Key, unsigned int _Index);
//	void DeleteTile(CVector _Pos, unsigned int _Index);
//	void DeleteTile(int _X, int _Y, unsigned int _Index);
//	void DeleteTile(__int64 _Key, unsigned int _Index);