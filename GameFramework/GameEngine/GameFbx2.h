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
//// #include "HRENDERTARGET" // 3d�� �ٽ�.
//
//#pragma comment(lib, "zlib-md.lib")
//#pragma comment(lib, "libxml2-md.lib")
//#pragma comment(lib, "libfbxsdk-md.lib")
//
//class BoneFrameData
//{
//public:
//	WVECTOR S; // ũ
//	WVECTOR Q; // ��
//	WVECTOR T; // ��
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
//	// 134 ���� ����
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
//			AMSG(L"ó���Ҽ� ���� ������ ī��Ʈ ����Դϴ�.");
//			break;
//		}
//
//		AMSG(L"ó���Ҽ� ���� ������ ī��Ʈ ����Դϴ�.");
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
//	int			iDepth; // ��Ʈ�� 0 -> �¿�� 
//	int			iIndex; // ���� �������� �������.
//	int			iParentIndex; // ���θ� 49��° �ִ�.
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
//	// �ȼ����̴����� �׳� �������� �����ָ� �Ǵ� ����.
//	WVECTOR DifColor;
//	WVECTOR AmbColor;
//	WVECTOR SpcColor;
//	WVECTOR EmvColor;
//	float SpecularPower;
//	float TransparencyFactor;
//	float Shininess;
//	WGAMESTRING DifTexture;	// ��ǻ�� 
//	// DifTexture �� �༮�� �����е��� �Ϲ������� �˰� �ִ� �����̶�� ���� ǥ�����ִ� ��ǻ�� �ؽ�ó�̴�.
//	WGAMESTRING BmpTexture; // ���� ���� ����
//	WGAMESTRING SpcTexture; // ����ŧ�� ���� ����
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
//	fbxsdk::FbxManager* m_Mgr; // ���� �⺻�� �Ǵ� fbx �ý����� ����.
//	fbxsdk::FbxIOSettings* m_Ios; // fbx ������ io�ý����� �����ϴ� �׸� fbx�� ��Ƽ �÷����̱� ������ �Ƹ� �̷��� �����ҰŶ� �����Ѵ�.
//	fbxsdk::FbxScene* m_Scene; // 3d�ƽ� �������� ���� �⺻���� ���� �����ϴ� �༮.
//	fbxsdk::FbxImporter* m_Imp; // �̳༮�� fbx�� �ε��ϴ� �������� ��ü
//	fbxsdk::FbxAxisSystem eLocalSpaceType; // �⺻ ���������� �⺻���� ������ �˾Ƴ���.
//	// 1 0 0 0
//	// 0 1 0 0
//	// 0 0 -1 0
//	// 0 0 0 1
//
//	// ���Ĵٵ� ���̺귯����?
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
//	// ���� �׷����� ����. �׷��� �ִٸ�.
//	// �����׷��� ����    
//	// �̳༮�� �������϶��� �ְ�
//	std::vector<       std::vector<VTX3DMESHIN>          > m_FbxVtx; // ���ؽ�
//
//	// �̰ɷ� ��������.
//	// std::vector<std::vector<UINT>>
//	// �׸��� �ε��� ���۰� 4����� ���� ������ 4���̴�.
//	std::vector<       std::vector<std::vector<UINT>>    > m_FbxIdx; // �ε���
//
//	// �� �����͵��� �츮 ������ ��ȯ���Ѿ� �ϱ�� ������.
//
//	// �츮������ ��ȯ��Ų �༮��
//	std::vector<WPTR<WVBBUFFER>> m_VB;
//	std::vector<std::vector<WPTR<WIBBUFFER>>> m_IB;
//
//
//	// ���׸���
//	std::vector<WFBXMATDATA> m_UserMatData;
//	// STATIC MESH END
//
//	// ���� ������������ �ȴ�. �������������ο� ���� �ؽ�ó ���÷� �÷�
//	// ��� ������ ��������.
//
//
//	std::map<WGAMESTRING, WFBXANIDATA*> m_UserAniDataMap; // �ִϸ��̼� 
//
//	std::map<WGAMESTRING, WFBXBONEDATA*> m_MapBoneData;
//
//	std::vector<WPTR<WMESH>> m_Mesh; // �޽�
//	std::vector<WFBXANIDATA> m_UserAniData; // �ִϸ��̼�
//	std::vector<WFBXBONEDATA> m_UserBoneData; // ��
//
//
//
//	// �ִϸ��̼� ����ġ �� �ε��� ������ �ڷᱸ��.
//	// ��񾲰� �Ⱦ���.
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
//	// ��͵��� ����ؼ� ���� ����� ���̴�.
//	// �ٽ� �����Ϸ���?
//	// Ŭ������ �׳������Ҽ��� ����.
//
//	// std::vector<std::vector<VTX3DMESHIN>> m_FbxVtx; // ���ؽ�
//	// std::vector<std::vector<std::vector<UINT>>> m_FbxIdx; // �ε���
//	// std::vector<WFBXBONEDATA> m_UserBoneData; // ��
//	// std::vector<WFBXANIDATA> m_UserAniData; // �ִϸ��̼� 
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
//	// ���������������� ���鶧 �ʿ��� �����̴�.
//	// ���� ���׸����̶�� �Ѵ�.
//	// ���⼭ ������� ���׸����� ������ ����
//	// ���������� ���������ִ� ����°����� �����ϴ�.
//
//
//	// �� �����Լ�
//	void LoadBoneCount(fbxsdk::FbxNode* _Node, int& _Count);
//	void LoadBone(fbxsdk::FbxNode* _Node, int& _iIndex, int _iDepth = 0, int _iParent = -1);
//
//	// ���� ���� �Լ�.
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
//	// ���׸��� ���� �Լ�.
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
