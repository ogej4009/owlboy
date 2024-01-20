#include "GameString.h"

GameString operator+(const wchar_t* _Left, const GameString& _Right)
{
	GameString Str = _Left;
	Str += _Right;
	return Str;
}

bool operator==(const wchar_t* _Left, const GameString& _Right)
{
	return _Right == _Left;
}

bool operator!=(const wchar_t* _Left, const GameString& _Right)
{
	return _Right != _Left;
}