// File Life Cycle

#include "MapToolEditor.h"

void MapToolEditor::FileCreate()
{

	/*{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"data");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameString StrName = _File.FileName();
			GameFile LoadFile = GameFile(Dic.CombineFileName(StrName), L"rb");
			SAVEMAPDATA Data;
			LoadFile.Load(Data);
			GameMap::AutoMapDataTEST(Data);
		}
		GameMap::CreateMap(ROOMNUMBER);
	}*/


	
	// Tile..
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}
		GameSprite::Create(L"ColLevel1.png", 10, 5);
		GameSprite::Create(L"__GRID_FRAME_1280x720.png", 1, 1);
	

		/*for (auto& _File : FileList)
		{
			GameSprite::Create(_File.FileName(), 1, 1);
		}*/
	}

	

}

void MapToolEditor::FileDelete()
{
	
	{
		GameDirectory Dic;
		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"tex");
		Dic.Move(L"Global");
		auto FileList = Dic.DirAllFile();
		for (auto& _File : FileList)
		{
			GameTexture::Delete(_File.FileName());
		}
		for (auto& _File : FileList)
		{
			GameTexture::Delete(_File.FileName());
		}
	}

}