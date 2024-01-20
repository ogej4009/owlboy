#include "GameIO.h"
#include <Windows.h>
#include <assert.h>
#include <iostream> 
#include <io.h> 
#include "GameFile.h"

GameDirectory::GameDirectory()
{
#pragma region CASE
	/*
		GetCurrentDirectory : 현재 실행되는 경로에 대한 정보

		LPWSTR typedef 해석
		LP : 포인터
		STR : 문자열
		W : 와이드 바이트 문자열
	*/
#pragma endregion

	WCHAR Str[256];
	GetCurrentDirectory(256, Str);
	m_Path.m_Str = Str;
}


GameDirectory::~GameDirectory() {}


void GameDirectory::MoveParent()
{
	size_t Start = m_Path.m_Str.FindLast(L"\\");
	size_t End = m_Path.m_Str.StrCount();
	m_Path.m_Str.EraseStr(Start, End);
}


void GameDirectory::MoveParent(const GameString& _Folder)
{
	while (true)
	{
		GameString Folder = FolderName();

		size_t S1 = Folder.StrCount();
		size_t S2 = _Folder.StrCount();

		if (Folder != _Folder)
		{
			MoveParent();
		}
		else
		{
			break;
		}
	}
}

GameString GameDirectory::FolderName()
{
	return IOName();
}

void GameDirectory::Move(const GameString& _Folder)
{
	GameString Path = m_Path.m_Str;

	Path += L"\\" + _Folder;

	if (false == GamePath::IsExistence(Path))
	{
		assert(false);
	}

	m_Path.m_Str = Path;
}


#pragma region 해석
/*
	C://*.*
	C:// 드라이브의 * 모든 파일명 . * 모든 확장자를 찾아라.
*/
#pragma endregion


std::list<GameFile> GameDirectory::DirAllFile(const wchar_t* _Ext, const wchar_t* _Name)
{
	std::list<GameFile> AllFileList;
	int checkDirFile = 0;
	GameString dirPath;
	GameString Ext = _Ext;
	GameString Name = _Name;

	if (Name != L"")
	{
		dirPath = m_Path.m_Str + L"\\" + Name + L"*";
	}
	else
	{
		dirPath = m_Path.m_Str + L"\\*";
	}

	if (Ext != L"")
	{
		dirPath += L"." + Ext;
	}
	else
	{
		dirPath += L".*";
	}

	_wfinddata64i32_t fd; // 디렉토리 내 파일 및 폴더 정보 저장 객체
	intptr_t handle;

#pragma region 파일도 핸들이다
	if ((handle = _wfindfirst(dirPath, &fd)) == -1L) // 최초의 파일 찾기 //fd 구조체 초기화.
	{
		return AllFileList;
	}
#pragma endregion

	do
	{
		if (fd.attrib & _A_SUBDIR)
		{
			// 디렉토리
			checkDirFile = 0;
		}
		else
		{
			// 파일
			checkDirFile = 1;
		}

#pragma region this Case Directory 재귀적 호출
		/*
			if (checkDirFile == 0 && fd.name[0] != '.')
			{
				cout << "Dir  : " << path << "\\" << fd.name << endl;
				searchingDir(path + "\\" + fd.name);
			}
		*/
#pragma endregion

		if (fd.name[0] == L'.')
		{
			continue;
		}

		if (checkDirFile == 1)
		{
			GameString FilePath = m_Path.m_Str + L"\\" + fd.name;

			GameFile NewFile = GameFile(FilePath);

			AllFileList.push_back(NewFile);
		}


	} while (_wfindnext(handle, &fd) == 0); // 파일이 없다 : return -1 

	_findclose(handle);

	return AllFileList;
}

GameString GameFile::Ext() const
{
	size_t Start = m_Path.m_Str.FindLast(L".");
	size_t End = m_Path.m_Str.StrCount();
	return m_Path.m_Str.RangeToStr(Start, End);
}
