
// CMainDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CounterManager.h"
#include "CycleList.h"


// CMainDlg dialog
class CMainDlg : public CDialogEx
{
	// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor
	~CMainDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRACTICEPROJECT_1_DIALOG };
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStartGame();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()



private:
	//constants
	CONST POINT PARTICIPANTS_START_POINT = { 0, 600 };
	CONST POINT POINTER_VERTEX[3] = { { 0, 500 },{ -20, 480 },{ 20, 480 } };
	static CONST INT NUMBER_OF_PARTICIPANTS = 6;
private:
	//Dialog data
	int cxClient_;
	int cyClient_;
	bool game_state_;
	bool participants_state_[NUMBER_OF_PARTICIPANTS];

	Counter RandomCounter_;
	CycleList<Student> participants_;
	CounterManager* manager_;
	Student current_participant_;
private:
	//Dialog service functions
	void SetIsotropic(CDC& dc, int cxClient, int cyClient);
	void RotatePoint(POINT pt[], int iNum, int iAngle);
	void DrawPointer(CDC& dc, int Angle);
	void DrawParticipantsCircle(CDC& dc);


};
