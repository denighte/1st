#include "stdafx.h"
#include "GraphClass.h"

#define MFCGPAINTCTRL_CLASSNAME    _T("MFCGPaintCtrl")

double GPaint::GetRound(double number) {  //note: Don't forget to define
	return number;
}

GPaint::GPaint() {
	RegisterWindowClass();
}


BOOL GPaint::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, MFCGPAINTCTRL_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = MFCGPAINTCTRL_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

GPaint::GPaint(CPaintDC& dc, const RECT & WorkSpace)
	: _dc(dc), _left(WorkSpace.left), _top(WorkSpace.top),
			   _right(WorkSpace.right), _bottom(WorkSpace.bottom),
	_LimitMaxX(0), _LimitMaxY(0), _LimitMinX(0), _LimitMinY(0),
	_dx(0), _dy(0),
	_BgFrameWidth(2), _BgFrameColor(RGB(0, 128, 0)), _BgFillingColor(RGB(255, 255, 255)), 
	_AxisWidth(1), _AxisColor(RGB(0, 0, 0)), 
	_GridColor(RGB(215, 215, 215))
{}

//values setters definition
void GPaint::SetGridDeltas(double x, double y) {
	_dx = x;
	_dy = y;
}

void GPaint::SetLimits(double minX, double maxX, double minY, double maxY) {
	_LimitMinX = GetRound(minX);
	_LimitMinY = GetRound(minY);
	_LimitMaxX = GetRound(maxX);
	_LimitMaxY = GetRound(maxY);
}

void GPaint::SetLableSteps(double x, double y) {
	_LabelStepX = x;
	_LabelStepY = y;
}


//style setters definition
void GPaint::SetBgStyle(int BevelWidth, COLORREF BgColor, COLORREF LineColor) {
	_BgFrameWidth = BevelWidth;
	_BgFrameColor = LineColor;
	_BgFillingColor = BgColor;
}
void GPaint::SetAxisStyle(int AxisWidth, COLORREF LineColor) {
	_AxisWidth = AxisWidth;
	_AxisColor = LineColor;
}
void GPaint::SetGraphStyle(int gStyle, int gWidth, COLORREF glColor) {
	_gStyle = gStyle;
	_gWidth = gWidth;
	_glColor = glColor;
}

double GPaint::GetAxisLabelsFrequency(char axis) { return 1; } //note: Don't forget to define

void GPaint::GetWorkSpace() {
	CPen GraphPen(PS_SOLID, _BgFrameWidth, _BgFrameColor);
	CBrush GraphBg(_BgFillingColor);
	_dc.SelectObject(GraphPen);
	_dc.SelectObject(GraphBg);
	_dc.Rectangle(_left, _top, _right, _bottom);
	_left += (_BgFrameWidth/2 + 1);
	_top += (_BgFrameWidth/2 + 1);
	_right -= (_BgFrameWidth/2 + 1);
	_bottom -= (_BgFrameWidth/2 + 1);
}


void GPaint::DrawGridLinesX() {

	CPen WndPen(PS_DOT, 1, _GridColor);
	_dc.SelectObject(WndPen);


	for (int i = 1; i < static_cast<int>(_LimitMaxX/_dx); ++i) {  //Draw grid from conventional 0 to maximum X
		_dc.MoveTo(toX(i*_dx), toY(_LimitMinY));
		_dc.LineTo(toX(i*_dx), toY(_LimitMaxY));
	}

	for (int i = 1; i < static_cast<int>(abs(_LimitMinX / _dx)); ++i) { //Draw grid from conventional 0 to minimum X
		_dc.MoveTo(toX(-i*_dx), toY(_LimitMinY));
		_dc.LineTo(toX(-i*_dx), toY(_LimitMaxY));
	}
}

void GPaint::DrawGridLinesY() {

	CPen WndPen(PS_DOT, 1, _GridColor);
	_dc.SelectObject(WndPen);



	for (int i = 1; i < static_cast<int>(_LimitMaxY/_dy); ++i) { //Draw grid from conventional 0 to maximum Y
		_dc.MoveTo(toX(_LimitMinX), toY(i*_dy));
		_dc.LineTo(toX(_LimitMaxX), toY(i*_dy));
	}

	for (int i = 1; i < static_cast<int>(abs(_LimitMinY / _dy)); ++i) { //Draw grid from conventional 0 to minimum Y
		_dc.MoveTo(toX(_LimitMinX), toY(-i*_dy));
		_dc.LineTo(toX(_LimitMaxX), toY(-i*_dy));
	}
}


void GPaint::DrawAxis() {
	CPen WndPen(PS_SOLID, _AxisWidth, _AxisColor);
	_dc.SelectObject(WndPen);

	LONG Ox = toX(0);
	LONG Oy = toY(0);

	_dc.MoveTo(toX(_LimitMinX), Oy);
	_dc.LineTo(toX(_LimitMaxX), Oy);
	_dc.MoveTo(Ox, toY(_LimitMinY));
	_dc.LineTo(Ox, toY(_LimitMaxY));

	int PtrSize = 5;
	//x - ptr
	_dc.MoveTo(_right - 1, Oy);
	_dc.LineTo(_right - PtrSize, Oy + PtrSize);
	_dc.MoveTo(_right - 1, Oy);
	_dc.LineTo(_right - PtrSize, Oy - PtrSize);
	_dc.LineTo(_right - PtrSize, Oy + PtrSize);

	//y - ptr
	_dc.MoveTo(Ox, _top);
	_dc.LineTo(Ox - PtrSize, _top + PtrSize);
	_dc.MoveTo(Ox, _top);
	_dc.LineTo(Ox + PtrSize, _top + PtrSize);
	_dc.LineTo(Ox - PtrSize, _top + PtrSize);
}

void GPaint::DrawLabels() {
	CFont font;
	font.CreateFont(-12, 0, 0, 0, 300, FALSE, FALSE, FALSE, (BYTE)0, (BYTE)3,  //Creating special font for graphics
		(BYTE)2, (BYTE)1, (BYTE)FIXED_PITCH | FF_MODERN,
		_T("System"));

	_dc.SelectObject(font);
	_dc.SetBkMode(OPAQUE);

	_dc.SetTextAlign(TA_CENTER);
	int RightCount = static_cast<int> (_LimitMaxX / _LabelStepX);
	int LeftCount = static_cast<int> (-_LimitMinX / _LabelStepX);

	for (int i = 1; i < max(LeftCount, RightCount); i++) {
		if (i < RightCount) 
		{
			_dc.TextOut(toX(i*_LabelStepX), toY(0) + _AxisWidth / 2 + 1, GetStepX(i*_LabelStepX));
		}
		if (i < LeftCount)  
		{
			_dc.TextOut(toX(-i*_LabelStepX), toY(0) + _AxisWidth / 2 + 1, GetStepX(-i*_LabelStepX));
		}
	}

	_dc.SetTextAlign(TA_LEFT | TA_BASELINE);
	int TopCount = static_cast<int> (_LimitMaxY / _LabelStepY);
	int BottomCount = static_cast<int> (-_LimitMinY / _LabelStepY);
	for (int i = 1; i < max(TopCount, BottomCount); i++) {
		if (i < TopCount)
		{
			_dc.TextOut(toX(0) + _AxisWidth / 2 + 1, toY(i*_LabelStepY), GetStepY(i*_LabelStepY));
		}
		if (i < BottomCount)
		{
			_dc.TextOut(toX(0) + _AxisWidth / 2 + 1, toY(-i*_LabelStepY), GetStepY(-i*_LabelStepY));
		}
	}

}

CString DefaultStepX(double value) {
	static double StepPrecision;  // !!! Temporary, must be replaced
	if (!StepPrecision)
		StepPrecision = abs(value);

	CString str;
	if (StepPrecision < 0.1)
		str.Format(_T("%.2f"), value);
	else if (StepPrecision < 1)
		str.Format(_T("%.1f"), value);
	else
		str.Format(_T("%.0f"), value);
	return str;
}

CString DefaultStepY(double value) {
	//return DefaultStepX(value);  
	static double StepPrecision;  // !!! Temporary, must be replaced
	if (!StepPrecision)
		StepPrecision = abs(value);

	CString str;
	if (StepPrecision < 0.1)
		str.Format(_T("%.2f"), value);
	else if (StepPrecision < 1)
		str.Format(_T("%.1f"), value);
	else
		str.Format(_T("%.0f"), value);
	return str;
}

void GPaint::DrawGraph(GraphFunction func) {
	CPen GraphPen(_gStyle, _gWidth, _glColor);
	_dc.SelectObject(GraphPen);

	_dc.MoveTo(toX(_LimitMinX), toY(func(_LimitMinX)));

	double delta = (_LimitMaxX - _LimitMinX) / (_right - _left);

	for (int i = 0; i < _right - _left; i++) {
		double x = _LimitMinX + i * delta;
		_dc.LineTo(toX(x), toY(func(x)));
	}
}

bool GPaint::DrawCoordinateSystem() {
	if (abs(_bottom - _top) < MIN_WORK_SPACE_SIZE) 
	{
		return false;
	}
	GetWorkSpace();
	DrawGridLinesX();
	DrawGridLinesY();
	DrawAxis();
	DrawLabels();
	
	return true;
}

void GPaint::DrawLine(double x1, double y1, double x2, double y2) {
	_dc.MoveTo(toX(x1), toY(y1));
	_dc.LineTo(toX(x2), toY(y2));
}
