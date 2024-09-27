// Dlg3.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "Dlg3.h"


// Dlg3 대화 상자

IMPLEMENT_DYNAMIC(Dlg3, CDialogEx)

Dlg3::Dlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG3, pParent)
	, m_MapSaveValue(_T(""))
	, m_MapSelValue(_T(""))
{

}

Dlg3::~Dlg3()
{
}

void Dlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TILE_GRID_COMBO, m_ComboBoxList);
	DDX_Control(pDX, IDC_LISTMAPSAVE, m_MapSaveListCtrl);
	DDX_Control(pDX, IDC_LISTMAPSELECT, m_MapSelListCtrl);
	DDX_LBString(pDX, IDC_LISTMAPSAVE, m_MapSaveValue);
	DDX_LBString(pDX, IDC_LISTMAPSELECT, m_MapSelValue);
}


BEGIN_MESSAGE_MAP(Dlg3, CDialogEx)
	ON_CBN_SELCHANGE(IDC_TILE_GRID_COMBO, &Dlg3::OnCbnSelchangeTileGridCombo)
	ON_BN_CLICKED(IDC_TILE_SEL_BTN, &Dlg3::OnBnClickedTileSelBtn)
	ON_BN_CLICKED(IDC_BUTTONSAVE, &Dlg3::OnBnClickedButtonsave)
	ON_LBN_SELCHANGE(IDC_LISTMAPSAVE, &Dlg3::OnLbnSelchangeListmapsave)
	ON_LBN_SELCHANGE(IDC_LISTMAPSELECT, &Dlg3::OnLbnSelchangeListmapselect)
END_MESSAGE_MAP()


// Dlg3 메시지 처리기


void Dlg3::OnCbnSelchangeTileGridCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}


BOOL Dlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetIcon(0, TRUE);
	SetIcon(0, FALSE);

	m_ComboBoxList.AddString(_T("BLUE"));
	m_ComboBoxList.AddString(_T("BROWN"));
	m_ComboBoxList.AddString(_T("DARK"));
	m_ComboBoxList.AddString(_T("EMERALD"));
	m_ComboBoxList.AddString(_T("MAGENTA"));
	m_ComboBoxList.AddString(_T("MAINMENU"));
	m_ComboBoxList.AddString(_T("MARKERINSTADEATH"));
	m_ComboBoxList.AddString(_T("NAVY"));
	m_ComboBoxList.AddString(_T("PURPLE"));
	m_ComboBoxList.AddString(_T("RED"));
	m_ComboBoxList.AddString(_T("SKYBLUE"));
	m_ComboBoxList.AddString(_T("TEXTCOLOR"));
	m_ComboBoxList.AddString(_T("WHITE"));



	// 콤보 박스에 항목이 1개 이상인 경우 첫번째 항목으로 선택
	if (m_ComboBoxList.GetCount() > 0)
	{
		m_ComboBoxList.SetCurSel(0);
	}
	int a = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Dlg3::OnBnClickedTileSelBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_ComboBoxList.GetCurSel();
	// 선택 Focus가 없어진 경우에는 -1을 반환

	if (nCurSel >= 0)
	{
		CString StrText = _T("");
		StrText.Format(_T("현재 선택한 콤보 박스의 인덱스는 %d 입니다."), nCurSel);
		MessageBox(StrText);
		m_bDlg3Trigger = true;
	}

	//LevelDesignTool::GetMainMapToolEditor()->TileTrigger(m_bDlg3Trigger); 
	//LevelDesignTool::GetMainMapToolEditor()->TileInit(nCurSel);


}


void Dlg3::OnBnClickedButtonsave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

//
//void WRightView::UserInit()
//{
//	UpdateData(TRUE);
//	MonsterList.AddString(L"WBIGSKUILLMONSTER");
//	MonsterList.AddString(L"WLITTLEGHOST");
//	MonsterList.AddString(L"WBANSHMONSTER");
//	MonsterList.AddString(L"WSKELDOG");
//	MonsterList.AddString(L"WMINOTAURS");
//	MonsterList.AddString(L"WSNAKE");
//	MonsterList.AddString(L"WWYVERN");
//	MonsterList.AddString(L"WGIANTBAT");
//
//
//	UpdateData(FALSE);
//
//	m_MapList.AddString(L"00");
//	m_MapList.AddString(L"01");
//	m_MapList.AddString(L"02");
//	m_MapList.AddString(L"03");
//	m_MapList.AddString(L"04");
//	m_MapList.AddString(L"05");
//	m_MapList.AddString(L"06");
//	m_MapList.AddString(L"07");
//	m_MapList.AddString(L"08");
//	m_MapList.AddString(L"09");
//	m_MapList.AddString(L"10");
//	m_MapList.AddString(L"11");
//	m_MapList.AddString(L"12");
//	m_MapList.AddString(L"13");
//	m_MapList.AddString(L"14");
//	m_MapList.AddString(L"15");
//	m_MapList.AddString(L"16");
//	m_MapList.AddString(L"17");
//	m_MapList.AddString(L"18");
//	m_MapList.AddString(L"19");
//	m_MapList.AddString(L"20");
//	m_MapList.AddString(L"21");
//	m_MapList.AddString(L"22");
//	m_MapList.AddString(L"23");
//	m_MapList.AddString(L"24");
//	m_MapList.AddString(L"25");
//	UpdateData(FALSE);
//}
//
//
//void WRightView::OnLbnSelchangeList1()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData(TRUE);
//	SelectMonster = MonsterList.GetCurSel();
//	UpdateData(FALSE);
//
//}
//
//
//
//void WRightView::OnLbnSelchangeMaplist()
//{
//	UpdateData(TRUE);
//
//
//	WTOOLMAPSCENE::ClearMonster();
//
//	WGAMEDIRECTORY Dic;
//
//	Dic.MoveParent(L"WDBDX");
//	Dic.Move(L"RES");
//	Dic.Move(L"DATA");
//
//	CString  MapName;
//	m_MapList.GetText(m_MapList.GetCurSel(), MapName);
//
//	WGAMESTRING Str = MapName.GetString();
//
//	Str += L".DataSave";
//
//	// 클래스화의 장점이다.
//	WGAMEFILE LoadFile = WGAMEFILE(Dic.PlusFileName(Str), L"rb");
//
//	number = MapName.GetString();
//
//	if (false == LoadFile.IsOpen())
//	{
//		return;
//	}
//
//
//	int Size = 0;
//	MONSTERDATA Data;
//	int LoadSize = sizeof(WVECTOR);
//
//
//	LoadFile.Load(Size);
//
//	for (size_t i = 0; i < Size; i++)
//	{
//		LoadFile.Load(Data);
//
//		WTOOLMAPSCENE::SCENECOM()->CreateMonster(Data.Type, Data.Pos);
//	}
//
//
//	UpdateData(FALSE);
//}
//
//
//
//void WRightView::OnBnClickedSave()
//{
//
//	if (0 == WTOOLMAPSCENE::m_MonsterData.size())
//	{
//		return;
//	}
//
//	if (-1 == m_MapList.GetCurSel())
//	{
//		AMSG(L"맵을 선택해야 세이브가 됩니다.");
//		return;
//	}
//
//	UpdateData(true);
//
//	CString MapName;
//	m_MapList.GetText(m_MapList.GetCurSel(), MapName);
//
//	WGAMESTRING Str = MapName.GetString();
//	Str += L".DataSave";
//
//	WGAMEDIRECTORY Dic;
//	Dic.MoveParent(L"WDBDX");
//	Dic.Move(L"RES");
//	Dic.Move(L"DATA");
//
//	WGAMEFILE SaveFile = WGAMEFILE(Dic.PlusFileName(Str), L"wb");
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	// 빌드 상황에 따라서 크기가 바뀌는 녀석은 굉장히 위험하다.
//	SaveFile.Save((int)WTOOLMAPSCENE::m_MonsterData.size());
//	for (auto& Var : WTOOLMAPSCENE::m_MonsterData)
//	{
//		SaveFile.Save(Var.second);
//	}
//	// HTOOLMAPSCENE::m_MonsterData;
//	// HTOOLMAPSCENE::m_MonsterActor;
//
//	UpdateData(false);
//}
//
//
//void WRightView::OnBnClickedClear()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	WTOOLMAPSCENE::ClearMonster();
//}
//
//
//
//
//void WRightView::OnBnClickedLoad()
//{
//	WTOOLMAPSCENE::ClearMonster();
//
//	WGAMEDIRECTORY Dic;
//
//	Dic.MoveParent(L"WDBDX");
//	Dic.Move(L"RES");
//	Dic.Move(L"DATA");
//
//	// 클래스화의 장점이다.
//	WGAMEFILE LoadFile = WGAMEFILE(Dic.PlusFileName(L"TestMapData.DataSave"), L"rb");
//
//	int Size = 0;
//	MONSTERDATA Data;
//	int LoadSize = sizeof(WVECTOR);
//
//
//	LoadFile.Load(Size);
//
//	for (size_t i = 0; i < Size; i++)
//	{
//		LoadFile.Load(Data);
//
//		WTOOLMAPSCENE::SCENECOM()->CreateMonster(Data.Type, Data.Pos);
//	}
//
//
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}
//
//
//void WRightView::OnBnClickedMapsave()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	if (number == L"")
//	{
//		return;
//	}
//
//	WGAMEDIRECTORY Dic;
//
//	Dic.MoveParent(L"WDBDX");
//	Dic.Move(L"RES");
//	Dic.Move(L"DATA");
//
//	SAVEMAPDATA SMD = WGAMEMAP::AutoMapDataTEST(number);
//
//	WGAMEFILE SaveFile = WGAMEFILE(Dic.PlusFileName(SMD.BackSprite), L"wb");
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	// 빌드 상황에 따라서 크기가 바뀌는 녀석은 굉장히 위험하다.
//	SaveFile.Save(SMD);
//
//
//}
//


void Dlg3::OnLbnSelchangeListmapsave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg3::OnLbnSelchangeListmapselect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
