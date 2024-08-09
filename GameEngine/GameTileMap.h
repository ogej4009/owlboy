#pragma once
#include <GameMath.h>
#include <vector>
#include "GameRenderer.h"


//////////////////////////////////////// 
struct TILE
{
	int2 Key; 
	UINT Index;
	CTransData TD;
	GameRenderPlayer* RP; 
};


class GameMesh;
class GameSprite;
class GameRenderer;
class GameRenderPlayer;
class GameTexture;
class GameTransform;
class GameTileMap : public ActorComponent
{
private:
	int X;
	int Y;

private:
	CPtr<GameSprite> m_Sprite;
	CPtr<GameMesh> m_Mesh;
	CPtr<GameRenderer> m_Render;
	CPtr<GameRenderPlayer> m_RP;
	std::vector<Vtx2D> m_VecVtx;
	std::map<__int64, TILE> m_mapAllTile;
	std::list<TILE*> m_listAllTile;
	CPtr<GameTexture> m_Tex;
	CPtr<GameTransform> m_Trans;
	CVector m_SprCutData;

private:
	CVector m_FocusInfo;
	CVector m_TilePos;

public:
	// 타일추가제거기능.. 
	void TileAdd(CVector _Pos, unsigned int _Index);
	void TileRemove(CVector _Pos, unsigned int _Index);
	void TileClear();
	void TileSave();
	void TileLoad();

public:
	// 디자인뷰어에서 활용할 함수..
	int2 CalCoord(float4 _Pos);
	float LimitLevel(float4 _Pos);
	CVector CalPosWorld(const CVector& _Pos);
	CVector CalTexPos(const CVector& _Pos);
	void SetWorldTexture(const GameString _Name);

public:
	void Init() override;
	void Init(int& _X, int& _Y, const GameString& _TexName, int _Index = 0);
	void Update() override;

};

#define TILE_INTERVAL 0.16f
