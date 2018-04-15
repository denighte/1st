#include "stdafx.h"
#include "DCGraphAdapter.h"
int graphic::GetRoundTo(int number) {
	if (number == 0)
		return 10;
	int RoundedNumber = 1;
	for (int i = 0; (number % 10 != 0 || number > 1); ++i, RoundedNumber *= 10, number /= 10);
	return RoundedNumber;
}
graphic::GPaint::GPaint(CPaintDC& dc, const RECT & WorkSpace)
	: _dc(dc), _left(WorkSpace.left), _top(WorkSpace.top),
					 _right(WorkSpace.right), _bottom(WorkSpace.bottom),
	_MarkingLineStepX(0), _MarkingLineStepY(0),
	_MarkingLinesCntX(0), _MarkingLinesCntY(0), _BgFrameWidth(2), _BgFrameColor(RGB(0, 128, 0)),
	_BgFillingColor(RGB(255, 255, 255)), _AxisWidth(1), _AxisColor(RGB(0, 0, 0)), _GridColor(RGB(215, 215, 215)),
	_GridNumber(10)
{
	_x_axisY = (_top - (_top - _bottom) / 2);
	_y_axisX = _right - (_right - _left) / 2;
}

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

void graphic::GPaint::GetWorkSpace() {
	CPen GraphPen(PS_SOLID, _BgFrameWidth, _BgFrameColor);
	CBrush GraphBg(_BgFillingColor);
	_dc.SelectObject(GraphPen);
	_dc.SelectObject(GraphBg);
	_dc.Rectangle(_left, _top, _right, _bottom);
}

bool graphic::GPaint::DrawMarkingLinesX(LONG MarkingLineFreq) {
	_MarkingLineStepX = 1;  //define MarkingLineStep by 0, to avoid exception in DrawMarkingLinesY() func
	if (abs(_right - _left) > WORK_SPACE_SIZE) {
		_MarkingLinesCntX = 0;

		CPen WndPen(PS_DOT, 1, _GridColor);
		_dc.SelectObject(WndPen);

		if (MarkingLineFreq == GRAPHIC_DEFAULT_TOOL) {
			if (_MarkingLineStepY)
				_MarkingLineStepX = _MarkingLineStepY;
			else
				throw DefaulToolError();
		}
		_MarkingLineStepX = (_right - _y_axisX) / MarkingLineFreq;

		for (LONG step = _y_axisX + _MarkingLineStepX; step < _right - 1; step += _MarkingLineStepX) {
			_dc.MoveTo(step, _bottom - 1);
			_dc.LineTo(step, _top);
			++_MarkingLinesCntX;
		}
		for (long step = _y_axisX - _MarkingLineStepX; step > _left - 1; step -= _MarkingLineStepX) {
			_dc.MoveTo(step, _bottom - 1);
			_dc.LineTo(step, _top);
			++_MarkingLinesCntX;
		}
		return true;
	}
	return false;
}

bool graphic::GPaint::DrawMarkingLinesY(LONG MarkingLineFreq) {
	_MarkingLineStepY = 1; //define MarkingLineStep by 0, to avoid exception in DrawMarkingLinesX() func
	if (abs(_bottom - _top) > WORK_SPACE_SIZE) {
		_MarkingLinesCntY = 0;

		CPen WndPen(PS_DOT, 1, _GridColor);
		_dc.SelectObject(WndPen);

		if (MarkingLineFreq == GRAPHIC_DEFAULT_TOOL) {
			if (_MarkingLineStepX)
				_MarkingLineStepY = _MarkingLineStepX;
			else
				throw DefaulToolError();
		}

		_MarkingLineStepY = (_bottom - _x_axisY) / MarkingLineFreq;


		for (long step = _x_axisY - _MarkingLineStepY; step > _top - 1; step -= _MarkingLineStepY) {
			_dc.MoveTo(_left + 1, step);
			_dc.LineTo(_right - 1, step);
			++_MarkingLinesCntY;
		}
		for (long step = _x_axisY + _MarkingLineStepY; step < _bottom - 1; step += _MarkingLineStepY) {
			_dc.MoveTo(_left + 1, step);
			_dc.LineTo(_right - 1, step);
			++_MarkingLinesCntY;
		}
		return true;
	}
	return false;

}

void graphic::GPaint::DrawAxis(int PtrSize) {

	//drawing Axis
	CPen WndPen(PS_SOLID, _AxisWidth, _AxisColor);
	_dc.SelectObject(WndPen);

	_dc.MoveTo(_left, _x_axisY);
	_dc.LineTo(_right, _x_axisY);

	_dc.MoveTo(_y_axisX, _top);
	_dc.LineTo(_y_axisX, _bottom);

	//x - ptr
	_dc.MoveTo(_right - 1, _x_axisY);
	_dc.LineTo(_right - PtrSize, _x_axisY + PtrSize);
	_dc.MoveTo(_right - 1, _x_axisY);
	_dc.LineTo(_right - PtrSize, _x_axisY - PtrSize);
	_dc.LineTo(_right - PtrSize, _x_axisY + PtrSize);

	//y - ptr
	_dc.MoveTo(_y_axisX, _top);
	_dc.LineTo(_y_axisX - PtrSize, _top + PtrSize);
	_dc.MoveTo(_y_axisX, _top);
	_dc.LineTo(_y_axisX + PtrSize, _top + PtrSize);
	_dc.LineTo(_y_axisX - PtrSize, _top + PtrSize);
}

void graphic::GPaint::SetGridFrequency(int Freq) {
	_GridNumber = Freq;
}


int graphic::GPaint::GetLableFrequency(LONG number, wchar_t axis) {
	const int SIZE_OF_FONT_PX = 10;
	
	LONG SizeOfStep;

	if (axis == L'x')
		SizeOfStep = _MarkingLineStepX;
	else if (axis == L'y')
		SizeOfStep = _MarkingLineStepX;

	number = GetRoundTo(number);

	int Numberquantity;
	for (Numberquantity = 0; number != 0; number /= 10, ++Numberquantity);
	//++Numberquantity;

	int Frequency;
	for (Frequency = 1; SizeOfStep < Numberquantity * SIZE_OF_FONT_PX; SizeOfStep += SizeOfStep , ++Frequency);
	return Frequency;
}

void graphic::GPaint::DrawLables(LONG MaxNumber, LONG scale, int AxisLabelsFreq) {

	CFont font;
	font.CreateFont(-12, 0, 0, 0, 300, FALSE, FALSE, FALSE, (BYTE)0, (BYTE)3,  //Creating special font for graphics
		(BYTE)2, (BYTE)1, (BYTE)FIXED_PITCH | FF_MODERN,
		_T("System"));

	//drawing axis symbols
	_dc.SelectObject(font);
	_dc.SetBkMode(OPAQUE);

	_dc.TextOut(_right - 20, _x_axisY - 17, _T("x"));
	_dc.TextOut(_y_axisX + 5, _top + 5, _T("y"));

	//drawing lables
	CString f_str;
	if (abs(_right - _left) > WORK_SPACE_SIZE && abs(_bottom - _top) > WORK_SPACE_SIZE) {
		_dc.SelectObject(font);

		if (AxisLabelsFreq)
			_AxisLabelsFreq = AxisLabelsFreq;
		else
			_AxisLabelsFreq = GetLableFrequency(MaxNumber, L'x');

		MaxNumber = GetRoundTo(MaxNumber);
		LONG LStep = MaxNumber / scale;
		int MarkerSizeX = _MarkingLinesCntX / 2 - _AxisLabelsFreq;
		int MarkerSizeY = _MarkingLinesCntY / 2 - _AxisLabelsFreq;

		//drawing lables on x-axis
		_dc.SetTextAlign(TA_CENTER);
		for (LONG step = _y_axisX + _MarkingLineStepX, lable_step = LStep, i = 1; step < _right - 1; step += _MarkingLineStepX, lable_step += LStep, ++i) {
			if (i <= MarkerSizeX && i % _AxisLabelsFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				_dc.TextOut(step, _x_axisY + 2, f_str);
			}
		}
		for (long step = _y_axisX - _MarkingLineStepX, lable_step = LStep, i = 1; step > _left - 1; step -= _MarkingLineStepX, lable_step += LStep, ++i) {
			if (i <= MarkerSizeX && i % _AxisLabelsFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				_dc.TextOut(step - 5, _x_axisY + 2, f_str);
			}
		}


		//drawing lables on y-axis
		_dc.SetTextAlign(TA_LEFT);
		for (LONG step = _x_axisY + _MarkingLineStepY, lable_step = LStep, i = 1; step < _bottom - 1; step += _MarkingLineStepY, lable_step += LStep, ++i) {
			if (i <= MarkerSizeY && i % _AxisLabelsFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				_dc.TextOut(_y_axisX + 2, step - 5, f_str);
			}
		}
		for (long step = _x_axisY - _MarkingLineStepY, lable_step = LStep, i = 1; step > _top - 1; step -= _MarkingLineStepY, lable_step += LStep, ++i) {
			if (i <= MarkerSizeY && i % _AxisLabelsFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				_dc.TextOut(_y_axisX + 2, step - 5, f_str);
			}
		}
	}
}

CPoint graphic::GPaint::DrawComplex(std::complex<double> number) {
	if (number == std::complex<double>(0, 0))
		return CPoint(_y_axisX, _x_axisY);

	CPen ComplexPen(PS_SOLID, 1, RGB(212, 53, 53));
	_dc.SelectObject(ComplexPen);
	_dc.MoveTo(_y_axisX, _x_axisY);
	double MaxNumber = (abs(number.real()) > abs(number.imag())) ? abs(number.real()) : abs(number.imag());
	
	LONG LStep = GetRoundTo(static_cast<int>(MaxNumber)) / _GridNumber;
	double factorX = _MarkingLineStepX / static_cast<double>(LStep);
	double factorY = _MarkingLineStepY / static_cast<double>(LStep);
	int resX = _y_axisX + static_cast<int>(number.real()*factorX);
	int resY = _x_axisY - static_cast<int>(number.imag()*factorY);
	_dc.LineTo(resX, resY);
	_dc.Arc(_y_axisX - 20, _x_axisY - 20, _y_axisX + 20, _x_axisY + 20, _y_axisX + 20, _x_axisY, resX, resY);


	DrawLables(static_cast<int>(MaxNumber), _GridNumber);

	return CPoint(resX, resY);
}

void graphic::GPaint::SelectPoint(CPoint point, COLORREF color) {
	CPen Pen(PS_DOT, 1, color);
	_dc.SelectObject(Pen);
	_dc.MoveTo(point.x, _x_axisY);
	_dc.LineTo(point.x, point.y);
	_dc.LineTo(_y_axisX, point.y);
}

void graphic::GPaint::DrawCoordinateSystem() {
	GetWorkSpace();
	DrawMarkingLinesX(_GridNumber);
	DrawMarkingLinesY(_GridNumber);
	DrawAxis();
	//DrawLables(999, (_GridNumberX < _GridNumberY) ? (_GridNumberX) : (_GridNumberY));
}