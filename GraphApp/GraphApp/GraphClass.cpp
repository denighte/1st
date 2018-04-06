#include "stdafx.h"
#include "GraphClass.h"
double graphic::GetRound(double number) {  //note: Don't forget to define
	return number;
}
graphic::GPaint::GPaint(CPaintDC& dc, const RECT & WorkSpace)
	: _dc(dc), _left(WorkSpace.left), _top(WorkSpace.top),
			   _right(WorkSpace.right), _bottom(WorkSpace.bottom),
	_LimitMaxX(0), _LimitMaxY(0), _LimitMinX(0), _LimitMinY(0),
	_BgFrameWidth(2), _BgFrameColor(RGB(0, 128, 0)),
	_BgFillingColor(RGB(255, 255, 255)), _AxisWidth(1), _AxisColor(RGB(0, 0, 0)), 
	_GridColor(RGB(215, 215, 215))
{}

void graphic::GPaint::SetBgStyle(int BevelWidth, COLORREF BgColor, COLORREF LineColor) {
	_BgFrameWidth = BevelWidth;
	_BgFrameColor = LineColor;
	_BgFillingColor = BgColor;
}
void graphic::GPaint::SetAxisStyle(int AxisWidth, COLORREF LineColor) {
	_AxisWidth = AxisWidth;
	_AxisColor = LineColor;
}
void graphic::GPaint::SetGridColor(COLORREF Color) {
	_GridColor = Color;
}

void graphic::GPaint::SetLimits(double minX, double minY, double maxX, double maxY) {
	_LimitMinX = GetRound(minX);
	_LimitMinY = GetRound(minY);
	_LimitMaxX = GetRound(maxX);
	_LimitMaxY = GetRound(maxY);
	_AxisLabelsFreqX = GetAxisLabelsFrequency('x');
	_AxisLabelsFreqY = GetAxisLabelsFrequency('y');
}

int graphic::GPaint::GetAxisLabelsFrequency(char axis) {} //note: Don't forget to define

void graphic::GPaint::GetWorkSpace() {
	CPen GraphPen(PS_SOLID, _BgFrameWidth, _BgFrameColor);
	CBrush GraphBg(_BgFillingColor);
	_dc.SelectObject(GraphPen);
	_dc.SelectObject(GraphBg);
	_dc.Rectangle(_left, _top, _right, _bottom);
}
