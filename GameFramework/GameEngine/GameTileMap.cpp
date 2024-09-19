#include "GameTileMap.h"
#include "GameActor.h"
#include "GameMesh.h"
#include "GameSprite.h"
#include "Vtx.h"


void GameTileMap::Init() {}
void GameTileMap::Init(int& _X, int& _Y, const GameString& _SrcTexName, int _Index)
{
	float TestX;
	float TestY;

	TestX = TILE_INTERVAL; // 0.16f
	TestY = TILE_INTERVAL; // 0.16f

	float FullScaleX = TestX * _X;
	float FullScaleY = TestY * _Y;

	float4 FullScaleVec;
	FullScaleVec.X = FullScaleX;
	FullScaleVec.Y = FullScaleY;
	
	X = _X;
	Y = _Y;

//	m_Render = GetActor()->CreateCom<GameRenderer>(_Index);
	m_Render = GetActor()->CreateCom<GameRenderer>(0);

	m_Sprite = GameSprite::Find(_SrcTexName);
	m_Tex = GameTexture::Find(_SrcTexName);

	m_Index = 0;

	m_Mesh = new GameMesh();
	CPtr<GameVtxBuffer> VB = new GameVtxBuffer();
	CPtr<GameIdxBuffer> IB = new GameIdxBuffer();

	m_VecVtx.resize((X + 1) * (Y + 1));

	float StartX = -0.5f;
	float StartY = 0.5f;

	for (int y = 0; y < Y + 1; y++)
	{
		for (int x = 0; x < X + 1; x++)
		{
			float PosY = StartY - (y * ((float)1 / Y));
			float PosX = StartX + (x * ((float)1 / X));

			int Index = y * (X + 1) + x;

			m_VecVtx[Index].Pos.X = PosX;
			m_VecVtx[Index].Pos.Y = PosY;

			m_VecVtx[Index].Uv.X = (float)x;
			m_VecVtx[Index].Uv.Y = (float)y;
		}
	}

	VB->Create(m_VecVtx.size(), sizeof(Vtx2D), &m_VecVtx[0]);

	std::vector<UINT> m_MapIdx;

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			int Pivot = y * (X + 1) + x;

			m_MapIdx.push_back(Pivot);
			m_MapIdx.push_back(Pivot + 1);
			m_MapIdx.push_back(Pivot + (X + 1) + 1);

			m_MapIdx.push_back(Pivot);
			m_MapIdx.push_back(Pivot + (X + 1) + 1);
			m_MapIdx.push_back(Pivot + (X + 1));
		}
	}

	IB->Create(m_MapIdx.size(), sizeof(UINT), &m_MapIdx[0], DXGI_FORMAT::DXGI_FORMAT_R32_UINT);

	m_Mesh->SetVtxBuffer(VB);
	m_Mesh->SetIdxBuffer(IB);

	int TILEIDX = X * Y;

	FullRectSize = CVector{ X * TILE_INTERVAL, Y * TILE_INTERVAL };

	RPList = m_Render->CreateRenderPlayerTileMap(m_Mesh, L"TileMap", TILEIDX);
	//SettingTile();
}

void GameTileMap::Update()
{
	// TILE 정보


}

//
//void GameTileMap::TileAdd(CVector _Pos, unsigned int _Index)
//{
//	// 좌표를 통해 키를 만든다. 
//	int2 Coord = CalCoord(_Pos);
//	__int64 Key = Coord.Key;
//
//	// 인덱스를 찾는 함수를 만든다. 
//	//int Index = CalIndex(Coord);
//
//	std::map<__int64, TILE>::iterator FindIter = m_mapAllTile.find(Key);
//
//	if (m_mapAllTile.end() != FindIter)
//	{
//		TileRemove(_Pos, _Index);
//		TILE* NewTile = new TILE();
//		NewTile->Key.Key = Key;
//		NewTile->Index = 0; // 수정 
//		NewTile->Rp = m_Render->GetRenderPlayer(NewTile->Index);
//		//  + 텍스쳐 옵션설정 바꾼다. 
//		NewTile->Rp->m_RenderOption.IsDifTexture = true;
//		NewTile->Rp->SetTexture(L"SrcTex", m_Tex);
//		NewTile->Rp->SetSampler(L"SrcSmp", L"LWSMP");
//		CVector SprCutData = m_Sprite->SpriteData(5);
//		NewTile->Rp->SetCBuffer(L"SrcCutData", &SprCutData, CBUFMODE::CB_LINK);
//		m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
//		NewTile->Rp->Render();
//		return;
//	}
//
//	TileRemove(_Pos, _Index);
//	TILE* NewTile = new TILE();
//	NewTile->Key.Key = Key;
//	NewTile->Index = 0; // 수정 
//	NewTile->Rp = m_Render->GetRenderPlayer(NewTile->Index);
//	//  + 텍스쳐 옵션설정 바꾼다. 
//	NewTile->Rp->m_RenderOption.IsDifTexture = true;
//	NewTile->Rp->SetTexture(L"SrcTex", m_Tex);
//	NewTile->Rp->SetSampler(L"SrcSmp", L"LWSMP");
//	CVector SprCutData = m_Sprite->SpriteData(5);
//	NewTile->Rp->SetCBuffer(L"SrcCutData", &SprCutData, CBUFMODE::CB_LINK);
//	m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
//	NewTile->Rp->Render();
//}



void GameTileMap::TileRemove(CVector _Pos, unsigned int _Index)
{

}

void GameTileMap::TileClear()
{

}

void GameTileMap::TileSave()
{

}

void GameTileMap::TileLoad()
{

}



int GameTileMap::CalIndex(int2 _Coord)
{
	int aTileIdx = 0;
	return aTileIdx;
}

//
//void GameTileMap::SettingTile()
//{
//	m_mapAllTile.clear();
//
//	int HX = (X / 2);
//	int HY = (Y / 2);
//
//	float InterX = (1.0f / (float)X);
//	float InterY = (1.0f / (float)Y);
//
//	float HInterX = InterX * 0.5f;
//	float HInterY = InterY * 0.5f;
//
//	for (int y = -HY; y < (HY + 1); y++)
//	{
//		for (int x = -HX; x < (HX + 1); x++)
//		{
//			int2 Index;
//
//			Index.x = x;
//			Index.y = y;
//
//			float CenterX = (x * InterX);
//			float CenterY = (y * InterY);
//
//			m_mapAllTile[Index.Key].Key.Arr[0] = CenterX + HInterX;
//			m_mapAllTile[Index.Key].Key.Arr[1] = CenterY + HInterY;
//			m_mapAllTile[Index.Key].Index = Index;
//			Index++;
//		}
//	}
//}




CVector GameTileMap::CalTexPos(const CVector& _Pos)
{
	CVector Size = FullRectSize;
	Size = GetTrans()->GetWScale();
	CVector Vec;
	Vec.X = _Pos.X + 0.5f;
	Vec.Y = (_Pos.Y * -1.0f) + 0.5f;
	Vec.X *= Size.X;
	Vec.Y *= Size.Y;
	return Vec;
}

CVector GameTileMap::CalPosWorld(const CVector& _Pos)
{
	CVector ScaleVec;
	ScaleVec = GetTrans()->GetWScale();
	CVector ResultVec;
	ResultVec.X = _Pos.X * ScaleVec.X;
	ResultVec.Y = _Pos.Y * ScaleVec.Y;
	ResultVec.Z = _Pos.Z;
	return ResultVec;
}

int2 GameTileMap::CalCoord(float4 _Pos)
{
	float4 Scale = GetTrans()->GetWScale();
	float XSize = Scale.X / (float)X;
	float YSize = Scale.Y / (float)Y;
	int2 ReturnIndex;
	float IndexX = _Pos.X / XSize;
	float IndexY = _Pos.Y / YSize;
	IndexX = roundf(IndexX);
	IndexY = roundf(IndexY);
	ReturnIndex.x = (int)IndexX;
	ReturnIndex.y = (int)IndexY;
	return ReturnIndex;
}

