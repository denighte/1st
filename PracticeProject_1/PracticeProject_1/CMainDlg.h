
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
	CONST POINT PARTICIPANTS_START_POINT = { 0, 600 };   //point, where the first student is to be drawn
	CONST POINT POINTER_VERTEX[3] = { { 0, 500 },{ -20, 480 },{ 20, 480 } };   //array, wich specifies the pointer
	static CONST INT NUMBER_OF_PARTICIPANTS = 6;
	CONST INT ROTATE_ANGLE = 360 / NUMBER_OF_PARTICIPANTS;
private:
	//Dialog data
	int cxClient_;
	int cyClient_;
	bool game_state_;  //the state of the game, if true - the game has started
	bool participants_state_[NUMBER_OF_PARTICIPANTS];  //array, wich shows which participants were removed

	Counter RandomCounter_;			//random counter
	CycleList<Student> participants_;   //list of the students-participants
	CounterManager* manager_;		//counter manager
	Student current_participant_;  //the student pointed to by the counter
private:
	//Dialog service functions
	void SetIsotropic(CDC& dc, int cxClient, int cyClient);
	void RotatePoint(POINT pt[], int iNum, int iAngle);
	void DrawPointer(CDC& dc, int Angle);
	void DrawParticipantsCircle(CDC& dc);
	void SelectCurrentParticipant(CDC& dc);


};
