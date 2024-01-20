#include "GameTexture.h"
#include <vector>

GameTexture::GameTexture() : m_SRV(nullptr), m_RTV(nullptr), m_DSV(nullptr)
{
}

GameTexture::~GameTexture()
{
	if (nullptr != m_SRV) { m_SRV->Release(); };
	if (nullptr != m_RTV) { m_RTV->Release(); };
	if (nullptr != m_DSV) { m_DSV->Release(); };
	if (nullptr != m_pTex) { m_pTex->Release(); };
}

void GameTexture::Load()
{
	GameString Ext = CFile.Ext();

	if (Ext == L"dds")
	{

	}
	else if (Ext == L"tga")
	{

	}
	else
	{
		// 로딩만 했다.권한은 아직 얻지 못했다. 
		if (S_OK != DirectX::LoadFromWICFile(CFile.FullPath(), DirectX::WIC_FLAGS_NONE, nullptr, m_Img))
		{
			MSG_ASSERT_CODE(CFile.FullPath() + L" : 텍스처 로딩에 실패했습니다.");
			return;
		}
	}

#pragma region 권한
	/*
		m_SRV
		쉐이더에 넣어주는 것 -> 이 행위도 권한이 필요하다.
		권한을 얻지 않고 하는 것이 없다. 그래픽카드의 권한이 필요하다
		이런 함수 내부는 결국 이중포인터를 넣어줘 그럼 바꿔줄게 식이다.
		상수버퍼, 샘플러, 텍스쳐는 쉐이더에 영향을 끼친다.
		(뎁스스텐실,블랜드 등등 렌더링 전체에 영향을 준다.)
	*/
#pragma endregion

	if (S_OK != DirectX::CreateShaderResourceView(GameDevice::MainObj()->Device(), m_Img.GetImages(), m_Img.GetImageCount(), m_Img.GetMetadata(), &m_SRV))
	{
		MSG_ASSERT_CODE(CFile.FullPath() + L" : 쉐이더 리소스 생성에 실패했습니다.");
		return;
	}

	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	Desc.Width = (unsigned int)m_Img.GetMetadata().width;
	Desc.Height = (unsigned int)m_Img.GetMetadata().height;
}


// 텍스쳐의 크기를 벡터로 바꿔주는 기능 
CVector GameTexture::Size()
{
	return CVector((float)Desc.Width, (float)Desc.Height, 1.0f);
}


void GameTexture::Setting(SHADERTYPE _Type, unsigned int _Reg)
{
	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		GameDevice::MainObj()->Context()->VSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_HS:
		GameDevice::MainObj()->Context()->HSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_DS:
		GameDevice::MainObj()->Context()->DSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_GS:
		GameDevice::MainObj()->Context()->GSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_PS:
		GameDevice::MainObj()->Context()->PSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}

#pragma region GetPixel
/*
	GetPixel 함수
	입력받은 위치에서 "텍스처 픽셀"의 가져오는 함수(왼쪽 상단 부터 0,0)
	=> 이때 입력받는 위치가 (x, y)라면 텍스처 픽셀 위치도 (x, y)여야한다.
	즉, 동일 선상에 있어야한다는 의미.
*/
#pragma endregion

CVector GameTexture::GetPixel(CVector _Pos)
{

	if (0.0f > _Pos.X || 0.0f > _Pos.Y)
	{
		return CVector::BLACK;
		MSG_ASSERT_CODE(L"이런 픽셀은 존재하지 않습니다.");
	}

	if ((float)Desc.Width <= _Pos.X || (float)Desc.Height <= _Pos.Y)
	{
		return CVector::BLACK;
		MSG_ASSERT_CODE(L"맵 이미지 바깥 픽셀의 색깔을 가져오려고 했습니다.");
	}

#pragma region 포맷
	/*
		캐릭터는 몇 바이트 일까? 1바이트
		uint8_t(unsigned char) : 1바이트 / uint16_t(unsigned short) : 2바이트
		0, 0 픽셀의 R의 포인터 => FirstColor[0]
		0, 0 픽셀의 G의 포인터 => FirstColor[1]
		0, 1 픽셀의 R의 포인터 => FirstColor[4]
		(단, 위의 식은 1바이트면서, rgba 순일 경우만 해당한다. 즉, 이미지 색깔 포맷에 따라 다르다!)
		이미지의 색깔 포맷을 가져올수 있다.
	*/
#pragma endregion

	uint8_t* FirstColor = m_Img.GetPixels();
	DXGI_FORMAT Fmt = m_Img.GetMetadata().format;
	CVector Color = CVector::BLACK;

#pragma region RGBA데이터(텍스쳐)
	/*
		(1, 0) 일 경우, x의 너비(width)을 1 곱하고 0번에 있는 위치
		=> 너비가 10이라고 가정하면, 10 * 1 + 0이기 때문에 10번 위치로asss
		RGBA의 개수만큼 추가로 4를 곱하는 것으로 원하는 텍스처 픽셀의 R 값을 얻을 수 있다.
		==> 즉, FirstColor는 원하는 위치의 텍스처의 0번째 포인터를 가지고 있는 것이다.
		(현재는 BGRA이기 때문에 B의 색상)
	*/
#pragma endregion

	switch (Fmt)
	{
	case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM:
		FirstColor = &FirstColor[(Desc.Width * _Pos.UIY() + _Pos.UIX()) * 4];
		Color = CVector::ColorToUintInt8(FirstColor[2], FirstColor[1], FirstColor[0], FirstColor[3]);
		break;
	default:
		MSG_ASSERT_CODE(L"처리할수 없는 포맷입니다.");
		break;
	}
	return Color;

}

#pragma region 포인터계산
/*
	0, 0픽셀의 r의 포인터이다
	가장 기본적인 포인터 문법
	한 픽셀을 건너뛰고 싶으면 보통 4로 해야한다.
	FirstColor += 4;
	0, 0픽셀의 g의 포인터
*/
#pragma endregion