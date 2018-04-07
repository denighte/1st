#pragma once
#include "stdafx.h"
#include <exception>
#include <cmath>

typedef double(*GraphFunction)(double);
typedef CString(*LabelStepCalc)(double);

class GPaint : public CWnd {
private:
	CONST INT MIN_WORK_SPACE_SIZE = 50;

	//Paint Device Context and size of the current window:
	CPaintDC& _dc;
	LONG _left;
	LONG _top;
	LONG _right;
	LONG _bottom;

	//Graph limits:
	double _LimitMaxX;
	double _LimitMaxY;
	double _LimitMinX;
	double _LimitMinY;
	double GetRound(double number);

	//Functions - converters from conventional units to pixels:
	LONG toX(double vx) { return static_cast<LONG>( _left + ((-_LimitMinX + vx) * ((_right - _left) / (_LimitMaxX - _LimitMinX))) ); }
	LONG toY(double vy) { return static_cast<LONG>( _top - ((-_LimitMaxY + vy) * ((_bottom - _top) / (_LimitMaxY - _LimitMinY))) ); }

	//Difference between two adjacent grid lines (on x, and on y)
	double _dx;
	double _dy;

	//Labels definition:
	double _LabelStepX;
	double _LabelStepY;
	double GetAxisLabelsFrequency(char axis);
	LabelStepCalc GetStepX = DefaultStepX;
	LabelStepCalc GetStepY = DefaultStepY;

	friend CString DefaultStepX(double value);
	friend CString DefaultStepY(double value);

	//void SetLimits(double minX, double maxX, double minY, double maxY);
	//void SetDeltas(double dX, double dY);
	//void SetLabelsStep(double, double);

	//Grid style
	COLORREF _GridColor;
	//double GetGridDeltas (LONG number, wchar_t axis);

	//Back ground style
	COLORREF _BgFillingColor;
	COLORREF _BgFrameColor;
	int _BgFrameWidth;

	//Axis style
	int _AxisWidth;
	COLORREF _AxisColor;

	//graph style
	int _gStyle; 
	int _gWidth;
	COLORREF _glColor;


	void GetWorkSpace();
	void DrawGridLinesX();	
	void DrawGridLinesY();
	void DrawAxis();
	void DrawLabels();
public:
	GPaint();
	GPaint(CPaintDC& dc, const RECT & WorkSpace);
	GPaint(const GPaint &) = delete;
	GPaint & operator=(const GPaint &) = delete;

	BOOL RegisterWindowClass();

	void __vectorcall SetBgStyle(
		int BevelWidth = 2, 
		COLORREF BgColor = RGB(255, 255, 255),
		COLORREF LineColor = RGB(0, 128, 0)
	);


	void __fastcall SetAxisStyle(
		int AxisWidth = 1, 
		COLORREF LineColor = RGB(0, 0, 0)
	);

	void SetGridColor(COLORREF Color) { _GridColor = Color; };

	void __vectorcall SetGraphStyle(
		int gStyle = PS_SOLID, 
		int gWidth = 1, 
		COLORREF glColor = RGB(212, 53, 53)
	);

	void __vectorcall SetLimits(double minX, double maxX, double minY, double maxY);
	void SetCustomLabelsX(CString(*XLabel)(double)) { GetStepX = XLabel; };
	void SetCustomLabelsY(CString(*YLabel)(double)) { GetStepY = YLabel; };

	void SetGridDeltas(double x, double y); //temporary
	void SetLableSteps(double x, double y);  //temporary

	bool DrawCoordinateSystem();
	void DrawLine(double x1, double y1, double x2, double y2);
	void DrawGraph(GraphFunction);

	class InitErrorException : std::exception {};
};
