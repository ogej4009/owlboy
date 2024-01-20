#include "GameTransform.h"
#include "GameActor.h"
#include "GameScene.h"
#include "GameCamera.h"
//#include <GameString.h>
#include "GameSprite.h"
#include <GameDebug.h>


/* 오류시점을 함수 안에서 늘 확인한다. */

#pragma region 함수포인터 
	/*
	*/
#pragma endregion
bool (*GameTransform::COLFUNC[(int)COLTYPE::MAX][(int)COLTYPE::MAX])(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right) = { nullptr, };

GameTransform::GameColStarter GameTransform::Starter;

GameTransform::GameColStarter::GameColStarter()
{
	GameTransform::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::AABB2D] = AABB2DCOLAABB2D;
	GameTransform::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::SPHERE2D] = AABB2DCOLSPHERE2D;
	GameTransform::COLFUNC[(int)COLTYPE::AABB2D][(int)COLTYPE::OBB2D] = AABB2DCOLOBB2D;

	GameTransform::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::AABB2D] = OBB2DCOLAABB2D;
	GameTransform::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::SPHERE2D] = OBB2DCOLSPHERE2D;
	GameTransform::COLFUNC[(int)COLTYPE::OBB2D][(int)COLTYPE::OBB2D] = OBB2DCOLOBB2D;

	GameTransform::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::AABB2D] = SPHERE2DCOLAABB2D;
	GameTransform::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::SPHERE2D] = SPHERE2DCOLSPHERE2D;
	GameTransform::COLFUNC[(int)COLTYPE::SPHERE2D][(int)COLTYPE::OBB2D] = SPHERE2DCOLOBB2D;
}

// 리터럴초기화개념(==상수초기화) -> 멤버변수가 시작하자마자 초기화 되는것 
// m_LPos(CVector::ZERO)
GameTransform::GameTransform()
	: m_LPos(CVector::ZERO), m_LScale(CVector::ONE), m_LRot(CVector::ZERO)
	, m_WPos(CVector::ZERO), m_WScale(CVector::ONE), m_WRot(CVector::ZERO)
	, m_TD(), CalMatrixCheck{ true, }
{
	memset(&CalMatrixCheck, 1, sizeof(CalMatrixCheck));
	m_TD.CalUnitMatrix();
}


#pragma region SetParent()함수의 의미 
/*
	누군가 부모가 되어준다.
	== 나는 부모의 SceneList -> 그 부모의 ChildList로 간다.
	== 나한테 부모가 생기면 나는 m_AllTrans(트랜스폼리스트)에서 빠지는거다.
	부모가 생기면 한번 CalMatrixCheck(재계산) 한다.
*/
#pragma endregion

#pragma region remove함수
/* remove함수 : 똑같은 것이 있으면 list 안에서 지워줌 erase() 대신 쓰는것. -> iterator */
#pragma endregion

void GameTransform::SetParent(CPtr<GameTransform> _Parent)
{
	GetActor()->GetScene()->m_AllTrans.remove(this);

	if (nullptr != _Parent)
	{
		// 현시점 부모가없는경우 == 현시점 최상위
		if (nullptr != m_Parent)
		{
			m_Parent->m_ChildList.remove(this);
		}

		_Parent->m_ChildList.push_back(this);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_PARENT] = true;
		m_TD.PARENT = _Parent->m_TD.WWORLD;
		m_Parent = _Parent;

		// 순서 : 크기->회전->이동
		SetLScale(GetWScale());
		SetLRot(GetWRot());
		SetLPos(GetWPos());

	}
	else
	{
		if (nullptr != m_Parent)
		{
			m_Parent->m_ChildList.remove(this);
		}

		GetActor()->GetScene()->m_AllTrans.push_back(this);

		// 순서 중요하다. 
		CalWPos();
		CalWScale();
		CalWRot();

		m_Parent = nullptr;
		m_TD.PARENT.UnitMat();
		// ※ 나의 LPos가 곧 w이다 

		// 순서 중요하다. 
		SetLPos(GetWPos());
		SetLScale(GetWScale());
		SetLRot(GetWRot());


	}

	// 환경이 변했으므로 행렬을 (방어적으로) 재계산한다. 
	TransformUpdate();
}



void GameTransform::Init()
{
	if (nullptr != GetActor()->m_Trans)
	{
		MSG_ASSERT_CODE(L"한 액터에 트랜스폼이 2개가 들어갈수는 없습니다.");
	}

	GetActor()->m_Trans = this;

	GetActor()->GetScene()->m_AllTrans.push_back(this);
	// 해석 : 날 가진 Actor의 Scene의 transform만 모아놓는 곳에 자신을 넣어둡니다. 
}


void GameTransform::TransformUpdate()
{
	// 벡터를 활용해서 행렬을 만드는 것은 연산이 많이 드는 작업이다. 
	// 그래서 Pos, Rot, Scale이 수정되었을 때만 행렬을 계산해서 효율을 높이고자 한다. 

	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_SCALE])
	{
		m_TD.SCALE.Scale3d(m_LScale);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_ROT])
	{
		m_TD.ROT.RotDeg(m_LRot);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_POS])
	{
		m_TD.POS.Pos3d(m_LPos);
		CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] = true;
	}

	// 크기 자전 이동 공전		-> 로컬(LWORLD)
	// 크기 자전 이동 공전 부모 -> 월드(WWORLD)
	if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_LWORLD] ||
		true == CalMatrixCheck[(int)MATTYPE::MATTYPE_PARENT])
	{
		m_TD.CalLWorld();
		m_TD.CalWWorld();

		// CalLWorld()를 사용하는 경우, Wpos가 변경되는가
		// 나의 WWorld가 변경되었다는 의미로 값을 TRUE로 변경

		CalMatrixCheck[(int)MATTYPE::MATTYPE_WWORLD] = true;

		if (nullptr != m_Parent)
		{
			CalWScale();
			CalWRot();
			CalWPos();
		}
	}

	for (auto& _Child : m_ChildList)
	{
		// == 이번 프레임이 행렬의 변경이 있었다
		// 나는 변한적없고, 부모행렬이 변했다면 나의 월드는 다시 계산해야 한다. 
		if (true == CalMatrixCheck[(int)MATTYPE::MATTYPE_WWORLD])
		{
			_Child->CalMatrixCheck[(int)MATTYPE::MATTYPE_PARENT] = true;
			_Child->m_TD.PARENT = m_TD.WWORLD;
		}

		// 부모행렬이 생기면 반드시 재계산 한다. 
		_Child->TransformUpdate();
	}

	memset(&CalMatrixCheck, 0, sizeof(CalMatrixCheck));
}

#pragma region 보이게해주는곳==CamUpdate
/*
	플레이어는 움직인다. (행렬의 관점에서)
	뷰행렬을 곱했다. 안움직인것처럼 되었다.
	움직인만큼 행렬에서 빼주어야 가시적으로 표현될 것이다. CalWVP()
	여기서 곱해준다.
*/
#pragma endregion

void GameTransform::CamUpdate(CPtr<GameCamera> _Cam)
{
	m_TD.PROJ = _Cam->m_Proj;
	m_TD.VIEW = _Cam->m_View;
	m_TD.CalWVP();
}


bool GameTransform::Col(COLTYPE _ThisType, CPtr<GameTransform> _Trans, COLTYPE _OtherType)
{
	if (nullptr == COLFUNC[(int)(_ThisType)][(int)(_OtherType)])
	{
		MSG_ASSERT_CODE(L"충돌 함수가 구현되지 않은 충돌을 하려고 했습니다.");
	}

	return COLFUNC[(int)(_ThisType)][(int)(_OtherType)](this, _Trans);


}

#pragma region 다양한케이스충돌
/*
	AABB 회전하지 않은 박스
	ex)
		DirectX::BoundingOrientedBox	ColThis;
		DirectX::BoundingBox			ColOther;

	ex)
		XMFLOAT3   CVector
		ColThis.Center = GetWPos();(오일러각)

	오일러각을 넣어주면 회전을 인식하지 못한다.
	Orientation사원수를 넣어줘야 한번에 회전행렬을 만들어서 회전이 인식된다.
	사원수를 쓴다 == 이해하기 어려운 복소수, 허수 등등이 조합된 행렬을 사용한다.


	회전에서 디그리가 라디안으로 바뀌고, 다시 쿼터니온을 해서 회전하는데. WROT() 자체는 그냥 디그리일 뿐이다.
	ColThis.Orientation = WROT();
	DirectX::XMQuaternionRotationRollPitchYaw()

	//ColThis.Extents = GetWScale().HalfVec();
	//ColOther.Center = _Trans->GetWPos();
	//ColOther.Extents = _Trans->GetWScale().HalfVec();

	if ((int)_ThisType < (int)COLTYPE::SPHERE3D)
	{
		ColThis.Center.z = 0.0f;
	}

	if ((int)_OtherType < (int)COLTYPE::SPHERE3D)
	{
		ColOther.Center.z = 0.0f;
	}

	Intersects 이 함수가 중요하다.
	//return ColThis.Intersects(ColOther);

	// 구
	DirectX::BoundingSphere m_Sphere1;
	DirectX::BoundingSphere m_Sphere2;

	// OBB 회전한 박스
	DirectX::BoundingOrientedBox m_OBBox1;
	DirectX::BoundingOrientedBox m_OBBox2;
	m_AABBBox1.Intersects(m_Sphere2);

	기본 도형 충돌을 체크할수 있다.
	매쉬충돌을 할 수 있다.
	A매쉬가 삼각형이 2000개
	B매쉬가 삼각형이 1200개
	내부에는	삼각형 VS 삼각형
				삼각형 VS 평면
				삼각형 VS 광선
	DirectX::TriangleTests::Intersects()
*/
#pragma endregion


DirectX::BoundingBox GameTransform::AABB2D()
{
	return DirectX::BoundingBox(GetWPos2d(), GetWScale().HalfVec().AbsVector()); //※ 디버깅
}


DirectX::BoundingSphere GameTransform::SPHERE2D()
{
	return DirectX::BoundingSphere(GetWPos2d(), abs(GetWScale().HalfVec().X));
}


DirectX::BoundingOrientedBox GameTransform::OBB2D()
{
	return DirectX::BoundingOrientedBox(GetWPos2d(), GetWScale().HalfVec().AbsVector(), GetWRot().DegToQ());
}


void GameTransform::SetSrcSizeOfTexture(const GameString& _Name) // Get Source texture Size 
{
	CPtr<GameSprite> _Sprite = GameSprite::Find(_Name);

	if (nullptr == _Sprite)
	{
		MSG_ASSERT_CODE(_Name + L"의 텍스처를 찾지 못했습니다.");
	}

	SetWScale({ _Sprite->Tex()->Size().X * 0.01f / (int)_Sprite->Count(), _Sprite->Tex()->Size().Y * 0.01f , 1.0f});

}