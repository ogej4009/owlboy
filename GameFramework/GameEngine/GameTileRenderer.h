#pragma once
#include <GameMath.h>
#include <vector>
#include "GameRenderer.h"
#include "GameSprite.h"


class TILE
{
public:
	int2 KEY;
	unsigned int INDEX;
};


class GameMesh;
class GameSprite;
class GameRenderer;
class GameRenderPlayer;
class GameTexture;
class GameTransform;
class GameTileRenderer : public GameRenderer
{
private:
	int X;
	int Y;

private:
	CPtr<GameSprite> m_Sprite;
	CPtr<GameTexture> m_Tex;
	CPtr<GameMesh> m_Mesh;
	CPtr<GameTransform> m_Trans;
	CPtr<GameRenderer> m_Render;
	CPtr<GameRenderPlayer> m_RP;
	std::vector<Vtx2D> m_VecVtx;
	std::vector<CPtr<GameRenderPlayer>> RPList;
	CVector m_SprCutData;
	CVector m_SprDrawColor;
	int m_SprRenderOption[4];
	std::map<__int64, TILE> m_mapAllTile;
	std::list<TILE*> m_listAllTile;
	int m_SprIndex;
	CVector MapSize;

public:
	void TileAdd(CVector _Pos, unsigned int _Index);
	void TileRemove(CVector _Pos, unsigned int _Index);
	void TileClear();
	void TileSave();
	void TileLoad();

public:  
	int2 CalCoord(float4 _Pos);
	CVector CalPosWorld(const CVector& _Pos);
	CVector CalTexPos(const CVector& _Pos);

public:
	void SettingTile();
	void SetMapSize(CVector _Size)
	{
		MapSize = _Size;
	}

public:
	void Init() override;
	void Init(int& _X, int& _Y, const GameString& _TexName, int _Index = 0);
	void Update() override;
	void Render(CPtr<GameCamera> _Cam) override;

public:
	GameTileRenderer();
	~GameTileRenderer();

};


#define TILE_INTERVAL_A 0.16f

