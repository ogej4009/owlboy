
#include "LevelDesignViewer.h"
#include <GameSound.h>


void LevelDesignViewer::File_In()
{

	{
		GameDirectory Dic;

		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"sound");

		auto FileList = Dic.DirAllFile();

		for (auto& _File : FileList)
		{
			GameSound::Load(_File);
		}

		//GameSound::Play(L"Dungeon.mp3");
	}

	/*{
		GameDirectory Dic;

		Dic.MoveParent(L"GameFramework");
		Dic.Move(L"resource");
		Dic.Move(L"data");

		auto FileList = Dic.DirAllFile();

		for (auto& _File : FileList)
		{
			GameTexture::Load(_File);
		}

		for (auto& _File : FileList)
		{
			GameSprite::Create(_File.FileName(), 1, 1);
		}
	}*/

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
		GameSprite::Create(L"ColLevel2.png", 10, 5);
		GameSprite::Create(L"TestGrid.png", 1, 1);
		GameSprite::Create(L"TransparencyFrame_1920x1040.png", 120, 65);
		GameSprite::Create(L"Error.png", 1, 1);
		GameSprite::Create(L"ErrorTile.png", 1, 1);

		//for (auto& _File : FileList)
		//{
		//	GameSprite::Create(_File.FileName(), 1, 1);
		//}
	}





	





}

void LevelDesignViewer::File_Out()
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
		//for (auto& _File : FileList)
		//{
		//	GameSprite::Delete(_File.FileName());
		//}
	}
}

// SetRenderTarget