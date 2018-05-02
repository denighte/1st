
// CMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PracticeProject_1.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#define TWOPI (2 * 3.14159)
#define ID_TIMER 1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg dialog



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRACTICEPROJECT_1_DIALOG, pParent), 
	  manager_(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMainDlg::~CMainDlg()
{
	if(manager_ != nullptr)
		delete manager_;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_START_GAME, &CMainDlg::OnBnClickedStartGame)
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//extra initialization

	//Timer init
	if (!(this->SetTimer(ID_TIMER, 1000, NULL)))
	{
		MessageBox(_T("Too many clocks or timers!"), _T("Clock"),
			MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	//Counter init
	CounterInit();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		SetIsotropic(dc, cxClient_, cyClient_);
		dc.SetTextAlign(TA_CENTER);
		DrawParticipantsCircle(dc);
		if (game_state_) {
			dc.TextOutW(800, 900, (manager_->CurrentWord().c_str()));
			SelectCurrentParticipant(dc);
		}

		

		CDialogEx::OnPaint();
	}
}

void CMainDlg::SetIsotropic(CDC& dc, int cxClient, int cyClient) {
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(1000, 1000);
	dc.SetViewportExt(cxClient / 2, -cyClient / 2);
	dc.SetViewportOrg(cxClient / 2, cyClient / 2);
}

void CMainDlg::RotatePoint(POINT pt[], int iNum, int iAngle) {
	int i;
	POINT ptTemp;
	for (i = 0; i < iNum; i++)
	{
		ptTemp.x = (int)(pt[i].x * cos(TWOPI * iAngle / 360) +
			pt[i].y * sin(TWOPI * iAngle / 360));
		ptTemp.y = (int)(pt[i].y * cos(TWOPI * iAngle / 360) -
			pt[i].x * sin(TWOPI * iAngle / 360));
		pt[i] = ptTemp;
	}
}

void CMainDlg::DrawParticipantsCircle(CDC& dc) {
	for (int i = 0; i != NUMBER_OF_PARTICIPANTS; ++i) {
		bool flag = false;
		CycleList<Student>::iterator it = participants_.begin();
		for (int j = 0; j <= participants_.length() && !flag; ++it, ++j) {
			flag = ((*it).id() == i) ? true : false;
		}
		if (flag) {
			POINT StartPoint(PARTICIPANTS_START_POINT);
			RotatePoint(&StartPoint, 1, static_cast<int>(i*ROTATE_ANGLE));
				//  Try to Draw avatar there
				//CString name = (*it).name().c_str();
				//DrawAvatar(dc, name, StartPoint.x, StartPoint.y);
			dc.TextOutW(StartPoint.x, StartPoint.y, (*it).name().c_str());
		}

	}
}


void CMainDlg::DrawAvatar(CDC &dc, int x, int y, const CString name)
{

	CString s = _T("D:\\Downloads\\Avatars\\");

	CImage image;

	if (!image.Load(s + name + _T(".bmp"))) {

		CBitmap bmp;
		bmp.Attach(image.Detach());

		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);

		CDC dcMemory;
		dcMemory.CreateCompatibleDC(&dc);

		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);


		for (int y = 0; y < bmpInfo.bmHeight/2; y++)
		{
			for (int x = 0; x < bmpInfo.bmWidth; x++)
			{
				COLORREF rgb1 = dcMemory.GetPixel(x, y);
				COLORREF rgb2 = dcMemory.GetPixel(x, bmpInfo.bmHeight-y-1);

				BYTE r = GetRValue(rgb2);
				BYTE g = GetGValue(rgb2);
				BYTE b = GetBValue(rgb2);
				dcMemory.SetPixel(x, y, RGB(r, g, b));

				r = GetRValue(rgb1);
				g = GetGValue(rgb1);
				b = GetBValue(rgb1);
				dcMemory.SetPixel(x, bmpInfo.bmHeight - y - 1, RGB(r, g, b));

			}
		}

		dc.BitBlt(x, y, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory,
			0, 0, SRCCOPY | NOMIRRORBITMAP);

		dcMemory.SelectObject(pOldBitmap);

	}

	/*class Avatar {
		CDC memDC;
		int width;
		int height;
		CBitmap* pOldBitmap;

		~Avatar() { memDC.SelectObject(pOldBitmap); }

	};*/

}

void CMainDlg::DrawPointer(CDC& dc, int Angle) {
	POINT pt[POINTER_POINTS_NUMBER];
	memcpy(&pt, &ARROWHEAD, sizeof(pt));
	RotatePoint(pt, POINTER_POINTS_NUMBER, Angle);
	dc.Polyline(pt, POINTER_POINTS_NUMBER);


}

void CMainDlg::SelectCurrentParticipant(CDC& dc) {
	int RAngle = current_participant_.id() * ROTATE_ANGLE;
	DrawPointer(dc, RAngle);
}


void CMainDlg::CounterInit() {
	//TODO: add random counter selection

	Counter cnt = L"Hush, mouse, cat on the roof";

	participants_.push_front(Student(L"Student1", 0, SPicture(1)));
	participants_.push_front(Student(L"Student2", 1, SPicture(2)));
	participants_.push_front(Student(L"Student3", 2, SPicture(3)));
	participants_.push_front(Student(L"Student4", 3, SPicture(4)));
	participants_.push_front(Student(L"Student5", 4, SPicture(5)));
	participants_.push_front(Student(L"Student6", 5, SPicture(6)));

	manager_ = new CounterManager(cnt, participants_);
	game_state_ = false;
	winner_state_ = false;

}

void CMainDlg::ResourcesInit() {

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	cxClient_ = cx;
	cyClient_ = cy;
	Invalidate();
}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (!(manager_->eog()) && game_state_) {
		current_participant_ = manager_->NextCount();
		Invalidate();
	}
	else if (manager_->eog()) {
		KillTimer(ID_TIMER);
		winner_state_ = true;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMainDlg::OnClose()
{
	DestroyWindow();
	CDialogEx::OnClose();
}


void CMainDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//KillTimer(ID_TIMER);
	PostQuitMessage(0);
}


void CMainDlg::OnBnClickedStartGame()
{
	game_state_ = true;
}
