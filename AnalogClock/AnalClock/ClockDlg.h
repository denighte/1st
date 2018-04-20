
// ClockDlg.h : header file
//

#pragma once
#pragma warning(disable:4996)
#include "Time.h"
#define TWOPI (2 * 3.14159)
#define ID_TIMER 1

// ÑClockDlg dialog
class CClockDlg : public CDialogEx
{
// Construction
public:
	CClockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANALCLOCK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private:
	void SetIsotropic(CDC& hdc, int cxClient, int cyClient);
	void RotatePoint(POINT pt[], int iNum, int iAngle);
	void DrawClock(CDC& dc);
	void DrawHands(CDC& hdc, Time& datetime/*struct tm *datetime*/, BOOL bChange);

	int cxClient;
	int cyClient;
	Time dtPrevious;
	//BOOL bChange;
	//PAINTSTRUCT ps;
	//time_t lTime;

	//Time datetime;
	//struct tm *datetime;
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	//virtual BOOL PreTranslateMessage(MSG *pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
};
