#include "stdafx.h"
#include "GraphFuncs.h"
int graph::GetRoundTo10(int number) {
	int RoundedNumber = 1;
	for (int i = 0; (number % 10 != 0 || number > 1); ++i, RoundedNumber *= 10, number /= 10);
	return RoundedNumber;
}

void graph::GetWndWorkSpace(HWND hWnd, long& left, long& top, long& right, long& bottom) {
	RECT WndSize;
	GetClientRect(hWnd, &WndSize);
	left = WndSize.left + left;
	top = WndSize.top + top;
	right = WndSize.right - right;
	bottom = WndSize.bottom - bottom;
}


void graph::DrawLinesLables(CPaintDC& dc, CPen& WndPenLines, long left, long top, long right, long bottom, long x_axisY, long y_axisX, int LineFreq, int AxisLablesFreq) {
	//drawing lines-lables X
	dc.SelectObject(WndPenLines);


	long LineStepX = (right - y_axisX) / LineFreq;
	if (abs(right - left) > 50) {
		for (long step = y_axisX + LineStepX; step < right - 1; step += LineStepX) {
			dc.MoveTo(step, bottom - 5);
			dc.LineTo(step, top);
		}
		for (long step = y_axisX - LineStepX; step > left - 1; step -= LineStepX) {
			dc.MoveTo(step, bottom - 5);
			dc.LineTo(step, top);
		}
	}

	//drawing lines-lables Y
	long LineStepY = (bottom - x_axisY) / LineFreq;
	if (abs(bottom - top) > 50) {
		for (long step = x_axisY - LineStepY; step > top - 1; step -= LineStepY) {
			dc.MoveTo(left + 1, step);
			dc.LineTo(right - 2, step);
		}
		for (long step = x_axisY + LineStepY; step < bottom - 1; step += LineStepY) {
			dc.MoveTo(left + 1, step);
			dc.LineTo(right - 2, step);
		}
	}

}

void graph::DrawAxis(CPaintDC& dc, CPen& WndPenAxis, CFont& font, long left, long top, long right, long bottom, long x_axisY, long y_axisX, int PtrSize) {
	//drawing symbols
	dc.SelectObject(font);
	dc.TextOut(right - 20, x_axisY, _T("x"));
	dc.TextOut(y_axisX + 5, top + 5, _T("y"));


	//drawing Axis
	dc.SelectObject(WndPenAxis);
	dc.MoveTo(left, x_axisY);
	dc.LineTo(right, x_axisY);

	dc.MoveTo(y_axisX, top);
	dc.LineTo(y_axisX, bottom);

	//x - ptr
	dc.MoveTo(right - 1, x_axisY);
	dc.LineTo(right - PtrSize, x_axisY + PtrSize);
	dc.MoveTo(right - 1, x_axisY);
	dc.LineTo(right - PtrSize, x_axisY - PtrSize);
	dc.LineTo(right - PtrSize, x_axisY + PtrSize);

	//y - ptr
	dc.MoveTo(y_axisX, top);
	dc.LineTo(y_axisX - PtrSize, top + PtrSize);
	dc.MoveTo(y_axisX, top);
	dc.LineTo(y_axisX + PtrSize, top + PtrSize);
	dc.LineTo(y_axisX - PtrSize, top + PtrSize);
}

void graph::DrawComplex(CPaintDC& dc, CPen& WndPenResult,const std::complex<double>& g_complex, long left, long top, long bottom, long right, long y_axisX, long x_axisY, int LSTEP, int LineFreq) {
	long LineStepX = (right - y_axisX) / LineFreq;
	long LineStepY = (bottom - x_axisY) / LineFreq;

	dc.SelectObject(WndPenResult);
	dc.MoveTo(y_axisX, x_axisY);

	double factor = LineStepX / static_cast<double>(LSTEP);
	int resX = y_axisX + static_cast<int>(g_complex.real()*factor);
	int resY = x_axisY - static_cast<int>(g_complex.imag()*factor);
	dc.LineTo(resX, resY);
}

void graph::DrawLables(CPaintDC& dc, CFont& font, long right, long top, long left, long bottom, long x_axisY, long y_axisX, int LSTEP, int LineFreq, int AxisLablesFreq) {
	long LineStepX = (right - y_axisX) / LineFreq;
	long LineStepY = (bottom - x_axisY) / LineFreq;

	CString f_str;

	if (abs(right - left) > 50) {
		for (long step = y_axisX + LineStepX, i = 1, lable_step = LSTEP; step < right - 1; step += LineStepX, ++i, lable_step += LSTEP) {
			if (i < LineFreq && i % AxisLablesFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				dc.TextOut(step - 5, x_axisY + 2, f_str);
			}
		}
		for (long step = y_axisX - LineStepX, i = 1, lable_step = LSTEP; step > left - 1; step -= LineStepX, ++i, lable_step += LSTEP) {
			if (i < LineFreq && i % AxisLablesFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				dc.TextOut(step - 5, x_axisY + 2, f_str);
			}
		}
	}

	if (abs(bottom - top) > 50) {
		for (long step = x_axisY - LineStepY, i = 1, lable_step = LSTEP; step > top - 1; step -= LineStepY, ++i, lable_step += LSTEP) {
			if (i < LineFreq && i % AxisLablesFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				dc.TextOut(y_axisX + 2, step - 5, f_str);
			}
		}
		for (long step = x_axisY + LineStepY, i = 1, lable_step = LSTEP; step < bottom - 1; step += LineStepY, ++i, lable_step += LSTEP) {
			if (i < LineFreq && i % AxisLablesFreq == 0) {
				f_str.Format(_T("%i"), lable_step);
				dc.TextOut(y_axisX + 2, step - 5, f_str);
			}
		}
	}
}