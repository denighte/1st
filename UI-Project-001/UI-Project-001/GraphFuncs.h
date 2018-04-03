#pragma once
#include <complex>
namespace graph {
	int GetRoundTo10(int number);
	void GetWndWorkSpace(HWND hWnd, long& left, long& top, long& right, long& bottom);
	void DrawLinesLables(CPaintDC& dc, CPen& WndPenLines, long left, long top, long right, long bottom, long x_axisY, long y_axisX, int LineFreq, int AxisLablesFreq);
	void DrawAxis(CPaintDC& dc, CPen& WndPenAxis, CFont& font, long left, long top, long right, long bottom, long x_axisY, long y_axisX, int PtrSize);
	void DrawComplex(CPaintDC& dc, CPen& WndPenResult, const std::complex<double>& g_complex, long left, long top, long bottom, long right, long y_axisX, long x_axisY, int LSTEP, int LineFreq);
	void DrawLables(CPaintDC& dc, CFont& font, long right, long top, long left, long bottom, long x_axisY, long y_axisX, int LSTEP, int LineFreq, int AxisLablesFreq = 2);
}
