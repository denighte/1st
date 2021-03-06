
// UI-Project-001Dlg.h : ���� ���������
//

#pragma once
#include <sstream>
#include <string>
#include "afxwin.h"
#include "GraphFuncs.h"
#include "DCGraphAdapter.h"


// ���������� ���� CMainDlg
class CMainDlg : public CDialogEx
{
// ��������
public:
	CMainDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UIPROJECT001_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void SetResult(std::complex<double> value);
	std::complex<double> GetComplex(CString& c);
	void CMainDlg::DataProcessing(char operation);
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();

	BOOL InfoUpdate;
	CString left_in; //������ ����������� �����
	CString right_in; //������ ����������� �����
	CEdit result;
//	CStatic mouseCoordinates;


	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeAnswer();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
