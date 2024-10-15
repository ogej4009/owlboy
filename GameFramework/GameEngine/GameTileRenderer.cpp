#include "GameTileRenderer.h"
#include "GameActor.h"
#include "GameMesh.h"
#include "GameSprite.h"
#include "Vtx.h"


GameTileRenderer::GameTileRenderer() {}
GameTileRenderer::~GameTileRenderer() {}

void GameTileRenderer::Init() {}
void GameTileRenderer::Init(int& _X, int& _Y, const GameString& _TexName, int _Index)
{

	X = _X;
	Y = _Y;

	m_Render = GetActor()->CreateCom<GameRenderer>(_Index);

	m_Sprite = GameSprite::Find(_TexName);

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

	int TileIndex = X * Y;

	RPList = m_Render->CreateRenderPlayerTileRender(m_Mesh, L"TileRender", TileIndex);
	
	//SettingTile();

	m_SprIndex = 0;

	CVector SprCutData = m_Sprite->SpriteData(m_SprIndex);
	m_Render->SetCBuffer(L"SprCutData", &SprCutData, CBUFMODE::CB_LINK);

}

void GameTileRenderer::Update()
{
	m_SprCutData = m_Sprite->SpriteData(m_SprIndex);
}

void GameTileRenderer::Render(CPtr<GameCamera> _Cam)
{
}

void GameTileRenderer::TileAdd(CVector _Pos, unsigned int _Index)
{
	// 소스 텍스쳐 인덱스를 가져온다. 
	//m_BaseTextureIndex = _Index;

	//// 좌표를 통해 키를 만든다. 
	//int2 Coord = CalCoord(_Pos);
	//__int64 Key = Coord.Key;

	//// 인덱스를 찾는 함수를 만든다. 
	////int Index = CalIndex(Coord);

	////m_Sprite = GameSprite::Find(L"ColLevel2.png");
	//m_SprCutData = m_Sprite->SpriteData(_Index);
	//m_SprDrawColor = CVector::WHITE;

	//std::map<__int64, TILE*>::iterator Find_Iter = m_mapAllTile.find(Key);

	//if (m_mapAllTile.end() != Find_Iter)
	//{
	//	TileRemove(_Pos, _Index);
	//	
	//	TILE* NEWTILE = new TILE(/*0, nullptr*/);
	//	NEWTILE->KEY.Key = Key;
	//	NEWTILE->INDEX = m_BaseTextureIndex;

	//	m_mapAllTile.insert(std::map<__int64, TILE*>::value_type(Key, NEWTILE));
	//	m_listAllTile.push_back(NEWTILE);

	//	RP = GetRenderPlayer(Coord.Key);
	//	RP->SetCBuffer(L"CutData", &m_SprCutData, CBUFMODE::CB_LINK);
	//	//RP->SetCBuffer(L"DrawColor", &m_SprDrawColor, CBUFMODE::CB_LINK);
	//	RP->SetCBuffer(L"RenderOptionData", &m_SprRenderOption, CBUFMODE::CB_LINK);
	//	RP->SetTexture(L"BaseTex", m_Sprite->Tex());
	//	RP->SetSampler(L"BaseSmp", L"LWSMP");
	//	RP->m_RenderOption.IsDifTexture = true;
	//	return;		
	//}

	//TILE* NEWTILE = new TILE(/*0, nullptr*/);
	//NEWTILE->KEY.Key = Key;
	//NEWTILE->INDEX = m_BaseTextureIndex;

	//m_mapAllTile.insert(std::map<__int64, TILE*>::value_type(Key, NEWTILE));
	//m_listAllTile.push_back(NEWTILE);

	//RP = GetRenderPlayer(Coord.Key);
	//RP->SetCBuffer(L"CutData", &m_SprCutData, CBUFMODE::CB_LINK);
	////RP->SetCBuffer(L"DrawColor", &m_SprDrawColor, CBUFMODE::CB_LINK);
	//RP->SetCBuffer(L"RenderOptionData", &m_SprRenderOption, CBUFMODE::CB_LINK);
	//RP->SetTexture(L"BaseTex", m_Sprite->Tex());
	//RP->SetSampler(L"BaseSmp", L"LWSMP");
	//RP->m_RenderOption.IsDifTexture = true;

}

void GameTileRenderer::TileRemove(CVector _Pos, unsigned int _Index)
{
}

void GameTileRenderer::TileClear()
{
}

void GameTileRenderer::TileSave()
{
}

void GameTileRenderer::TileLoad()
{
}

int2 GameTileRenderer::CalCoord(float4 _Pos)
{
	float XSize = MapSize.X / (float)X;
	float YSize = MapSize.Y / (float)Y;
	int2 ReturnIndex;
	float IndexX = _Pos.X / XSize;
	float IndexY = _Pos.Y / YSize;
	IndexX = round(IndexX);
	IndexY = round(IndexY);
	ReturnIndex.x = (int)IndexX;
	ReturnIndex.y = (int)IndexY;
	return ReturnIndex;
}

CVector GameTileRenderer::CalPosWorld(const CVector& _Pos)
{
	CVector ScaleVec;
	ScaleVec = GetTrans()->GetWScale();
	CVector ResultVec;
	ResultVec.X = _Pos.X * ScaleVec.X;
	ResultVec.Y = _Pos.Y * ScaleVec.Y;
	ResultVec.Z = _Pos.Z;
	return ResultVec;
}

CVector GameTileRenderer::CalTexPos(const CVector& _Pos)
{
	CVector Size;
	Size = GetTrans()->GetWScale();
	CVector Vec;
	Vec.X = _Pos.X + 0.5f;
	Vec.Y = (_Pos.Y * -1.0f) + 0.5f;
	Vec.X *= Size.X;
	Vec.Y *= Size.Y;
	return Vec;
}

void GameTileRenderer::SettingTile()
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

			float CenterX = (x * InterX * 100);
			float CenterY = (y * InterY * 100);

			m_mapAllTile[Index.Key]->KEY.x = CenterX + HInterX;
			m_mapAllTile[Index.Key]->KEY.y = CenterY + HInterY;
			m_mapAllTile[Index.Key]->INDEX = m_SprIndex;
			m_SprIndex++;
		}
	}
}

