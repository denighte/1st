
// GraphMainDlg.h : header file
//

#pragma once
#include "afxmaskededit.h"
#include "GraphClass.h"
#include "Date.h"
#define M_PI 3.14159265358979323846

// CGraphMainDlg dialog
class CGraphMainDlg : public CDialogEx
{
// Construction
public:
	CGraphMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPHAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedButtonexit();
	afx_msg void OnBnClickedButtoncalc();
private:
	Date CurrentDate;
	CMFCMaskedEdit BirthEdit;
	CMFCMaskedEdit CalcEdit;
	BOOL BCBirth;
	BOOL BCCalc;
	BOOL OnClickedCalc;

	void DrawBiorithms(GPaint & Obj, int DateDelta);
	int GetDate(Date& BirthDate, Date& CalcDate);
	void DrawInfoBox(CPaintDC & Obj, RECT* WndSize, int DateDelta);
public:
	afx_msg void OnBnClickedCheckBirth();
	afx_msg void OnBnClickedCheckCalc();
};
