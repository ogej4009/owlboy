#include "GameCol.h"
#include "GameScene.h"
#include "GameActor.h"

GameCol::GameCol()
{
}

GameCol::~GameCol()
{
}

void GameCol::ColCheck(CPtr<GameCol> _Other)
{

	if (true == Col(m_Type, _Other.PTR, _Other.PTR->m_Type)) // _Other.PTR 이거 업캐스팅이다. 
	{

		if (m_ColSet.end() == m_ColSet.find(_Other.PTR))
		{
			m_ColSet.insert(_Other.PTR);
			_Other.PTR->m_ColSet.insert(this);

			CallEnter(_Other);
			_Other->CallEnter(this);
		}
		else
		{
			CallStay(_Other);
			_Other->CallStay(this);
		}
	}
	else
	{

		if (m_ColSet.end() != m_ColSet.find(_Other.PTR))
		{
			CallExit(_Other);
			_Other->CallExit(this);

			// 충돌을 하지 않았는데 other가 this에 속해있는 경우 
			m_ColSet.erase(_Other.PTR);
			_Other.PTR->m_ColSet.erase(this);
		}
	}

}


void GameCol::Init(int _Order)
{
	SetParent(GetActor()->GetTrans());
	Order(_Order);
	GetActor()->GetScene()->PushCol(this);
}


#pragma region this문법
/*
	this == GameCol* const
	CPtr<GameCol>
*/
#pragma endregion

void GameCol::CallEnter(GameCol* _Other)
{
	for (auto& _Value : m_EnterFunc)
	{
		_Value(this, _Other);
	}
}


void GameCol::CallStay(GameCol* _Other)
{
	for (auto& _Value : m_StayFunc)
	{
		_Value(this, _Other);
	}
}


void GameCol::CallExit(GameCol* _Other)
{
	for (auto& _Value : m_ExitFunc)
	{
		_Value(this, _Other);
	}
}


void GameCol::Release()
{
	for (auto& _OtherCol : m_ColSet)
	{
		_OtherCol->m_ColSet.erase(this);
	}
}


void GameCol::Off()
{
	GameVirtualProgress::Off();

	for (auto& _OtherCol : m_ColSet)
	{
		_OtherCol->m_ColSet.erase(this);
	}

}


