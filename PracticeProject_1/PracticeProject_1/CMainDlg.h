
// CMainDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CounterManager.h"
#include "CycleList.h"
#include <experimental\filesystem>
#include <unordered_map>
#include "DefineList.h"
#include "ImageObject.h"

//DIALOG CONSTANTS

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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg LRESULT OnDetermineWinner(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()



private:
	//Dialog data
	int cxClient_;
	int cyClient_;
	bool first_OnPaint_;
	bool game_state_;  //the state of the game, if true - the game has started
	bool winner_state_; //true in case that the counter was over and winner was determined

	Counter RandomCounter_;			//random counter
	CycleList<Student> participants_;   //list of the students-participants
	std::unordered_map<std::wstring, ImageObject> dict_;
	CounterManager* manager_;		//counter manager

	Student current_participant_;  //the student pointed to by the counter
private:
	//Dialog service functions
	void CounterInit();
	void ResourcesInit(CDC& dc);

	void SetIsotropic(CDC& dc, int cxClient, int cyClient);
	void RotatePoint(POINT pt[], int iNum, int iAngle);
	void DrawPointer(CDC& dc, int Angle);
	void DrawParticipantsCircle(CDC& dc);
	void SelectCurrentParticipant(CDC& dc);
	void DrawAvatar(CDC& dc, int x, int y, const CString name);  // NOTE: out-of-date function, has to be removed
	void Playmp3();


};
