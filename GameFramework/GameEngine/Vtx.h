#pragma once
#include <GameMath.h>

class Vtx2D
{
public:
	CVector Pos;
	CVector Uv;
	CVector Color;

	//Vtx2D& operator=(const CVector& _Value)
	//{
	//	Pos.X = _Value.X;
	//	Pos.Y = _Value.Y;
	//	Pos.Z = _Value.Z;
	//	return *this;
	//}
};

class TargetVtx
{
public:
	CVector Pos;
	CVector Uv;
};

class Vtx3D
{
public:
	CVector Pos;
	CVector Uv;
	CVector Color;
	CVector Normal; // Y축
	CVector BiNormal; // X축
	CVector Tangent; // Z축
	CVector Weight; // 스키닝 정보 
	int	Index[4]; // 21번째 본에 60 이 버텍스는 60번째 본이랑 곱하는 녀석이다.
};	
//  Weight:        0.5    0.5
//  Index:         60     59