#include "GameIdxBuffer.h"

GameIdxBuffer::GameIdxBuffer() : m_Offset(0) {}
GameIdxBuffer::~GameIdxBuffer() {}

void GameIdxBuffer::Create(size_t _Count, size_t _Size, const void* _Data, DXGI_FORMAT _Fmt, D3D11_USAGE _USAGE)
{
	// 정수를 알려주는 방식 int / short 인지
	m_Fmt = _Fmt;
	m_Size = (unsigned int)_Size;
	m_Count = (unsigned int)_Count;

	//                       4         32
	m_BufferDesc.ByteWidth = (unsigned int)(_Count * _Size);
	m_BufferDesc.Usage = _USAGE;
	// 어디에 저장해 달라. 보통 그래픽카드에 저장
	// 이녀석은 cpu에서 수정할거다 안할거다.
	// D3D11_USAGE::D3D11_USAGE_DEFAULT 그래픽 카드에 저장되는데 수정 안한다.
	// D3D11_USAGE::D3D11_USAGE_DYNAMIC 그래픽 카드에 저장되는데 수정 한다.

	if (m_BufferDesc.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA DS = {};
	DS.pSysMem = _Data;

	if (S_OK != GameDevice::MainObj()->Device()->CreateBuffer(&m_BufferDesc, &DS, &m_pBuffer))
	{
		MSG_ASSERT_CODE(L"버텍스 버퍼 생성에 실패했습니다");
	}
}

void GameIdxBuffer::Setting()
{
	GameDevice::MainObj()->Context()->IASetIndexBuffer(m_pBuffer, m_Fmt, m_Offset);
}