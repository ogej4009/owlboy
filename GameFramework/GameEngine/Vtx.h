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
	CVector Normal; // Y��
	CVector BiNormal; // X��
	CVector Tangent; // Z��
	CVector Weight; // ��Ű�� ���� 
	int	Index[4]; // 21��° ���� 60 �� ���ؽ��� 60��° ���̶� ���ϴ� �༮�̴�.
};	
//  Weight:        0.5    0.5
//  Index:         60     59