// Dlg0.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "Dlg0.h"


// Dlg0 대화 상자

IMPLEMENT_DYNAMIC(Dlg0, CDialogEx)

Dlg0::Dlg0(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG0, pParent)
{

}

Dlg0::~Dlg0()
{
}

void Dlg0::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BD_VIEW_LAYER_LIST, m_ChkList);
}


BEGIN_MESSAGE_MAP(Dlg0, CDialogEx)
	ON_LBN_SELCHANGE(IDC_BD_VIEW_LAYER_LIST, &Dlg0::OnLbnSelchangeBdViewLayerList)
	ON_CBN_SELCHANGE(IDC_NEW_BD_NAME_COMBO, &Dlg0::OnCbnSelchangeNewBdNameCombo)
	ON_BN_CLICKED(IDC_BD_UPDATE_BTN, &Dlg0::OnBnClickedBdUpdateBtn)
END_MESSAGE_MAP()


// Dlg0 메시지 처리기


BOOL Dlg0::OnInitDialog()
{
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CDialogEx::OnInitDialog();

	SetIcon(0, TRUE);
	SetIcon(0, FALSE);

	//m_ChkList.SubclassDlgItem(IDC_BD_VIEW_LAYER_LIST, this);
	m_ChkList.InsertString(0, L"0");
	m_ChkList.InsertString(1, L"1");
	m_ChkList.InsertString(2, L"2");
	m_ChkList.InsertString(3, L"3");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Dlg0::OnLbnSelchangeBdViewLayerList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg0::OnCbnSelchangeNewBdNameCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg0::OnBnClickedBdUpdateBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//void StaticView::OnBnClickedStaticsavebtn() // 세이브버튼
//{
//	UpdateData(TRUE);
//
//	if (0 == WTOOLMAPSCENE::Inst->m_StaticActorData.size())
//	{
//		return;
//	}
//
//	WGAMEDIRECTORY DIC;
//	DIC.MoveParent(L"Wah3DX");
//	DIC.Move(L"RES");
//	DIC.Move(L"STATICMESH");
//	DIC.Move(m_ACTORIDXEDITS.GetString(), true);
//
//
//	CString FBXNAME;
//	m_StaticSetListCtrl.GetText(m_StaticSetListCtrl.GetCurSel(), FBXNAME);
//	WGAMESTRING FILENAME = FBXNAME.GetString();
//	//FILENAME
//
//
//	FILENAME.ChangeStr(L".FBX", L".WFBXEX");
//	int Name = ActorNameReturn(FBXNAME.GetString());
//	int Num = _ttoi(m_ACTORIDXEDITS);
//	WGAMEFILE SaveFile = WGAMEFILE(DIC.PlusFileName(FILENAME), L"wb");
//
//
//
//	for (auto& Var : WTOOLMAPSCENE::Inst->m_StaticActorData)
//	{
//		if (Var.second.m_ActorType.x != Name || Var.second.m_MeshData.m_Index.x != Num)
//		{
//			int a = 0;
//			continue;
//		}
//
//		SaveFile.SaveValue(Var.second.m_ActorType);
//		SaveFile.SaveValue(Var.second.m_MeshData.m_Index);
//		SaveFile.SaveValue(Var.second.m_MeshData.m_Scale);
//		SaveFile.SaveValue(Var.second.m_MeshData.m_Rot);
//		SaveFile.SaveValue(Var.second.m_MeshData.m_Pos);
//
//	}
//
//
//	UpdateData(FALSE);
//}

//
//void StaticView::OnBnClickedStaticmodifybtn() // 트랜스폼수정버튼  
//{
//	UpdateData(TRUE);
//
//	// 벡터로 넣어주기 위해서 float으로 변환한다. 
//	float SCALEX = (float)_wtof(m_StaticScaleXEditV);
//	float SCALEY = (float)_wtof(m_StaticScaleYEditV);
//	float SCALEZ = (float)_wtof(m_StaticScaleZEditV);
//	float ROTX = (float)_wtof(m_StaticRotXEditV);
//	float ROTY = (float)_wtof(m_StaticRotYEditV);
//	float ROTZ = (float)_wtof(m_StaticRotZEditV);
//	float POSX = (float)_wtof(m_StaticPosXEditV);
//	float POSY = (float)_wtof(m_StaticPosYEditV);
//	float POSZ = (float)_wtof(m_StaticPosZEditV);
//
//	// 리스트에서 커서에 해당하는 이름을 가지고 있다. 
//	int SELECTONE = m_StaticSetListCtrl.GetCurSel();
//	if (-1 == SELECTONE)
//	{
//		return;
//	}
//
//	CString FBXNAME;
//	m_StaticSetListCtrl.GetText(SELECTONE, FBXNAME);
//	// 인덱스 컨트롤에서 값을 가져온 후 m_ACTORIDXEDITS	
//	// 그것을 변수에 담아서 맞는지 확인한다. 
//
//	WGAMESTRING Name = FBXNAME.GetString();
//
//	m_ActorName = ActorNameReturn(Name);
//
//	CString StrNumber;
//
//	// 찾기 
//	for (auto& _VAR : WTOOLMAPSCENE::Inst->m_StaticActorData)
//	{
//		StrNumber.Format(_T("%d"), _VAR.second.m_MeshData.m_Index.x);
//		// 데이터들 중에서 현재 커서에 해당하는 이름과 비교해서 
//		if (_VAR.second.m_ActorType.x == m_ActorName && StrNumber == m_ACTORIDXEDITS /*&& _VAR.second.m_MeshData.m_Index.x ==*/)
//		{
//			// 데이터의 값을 수정한다. 
//			_VAR.second.m_MeshData.m_Scale = WVECTOR({ SCALEX, SCALEY, SCALEZ });
//			_VAR.second.m_MeshData.m_Rot = WVECTOR({ ROTX, ROTY, ROTZ });
//			_VAR.second.m_MeshData.m_Pos = WVECTOR({ POSX, POSY, POSZ });
//			// 액터들의 값을 수정한다. 
//			_VAR.first->TRANS()->WSCALE({ SCALEX, SCALEY, SCALEZ });
//			_VAR.first->TRANS()->WROT({ ROTX, ROTY, ROTZ });
//			_VAR.first->TRANS()->WPOS({ POSX, POSY, POSZ });
//		}
//	}
//
//	m_ACTORIDXEDITC.SetWindowTextW(m_ACTORIDXEDITS);
//
//	// 수정된 값들이 에디트박스에 그대로 출력된다. 
//	m_StaticScaleXEditC.SetWindowTextW(m_StaticScaleXEditV);
//	m_StaticScaleYEditC.SetWindowTextW(m_StaticScaleYEditV);
//	m_StaticScaleZEditC.SetWindowTextW(m_StaticScaleZEditV);
//	m_StaticRotXEditC.SetWindowTextW(m_StaticRotXEditV);
//	m_StaticRotYEditC.SetWindowTextW(m_StaticRotYEditV);
//	m_StaticRotZEditC.SetWindowTextW(m_StaticRotZEditV);
//	m_StaticPosXEditC.SetWindowTextW(m_StaticPosXEditV);
//	m_StaticPosYEditC.SetWindowTextW(m_StaticPosYEditV);
//	m_StaticPosZEditC.SetWindowTextW(m_StaticPosZEditV);
//
//
//	UpdateData(FALSE);
//}

//
//void StaticView::OnBnClickedStaticreleasebtn() // 릴리즈버튼
//{
//	UpdateData(TRUE);
//	int CURIDX = m_StaticSetListCtrl.GetCurSel();
//	if (-1 == CURIDX)
//	{
//		return;
//	}
//	CString FBXNAME;
//	m_StaticSetListCtrl.GetText(CURIDX, FBXNAME);
//	WTOOLMAPSCENE::Inst->DeleteStaticMesh(FBXNAME.GetString()); // Delete함수 있어야 합니다. 화면에서도 지워야 합니다. 
//	m_StaticSetListCtrl.DeleteString(CURIDX);
//	UpdateData(FALSE);
//}

//
//void StaticView::OnBnClickedStaticsetbtn() // 셋버튼
//{
//	UpdateData(TRUE);
//	int CURIDX = m_StaticLoadListCtrl.GetCurSel();
//	if (-1 == CURIDX)
//	{
//		return;
//	}
//	MeshActorData Data;
//	CString FBXNAME;
//	int MESHINDEX = (int)_wtof(m_ActorIndexCtrlS);
//	m_StaticLoadListCtrl.GetText(CURIDX, FBXNAME);
//	Data.m_ActorType.x = CURIDX;
//	Data.m_MeshData.m_Index.x = MESHINDEX;
//	// 꼭 필요한 함수입니다. 
//	WTOOLMAPSCENE::Inst->CreateStaticMesh(Data);
//	m_StaticSetListCtrl.AddString(FBXNAME);
//
//
//	UpdateData(FALSE);
//}
//

//
//void StaticView::OnBnClickedStaticloadbtn() // 시작로드버튼
//{
//	// 폴더 안의 모든 FBX를 로드한다. 
//	WGAMEDIRECTORY DIC;
//	DIC.MoveParent(L"Wah3DX");
//	DIC.Move(L"RES");
//	DIC.Move(L"STATICMESH");
//	auto FileList = DIC.DirAllFile(L"FBX");
//	for (auto& _File : FileList)
//	{
//		WGAMESTRING FILENAME = _File.FileName();
//		WGAMESTRING FullPath = _File.FullPath();
//		m_StaticLoadListCtrl.AddString(FILENAME);
//	}
//}



//
//for (auto& _VAR : WTOOLMAPSCENE::Inst->m_LightCreateMeshComData)
//{
//	if (_VAR.second.m_Type.x == SELECTONE)
//	{
//		_VAR.second.m_Scale = WVECTOR({ SCALEX, SCALEY, SCALEZ });
//		_VAR.second.m_Rot = WVECTOR({ ROTX, ROTY, ROTZ });
//		_VAR.second.m_Pos = WVECTOR({ POSX, POSY, POSZ });
//		_VAR.second.m_AmbColor = WVECTOR({ AMBX , AMBY, AMBZ });
//		_VAR.second.m_LightPower = WVECTOR({ POWERX, POWERY, POWERZ });
//		_VAR.second.m_SpecPow = WVECTOR({ POWX, POWY, POWZ });
//		_VAR.second.m_LightDir = WVECTOR({ DIRX, DIRY, DIRZ });
//		_VAR.second.m_LIghtDirInv = WVECTOR({ DIRINVX, DIRINVY, DIRINVZ });
//	}
//}


//
//void LIGHTVIEW::SaveLightSpec()
//{
//	UpdateData(TRUE);
//
//	if (0 == WTOOLMAPSCENE::Inst->m_LightCreateMeshComData.size())
//	{
//		return;
//	}
//
//	int SELECTONE = m_IdxComboEditC.GetCurSel();
//	if (-1 == SELECTONE)
//	{
//		return;
//	}
//
//	WGAMEDIRECTORY DIC;
//	DIC.MoveParent(L"Wah3DX");
//	DIC.Move(L"RES");
//	DIC.Move(L"LIGHT");
//	CString CNAME;
//	m_IdxComboEditC.GetLBText(SELECTONE, CNAME);
//	WGAMESTRING FILENAME = CNAME.GetString();
//	FILENAME += L".LIGHTSAVE";
//	WGAMEFILE SaveFile = WGAMEFILE(DIC.PlusFileName(FILENAME), L"wb");
//
//	for (auto& Var : WTOOLMAPSCENE::Inst->m_LightCreateMeshComData)
//	{
//		SaveFile.SaveValue(Var.second.m_Type);
//		SaveFile.SaveValue(Var.second.m_Scale);
//		SaveFile.SaveValue(Var.second.m_Rot);
//		SaveFile.SaveValue(Var.second.m_Pos);
//		SaveFile.SaveValue(Var.second.m_AmbColor);
//		SaveFile.SaveValue(Var.second.m_LightPower);
//		SaveFile.SaveValue(Var.second.m_SpecPow);
//		SaveFile.SaveValue(Var.second.m_LightDir);
//		SaveFile.SaveValue(Var.second.m_LIghtDirInv);
//	}
//
//	UpdateData(FALSE);
//}


//std::map<WGAMEACTOR*, MeshCreateData> m_StaticMeshComData;
//std::map<WGAMEACTOR*, MeshActorData> m_StaticActorData;
//std::vector<MeshCreateData> m_AllMeshData;
//WPTR<WGAMEACTOR> NewActor;
//std::map<WGAMEACTOR*, MeshCreateData> m_AniMeshComData;
//std::map<int, LightCreateData> m_LightCreateMeshComData;
//std::map<int, WPTR<WLight>> m_LightMeshComData;



//
//void AniView::OnBnClickedAniloadbtn()
//{
//	// 폴더 안의 모든 FBX를 로드한다. 
//	WGAMEDIRECTORY DIC;
//	DIC.MoveParent(L"Wah3DX");
//	DIC.Move(L"RES");
//	DIC.Move(L"MESH");
//	auto FileList = DIC.DirAllDic(L"");
//	for (auto& _File : FileList)
//	{
//		WGAMESTRING FILENAME = _File.FileName();
//		WGAMESTRING FullPath = _File.FullPath();
//		m_MainFbxListCtrl.AddString(FILENAME);
//	}
//}
//
//
//void AniView::OnBnClickedAnibrowsebtn()
//{
//	UpdateData(TRUE);
//	// 시작할 때 지운다. 
//	m_AniFbxListCtrl.ResetContent();
//	CString FBXNAME;
//	int CURIDX = m_MainFbxListCtrl.GetCurSel();
//	if (-1 == CURIDX)
//	{
//		return;
//	}
//	m_MainFbxListCtrl.GetText(CURIDX, FBXNAME);
//	WGAMEDIRECTORY DIC;
//	DIC.MoveParent(L"Wah3DX");
//	DIC.Move(L"RES");
//	DIC.Move(L"MESH");
//	DIC.Move(FBXNAME.GetString());
//	auto FileList = DIC.DirAllFile();
//	for (auto& _File : FileList)
//	{
//		WGAMESTRING FILENAME = _File.FileName();
//		WGAMESTRING FullPath = _File.FullPath();
//		m_AniFbxListCtrl.AddString(FILENAME);
//	}
//	UpdateData(FALSE);
//}