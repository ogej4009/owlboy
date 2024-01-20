#pragma once
#include "GameIO.h"

class GameFile : public GameIO
{
public:
	FILE* FILEPOINTER;
	bool m_IsOpen;

public:
	bool GetIsOpen()
	{
		return m_IsOpen;
	}

	GameString FullPath() const
	{
		return m_Path.m_Str;
	}

	GameString FileName() const
	{
		return IOName();
	}

	GameString Ext() const;

public:

	// * & 이중포인터 주의 
	template<typename T>
	void Save(const T& _Value) // const 
	{
		fwrite(&_Value, sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void Save(T* _Value, int _Count) // 자료형 벡터의 사이즈를 넣어준다.  
	{
		fwrite(_Value, sizeof(T) * _Count, 1, FILEPOINTER);
	}

	template<typename T>
	void Load(T& _Value)
	{
		fread_s(&_Value, sizeof(T), sizeof(T), 1, FILEPOINTER);
	}

public:
	GameFile() : m_IsOpen(false) {}

	GameFile(const GameString& _FilePath) : m_IsOpen(false)
	{
		m_Path = _FilePath;
	}

	GameFile(const wchar_t* _Path) : m_IsOpen(false)
	{
		m_Path = _Path;
	}

	GameFile(const GameString& _FilePath, const GameString& _FileMode)
		: FILEPOINTER(nullptr), m_IsOpen(false)
	{
		_wfopen_s(&FILEPOINTER, _FilePath, _FileMode);
		//wopen
		//fopen_s(PTR, "C:DJKALFSDJFKLDASJFKLA.PNG", "wb");

		if (nullptr != FILEPOINTER)
		{
			m_IsOpen = true; // == 실행중
		}
	}

	~GameFile()
	{
#pragma region 파일의 스코프 생명주기 활용 기법
		/*
			Local ==> Stack
			만들어진 곳에서 {}스코프를 넘어가면 자연스럽게 사라진다.
			파일은 그곳에서 사라진다.
		*/
#pragma endregion

		if (nullptr != FILEPOINTER)
		{
			fclose(FILEPOINTER);
		}
	}
};

#pragma region 파일 포인터 크기 
/*
	FILE* PTR;
	int 1
	== b 0000 0001 0000 0000 0000 0000 0000 0000
	  '1'
*/
#pragma endregion

#pragma region 모드 
// write, read, textmode, binarymode 
// "rb" 
// "rt"
// "wb"
// "wt"
#pragma endregion