#pragma once
class GameFbx2
{
};
//
//#pragma once
//#include "WGAMERES.h"
//#include "WGAMEDEVICE.h"
//#include <DirectXTex.h>
//#include "WSHADER.h"
//#include <fbxsdk.h>
//#include "WVTXSHADER.h"
//#include "DEFVTXHEADER.h"
//// #include "HRENDERTARGET" // 3d의 핵심.
//
//#pragma comment(lib, "zlib-md.lib")
//#pragma comment(lib, "libxml2-md.lib")
//#pragma comment(lib, "libfbxsdk-md.lib")
//
//class BoneFrameData
//{
//public:
//	WVECTOR S; // 크
//	WVECTOR Q; // 자
//	WVECTOR T; // 이
//	double Time;
//	WMATRIX FrameMat;
//};
//
//class BoneFrame
//{
//public:
//	int BoneIndex;
//	// 1434
//	std::vector<BoneFrameData> m_Data;
//};
//
//class WFBXANIDATA
//{
//public:
//	WGAMESTRING AniName;
//	fbxsdk::FbxTime StartTime;
//	fbxsdk::FbxTime EndTime;
//	fbxsdk::FbxLongLong TimeStartCount;
//	fbxsdk::FbxLongLong TimeEndCount;
//	fbxsdk::FbxLongLong FrameCount;
//	fbxsdk::FbxTime::EMode TimeMode;
//	int FbxModeCount;
//
//	// 134 본의 개수
//	std::vector<BoneFrame> m_AniFrameData;
//
//public:
//	float FrameTime(int _Frame)
//	{
//		fbxsdk::FbxTime tTime = {};
//		tTime.SetFrame(_Frame, TimeMode);
//
//		return (float)tTime.GetSecondDouble();
//	}
//
//public:
//	int FrameModeCount()
//	{
//		switch (TimeMode)
//		{
//		case fbxsdk::FbxTime::eFrames120:
//			return 120;
//		case fbxsdk::FbxTime::eFrames100:
//			return 100;
//		case fbxsdk::FbxTime::eFrames60:
//			return 60;
//		case fbxsdk::FbxTime::eFrames50:
//			return 50;
//		case fbxsdk::FbxTime::eFrames48:
//			return 48;
//		case fbxsdk::FbxTime::eFrames30:
//			return 30;
//		case fbxsdk::FbxTime::eFrames24:
//			return 24;
//		default:
//			AMSG(L"처리할수 없는 프레임 카운트 모드입니다.");
//			break;
//		}
//
//		AMSG(L"처리할수 없는 프레임 카운트 모드입니다.");
//		return -1;
//	}
//
//public:
//	WFBXANIDATA() {}
//	~WFBXANIDATA() {}
//};
//
//class WFBXBONEDATA
//{
//public:
//	WGAMESTRING Name;
//	int			iDepth; // 루트면 0 -> 좌우로 
//	int			iIndex; // 임의 선생님이 만들었다.
//	int			iParentIndex; // 내부모가 49번째 애다.
//	WMATRIX		Offset;
//	WMATRIX		Bone;
//
//public:
//	WFBXBONEDATA() {}
//	~WFBXBONEDATA() {}
//};
//
//class WFBXMATDATA
//{
//public:
//	// 픽셀쉐이더에서 그냥 최종색상에 곱해주면 되는 색상.
//	WVECTOR DifColor;
//	WVECTOR AmbColor;
//	WVECTOR SpcColor;
//	WVECTOR EmvColor;
//	float SpecularPower;
//	float TransparencyFactor;
//	float Shininess;
//	WGAMESTRING DifTexture;	// 디퓨즈 
//	// DifTexture 이 녀석이 여러분들이 일반적으로 알고 있는 색깔이라는 것을 표현해주는 디퓨즈 텍스처이다.
//	WGAMESTRING BmpTexture; // 범프 후일 설명
//	WGAMESTRING SpcTexture; // 스펙큘러 후일 설명
//
//public:
//	WFBXMATDATA() {}
//	~WFBXMATDATA() {}
//};
//
//class WFBXIW
//{
//public:
//	int Index;
//	double Weight;
//};
//
//class WMESH;
//class WVBBUFFER;
//class WIBBUFFER;
//class WRENDERPIPELINE;
//class WFBX : public WFILEMGR<WFBX>
//{
//public:
//	static WPTR<WFBX> Load(const WGAMEFILE& _File)
//	{
//		std::wcout << L"Load START" << std::endl;
//		WPTR<WFBX> Res = CreateToInsertToFile(_File.FullPath());
//		Res->Load();
//		std::wcout << L"Load End" << std::endl;
//		return Res;
//	}
//
//
//	// 
//	static void LoadToUserFormat(const WGAMEFILE& _File, const WGAMESTRING& _UserPath)
//	{
//		WPTR<WFBX> Res = CreateToInsertToFile(_File.FullPath());
//		Res->LoadUserFormat(_UserPath);
//		return;
//	}
//
//
//private:
//	fbxsdk::FbxAMatrix ReMat;
//	fbxsdk::FbxManager* m_Mgr; // 가장 기본이 되는 fbx 시스템의 권한.
//	fbxsdk::FbxIOSettings* m_Ios; // fbx 파일의 io시스템을 정의하는 항목 fbx다 멀티 플랫폼이기 때문에 아마 이렇게 지원할거라 예상한다.
//	fbxsdk::FbxScene* m_Scene; // 3d맥스 편집에서 가장 기본적인 씬을 정의하는 녀석.
//	fbxsdk::FbxImporter* m_Imp; // 이녀석은 fbx를 로드하는 실질적인 객체
//	fbxsdk::FbxAxisSystem eLocalSpaceType; // 기본 기저백터의 기본적인 방향을 알아낸다.
//	// 1 0 0 0
//	// 0 1 0 0
//	// 0 0 -1 0
//	// 0 0 0 1
//
//	// 스탠다드 라이브러리죠?
//	// std::string
//
//	bool HasAnimation;
//
//public:
//
//	bool HasAni()
//	{
//		return HasAnimation;
//	}
//
//	// STATIC MESH
//	// 보통 그런경우는 없다. 그런데 있다면.
//	// 정점그룹의 모임    
//	// 이녀석이 여러개일때도 있고
//	std::vector<       std::vector<VTX3DMESHIN>          > m_FbxVtx; // 버텍스
//
//	// 이걸로 나눠놨다.
//	// std::vector<std::vector<UINT>>
//	// 그리고 인덱스 버퍼가 4개라면 재질 정보도 4개이다.
//	std::vector<       std::vector<std::vector<UINT>>    > m_FbxIdx; // 인덱스
//
//	// 이 데이터들은 우리 구조로 변환시켜야 하기는 하지만.
//
//	// 우리구조로 변환시킨 녀석들
//	std::vector<WPTR<WVBBUFFER>> m_VB;
//	std::vector<std::vector<WPTR<WIBBUFFER>>> m_IB;
//
//
//	// 메테리얼
//	std::vector<WFBXMATDATA> m_UserMatData;
//	// STATIC MESH END
//
//	// 랜더 파이프라인이 된다. 랜더파이프라인에 들어가는 텍스처 샘플러 컬러
//	// 어떠한 정점에 곱해진다.
//
//
//	std::map<WGAMESTRING, WFBXANIDATA*> m_UserAniDataMap; // 애니메이션 
//
//	std::map<WGAMESTRING, WFBXBONEDATA*> m_MapBoneData;
//
//	std::vector<WPTR<WMESH>> m_Mesh; // 메쉬
//	std::vector<WFBXANIDATA> m_UserAniData; // 애니메이션
//	std::vector<WFBXBONEDATA> m_UserBoneData; // 본
//
//
//
//	// 애니메이션 가중치 및 인덱스 정리용 자료구조.
//	// 잠깐쓰고 안쓴다.
//	std::vector<std::map<int, std::vector<WFBXIW>>> m_MapWI;
//
//public:
//	size_t UserAniDataSize()
//	{
//		return m_UserAniData.size();
//	}
//
//	WGAMESTRING UserAniDataName(size_t _Index)
//	{
//		return m_UserAniData[_Index].AniName;
//	}
//
//
//	// 요것들이 계산해서 나온 결과물 들이다.
//	// 다시 계산안하려면?
//	// 클래스를 그냥저장할수는 없다.
//
//	// std::vector<std::vector<VTX3DMESHIN>> m_FbxVtx; // 버텍스
//	// std::vector<std::vector<std::vector<UINT>>> m_FbxIdx; // 인덱스
//	// std::vector<WFBXBONEDATA> m_UserBoneData; // 본
//	// std::vector<WFBXANIDATA> m_UserAniData; // 애니메이션 
//	// std::vector<WFBXMATDATA> m_UserMatData;
//
//public:
//	WFBX();
//	~WFBX();
//
//public:
//	void Load();
//	void LoadUserFormat(const WGAMESTRING& _Path);
//	void SaveUserFormat(const WGAMESTRING& _Path);
//
//public:
//	WFBXANIDATA* FindAniData(const WGAMESTRING& _Name)
//	{
//		if (m_UserAniDataMap.end() == m_UserAniDataMap.find(_Name))
//		{
//			return nullptr;
//		}
//
//		return m_UserAniDataMap[_Name];
//	}
//
//private:
//
//	void AniCheck();
//	void BoneCheck();
//	void Trangulate(fbxsdk::FbxNode* _Node, int& _MatCount);
//	// 랜더파이프라인을 만들때 필요한 정보이다.
//	// 보통 메테리얼이라고 한다.
//	// 여기서 얻어지는 메테리얼의 개수는 보통
//	// 정점집합이 나뉘어져있는 서브셋개수와 동일하다.
//
//
//	// 본 관련함수
//	void LoadBoneCount(fbxsdk::FbxNode* _Node, int& _Count);
//	void LoadBone(fbxsdk::FbxNode* _Node, int& _iIndex, int _iDepth = 0, int _iParent = -1);
//
//	// 정점 관련 함수.
//	void MeshVtxData(fbxsdk::FbxNode* _Node);
//	void VtxData(fbxsdk::FbxMesh* _Mesh);
//
//	int MeshCount;
//	void AnimationClipCheck(fbxsdk::FbxNode* _Node);
//	void CalAnimationClip(fbxsdk::FbxMesh* _Mesh);
//	void CalWeightAndIndex();
//
//
//	void LoadNormal(fbxsdk::FbxMesh* _Mesh, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//	void LoadUv(fbxsdk::FbxMesh* _Mesh, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//	void LoadTangent(fbxsdk::FbxMesh* _Mesh, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//	void LoadBinormal(fbxsdk::FbxMesh* _Mesh, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//
//
//	void LoadWeightAndIndex(fbxsdk::FbxCluster* _Cluster, int _BoneIndex, std::vector<VTX3DMESHIN>& _ArrVtx);
//	void LoadOffsetMatrix(fbxsdk::FbxCluster* _Cluster, const fbxsdk::FbxAMatrix& _BaseTrans, WFBXBONEDATA* _Bone);
//	void LoadTimeTransForm(fbxsdk::FbxNode* _Node, fbxsdk::FbxCluster* _Cluster, const fbxsdk::FbxAMatrix& _BaseTrans, WFBXBONEDATA* _Bone);
//
//
//	// std::map<WGAMESTRING, WFBXBONEDATA*> m_MapBoneData;
//
//	WFBXBONEDATA* FindBone(const WGAMESTRING& _Name);
//
//	// 메테리얼 관련 함수.
//	void MaterialCheck(fbxsdk::FbxNode* _Node, int& _Count);
//	WVECTOR MaterialColor(FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName);
//	float MaterialFactor(FbxSurfaceMaterial* pMtrl, const char* _FactorName);
//	WGAMESTRING MaterialTex(FbxSurfaceMaterial* pMtrl, const char* _FactorName);
//
//
//	static WMATRIX FbxMatToHMAT(const fbxsdk::FbxAMatrix& _BaseTrans);
//	static WVECTOR FbxVecToHVEC(const fbxsdk::FbxVector4& _BaseVector);
//	static WVECTOR FbxQToHVEC(const fbxsdk::FbxQuaternion& _BaseQ);
//
//
//public:
//	void CreateMesh();
//	void SetRenderer(WPTR<WRENDERER> NewRenderer, const WGAMESTRING& _Fbx);
//};
