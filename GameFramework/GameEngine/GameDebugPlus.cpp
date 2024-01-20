#include "GameDebugPlus.h"

std::vector<GameDebugPlus::DebugTextInfo> GameDebugPlus::m_AllDebugText;
CPtr<GameFont>	GameDebugPlus::m_DebugFont;
float GameDebugPlus::m_BasicFontSize = 20.0f;
CVector GameDebugPlus::m_BasicStartPos = CVector(0.0F, 0.0F, 0.0F, 0.0F);
CVector GameDebugPlus::m_CurTextSize = CVector(0.0F, 0.0F, 0.0F, 0.0F);
CVector GameDebugPlus::m_BasicColor = CVector::BLACK;

bool GameDebugPlus::bDebugMode = true;

void GameDebugPlus::DebugSwitch()
{
	if (false == bDebugMode)
	{
		bDebugMode = true;
	}
	else
	{
		bDebugMode = false;
	}
}

bool GameDebugPlus::DebugMode()
{
	return bDebugMode;
}

void GameDebugPlus::DebugInit(bool _IsOpenConsole)
{
	GameFont::FontInit();
	m_DebugFont = new GameFont();
	m_DebugFont->CreateGameFont(L"DroidSansFallback.ttf");
	//m_DebugFont->CreateGameFont(L"±¼¸²");
	m_AllDebugText.reserve(100);
	if (true == _IsOpenConsole)
	{
		OpenConsole();
	}
}

void GameDebugPlus::DrawDebugText(const GameString& _Text, float _Size, CVector _Pos, CVector _Color)
{
	m_AllDebugText.push_back({ _Text, _Size, _Pos, _Color });
}

void GameDebugPlus::DebugRender()
{
	if (true == bDebugMode)
	{
		for (size_t i = 0; i < m_AllDebugText.size(); i++)
		{
			m_DebugFont->DrawFont(m_AllDebugText[i].Text, m_AllDebugText[i].Size, m_AllDebugText[i].Pos, m_AllDebugText[i].Color);
		}
	}

	m_CurTextSize = m_BasicStartPos;
	m_AllDebugText.clear();
	GameDevice::Reset();
}