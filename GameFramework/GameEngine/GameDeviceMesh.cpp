#include "GameDevice.h"
#include "GameVtxBuffer.h"
#include "GameIdxBuffer.h"
#include "Vtx.h"



#pragma region 버퍼 
/*
	버퍼는 디바이스를 통해 만들었으므로 그래픽 카드에 저장됨
	LOAD는 -> CPU(RAM), GPU(RAM)에 영향을 줌
*/
#pragma endregion

void GameDevice::MeshInit()
{
#pragma region 리소스 
	/*
		리소스 중에 LOAD해야 하는 것은?
		로드를 하는 요소들은 경로를 내뱉어야 한다.
		따라서 경로 때문에 로드가 있는 케이스와 없는 케이스로 나눈다.
		서로 다른 방식을 처리한다.

	*/
#pragma endregion

#pragma region 점
	/*
		점의 집합은 로드를 하지 않는다.
		점이 특정한 파일로 빠져있는 경우가 있는가? 없다.
		점은 가변적인 점의 집합
		여러개 -> 자료구조로 관리
		점--> vector
		그 집합을 갯수만큼 하나하나를 그래픽카드에 전달한다.
		그것을 1대1로 매칭 시켜주는 것이 버텍스 쉐이더
		점의 정보 매쉬는 복합적이다.
		버텍스 버퍼는 오직 점에 관련된 것이다.

		기본 매쉬를 만들때는 크기를 1로 만들어 놓는 경우가 대부분이다.

		인덱스 버퍼
		시계방향으로 그린다는게 중요하다.
		뒷면은 안그리게 하는게 이 그려지는 방향에 의해서 결정된다.

	*/
	/*
								상수 -> 코드 영역
		m_Mesh[3].Pos = { -0.5f, -0.5f, 0.0f, 1.0f }; -> 이것은 스택영역
		전역 -> 데이터 영역
	*/
#pragma endregion

	{
		std::vector<CVtx> m_Mesh;
		m_Mesh.resize(4);
		m_Mesh[0].Pos = { -0.5f, 0.5f, 0.0f, 1.0f }; // W = 1.0f 나중에 행렬곱에서 이동 적용 (0이면 이동 안함)
		m_Mesh[1].Pos = { 0.5f, 0.5f, 0.0f, 1.0f };
		m_Mesh[2].Pos = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_Mesh[3].Pos = { -0.5f, -0.5f, 0.0f, 1.0f };

		m_Mesh[0].Uv = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_Mesh[1].Uv = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_Mesh[2].Uv = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_Mesh[3].Uv = { 0.0f, 1.0f, 0.0f, 1.0f };

		m_Mesh[0].Color = m_Mesh[1].Color = m_Mesh[2].Color = m_Mesh[3].Color = CVector::WHITE;
		GameVtxBuffer::Create<CVtx>(L"RECT2DCOLOR", m_Mesh);

		std::vector<UINT> m_IDX = { 0, 1, 2, 0, 2, 3 };
		GameIdxBuffer::Create<UINT>(L"RECT2DCOLOR", m_IDX);
	}

	{
		std::vector<CVtx> m_Mesh;
		m_Mesh.resize(4);
		m_Mesh[0].Pos = { -0.5f, 0.5f, 0.0f, 1.0f }; // W = 1.0f 나중에 행렬곱에서 이동 적용 (0이면 이동 안함)
		m_Mesh[1].Pos = { 0.5f, 0.5f, 0.0f, 1.0f };
		m_Mesh[2].Pos = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_Mesh[3].Pos = { -0.5f, -0.5f, 0.0f, 1.0f };

		m_Mesh[0].Uv = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_Mesh[1].Uv = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_Mesh[2].Uv = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_Mesh[3].Uv = { 0.0f, 1.0f, 0.0f, 1.0f };

		m_Mesh[0].Color = m_Mesh[1].Color = m_Mesh[2].Color = m_Mesh[3].Color = CVector::WHITE;
		GameVtxBuffer::Create<CVtx>(L"RECT_TILE", m_Mesh);

		std::vector<UINT> m_IDX = { 0, 1, 2, 0, 2, 3 };
		GameIdxBuffer::Create<UINT>(L"RECT_TILE", m_IDX);
	}


}



/*

void HSGAMEDEVICE::MeshInit()
{
#pragma region SptiteRect
	{
		// 버텍스버퍼
		std::vector<HSVTX2D> ArrVTX;
		ArrVTX.resize(4);

		ArrVTX[0].m_Pos = { -0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[1].m_Pos = { 0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[2].m_Pos = { 0.5f, -0.5f, 0.0f, 1.0f };
		ArrVTX[3].m_Pos = { -0.5f, -0.5f, 0.0f, 1.0f };

		ArrVTX[0].m_UV = { 0.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[1].m_UV = { 1.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[2].m_UV = { 1.0f, 1.0f, 0.0f, 0.0f };
		ArrVTX[3].m_UV = { 0.0f, 1.0f, 0.0f, 0.0f };

		ArrVTX[0].m_Color = HSVEC4::White;
		ArrVTX[1].m_Color = HSVEC4::White;
		ArrVTX[2].m_Color = HSVEC4::White;
		ArrVTX[3].m_Color = HSVEC4::White;

		HSVERTEXBUFFER::Create(L"2DRECT", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);

		//인덱스 버퍼
		std::vector<UINT> ArrIdx = { 0, 1, 2, 0, 2, 3 };
		HSINDEXBUFFER::Create(L"2DRECT", ArrIdx, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		HSMESH::Create(L"2DRECT", L"2DRECT", L"2DRECT");
	}
#pragma endregion

#pragma region SptiteFullRect
	{
		// 버텍스버퍼
		std::vector<HSVTX2D> ArrVTX;
		ArrVTX.resize(4);

		ArrVTX[0].m_Pos = { -1.0f, 1.0f, 0.0f, 1.0f };
		ArrVTX[1].m_Pos = { 1.0f, 1.0f, 0.0f, 1.0f };
		ArrVTX[2].m_Pos = { 1.0f, -1.0f, 0.0f, 1.0f };
		ArrVTX[3].m_Pos = { -1.0f, -1.0f, 0.0f, 1.0f };

		ArrVTX[0].m_UV = { 0.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[1].m_UV = { 1.0f, 0.0f, 0.0f, 0.0f };
		ArrVTX[2].m_UV = { 1.0f, 1.0f, 0.0f, 0.0f };
		ArrVTX[3].m_UV = { 0.0f, 1.0f, 0.0f, 0.0f };

		ArrVTX[0].m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		ArrVTX[1].m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		ArrVTX[2].m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		ArrVTX[3].m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

		HSVERTEXBUFFER::Create(L"FullRect", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);

		//인덱스 버퍼
		std::vector<UINT> ArrIdx = { 0, 1, 2, 0, 2, 3 };
		HSINDEXBUFFER::Create(L"FullRect", ArrIdx, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		HSMESH::Create(L"FullRect", L"FullRect", L"FullRect");
	}
#pragma endregion

#pragma region DebugRect
	{
		// 버텍스버퍼
		std::vector<HSVEC4> ArrVTX;
		ArrVTX.resize(4);

		ArrVTX[0] = { -0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[1] = { 0.5f, 0.5f, 0.0f, 1.0f };
		ArrVTX[2] = { 0.5f, -0.5f, 0.0f, 1.0f };
		ArrVTX[3] = { -0.5f, -0.5f, 0.0f, 1.0f };


		HSVERTEXBUFFER::Create(L"DEBUG2DRECT", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);

		//인덱스 버퍼
		std::vector<UINT> ArrIdx = { 0, 1, 2, 3, 0 };
		HSINDEXBUFFER::Create(L"DEBUG2DRECT", ArrIdx, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		HSMESH::Create(L"DEBUG2DRECT", L"DEBUG2DRECT", L"DEBUG2DRECT");
	}
#pragma endregion

#pragma region SptiteCiCle
	{
		// 버텍스버퍼
		std::vector<HSVTX2D> ArrVTX;
		ArrVTX.resize(36);

		float Theta = 10.0f;

		HSVEC4 Start = { 0.0f, 0.2f, 0.0f, 1.0f };
		HSMAT RM;
		RM.IDEN();
		ArrVTX[0] = Start;

		for (int i = 0; i < ArrVTX.size(); ++i)
		{
			RM.ArrVec[0] = { cosf(HSMATH::DTOR * Theta * i), sinf(HSMATH::DTOR * Theta * i) + 0.7f, 0.0f, 1.0f };
			RM.ArrVec[1] = { sinf(HSMATH::DTOR * Theta * i), cosf(HSMATH::DTOR * Theta * i) + 0.7f ,0.0f, 1.0f };
			ArrVTX[i].m_Pos = Start * RM;
			ArrVTX[i].m_Color = HSVEC4::Red;
		}


		HSVERTEXBUFFER::Create(L"2DCICLE", ArrVTX, D3D11_USAGE::D3D11_USAGE_DEFAULT);

		//인덱스 버퍼
		std::vector<UINT> ArrIdx = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
									10,	11, 12, 13, 14, 15, 16, 17, 18, 19,
									20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
									30, 31, 32, 33, 34, 35, 0 };
		HSINDEXBUFFER::Create(L"2DCICLE", ArrIdx, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		HSMESH::Create(L"2DCICLE", L"2DCICLE", L"2DCICLE");
	}
#pragma endregion
}

*/