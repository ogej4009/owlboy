#pragma once
class GameFbxEx
{
};
//
//#pragma once
//#include <WGAMEMATH.h>
//#include <WGAMESTRING.h>
//#include <vector>
//#include <map>
//
//#include <fbxsdk.h> 
//
//#include "WGAMERES.h"
//#include "WGAMEDEVICE.h"
//#include <DirectXTex.h>
//#include "WSHADER.h"
//#include <fbxsdk.h>
//#include "WVTXSHADER.h"
//#include "DEFVTXHEADER.h"
//#include "WMESH.h"
//// #include "WRenderTarget" // 3d의 핵심.
//
//#pragma comment(lib, "zlib-md.lib")
//#pragma comment(lib, "libxml2-md.lib")
//#pragma comment(lib, "libfbxsdk-md.lib")
//
//class WFbxExIW
//{
//public:
//	int Index;
//	double Weight;
//};
//
//class WVBBUFFER;
//class WVBBUFFER;
//class WFbxExMaterialData;
//struct DRAWSET
//{
//public:
//	int IsLodLv;
//	bool IsLod;
//
//	std::map<FbxMesh*, std::vector<VTX3DMESHIN>*> m_FbxVtxMap;
//	std::map<FbxMesh*, std::map<int, std::vector<WFbxExIW>>> m_MapWI;
//
//	std::vector<std::vector<VTX3DMESHIN>*> m_FbxVtx;
//	std::vector<std::vector<std::vector<UINT>>*> m_FbxIdx;
//	std::vector<std::vector<WFbxExMaterialData>> m_MatialData;
//
//	std::vector<WPTR<WVBBUFFER>> m_VB;
//	std::vector<std::vector<WPTR<WVBBUFFER>>> m_IB;
//	std::vector<std::vector<WPTR<WMESH>>> m_Mesh;
//
//	DRAWSET();
//	~DRAWSET();
//};
//
//
//class WFbxExBoneFrameData
//{
//public:
//	float4 S; // 크
//	float4 Q; // 자
//	float4 T; // 이
//	double Time;
//	WMATRIX FrameMat;
//
//	fbxsdk::FbxAMatrix GlobalAnimation;
//	fbxsdk::FbxAMatrix LocalAnimation;
//};
//
//class WFbxExBoneFrame
//{
//public:
//	int BoneIndex;
//	int BoneParentIndex;
//	std::vector<WFbxExBoneFrameData> m_Data;
//};
//
//class WFbxExAniData
//{
//public:
//	WGAMESTRING AniName;
//	fbxsdk::FbxTime StartTime;
//	fbxsdk::FbxTime EndTime;
//	fbxsdk::FbxLongLong TimeStartCount;
//	fbxsdk::FbxLongLong TimeEndCount;
//	fbxsdk::FbxLongLong FrameCount;
//	fbxsdk::FbxTime::EMode TimeMode;
//	__int64 FbxModeCount;
//	double FbxModeRate;
//
//	std::vector<WFbxExBoneFrame> m_AniFrameData;
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
//	__int64 FrameModeRateInt()
//	{
//		return static_cast<__int64>(fbxsdk::FbxGetFrameRate(TimeMode));
//	}
//	double FrameModeRateDouble()
//	{
//		return fbxsdk::FbxGetFrameRate(TimeMode);
//	}
//
//	float FrameModeRateFloat()
//	{
//		return static_cast<float>(fbxsdk::FbxGetFrameRate(TimeMode));
//	}
//
//
//public:
//	WFbxExAniData() : AniName(L""), StartTime(0), EndTime(0), TimeStartCount(0), TimeEndCount(0), FrameCount(0), FbxModeCount(0), FbxModeRate(0.0)
//	{}
//	~WFbxExAniData() {}
//};
//
//class WFbxExMaterialData
//{
//public:
//	WGAMESTRING Name;
//
//	float4 DifColor;
//	float4 AmbColor; // 빛
//	float4 SpcColor; // 빛
//	float4 EmvColor; // 빛
//	float SpecularPower;		// 빛의 강도
//	float TransparencyFactor;	// 빛의 강도
//	float Shininess;			// 빛의 강도
//	WGAMESTRING DifTexture;	// 텍스처경로 
//	WGAMESTRING BmpTexture; // 텍스처경로
//	WGAMESTRING SpcTexture; // 텍스처경로
//
//public:
//	WFbxExMaterialData() {}
//	~WFbxExMaterialData() {}
//};
//
//////////////////////////////////////////////////////////////
//struct WFbxExMeshInfo
//{
//	WGAMESTRING Name;
//	fbxsdk::FbxMesh* pMesh;
//	bool bTriangulated;
//
//	unsigned __int64 UniqueId;
//	int FaceNum;
//	int VertexNum;
//	int MaterialNum;
//	bool bIsSkelMesh;
//	WGAMESTRING SkeletonRoot;
//	int SkeletonElemNum;
//	bool bIsLodGroup;
//	WGAMESTRING LODGroup;
//	int LODLevel;
//	int MorphNum;
//
//	WFbxExMeshInfo()
//	{
//		Name = "";
//		UniqueId = 0;
//		FaceNum = 0;
//		VertexNum = 0;
//		bTriangulated = false;
//		MaterialNum = 0;
//		bIsSkelMesh = false;
//		SkeletonRoot = "";
//		SkeletonElemNum = 0;
//		bIsLodGroup = false;
//		LODGroup = "";
//		LODLevel = 0;
//		MorphNum = 0;
//	}
//};
//
//struct WFbxExNodeInfo
//{
//	const char* ObjectName;
//	unsigned __int64 UniqueId;
//	fbxsdk::FbxAMatrix Transform;
//	fbxsdk::FbxVector4 RotationPivot;
//	fbxsdk::FbxVector4 ScalePivot;
//
//	// 어트리뷰트 네임음 enum
//	const char* AttributeName;
//	unsigned __int64 AttributeUniqueId;
//	const char* AttributeType;
//
//	const char* ParentName;
//	unsigned __int64 ParentUniqueId;
//
//	WFbxExNodeInfo() :
//		ObjectName(nullptr),
//		AttributeName(nullptr),
//		AttributeType(nullptr),
//		ParentName(nullptr)
//	{
//		UniqueId = 0;
//		Transform.SetIdentity();
//		RotationPivot.Set(0, 0, 0);
//		ScalePivot.Set(1, 1, 1);
//
//		AttributeUniqueId = 0;
//
//		ParentUniqueId = 0;
//	}
//};
//
//struct WFbxExSceneInfo
//{
//	int NonSkinnedMeshNum;
//
//	int SkinnedMeshNum;
//
//	// common data
//	int TotalGeometryNum; // 토탈 본
//	int TotalMaterialNum; // 토탈 메트릭스
//	int TotalTextureNum;  // 토탈 텍스처
//
//	std::vector<WFbxExMeshInfo> MeshInfo;
//	std::vector<WFbxExNodeInfo> HierarchyInfo;
//
//	/* true if it has animation */
//	bool bHasAnimation;
//	double FrameRate;
//	double TotalTime;
//
//	WFbxExSceneInfo()
//	{
//		Reset();
//	}
//
//	void Reset()
//	{
//		NonSkinnedMeshNum = 0;
//		SkinnedMeshNum = 0;
//		TotalGeometryNum = 0;
//		TotalMaterialNum = 0;
//		TotalTextureNum = 0;
//		MeshInfo.clear();
//		HierarchyInfo.clear();
//		bHasAnimation = false;
//		FrameRate = 0.0;
//		TotalTime = 0.0;
//	}
//};
//
//// 본 위
//struct JointPos
//{
//	float4 Scale;
//	float4 Rotation; // 쿼터니온.
//	float4 Translation;
//
//	float4 GlobalScale;
//	float4 GlobalRotation;
//	float4 GlobalTranslation;
//
//	WMATRIX Offset;
//	WMATRIX SotredOffset;
//	WMATRIX Local;
//	WMATRIX Global;
//
//	float Length;
//	float XSize;
//	float YSize;
//	float ZSize;
//
//	void BuildMatrix()
//	{
//		Global = WMATRIX::Transformation(GlobalScale, GlobalRotation, GlobalTranslation);
//		Local = WMATRIX::Transformation(Scale, Rotation, Translation);
//		Offset = Global.InverseReturn();
//	}
//
//	void SetScale(fbxsdk::FbxVector4& scale)
//	{
//		Scale.x = (float)scale.mData[0];
//		Scale.y = (float)scale.mData[1];
//		Scale.z = (float)scale.mData[2];
//		Scale.w = 0.0f;
//	}
//
//	void SetRotation(fbxsdk::FbxQuaternion& quaternion)
//	{
//		Rotation.x = (float)quaternion.mData[0];
//		Rotation.y = (float)quaternion.mData[1];
//		Rotation.z = -(float)quaternion.mData[2];
//		Rotation.w = -(float)quaternion.mData[3];
//	}
//
//	void SetTranslation(fbxsdk::FbxVector4& translation)
//	{
//		Translation.x = (float)translation.mData[0];
//		Translation.y = (float)translation.mData[1];
//		Translation.z = -(float)translation.mData[2];
//		Translation.w = 0.0f;
//	}
//
//	void SetGlobalScale(fbxsdk::FbxVector4& scale)
//	{
//		GlobalScale.x = (float)scale.mData[0];
//		GlobalScale.y = (float)scale.mData[1];
//		GlobalScale.z = (float)scale.mData[2];
//		GlobalScale.w = 0.0f;
//	}
//
//	void SetGlobalRotation(fbxsdk::FbxQuaternion& quaternion)
//	{
//		GlobalRotation.x = (float)quaternion.mData[0];
//		GlobalRotation.y = (float)quaternion.mData[1];
//		GlobalRotation.z = -(float)quaternion.mData[2];
//		GlobalRotation.w = -(float)quaternion.mData[3];
//	}
//
//	void SetGlobalTranslation(fbxsdk::FbxVector4& translation)
//	{
//		GlobalTranslation.x = (float)translation.mData[0];
//		GlobalTranslation.y = (float)translation.mData[1];
//		GlobalTranslation.z = -(float)translation.mData[2];
//		GlobalTranslation.w = 0.0f;
//	}
//
//	void SetFromMatrix(const WMATRIX& InMatrix)
//	{
//		WMATRIX M = InMatrix;
//
//		// Get the 3D scale from the matrix
//		Scale = M.ExtractScaling();
//		Scale.w = 0.0;
//
//		// If there is negative scaling going on, we handle that here
//		if (InMatrix.Determinant() < 0.f)
//		{
//			// Assume it is along X and modify transform accordingly. 
//			// It doesn't actually matter which axis we choose, the 'appearance' will be the same
//			float4 FloatMinus1_111(-1.f, 1.f, 1.f, 1.f);
//			Scale *= FloatMinus1_111;// VectorMultiply(Scale, FloatMinus1_111);
//			float4 XAxis = -float4(M.Arr2D[0][0], M.Arr2D[0][1], M.Arr2D[0][2], 0.0f);
//			M.Arr2D[0][0] = XAxis.x;
//			M.Arr2D[0][1] = XAxis.w;
//			M.Arr2D[0][2] = XAxis.z;
//		}
//
//		Rotation = WVECTOR::MatrixToQuaternion(M);
//		Translation = float4(InMatrix.Arr2D[3][0], InMatrix.Arr2D[3][1], InMatrix.Arr2D[3][2], 0.0f);
//
//		// Normalize rotation
//		__m128 Temp1 = _mm_mul_ps(Rotation.DXVEC, Rotation.DXVEC);
//		__m128 Temp2 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(1, 0, 3, 2));	// (Z,W,X,Y).
//		Temp1 = _mm_add_ps(Temp1, Temp2);								// (X*X + Z*Z, Y*Y + W*W, Z*Z + X*X, W*W + Y*Y)
//		Temp2 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(0, 3, 2, 1));
//		__m128 SquareSum = _mm_add_ps(Temp1, Temp2);
//		const __m128 NonZeroMask = _mm_cmpge_ps(SquareSum, _mm_setr_ps(1.e-8f, 1.e-8f, 1.e-8f, 1.e-8f));
//		const __m128 OneHalf = _mm_setr_ps(0.5f, 0.5f, 0.5f, 0.5f);
//		const __m128 VecDivBy2 = _mm_mul_ps(SquareSum, OneHalf);
//
//		// Initial estimate
//		const __m128 x0 = _mm_rsqrt_ps(SquareSum);
//
//		// First iteration
//		__m128 x1 = _mm_mul_ps(x0, x0);
//		x1 = _mm_sub_ps(OneHalf, _mm_mul_ps(VecDivBy2, x1));
//		x1 = _mm_add_ps(_mm_mul_ps(x0, x1), x0);
//
//		// Second iteration
//		__m128 x2 = _mm_mul_ps(x1, x1);
//		x2 = _mm_sub_ps(OneHalf, _mm_mul_ps(VecDivBy2, x2));
//		const __m128 InvLength = _mm_add_ps(_mm_mul_ps(x1, x2), x1);
//
//		const __m128 NormalizedVector = _mm_mul_ps(InvLength, Rotation.DXVEC);
//		__m128 DefaultValue = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
//		Rotation.DXVEC = _mm_xor_ps(DefaultValue, _mm_and_ps(NonZeroMask, _mm_xor_ps(NormalizedVector, DefaultValue)));
//	}
//
//	void ToMatrixInternal(__m128& OutDiagonals, __m128& OutAdds, __m128& OutSubtracts) const
//	{
//		const __m128 RotationX2Y2Z2 = _mm_add_ps(Rotation.DXVEC, Rotation.DXVEC);	// x2, y2, z2
//		const __m128 RotationXX2YY2ZZ2 = _mm_mul_ps(RotationX2Y2Z2, Rotation.DXVEC);	// xx2, yy2, zz2		
//
//		const __m128 yy2_xx2_xx2 = _mm_shuffle_ps(RotationXX2YY2ZZ2, RotationXX2YY2ZZ2, _MM_SHUFFLE(0, 0, 0, 1));
//		const __m128 zz2_zz2_yy2 = _mm_shuffle_ps(RotationXX2YY2ZZ2, RotationXX2YY2ZZ2, _MM_SHUFFLE(0, 1, 2, 2));
//		const __m128 DiagonalSum = _mm_add_ps(yy2_xx2_xx2, zz2_zz2_yy2);
//		const __m128 Diagonals = _mm_sub_ps(float4::ONE.DXVEC, DiagonalSum);
//		OutDiagonals = _mm_mul_ps(Diagonals, Scale.DXVEC);
//
//		const __m128 x_y_x = _mm_shuffle_ps(Rotation.DXVEC, Rotation.DXVEC, _MM_SHUFFLE(0, 0, 1, 0)); // 1, 2, 2, 0
//		const __m128 y2_z2_z2 = _mm_shuffle_ps(RotationX2Y2Z2, RotationX2Y2Z2, _MM_SHUFFLE(0, 2, 2, 1));
//		const __m128 RotBase = _mm_mul_ps(x_y_x, y2_z2_z2);
//
//		const __m128 w_w_w = _mm_shuffle_ps(Rotation.DXVEC, Rotation.DXVEC, _MM_SHUFFLE(3, 3, 3, 3));
//		const __m128 z2_x2_y2 = _mm_shuffle_ps(RotationX2Y2Z2, RotationX2Y2Z2, _MM_SHUFFLE(0, 1, 0, 2));
//		const __m128 RotOffset = _mm_mul_ps(w_w_w, z2_x2_y2);
//
//		const __m128 Adds = _mm_add_ps(RotBase, RotOffset);
//		OutAdds = _mm_mul_ps(Adds, Scale.DXVEC);
//		const __m128 Scale3DYZXW = _mm_shuffle_ps(Scale.DXVEC, Scale.DXVEC, _MM_SHUFFLE(3, 0, 2, 1));
//		const __m128 Subtracts = _mm_sub_ps(RotBase, RotOffset);
//		OutSubtracts = _mm_mul_ps(Subtracts, Scale3DYZXW);
//	}
//
//	WMATRIX ToMatrixWithScale()
//	{
//		WMATRIX OutMatrix;
//		__m128 DiagonalsXYZ;
//		__m128 Adds;
//		__m128 Subtracts;
//
//		ToMatrixInternal(DiagonalsXYZ, Adds, Subtracts);
//		union { __m128 v; __m128i i; } tmp;
//		tmp.i = _mm_setr_epi32((unsigned int)0xffffffff, (unsigned int)0xffffffff, (unsigned int)0xffffffff, (unsigned int)0x00000000);
//		const __m128 DiagonalsXYZ_W0 = _mm_and_ps(DiagonalsXYZ, tmp.v);
//
//		const __m128 AddX_DC_DiagX_DC = _mm_shuffle_ps(Adds, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 0, 0, 0));
//		const __m128 SubZ_DC_DiagW_DC = _mm_shuffle_ps(Subtracts, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 3, 0, 2));
//		const __m128 Row0 = _mm_shuffle_ps(AddX_DC_DiagX_DC, SubZ_DC_DiagW_DC, _MM_SHUFFLE(2, 0, 0, 2));
//
//		// OutMatrix.M[1][0] = (xy2 - wz2) * Scale.Y;             // Subtracts.X
//		// OutMatrix.M[1][1] = (1.0f - (xx2 + zz2)) * Scale.Y;    // Diagonal.Y
//		// OutMatrix.M[1][2] = (yz2 + wx2) * Scale.Y;             // Adds.Y
//		// OutMatrix.M[1][3] = 0.0f;                            // DiagonalsXYZ_W0.W
//		const __m128 SubX_DC_DiagY_DC = _mm_shuffle_ps(Subtracts, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 1, 0, 0));
//		const __m128 AddY_DC_DiagW_DC = _mm_shuffle_ps(Adds, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 3, 0, 1));
//		const __m128 Row1 = _mm_shuffle_ps(SubX_DC_DiagY_DC, AddY_DC_DiagW_DC, _MM_SHUFFLE(2, 0, 2, 0));
//
//		// OutMatrix.M[2][0] = (xz2 + wy2) * Scale.Z;             // Adds.Z
//		// OutMatrix.M[2][1] = (yz2 - wx2) * Scale.Z;             // Subtracts.Y
//		// OutMatrix.M[2][2] = (1.0f - (xx2 + yy2)) * Scale.Z;    // Diagonals.Z
//		// OutMatrix.M[2][3] = 0.0f;                              // DiagonalsXYZ_W0.W
//		const __m128 AddZ_DC_SubY_DC = _mm_shuffle_ps(Adds, Subtracts, _MM_SHUFFLE(0, 1, 0, 2));
//		const __m128 Row2 = _mm_shuffle_ps(AddZ_DC_SubY_DC, DiagonalsXYZ_W0, _MM_SHUFFLE(3, 2, 2, 0));
//
//		_mm_store_ps(&(OutMatrix.Arr2D[0][0]), Row0);
//		_mm_store_ps(&(OutMatrix.Arr2D[1][0]), Row1);
//		_mm_store_ps(&(OutMatrix.Arr2D[2][0]), Row2);
//
//		__m128 Temp1 = _mm_movehl_ps(float4::ONE.DXVEC, Translation.DXVEC);
//
//		const __m128 Row3 = _mm_shuffle_ps(Translation.DXVEC, Temp1, _MM_SHUFFLE(3, 0, 1, 0));
//		_mm_store_ps(&(OutMatrix.Arr2D[3][0]), Row3);
//
//		return OutMatrix;
//	}
//
//	void Reset()
//	{
//		Scale = float4::ONE;
//		Rotation = float4::ZERO;
//		Translation = float4::ZERO;
//
//		Offset.IDEN();
//	}
//
//	JointPos()
//	{
//		Scale = float4::ONE;
//		Rotation = float4::ZERO;
//		Translation = float4::ZERO;
//
//		Offset.IDEN();
//	}
//};
//
//struct Bone
//{
//	WGAMESTRING Name;
//
//	unsigned int Flags;
//	int NumChildren;
//	int Index;
//	int ParentIndex;
//	JointPos BonePos;
//
//	Bone()
//	{
//		Name = L"";
//		Flags = 0;
//		NumChildren = 0;
//		Index = -1;
//		ParentIndex = 0;
//		BonePos.Reset();
//	}
//};
//
//// 클러스터를 모아놓는다.
//class ClusterData
//{
//public:
//	fbxsdk::FbxCluster* m_Cluster;
//	fbxsdk::FbxMesh* m_Mesh;
//	WGAMESTRING LinkName;
//};
//
//enum class FbxImportType
//{
//	Failed,
//	Geometry,
//	Deformers,
//	Otherwise
//};
//
//
//class WMESH;
//class WVBBUFFER;
//class WVBBUFFER;
//class WRenderTarget;
//class WFbxEx : public WFILEMGR<WFbxEx>
//{
//public:
//	static WPTR<WFbxEx> Load(const WGAMEFILE& _File, float4 _Angle = float4::ZERO)
//	{
//		WPTR<WFbxEx> Res = CreateToInsertToFile(_File.FullPath());
//		Res->Load(_Angle);
//		return Res;
//	}
//
//
//public:
//	bool IsMesh();
//	bool IsSkeleton();
//	bool IsAnimation();
//
//private:
//	fbxsdk::FbxManager* m_pFbxManager; // 가장 기본이 되는 fbx 시스템의 권한.
//	fbxsdk::FbxScene* m_pFbxScene; // 3d맥스 편집에서 가장 기본적인 씬을 정의하는 녀석.
//	fbxsdk::FbxNode* m_pFbxRootNode;
//
//	fbxsdk::FbxAMatrix m_AxisConversionMatrix;
//	fbxsdk::FbxAMatrix m_JointPostConversionMatrix;
//	fbxsdk::FbxVector4 m_ModifyRotationAxis;
//
//	FbxImportType m_ImportType;
//	WFbxExSceneInfo m_SceneInfo;
//
//	std::map<int, std::vector<ClusterData>> m_mapClusterData;
//	std::map<int, DRAWSET*> m_mapDrawsets;
//
//	std::vector<Bone> m_vecRefBones;
//
//public:
//	std::vector<Bone>& AllBoneData()
//	{
//		return m_vecRefBones;
//	}
//
//private:
//	bool ImportScene();
//	void ConvertScene();
//	void ImportSceneInfo();
//	void ImportCluster();
//	void ImportControlPoints();
//	void ImportBone();
//	void LoadSkinAndCluster();
//	void DrawSetMeshesCreate();
//
//private:
//	fbxsdk::FbxNode* RecursiveFindParentLodGroup(fbxsdk::FbxNode* parentNode);
//	fbxsdk::FbxNode* FindLODGroupNode(fbxsdk::FbxNode* NodeLodGroup, int LodIndex, fbxsdk::FbxNode* NodeToFind = nullptr);
//	fbxsdk::FbxNode* RecursiveGetFirstMeshNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNode* NodeToFind = nullptr);
//	void TraverseHierarchyNodeRecursively(WFbxExSceneInfo& SceneInfo, fbxsdk::FbxNode* ParentNode, WFbxExNodeInfo& ParentInfo);
//	fbxsdk::FbxAMatrix ComputeTotalMatrix(fbxsdk::FbxNode* Node);
//	bool IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix);
//	void DrawSetMaterialSetting(fbxsdk::FbxNode* _Node, DRAWSET* _DrawData);
//	float4 MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName);
//	float MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);
//	WGAMESTRING MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);
//	void LoadUv(fbxsdk::FbxMesh* _Mesh, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//	void LoadNormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//	void LoadTangent(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//	void LoadBinormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<VTX3DMESHIN>& _ArrVtx, int VtxId, int _Index);
//	void DrawSetMeshCreate(DRAWSET* _DrawData);
//	void LoadAnimationVertexData(DRAWSET* _DrawData, const std::vector<ClusterData>& vecClusterData);
//	void CalAnimationVertexData(DRAWSET* _DrawData);
//	void DrawSetWeightAndIndexSetting(DRAWSET* _DrawSet, fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxCluster* _Cluster, int _BoneIndex);
//	Bone* FindBone(const WGAMESTRING& _boneName);
//
//private:
//	static bool RetrievePoseFromBindPose(fbxsdk::FbxScene* pScene, const std::vector<fbxsdk::FbxNode*>& NodeArray, fbxsdk::FbxArray<fbxsdk::FbxPose*>& PoseArray);
//	static void BuildSkeletonSystem(fbxsdk::FbxScene* pScene, std::vector<fbxsdk::FbxCluster*>& ClusterArray, std::vector<fbxsdk::FbxNode*>& OutSortedLinks);
//	static fbxsdk::FbxNode* GetRootSkeleton(fbxsdk::FbxScene* pScene, fbxsdk::FbxNode* Link);
//	static void RecursiveBuildSkeleton(fbxsdk::FbxNode* Link, std::vector<fbxsdk::FbxNode*>& OutSortedLinks);
//	static bool IsBone(fbxsdk::FbxNode* Link);
//	static bool IsNull(fbxsdk::FbxNode* Link);
//
//public:
//	void CalWFbxExBoneFrameTransMatrix(WPTR<WFbxEx> _Fbx);
//
//	int GetDrawSetCount();
//	DRAWSET* GetDrawSet(int LodLevel);
//	size_t GetBoneCount();
//	Bone* FindBone(const int Index);
//	WGAMESTRING GetMeshNameByIndex(const int Index);
//	int GetFbxMeshCount();
//public:
//	std::vector<WFbxExAniData> m_UserAniData; // 애니메이션 
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
//public:
//	WFbxEx();
//	~WFbxEx();
//
//public:
//	void Load(float4 modifyRotationAxis = float4::ZERO);
//	void LoadUserFormat(const WGAMESTRING& _AniName, const WGAMESTRING& _MainFBXName);
//	void SaveUserFormat(const WGAMESTRING& _AniName, const WGAMESTRING& _MainFBXName);
//
//public:
//	WFbxExAniData* FindAniData(const int _Index)
//	{
//		if (m_UserAniData.size() < _Index)
//		{
//			return nullptr;
//		}
//
//		return &m_UserAniData[_Index];
//	}
//
//private:
//	void AniCheck();
//
//
//	static WMATRIX FbxMatToWMATRIX(const fbxsdk::FbxAMatrix& _BaseTrans);
//	static float4 FbxVecTofloat4(const fbxsdk::FbxVector4& _BaseVector);
//	static float4 FbxVecToTransform(const fbxsdk::FbxVector4& _BaseVector);
//	static float4 FbxQuaternionTofloat4(const fbxsdk::FbxQuaternion& _BaseQ);
//
//private:
//	void ProcessAnimationLoad(WPTR<WFbxEx> _Fbx, fbxsdk::FbxNode* pNode);
//	void ProcessAnimationCheckState(WPTR<WFbxEx> _Fbx);
//	void MeshAnimationLoad(WPTR<WFbxEx> _Fbx, fbxsdk::FbxNode* pNode);
//	fbxsdk::FbxAMatrix GetGeometryTransformation(fbxsdk::FbxNode* pNode);
//
//	WVECTOR ReadUv(FbxMesh* mesh, int ControlPointIndex, int vertexCounter);
//};
//
