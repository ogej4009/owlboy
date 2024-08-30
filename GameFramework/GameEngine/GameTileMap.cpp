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

	Setting();

}

void GameTileMap::Update()
{
	// TILE 정보 
}

void GameTileMap::Setting()
{
	m_mapAllTile.clear();

	int HX = (X / 2);
	int HY = (Y / 2);

	float InterX = (1.0f / (float)X);
	float InterY = (1.0f / (float)Y);

	float HInterX = InterX * 0.5f;
	float HInterY = InterY * 0.5f;

	for (int y = -HY; y < (HY + 1); y++)
	{
		for (int x = -HX; x < (HX + 1); x++)
		{
			int2 Index;

			Index.x = x;
			Index.y = y;

			float CenterX = (x * InterX);
			float CenterY = (y * InterY);

			m_mapAllTile[Index.Key].Key.Arr[0] = CenterX + HInterX;
			m_mapAllTile[Index.Key].Key.Arr[1] = CenterY + HInterY;
			m_mapAllTile[Index.Key].Index = m_Index;
			m_mapAllTile[Index.Key].RP = m_Render->GetRenderPlayer(m_Index);

			CalTexPos({ m_mapAllTile[Index.Key].Key.Arr[0], m_mapAllTile[Index.Key].Key.Arr[1] });

			m_Index++;
			int TEST = 0;
		}
	}
}









void GameTileMap::TileAdd(CVector _Pos, unsigned int _Index)
{
	int2 Coord = CalCoord(_Pos);
	__int64 Key = Coord.Key;
	std::map<__int64, TILE>::iterator FindIter = m_mapAllTile.find(Key);

	if (m_mapAllTile.end() != FindIter)
	{
		//TileRemove(_Pos, _Index);
		TILE* NewTile = new TILE();
		NewTile->Key.Key = Key;
		NewTile->Index = _Index;
		NewTile->RP = m_RP;
		m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
		//m_Render->RPAddOn(_Index);
		return;
	}

	//TileRemove(_Pos, _Index);
	TILE* NewTile = new TILE();
	NewTile->Key.Key = Key;
	m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
	m_Render->RPAddOn(RPList, _Index);
	return;
}


/* 
	void CreateTile(__int64 _Key, unsigned int _Index)
	{
		__int64 Key = _Key;
		std::map<__int64, TILE*>::iterator Fiter = m_AllTile.find(Key);
		if (m_AllTile.end() != Fiter)
		{
			DeleteTile(_Key, _Index);

			TILE* NewTile = new TILE(0, nullptr);
			NewTile->m_Key.TileKey = Key;
			NewTile->m_Index = _Index;

			m_AllTile.insert(std::map<__int64, TILE*>::value_type(Key, NewTile));
			m_AllTileList.push_back(NewTile);

			HSRENDERDATA* RD = CreateRenderData(L"2DRECT", L"2DSPRITE", NewTile->m_TransData);
			RD->SMP(L"LSMP", L"LSMP");
			RD->SMP(L"PSMP", L"PSMP");
			RD->CB(L"TEXCOLOR", m_Color, true);
			RD->TEX(L"SpriteTex", m_Sprite->Tex());

			NewTile->RD = RD;
			NewTile->RD->CB(L"TEXCUT", m_Sprite->CutData(NewTile->m_Index));
			return;
		}
		TILE* NewTile = new TILE(0, nullptr);
		NewTile->m_Key.TileKey = Key;

		m_AllTile.insert(std::map<__int64, TILE*>::value_type(Key, NewTile));
		m_AllTileList.push_back(NewTile);

		HSRENDERDATA* RD = CreateRenderData(L"2DRECT", L"2DSPRITE", NewTile->m_TransData);
		RD->SMP(L"LSMP", L"LSMP");
		RD->SMP(L"PSMP", L"PSMP");
		RD->CB(L"TEXCOLOR", m_Color, true);
		RD->TEX(L"SpriteTex", m_Sprite->Tex());
		NewTile->RD = RD;
		NewTile->m_Index = _Index;
		NewTile->RD->CB(L"TEXCUT", m_Sprite->CutData(NewTile->m_Index));

	}
*/






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



// 스케일에 문제 있다. 딱 Y 0.16만큼
