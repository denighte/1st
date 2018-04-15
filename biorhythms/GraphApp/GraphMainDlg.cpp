
// GraphMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphApp.h"
#include "GraphMainDlg.h"
#include "afxdialogex.h"
#include "GraphClass.h"
#include "Date.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CONST INT MAX_X = 20;
static CONST INT MIN_X = -1;
static CONST INT MAX_Y = 110;
static CONST INT MIN_Y = -110;
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


// CGraphMainDlg dialog



CGraphMainDlg::CGraphMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAPHAPP_DIALOG, pParent),
	BCBirth(0), BCCalc(0), OnClickedCalc(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraphMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCMASKEDEDIT_BIRTHDATE, BirthEdit);
	DDX_Control(pDX, IDC_MFCMASKEDEDIT_CALCDATE, CalcEdit);
}

BEGIN_MESSAGE_MAP(CGraphMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGraphMainDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTONEXIT, &CGraphMainDlg::OnBnClickedButtonexit)
	ON_BN_CLICKED(IDC_BUTTONCALC, &CGraphMainDlg::OnBnClickedButtoncalc)
	ON_BN_CLICKED(IDC_CHECKBIRTH, &CGraphMainDlg::OnBnClickedCheckBirth)
	ON_BN_CLICKED(IDC_CHECKCALC, &CGraphMainDlg::OnBnClickedCheckCalc)
END_MESSAGE_MAP()


// CGraphMainDlg message handlers

BOOL CGraphMainDlg::OnInitDialog()
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
	//Extra init
	//Control flags init
	BCBirth = 0;
	BCCalc = 0;
	OnClickedCalc = 0;
	ShowWindow(SW_MAXIMIZE);

	//Current date init
	CurrentDate;

	//CMFCMaskedEdit init
	BirthEdit.EnableGetMaskedCharsOnly(FALSE);
	BirthEdit.SetWindowText(_T("31/10/1921"));

	CalcEdit.EnableGetMaskedCharsOnly(FALSE);
	CalcEdit.SetWindowText(CurrentDate.to_string());

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGraphMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGraphMainDlg::OnPaint()
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
		RECT MainWndRect;
		GetClientRect(&MainWndRect);
		MainWndRect.left += 12;
		MainWndRect.top += 42;
		MainWndRect.right -= 12;
		MainWndRect.bottom -= 12;
		GPaint Obj(dc, MainWndRect);

		Obj.SetLimits(MIN_X, MAX_X, MIN_Y, MAX_Y);
		Obj.SetGridDeltas(0.5, 5);
		Obj.SetLableSteps(5, 10);

		Obj.SetCustomLabelsY([](double x) -> CString {
			CString str;
			str.Format(_T("%i%%"), static_cast<int>(x));
			return str;
		});

		int DateDelta = 0;

		if (OnClickedCalc) {
			Date BirthDate;
			Date CalcDate;
			DateDelta = GetDate(BirthDate, CalcDate);
			Obj.SetCustomLabelsX([CalcDate](double x) mutable -> CString {
				return (CalcDate + static_cast<int>(x)).to_string();
			});
		}
		else {
			Obj.SetCustomLabelsX([CurrentDate = CurrentDate](double x) -> CString {
				return (CurrentDate + static_cast<int>(x)).to_string();
			});
		}

		Obj.DrawCoordinateSystem();		

		if (OnClickedCalc) {
			DrawBiorithms(Obj, DateDelta);
			DrawInfoBox(dc, &MainWndRect, DateDelta);
		}



		CDialogEx::OnPaint();
	}
}

//Biorithm procedures

int CGraphMainDlg::GetDate(Date& BirthDate, Date& CalcDate) {
	CString Birth;
	CString Calc;
	BirthEdit.GetWindowText(Birth);
	CalcEdit.GetWindowText(Calc);
	if (BCBirth)
		Birth += _T(" BC");
	if (BCCalc)
		Calc += _T(" BC");
	BirthDate = StringToDate(Birth);
	CalcDate = StringToDate(Calc);
	return CalcDate - BirthDate;
}

void CGraphMainDlg::DrawBiorithms(GPaint & Obj, int DateDelta) {
	Obj.SetGraphStyle(PS_SOLID, 1, RGB(255, 0, 0));
	Obj.DrawGraph([DateDelta](double x) mutable {return 100 * sin(2 * (x + DateDelta) * M_PI / 23); });  //Physical biorhythm

	Obj.SetGraphStyle(PS_SOLID, 1, RGB(0, 255, 0));
	Obj.DrawGraph([DateDelta](double x) {return 100 * sin(2 * (x + DateDelta) * M_PI / 28); });  //Emotional biorhythm

	Obj.SetGraphStyle(PS_SOLID, 1, RGB(0, 0, 255));
	Obj.DrawGraph([DateDelta](double x) {return 100 * sin(2 * (x + DateDelta) * M_PI / 33); });  //intellectual biorhythm
}

void CGraphMainDlg::DrawInfoBox(CPaintDC & Obj, RECT* WndSize, int DateDelta) {
	CONST INT INDENTATION_X = 11;
	CONST INT INDENTATION_Y = 0;
	CONST INT LINE_SPACING = 3;
	CONST INT BORDER_INDENTATION_X = 10;
	CONST INT BORDER_INDENTATION_Y = 10;

	CString str = _T("Biorhythms for the specified date: ");
	CSize StrSize = Obj.GetTextExtent(str);
	CString number;
	CPen BoxPen(PS_SOLID, 1, RGB(0, 0, 0));
	Obj.SelectStockObject(BLACK_PEN);
	Obj.Rectangle(WndSize->right - INDENTATION_X + BORDER_INDENTATION_X, WndSize->top + INDENTATION_Y, 
		WndSize->right - (StrSize.cx + INDENTATION_X + BORDER_INDENTATION_X), WndSize->top + (4*StrSize.cy + 4*LINE_SPACING + INDENTATION_Y + 2*BORDER_INDENTATION_Y));

	Obj.TextOut(WndSize->right - StrSize.cx - INDENTATION_X, WndSize->top + StrSize.cy + INDENTATION_Y + BORDER_INDENTATION_Y, str);

	double PhysicalB = 100 * sin(2 * DateDelta * M_PI / 23);
	number.Format(_T("Physical:       %+.2f%%"), PhysicalB);
	Obj.SetTextColor(RGB(255, 0, 0));
	Obj.TextOut(WndSize->right - StrSize.cx - INDENTATION_X, WndSize->top + 2*StrSize.cy + INDENTATION_Y + BORDER_INDENTATION_Y + LINE_SPACING, number);

	double EmotionalB = 100 * sin(2 * DateDelta * M_PI / 28);
	number.Format(_T("Emotional:      %+.2f%%"), EmotionalB);
	Obj.SetTextColor(RGB(0, 255, 0));
	Obj.TextOut(WndSize->right - StrSize.cx - INDENTATION_X, WndSize->top + 3*StrSize.cy + INDENTATION_Y + BORDER_INDENTATION_Y + 2*LINE_SPACING, number);

	double IntellectualB = 100 * sin(2 * DateDelta * M_PI / 33);
	number.Format(_T("Intellectual:   %+.2f%%"), IntellectualB);
	Obj.SetTextColor(RGB(0, 0, 255));
	Obj.TextOut(WndSize->right - StrSize.cx - INDENTATION_X, WndSize->top + 4*StrSize.cy + INDENTATION_Y + BORDER_INDENTATION_Y + 3*LINE_SPACING, number);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGraphMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGraphMainDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CGraphMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	Invalidate();
	// TODO: Add your message handler code here
}


void CGraphMainDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnGetMinMaxInfo(lpMMI);


	lpMMI->ptMinTrackSize.x = 800;
	lpMMI->ptMinTrackSize.y = 600;

}


void CGraphMainDlg::OnBnClickedButtonexit()
{
	EndDialog(0);
}


void CGraphMainDlg::OnBnClickedButtoncalc()
{
	OnClickedCalc = 1;
	Invalidate();
	// TODO: Add your control notification handler code here
}


void CGraphMainDlg::OnBnClickedCheckBirth()
{
	if (BCBirth)
		BCBirth = 0;
	else
		BCBirth = 1;
}


void CGraphMainDlg::OnBnClickedCheckCalc()
{
	if (BCCalc)
		BCCalc = 0;
	else
		BCCalc = 1;
}
