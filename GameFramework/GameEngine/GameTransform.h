#pragma once
#include "GameComponent.h"
#include <GameString.h>

#pragma region 트랜스폼개념
/*
	트랜스폼은 "어디에 있다"의 개념이다.
	트랜스폼 연산을 이해하는 가장 좋은 방법은
		연산을 이해하려면
		가상의 수를 연상해서
		그것으로 계산을 해봐야 한다.
*/
#pragma endregion

#pragma region 프레임워크에서 관계성
/*
	이러한 관계를 주시한다.
		   [트렌스폼의 부모-자식관계]
		   [정렬순서]
		   [씬, 액터에 리스트로 모아두는 방식]
		   [리스트 for문 루프]
		   [업데이트함수]
*/
#pragma endregion

//COLTYPE 결국 API이다.

enum class COLTYPE
{
	SPHERE2D,
	AABB2D,
	OBB2D,
	SPHERE3D,
	AABB3D,
	OBB3D,
	MAX,
};

class GameCamera;
class GameTransform : public ActorComponent
{

private:
	class GameColStarter
	{
	public:
		GameColStarter();
		~GameColStarter() {}
	};
	friend GameColStarter; // private에서 강제로 friend만 허가하기  
	static GameColStarter Starter;

public:
	static bool __stdcall SPHERE2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall SPHERE2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall SPHERE2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall AABB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall AABB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall AABB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall OBB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall OBB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);
	static bool __stdcall OBB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);

#pragma region 함수포인터 

#pragma endregion
	static bool(__stdcall* COLFUNC[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right);

protected:
	CVector m_LPos;
	CVector m_LScale;
	CVector m_LRot;
	CVector m_WPos;
	CVector m_WScale;
	CVector m_WRot;

	// 명시적으로 체크하는 방법
	bool CalMatrixCheck[(int)MATTYPE::MATTYPE_MAX];

	CTransformData m_TD;



#pragma region 주의해야할 구조 
	/*
		스케일에서 크기가 0은 없다.
		트랜스폼은 부모를 가질 수 없다. (GameTransform* m_Parent)
		트랜스폼들은 자신의 자식들을 자신의 리스트에 모아놨다.(m_ChildList)
			트랜스폼 연산을 이해하는 가장 좋은 방법은
		연산을 이해하려면
		가상의 수를 연상해서
		그것으로 계산을 해봐야 한다.
	*/
#pragma endregion

	GameTransform* m_Parent;
	std::list<GameTransform*> m_ChildList;

public:
	CTransformData& GetTD()
	{
		return m_TD;
	}

public:
	GameTransform* GetParent()
	{
		return m_Parent;
	}

	void SetParent(CPtr<GameTransform> _Parent);

public:
	GameTransform();

public:
	// 크기 자전 이동 공전		-> 로컬(LWORLD)
	// 크기 자전 이동 공전 부모 -> 월드(WWORLD)
	CVector GetLPos() { return m_LPos; }
	CVector GetLScale() { return m_LScale; }
	CVector GetLRot() { return m_LRot; }
	CVector GetWPos() { return m_WPos; }
	CVector GetWScale() { return m_WScale; }
	CVector GetWRot() { return m_WRot; }
	CVector GetWPos2d() { return CVector(m_WPos.X, m_WPos.Y, 0.0f, m_WPos.W); }

public:
	void CalWPos()
	{
		DEBUG_CHECK;
		// m_LPos가 결정나 있는 상태만 계산이 가능하다.(조건)
		// 월드 포지션을 계산하는 것이다.(목적)
														// <테스트> 
		CVector POS = m_LPos * m_Parent->GetWScale(); // [로컬의 포지션] 과 [부모의 스케일] 을 곱한다. 
		CVector ROT = GetWRot();						// [월드의 회전]
		CVector RESULTQ = POS.RotDegReturn(ROT);		// [행렬을 만드는 함수] 

		/* 
		if (IsDebug())
		{
			CVector Scale = m_PARENT->WSCALE();
			CVector Pos = m_LPOS * m_PARENT->WSCALE();
			Pos = Pos.RotDegReturn(m_PARENT->WROT());
			Pos = m_PARENT->WPOS() + Pos;
		}	
		*/



		// 기존코드의 잘못된 점 [1] 
		// m_WPos = m_Parent->GetWPos() + ((m_LPos * m_Parent->GetWScale()).RotDegReturn(GetWRot()));
		// 부모의 WRot영향을 미친다. 
		// WRot()은 자전이 적용된 것이다. 이것이 나의 Pos에 영향을 주고 있었다.

		// 기존코드의 잘못된 점 [2]
		// m_WPos = m_Parent->GetWPos() + ((m_LPos * m_Parent->GetWScale()).RotDegReturn(m_Parent->GetWRot()));
		// 문제는 WPos를 구하는 중에 LPos를 회전시킨다.  
		// 또한 크기를 키운다. 크기를 먼저계산하기에 -1 스케일로 반전된 위치가 적용이 되지 않는다. 
		m_WPos = m_Parent->GetWPos() + (m_LPos.RotDegReturn(m_Parent->GetWRot()) * m_Parent->GetWScale());
	}

	void CalWRot()
	{
		m_WRot = m_Parent->GetWRot() + m_LRot; // [부모의 월드회전] 과 [로컬회전] 을 더한다. 
	}

	void CalWScale()
	{
		m_WScale = m_Parent->GetWScale() * m_LScale; // [부모의 월드스케일] 과 [로컬스케일] 을 곱한다.  
	}

	void CalChildPos()
	{
		for (auto& _Child : m_ChildList)
		{
			_Child->CalWPos();
		}
	}

	void CalChildRot()
	{
		for (auto& _Child : m_ChildList)
		{
			_Child->CalWRot();
		}
	}

	void CalChildScale()
	{
		for (auto& _Child : m_ChildList)
		{
			_Child->CalWScale();
		}
	}

	void SetLPos(const CVector& _Value)
	{
		// 부모가 없는 경우, L==W 이다. 
		if (nullptr == m_Parent)	// 부모가없는경우==최상위
		{
			m_LPos = m_WPos = _Value;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
			CalChildPos();
			return;
		}

		// 부모가 있는 경우, LPos --> LPos, WPos --> 부모의 스케일을 고려한 이동계산을 한다. 
		m_LPos = _Value;
		CalWPos();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void SetWPos(const CVector& _Value)
	{
		if (nullptr == m_Parent)	// 부모가없는경우==최상위
		{
			m_LPos = m_WPos = _Value;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
			CalChildPos();
			return;
		}

		m_LPos = ((_Value - m_Parent->GetWPos()) / m_Parent->GetWScale()).RotDegReturn(-GetWRot()); // m_Parent->GetWRot()
		CalWPos();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void SetWPos2d(const CVector& _Value, float _Z = 0.0F)
	{
		CVector Vec = _Value;
		Vec.Z = _Z;

		if (nullptr == m_Parent)	// 부모가없는경우==최상위
		{
			m_LPos = m_WPos = Vec;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
			CalChildPos();
			return;
		}

		m_LPos = ((Vec - m_Parent->GetWPos()) / m_Parent->GetWScale()).RotDegReturn(-m_Parent->GetWRot());
		CalWPos();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_POS] = true;
	}

	void SetLRot(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LRot = m_WRot = _Value;
			CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
			CalChildRot();
			CalChildPos();
			return;
		}
		m_LRot = _Value;
		// 회전을 하면 위치도 바뀐다
		// 자전은 더하기 
		CalWRot();
		CalChildRot();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
	}

	void SetWRot(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LRot = m_WRot = _Value;
			CalChildRot();
			CalChildPos();
			CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
			return;
		}

		m_LRot = _Value - m_Parent->GetWRot();
		CalWRot();
		CalChildRot();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT] = true;
	}

	void SetLScale(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LScale = m_WScale = _Value;
			CalChildScale();
			CalChildPos();
			CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
			return;
		}

		m_LScale = _Value;
		CalWScale();
		CalChildScale();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
	}

	void SetWScale(const CVector& _Value)
	{
		if (nullptr == m_Parent)
		{
			m_LScale = m_WScale = _Value;
			CalChildScale();
			CalChildPos();
			CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
			return;
		}

		m_LScale = _Value / m_Parent->GetWScale();	// 스케일의 어떤 속성이 0인걸 허용하지 않는다.
		CalWScale();
		CalChildScale();
		CalChildPos();
		CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE] = true;
	}

public:
	void ScaleXMinus()
	{
		if (0 < m_LScale.X)
		{
			m_LScale.X = m_LScale.X * -1.0f;
		}
	}

	void ScaleXPlus()
	{
		if (0 > m_LScale.X)
		{
			m_LScale.X = m_LScale.X * -1.0f;
		}
	}

public:
	void LMove(const CVector& _Value) { SetLPos(GetLPos() + _Value); }
	void WMove(const CVector& _Value) { SetWPos(GetWPos() + _Value); }

public:
	void LRotAddX(float _Value) { m_LRot.X += _Value;	SetLRot(m_LRot); }
	void LRotAddY(float _Value) { m_LRot.Y += _Value;	SetLRot(m_LRot); }
	void LRotAddZ(float _Value) { m_LRot.Z += _Value;	SetLRot(m_LRot); }
	void WRotAddX(float _Value) { m_WRot.X += _Value;	SetWRot(m_WRot); }
	void WRotAddY(float _Value) { m_WRot.Y += _Value;	SetWRot(m_WRot); }
	void WRotAddZ(float _Value) { m_WRot.Z += _Value;	SetWRot(m_WRot); }

public:
	CVector LForward() { return m_TD.ROT.ArrV[2]; }
	CVector LBack() { return -m_TD.ROT.ArrV[2]; }
	CVector LRight() { return m_TD.ROT.ArrV[0]; }
	CVector LLeft() { return -m_TD.ROT.ArrV[0]; }
	CVector LUp() { return m_TD.ROT.ArrV[1]; }
	CVector LDown() { return -m_TD.ROT.ArrV[1]; }

	CVector WForward() { return m_TD.WWORLD.ArrV[2].Normal3dVecReturn(); }
	CVector WBack() { return -m_TD.WWORLD.ArrV[2].Normal3dVecReturn(); }
	CVector WRight() { return m_TD.WWORLD.ArrV[0].Normal3dVecReturn(); }
	CVector WLeft() { return -m_TD.WWORLD.ArrV[0].Normal3dVecReturn(); }
	CVector WUp() { return m_TD.WWORLD.ArrV[1].Normal3dVecReturn(); }
	CVector WDown() { return -m_TD.WWORLD.ArrV[1].Normal3dVecReturn(); }

public:
	bool Col(COLTYPE _ThisType, CPtr<GameTransform> _Trans, COLTYPE _OtherType);

public:
	DirectX::BoundingBox AABB2D();
	DirectX::BoundingSphere SPHERE2D();
	DirectX::BoundingOrientedBox OBB2D();

public:
	void SetSrcSizeOfTexture(const GameString& _Name);

public:
	void Init() override;
	void TransformUpdate();
	void CamUpdate(CPtr<GameCamera> _Cam);

};

