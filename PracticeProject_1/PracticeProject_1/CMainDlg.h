
// CMainDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CounterManager.h"
#include "CycleList.h"
#include <experimental\filesystem>
#include <unordered_map>
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
	DECLARE_MESSAGE_MAP()



private:
	//CONSTANTS
	static CONST INT POINTER_POINTS_NUMBER = 5;  //number of points in ARROWHEAD
	static CONST INT NUMBER_OF_PARTICIPANTS = 6;  //number of participants

	CONST POINT ARROWHEAD[POINTER_POINTS_NUMBER] = { { 0, 0 },{ -30, 230 },{ 0, 500 },{ 30, 230 },{ 0, 0 } };   //array, wich specifies the pointer
	CONST POINT PARTICIPANTS_START_POINT = { 0, 600 };   //point, where the first student is to be drawn
	CONST INT ROTATE_ANGLE = 360 / NUMBER_OF_PARTICIPANTS;

	const std::wstring RESOURCES_CURRENT_FOLDER = L"\\Resources\\";
	const std::wstring RESOURCES_CURRENT_FULL_PATH = static_cast<std::wstring>(std::experimental::filesystem::current_path()) + RESOURCES_CURRENT_FOLDER;
	const std::wstring RESOURCES_COUNTERS_FILE_NAME = L"Counters.txt";
	const std::wstring RESOURCES_MUSIC_FILE_NAME = L"WrathOfTheGiants.mp3";
	const std::wstring PARTICIPANT_IMAGE_FILE_EXTENSION = L".bmp";
	
private:
	//Dialog data
	int cxClient_;
	int cyClient_;
	bool first_OnPaint_;
	bool game_state_;  //the state of the game, if true - the game has started
	bool winner_state_; //if the winner was detemined, the value is true

	ImageObject img;

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
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
