#pragma once
#include <string>
#include <atlstr.h> // char => wchar wchar => char로 변환시켜주는 함수가 들어있다.

#pragma region 
/*
	내부에 있는 배열의 포인터를 리턴. -> c_str()를 해서 문자열 + NULL 스타일로 바꿔줌
*/
#pragma endregion

class GameString
{
private:
	std::wstring m_Str;

public:
	static GameString IntToString(int _Value)
	{
		GameString ReturnStr;
		ReturnStr = std::to_wstring(_Value);
		return ReturnStr;
	}

	wchar_t At(int _Index)
	{
		return m_Str.at(_Index);
	}

public:
	size_t StrCount() const
	{
		return m_Str.size();
	}

public:
	operator const wchar_t* () const
	{
		return m_Str.c_str();
	}

	operator std::wstring() const
	{
		return m_Str;
	}

	operator std::string() const
	{
		return CW2A(m_Str.c_str()).m_psz;
	}

	operator char* () const
	{
		return CW2A(m_Str.c_str()).m_psz;
	}

	bool operator==(const wchar_t* _Other) const
	{
		return m_Str == _Other;
	}

	bool operator!=(const wchar_t* _Other) const
	{
		return m_Str != _Other;
	}

	bool operator==(const GameString& _Other) const
	{
		return _Other.m_Str == m_Str;
	}

	bool operator!=(const GameString& _Other) const
	{
		return _Other.m_Str != m_Str;
	}

	bool operator>(const GameString& _Other) const
	{
		return _Other.m_Str > m_Str;
	}

	bool operator<(const GameString& _Other) const
	{
		return _Other.m_Str < m_Str;
	}

	GameString& operator=(const wchar_t* _Ptr)
	{
		m_Str = _Ptr;
		return *this;
	}

	GameString& operator=(const GameString& _Other)
	{
		m_Str = _Other.m_Str;
		return *this;
	}

	GameString operator+(const wchar_t* _Other) const
	{
		return m_Str + _Other;
	}

	GameString operator+(const GameString& _Other) const
	{
		return m_Str + _Other.m_Str;
	}

	GameString& operator+=(const GameString& _Other)
	{
		m_Str += _Other.m_Str;
		return *this;
	}

#pragma region operater[] 오버로딩
	/*
		wchar_t operator[](const int index);

		std::wstring& operator[](int i);

		const std::wstring& operator[](int i) const;
	*/
#pragma endregion

	std::wstring& operator[](const int index);

	size_t Find(const GameString& _Find) const
	{
		return m_Str.find(_Find.m_Str);
	}

	size_t FindLast(const GameString& _Find) const
	{
		return m_Str.find_last_of(_Find.m_Str);
	}

	void EraseStr(size_t _Start, size_t _End)
	{
		m_Str.replace(_Start, _End, L"");
	}

	/* 문자열에서 일부만 뜯어냄 */
	GameString RangeToStr(size_t _Start, size_t _End) const
	{
		std::wstring Str;
		Str.resize(_End - _Start - 1); // 미리 버퍼 할당 
		m_Str.copy(&Str[0], _End - _Start - 1, _Start + 1);
		return Str;
	}

public:
	GameString() : m_Str() {}
	GameString(const char* _Ptr) : m_Str(CA2W(_Ptr).m_psz) {}
	GameString(const wchar_t* _Ptr) : m_Str(_Ptr) {}
	GameString(std::wstring _Str) : m_Str(_Str) {}
};

#pragma region 전역오퍼레이팅
/*
	전역 오퍼레이팅
	헤더에다가는 전역함수 구현해놓으면 안된다.
*/
#pragma endregion

GameString operator+(const wchar_t* _Left, const GameString& _Right);
bool operator==(const wchar_t* _Left, const GameString& _Right);
bool operator!=(const wchar_t* _Left, const GameString& _Right);

#pragma region wchar_t -> char
/*
	wchar_t* CharToWChar(const char* pstrSrc)
	{
		int nLen = strlen(pstrSrc)+1;
		wchar_t* pwstr      = (LPWSTR) malloc ( sizeof( wchar_t )* nLen);
		mbstowcs(pwstr, pstrSrc, nLen);
		return pwstr;
	}

	char* WCharToChar(const wchar_t* pwstrSrc)
	{
	#if !defined _DEBUG
		int len = 0;
		len = (wcslen(pwstrSrc) + 1)*2;
		char* pstr      = (char*) malloc ( sizeof( char) * len);
		WideCharToMultiByte( 949, 0, pwstrSrc, -1, pstr, len, NULL, NULL);
	#else
		int nLen = wcslen(pwstrSrc);
		char* pstr      = (char*) malloc ( sizeof( char) * nLen + 1);
		wcstombs(pstr, pwstrSrc, nLen+1);
	#endif
		return pstr;
	}
*/
#pragma endregion
