#include "GameTileMap.h"
#include "GameActor.h"
#include "GameMesh.h"
#include "GameSprite.h"
#include "Vtx.h"


void GameTileMap::TileAdd(CVector _Pos, unsigned int _Index)
{
	int2 Coord = CalCoord(_Pos);
	__int64 Key = Coord.Key;
	std::map<__int64, TILE>::iterator FindIter = m_mapAllTile.find(Key);

	if (m_mapAllTile.end() != FindIter)
	{
		TileRemove(_Pos, _Index);

		TILE* NewTile = new TILE();
		NewTile->Key.Key = Key;

		m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
		m_listAllTile.push_back(NewTile);

		NewTile->RPlayer = m_RPlayer; 
		CVector SpriteVec = m_Sprite->SpriteData(NewTile->Index);
		NewTile->RPlayer->SetCBuffer(L"SrcTexIdx", &SpriteVec, CBUFMODE::CB_LINK);
		NewTile->RPlayer->SetSampler(L"SrcSmp", L"LWSMP");
		return;
	}

	TILE* NewTile = new TILE();
	NewTile->Key.Key = Key;

	m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
	m_listAllTile.push_back(NewTile);

	NewTile->RPlayer = m_RPlayer;
	NewTile->Index = _Index;
	CVector SpriteVec = m_Sprite->SpriteData(NewTile->Index);
	NewTile->RPlayer->SetCBuffer(L"SrcTexIdx", &SpriteVec, CBUFMODE::CB_LINK);
	NewTile->RPlayer->SetSampler(L"SrcSmp", L"LWSMP");

}



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
	CVector Size = m_Tex->Size();
	CVector Vec;
	Vec.X = _Pos.X + 0.5f;
	Vec.Y = (_Pos.Y * -1.0f) + 0.5f;
	Vec.X *= Size.X;
	Vec.Y *= Size.Y;
	return Vec;
}


CVector GameTileMap::CalPosWorld(const CVector& _Pos)
{
	CVector ReturnVec;
	CVector ScaleVec;
	ScaleVec = GetTrans()->GetWScale();
	ReturnVec.X = _Pos.X * ScaleVec.X;
	ReturnVec.Y = _Pos.Y * ScaleVec.Y;
	ReturnVec.Z = _Pos.Z;
	return ReturnVec;
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


void GameTileMap::SetTileTex(const GameString _Name)
{

	m_Render->SetTexture(L"SrcTex", _Name); 
//	CVector SpriteVec = m_Sprite->SpriteData(NewTile->Index);
//	m_Render->SetCBuffer(L"SrcTexIdx", &SpriteVec, CBUFMODE::CB_LINK);
	m_Render->SetSampler(L"SrcSmp", L"LWSMP");

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

			// 트랜스폼 만들기..
			//TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x);
			//TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y);
			//TilePos.z = Tile->m_TransData.W.ArrVec[3].z;

			CVector TilePos;

			//TilePos = GetActor()->GetTrans()->GetWPos();
			//TilePos.X += (float)m_mapAllTile[Index.Key].TileKey.Arr[0];
			//TilePos.Y += (float)m_mapAllTile[Index.Key].TileKey.Arr[1];

			// 1
			TilePos = CalTexPos({(float)m_mapAllTile[Index.Key].Key.Arr[0]
				, (float)m_mapAllTile[Index.Key].Key.Arr[1]	});
			// 2
			//m_mapAllTile = 여기다 넣어  


		}
	}


}


void GameTileMap::Init() {}
void GameTileMap::Init(int& _X, int& _Y, const GameString& _SrcTexName, int _Index)
{

	// 값확인
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

	m_Render = GetActor()->CreateCom<GameRenderer>(_Index);  

	m_Sprite = GameSprite::Find(_SrcTexName);
	m_Tex = GameTexture::Find(_SrcTexName);

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

	m_Render->CreateRenderPlayer(m_Mesh, L"TileMap");
	
	SetTileTex(_SrcTexName);

}

void GameTileMap::Update()
{
	m_FocusInfo = CVector(0.0f, 0.0f);

	CVector TilePos;

	for (auto& Tile : m_listAllTile)
	{

		if ((-TILE_INTERVAL + m_FocusInfo.X) > Tile->Key.x	||
			(TILE_INTERVAL + m_FocusInfo.X) < Tile->Key.x	||
			(-TILE_INTERVAL + m_FocusInfo.Y) > Tile->Key.y	||
			(TILE_INTERVAL + m_FocusInfo.Y) < Tile->Key.y)
		{
			continue;
		}

		TilePos.X = Tile->Data.WWORLD.ArrV[3].X + (float)(Tile->Key.x * Tile->Data.WWORLD.ArrV[0].X);
		TilePos.Y = Tile->Data.WWORLD.ArrV[3].Y + (float)(Tile->Key.y * Tile->Data.WWORLD.ArrV[0].Y);
		TilePos.Z = Tile->Data.WWORLD.ArrV[3].Z;

		Tile->Data.WWORLD.ArrV[3] = TilePos;

	}

//	CVector	WorldPos = CalPosWorld();
	float4 MapCenterPos = GetTrans()->GetWPos();
	int2 MapCoord = CalCoord(MapCenterPos);


}


/* 

float GameHeightMap::YHeight(float4 _Pos)
{
	float4 Scale = GetTrans()->GetWScale();

	Scale = Scale.HalfVec();

	if (
		_Pos.Z > Scale.Z ||
		_Pos.Z < -Scale.Z ||
		_Pos.X > Scale.X ||
		_Pos.X < -Scale.X
		)
	{
		return Min;
	}

	CVector Ori = _Pos;
	Ori.Y = 0.0f;
	CVector Dir = CVector::UP;


	int2 Key = Index(_Pos);
	float YDis = Min;

	CVector UpTri0 = CalPosToWorld(m_YTileMap[Key.Key].Up.Arr[0]);
	CVector UpTri1 = CalPosToWorld(m_YTileMap[Key.Key].Up.Arr[1]);
	CVector UpTri2 = CalPosToWorld(m_YTileMap[Key.Key].Up.Arr[2]);
	DirectX::TriangleTests::Intersects(Ori, Dir, UpTri0, UpTri1, UpTri2, YDis);
	if (YDis != Min)
	{
		return YDis;
	}

	CVector DownTri0 = CalPosToWorld(m_YTileMap[Key.Key].Down.Arr[0]);
	CVector DownTri1 = CalPosToWorld(m_YTileMap[Key.Key].Down.Arr[1]);
	CVector DownTri2 = CalPosToWorld(m_YTileMap[Key.Key].Down.Arr[2]);
	DirectX::TriangleTests::Intersects(Ori, Dir, DownTri0, DownTri1, DownTri2, YDis);
	if (YDis != Min)
	{
		return YDis;
	}

	return Min;

}

*/

/* 

★ 트랜스 데이터를 계산하고 맞추는  함수를 만듭니다. 

void HSTRANS::CalTransData(HSCAM* _Cam)
{
	m_TransData.W = m_MatWWorld;
	m_TransData.V = _Cam->MatView();
	m_TransData.P = _Cam->MatProj();
	m_TransData.WV = m_TransData.W * m_TransData.V;
	m_TransData.VP = _Cam->MatViewProj();
	m_TransData.WVP = m_TransData.W * m_TransData.V * m_TransData.P;

	m_TransData.AllTP();
}

	void AllTP()
	{
		for (size_t i = 0; i < 6; i++)
		{
			Arr[i].TransPos();
		}
	}
*/


/*

★	트랜스폼을 세팅한다. 
	HSTRANS::Update();
	HSTRANS::CalTransData(_Cam); // 완 트랜스폼에서 이미 했다. 

	HSVEC4 TilePos;

	for (auto& Tile : m_listAllTile)
	{

		if ((-TILE_INTERVAL + m_CamKey.X) > Tile->m_Key.X ||
			(TILE_INTERVAL + m_CamKey.X) < Tile->m_Key.X  ||
			(-TILE_INTERVAL + m_CamKey.Y) > Tile->m_Key.Y ||
			(TILE_INTERVAL + m_CamKey.Y) < Tile->m_Key.Y)
		{
			continue;
		}
	
	
		--------------------- 타일의 위치를 정할 떄 트랜스 폼을 정의할 것이다. ---------------------
	
	
		Tile->m_TransData.W = CREFWW();
	
		TilePos.x = Tile->m_TransData.W.ArrVec[3].x + (float)(Tile->m_Key.X * Tile->m_TransData.W.ArrVec[0].x);
		TilePos.y = Tile->m_TransData.W.ArrVec[3].y + (float)(Tile->m_Key.Y * Tile->m_TransData.W.ArrVec[1].y);
		TilePos.z = Tile->m_TransData.W.ArrVec[3].z;
	
		Tile->m_TransData.W.ArrVec[3] = TilePos;
		Tile->m_TransData.V = _Cam->MatView();
		Tile->m_TransData.P = _Cam->MatProj();
		Tile->m_TransData.WV = Tile->m_TransData.W * Tile->m_TransData.V;
		Tile->m_TransData.VP = _Cam->MatViewProj();
		Tile->m_TransData.WVP = Tile->m_TransData.W * Tile->m_TransData.V * Tile->m_TransData.P;
		Tile->m_TransData.AllTP();
	
		if (false == Tile->RD->IsUpdate())
		{
			continue;
		}
		Tile->RD->Render();
	
	}
*/

