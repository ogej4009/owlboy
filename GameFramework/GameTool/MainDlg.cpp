// MainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "MainDlg.h"


// RView->MainDlg->Tab->Dlg0,1,2,3,4
#include "Dlg0.h"
#include "Dlg1.h"
#include "Dlg2.h"
#include "Dlg3.h"
#include "Dlg4.h"


// define MACRO
#define TAB_NUMBER_MIN 0
int TabCount = TAB_NUMBER_MIN;
#define TAB_NUMBER_MAX TabCount
#define TAB_NUMBER_PLUS_PLUS TabCount++

#define SAFE_DELETE(p) {if(p){delete p; p = NULL;}}


// MainDlg 대화 상자

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RView, pParent)
{
	/*
	dlg0 = NULL;
	dlg1 = NULL;
	dlg2 = NULL;
	dlg3 = NULL;
	*/
	m_pWndShow = nullptr;
}

MainDlg::~MainDlg()
{
	/*
	SAFE_DELETE(dlg0);
	SAFE_DELETE(dlg1);
	SAFE_DELETE(dlg2);
	SAFE_DELETE(dlg3);
	*/
	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		delete ArrDlg[i];
	}
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &MainDlg::OnSelchangeTab1)

END_MESSAGE_MAP()


// MainDlg 메시지 처리기


BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_TabCtrl.DeleteAllItems();

	/*
		CRect rect;
		dlg0 = new Dlg0;
		dlg0->Create(IDD_DLG0, &m_TabCtl);
		dlg0->GetWindowRect(&rect);
		dlg0->MoveWindow(10, 30, rect.Width(), rect.Height());
	*/
	CreateNewDlg<Dlg0>(IDD_DLG0);
	CreateNewDlg<Dlg1>(IDD_DLG1);
	CreateNewDlg<Dlg2>(IDD_DLG2);
	CreateNewDlg<Dlg3>(IDD_DLG3);
	CreateNewDlg<Dlg4>(IDD_DLG4);

	m_TabCtrl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Backdrops");
	m_TabCtrl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Sprites");
	m_TabCtrl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Layers");
	m_TabCtrl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Collisions");
	m_TabCtrl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Properties");


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MainDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pWndShow != NULL)
	{
		m_pWndShow->ShowWindow(SW_HIDE);
		m_pWndShow = NULL;
	}

	UpdateData(TRUE);

	int SIdx = m_TabCtrl.GetCurSel();

	WCHAR ArrText[256];
	TCITEMW Item;
	Item.mask = TCIF_TEXT;
	Item.cchTextMax = 256;
	Item.pszText = ArrText;
	m_TabCtrl.GetItem(SIdx, &Item);

	if (TAB_NUMBER_MIN > SIdx || TAB_NUMBER_MAX < SIdx)
	{
		return;
	}

	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		ArrDlg[i]->ShowWindow(SW_HIDE);
	}

	ArrDlg[SIdx]->ShowWindow(SW_SHOW);

	//GameScene::ChangeScene(ArrText);

	UpdateData(FALSE);
	*pResult = 0;
}
