
// UI-Project-001Dlg.cpp : файл реализации
//

#include "stdafx.h"
#include "UI-Project-001.h"
#include "UI-Project-001Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// диалоговое окно CMainDlg


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UIPROJECT001_DIALOG, pParent)
	, left_in(_T(""))
	, right_in(_T(""))
	, InfoUpdate(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMBER_1, left_in);
	DDX_Text(pDX, IDC_NUMBER_2, right_in);
	DDX_Control(pDX, IDC_ANSWER, result);
	//  DDX_Control(pDX, IDC_STATIC6, mouseCoordinates);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CMainDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CMainDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CMainDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CMainDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_ANSWER, &CMainDlg::OnEnChangeAnswer)
	ON_WM_SIZE()
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// обработчики сообщений CMainDlg

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CFont font;
		font.CreateFont(-12, 0, 0, 0, 300, FALSE, FALSE, FALSE, (BYTE)0, (BYTE)3,  //Creating special font for graphics
			(BYTE)2, (BYTE)1, (BYTE)FIXED_PITCH | FF_MODERN,
			_T("System"));

		//Experimental:
		RECT ClientWS;
		GetClientRect(&ClientWS);
		CPaintDC dc(this);

		graphic::GPaint Obj(dc, { ClientWS.left + 350, ClientWS.top + 16, ClientWS.right - 16, ClientWS.bottom - 16 });
		Obj.SetGridFrequency(10);
		Obj.DrawCoordinateSystem();
		if (InfoUpdate) {
			CString buffer;
			result.GetWindowText(buffer);
			std::complex<double> number = GetComplex(buffer);
			Obj.SelectPoint(Obj.DrawComplex(number));
		}

		//Obj.DrawLine(...., RGB color);
		//Obj.DrawFunction(startx, endx, sin())
		

		/*
		CPen* WndNewPen = new CPen(PS_SOLID, 2, RGB(0, 128, 0));
		Obj.GetWorkSpace(WndNewPen);
		delete WndNewPen;

		WndNewPen = new CPen(PS_DOT, 1, RGB(215, 215, 215));
		Obj.DrawMarkingLinesX(10, WndNewPen);
		Obj.DrawMarkingLinesY(10);
		delete WndNewPen;

		WndNewPen = new CPen(PS_SOLID, 1, RGB(0, 0, 0));
		Obj.DrawAxis(WndNewPen, &font);
		delete WndNewPen;

		Obj.DrawLables(100, 10);*/

		

	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMainDlg::DataProcessing(char operation)
{
	UpdateData(TRUE);

	switch (operation) 
	{
	case '+':
		SetResult(GetComplex(left_in) + GetComplex(right_in));
		break;

	case '-':
		SetResult(GetComplex(left_in) - GetComplex(right_in));
		break;

	case '*':
		SetResult(GetComplex(left_in) * GetComplex(right_in));
		break;

	case '/':
		SetResult(GetComplex(left_in) / GetComplex(right_in));
		break;
	}

}

std::complex<double> CMainDlg::GetComplex(CString& c)
{
	int pos = 0;
	const CString SEPARATORS = _T("(, )");

	CString img = _T("0");
	CString re = c.Tokenize(SEPARATORS, pos);
	if (re != _T(""))
	{
		img = c.Tokenize(SEPARATORS, pos);
		if (img == _T(""))
		{
			img = _T("0");
		}
	}
	else {
		re = _T("0");
	}
		
	return std::complex<double>(wcstod(re, 0), wcstod(img, 0));
}

void CMainDlg::SetResult(std::complex<double> value) 
{
	CString c;
	c.Format(_T("(%f,%f)"), value.real(), value.imag());
	result.SetWindowTextW(c);
	InfoUpdate = TRUE;
	Invalidate();
}



void CMainDlg::OnBnClickedButtonPlus()
{
	DataProcessing('+');
}


void CMainDlg::OnBnClickedButtonMinus()
{
	DataProcessing('-');
}


void CMainDlg::OnBnClickedButtonMul()
{
	DataProcessing('*');
}


void CMainDlg::OnBnClickedButtonDiv()
{
	DataProcessing('/');
}

void CMainDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CMainDlg::OnEnChangeAnswer()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	Invalidate();

	// TODO: Add your message handler code here
}


//void CMainDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CString str;
//	str.Format(_T("x: %d, y: %d"), point.x, point.y);
//
//	mouseCoordinates.SetWindowText(str);
//
//
//	CDialogEx::OnMouseMove(nFlags, point);
//}
