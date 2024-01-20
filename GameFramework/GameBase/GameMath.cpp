#include "GameMath.h"

const float GameMath::PI = 3.14159265358979323846264338f;
const float GameMath::PI2 = 3.14159265358979323846264338f * 2;
const float GameMath::DTOR = GameMath::PI / 180.0f;
const float GameMath::RTOD = 180.0f / GameMath::PI;

const CVector CVector::RIGHT = { 1.0f, 0.0f };
const CVector CVector::LEFT = { -1.0f, 0.0f };
const CVector CVector::UP = { 0.0f, 1.0f };
const CVector CVector::DOWN = { 0.0f, -1.0f, 0.0f, 1.0f };
const CVector CVector::FORWARD = { 0.0f, 0.0f, 1.0f };
const CVector CVector::BACK = { 0.0f, 0.0f, -1.0f };

const CVector CVector::RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const CVector CVector::GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const CVector CVector::BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };

const CVector CVector::BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
const CVector CVector::WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

const CVector CVector::MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };
//const CVector CVector::PURPLE = { 0.0f, 1.0f, 1.0f, 1.0f };
//const CVector CVector::MARKER = { 1.0f, 1.0f, 0.0f, 1.0f };
//const CVector CVector::MARKER = { 1.0f, 1.0f, 0.0f, 1.0f };

const CVector CVector::NONE = { 0.0f, 0.0f, 0.0f, 0.0f };
const CVector CVector::ZERO = { 0.0f, 0.0f, 0.0f, 1.0f };
const CVector CVector::ONE = { 1.0f, 1.0f, 1.0f, 1.0f };


CVector& CVector::operator*=(const CMatrix& _Value)
{
#pragma region 반복문으로 행렬만들기 
	/*
		for (size_t x = 0; x < 4; x++)
		{
			NewResult.Arr2D[0][x] = 0.0f;
			for (size_t CalCount = 0; CalCount < 4; CalCount++)
			{
				NewResult.Arr2D[0][x] += Arr2D[0][CalCount] * _Value.ArrF2D[CalCount][x];
			}
		}
		*this = NewResult;
	*/
#pragma endregion

	CVector NewResult;
	DXVEC = DirectX::XMVector4Transform(DXVEC, _Value);
	return *this;
}


CVector CVector::operator*(const CMatrix& _Value)
{
	CVector NewResult;

	for (size_t x = 0; x < 4; x++)
	{
		NewResult.Arr2D[0][x] = 0.0f;

		for (size_t CalCount = 0; CalCount < 4; CalCount++)
		{
			NewResult.Arr2D[0][x] += Arr2D[0][CalCount] * _Value.ArrF2D[CalCount][x];
		}
	}

	return NewResult;
}
