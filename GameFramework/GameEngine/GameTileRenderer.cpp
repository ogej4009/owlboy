#include "GameTileRenderer.h"

#include "GameActor.h"
#include "GameMesh.h"
#include "GameSprite.h"
#include "Vtx.h"


GameTileRenderer::GameTileRenderer()
{
}

GameTileRenderer::~GameTileRenderer()
{
}

void GameTileRenderer::Init()
{
	GameRenderer::Init(L"FrameRect", L"Default", 0);
}

void GameTileRenderer::Init(int& _X, int& _Y, const GameString& _TexName, int _Index)
{
	GameRenderer::Init(L"FrameRect", L"Default", _Index);

	X = _X;
	Y = _Y;

	m_SprDrawColor = CVector::WHITE;
	m_SprRenderOption[3] = m_SprRenderOption[2] = m_SprRenderOption[1] = m_SprRenderOption[0] = 0;
	m_Sprite = GameSprite::Find(_TexName);

	if (m_Sprite != nullptr)
	{
		m_SprCutData = m_Sprite->SpriteData(0);
		//SetCBuffer(L"TransData", m_Parent->GetPTransData(), CBUFMODE::CB_LINK);
		//SetCBuffer(L"RenderOption", &m_SprRenderOption, CBUFMODE::CB_LINK);
		//m_SprParent->CreateRenderPlayer(0)->m_RenderOption.IsDifTexture = false;
		SetTexture(L"Tex", m_Sprite->Tex());
		SetSampler(L"Smp", L"LWSMP");
		SetCBuffer(L"CutData", &m_SprCutData, CBUFMODE::CB_LINK);
		SetCBuffer(L"DrawColor", &m_SprDrawColor, CBUFMODE::CB_LINK);	
	}

	SettingTile();

}

void GameTileRenderer::Update()
{
	m_SprCutData = m_Sprite->SpriteData(0);

}

void GameTileRenderer::Render(CPtr<GameCamera> _Cam)
{
}

void GameTileRenderer::TileAdd(CVector _Pos, unsigned int _Index)
{
	// 좌표를 통해 키를 만든다. 
	int2 Coord = CalCoord(_Pos);
	__int64 Key = Coord.Key;

	// 인덱스를 찾는 함수를 만든다. 
	//int Index = CalIndex(Coord);

	std::map<__int64, TILE>::iterator FindIter = m_mapAllTile.find(Key);

	//if (m_mapAllTile.end() != FindIter)
	//{
	//	TileRemove(_Pos, _Index);
	//	TILE* NewTile = new TILE();
	//	
	//	NewTile->Key.Key = Key;
	//	NewTile->Index = FindIter->second.Index; // 수정 
	//	NewTile->Rp = m_Render->GetRenderPlayer(NewTile->Index);
	//	//  + 텍스쳐 옵션설정 바꾼다. 
	//	NewTile->Rp->m_RenderOption.IsDifTexture = true;
	//	NewTile->Rp->SetTexture(L"SrcTex", m_Tex);
	//	NewTile->Rp->SetSampler(L"SrcSmp", L"LWSMP");
	//	CVector SprCutData = m_Sprite->SpriteData(5);
	//	NewTile->Rp->SetCBuffer(L"SrcCutData", &SprCutData, CBUFMODE::CB_LINK);
	//	m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
	//	NewTile->Rp->Render();
	//	return;
	//}

	//TileRemove(_Pos, _Index);
	//TILE* NewTile = new TILE();
	//NewTile->Key.Key = Key;
	//NewTile->Index = FindIter->second.Index; // 수정 
	//NewTile->Rp = m_Render->GetRenderPlayer(NewTile->Index);
	////  + 텍스쳐 옵션설정 바꾼다. 
	//NewTile->Rp->m_RenderOption.IsDifTexture = true;
	//NewTile->Rp->SetTexture(L"SrcTex", m_Tex);
	//NewTile->Rp->SetSampler(L"SrcSmp", L"LWSMP");
	//CVector SprCutData = m_Sprite->SpriteData(5);
	//NewTile->Rp->SetCBuffer(L"SrcCutData", &SprCutData, CBUFMODE::CB_LINK);
	//m_mapAllTile.insert(std::map<__int64, TILE>::value_type(Key, *NewTile));
	//NewTile->Rp->Render();
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
	//float4 Scale = GetTrans()->GetWScale(); // 맵 크기 ? 
	float XSize = MapSize.X / (float)X;
	float YSize = MapSize.Y / (float)Y;
	int2 ReturnIndex;
	float IndexX = _Pos.X / XSize;
	float IndexY = _Pos.Y / YSize;
	IndexX = roundf(IndexX);
	IndexY = roundf(IndexY);
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

			float CenterX = (x * InterX);
			float CenterY = (y * InterY);

			m_mapAllTile[Index.Key].KEY.Arr[0] = CenterX + HInterX;
			m_mapAllTile[Index.Key].KEY.Arr[1] = CenterY + HInterY;
			m_mapAllTile[Index.Key].INDEX = m_SprIndex;
			m_SprIndex++;
		}
	}
}

