
// ClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnalClock.h"
#include "ClockDlg.h"
#include "afxdialogex.h"

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


// ÑClockDlg dialog



ÑClockDlg::ÑClockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ANALCLOCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ÑClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ÑClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// ÑClockDlg message handlers

BOOL ÑClockDlg::OnInitDialog()
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

	ShowWindow(SW_SHOW);

	//extra initialization
	dtPrevious;
	if (!(this->SetTimer(ID_TIMER, 1000, NULL)))
	{
		MessageBox(_T("Too many clocks or timers!"), _T("Clock"),
			MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	//------

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ÑClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void ÑClockDlg::OnPaint()
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
		SetIsotropic(dc, cxClient, cyClient);
		DrawClock(dc);
		DrawHands(dc, dtPrevious, TRUE);
		CDialogEx::OnPaint();
	}
}

void ÑClockDlg::SetIsotropic(CDC& dc, int cxClient, int cyClient) {
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(1000, 1000);
	dc.SetViewportExt(cxClient / 2, -cyClient / 2);
	dc.SetViewportOrg(cxClient / 2, cyClient / 2);
}

void ÑClockDlg::RotatePoint(POINT pt[], int iNum, int iAngle)
{
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

void ÑClockDlg::DrawClock(CDC& dc)
{
	int iAngle;
	POINT pt[3];
	for (iAngle = 0; iAngle < 360; iAngle += 6)
	{
		pt[0].x = 0;
		pt[0].y = 900;
		RotatePoint(pt, 1, iAngle);
		pt[2].x = pt[2].y = iAngle % 5 ? 33 : 100;
		pt[0].x -= pt[2].x / 2;
		pt[0].y -= pt[2].y / 2;
		pt[1].x = pt[0].x + pt[2].x;
		pt[1].y = pt[0].y + pt[2].y;
		dc.SelectStockObject(BLACK_BRUSH);
		dc.Ellipse(pt[0].x, pt[0].y, pt[1].x, pt[1].y);
	}
}
void ÑClockDlg::DrawHands(CDC& dc, Time& datetime, BOOL bChange)
{
	static POINT pt[3][5] = { 0, -150, 100, 0, 0, 600, -100, 0, 0, -150,
		0, -200, 50, 0, 0, 800, -50, 0, 0, -200,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 800 };
	int i, iAngle[3];
	POINT ptTemp[3][5];
	iAngle[0] = (datetime.getHour() * 30) % 360 + datetime.getMin() / 2;
	iAngle[1] = datetime.getMin() * 6;
	iAngle[2] = datetime.getSec() * 6;
	memcpy(ptTemp, pt, sizeof(pt));
	for (i = bChange ? 0 : 2; i < 3; i++)
	{
		RotatePoint(ptTemp[i], 5, iAngle[i]);
		dc.Polyline(ptTemp[i], 5);
	}
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ÑClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void ÑClockDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	cxClient = cx;
	cyClient = cy;
	Invalidate();
}


void ÑClockDlg::OnTimer(UINT_PTR nIDEvent)
{
	CPaintDC dc(this);
	// TODO: Add your message handler code here and/or call default
	Time datetime;
	BOOL bChange = datetime != dtPrevious;//datetime->tm_hour != dtPrevious.tm_hour || datetime->tm_min != dtPrevious.tm_min;
	SetIsotropic(dc, cxClient, cyClient);
	dc.SelectStockObject(WHITE_PEN);
	DrawHands(dc, dtPrevious, bChange);
	dc.SelectStockObject(BLACK_PEN);
	DrawHands(dc, datetime, TRUE);
	ReleaseDC(&dc);
	dtPrevious = datetime;
	Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}
/*
BOOL ÑClockDlg::PreTranslateMessage(MSG *pMsg)
{
	// If this is a timer callback message let it pass on through to the
	// DispatchMessage call.
	if ((pMsg->message == WM_TIMER) && (pMsg->hwnd == NULL))
		return FALSE;

	return CDialogEx::PreTranslateMessage(pMsg);
}*/




void ÑClockDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	DestroyWindow();
	CDialogEx::OnClose();
}


void ÑClockDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(ID_TIMER);
	PostQuitMessage(0);
}
