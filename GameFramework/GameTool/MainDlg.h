#pragma once
#include "afxdialogex.h"


// MainDlg 대화 상자

class MainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MainDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RView };
#endif


public:
	/*
	Dlg0* dlg0;
	Dlg1* dlg1;
	Dlg2* dlg2;
	Dlg3* dlg3;
	*/
	template<typename T>
	void CreateNewDlg(unsigned int _Id)
	{
		T* NewDlg = new T();
		NewDlg->Create(_Id, &m_TabCtrl);
		//NewDlg->ShowWindow(SW_HIDE);
		NewDlg->SetBackgroundColor(RGB(153, 200, 240));
		//NewDlg->SetWindowPos(nullptr, 4, 20, 500, 500, 0);
		NewDlg->SetWindowPos(nullptr, 4, 20, 500, 600, 0);

		ArrDlg.push_back(NewDlg);
	}
	std::vector<CDialogEx*> ArrDlg;

	CTabCtrl m_TabCtrl;
	CWnd* m_pWndShow;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};

