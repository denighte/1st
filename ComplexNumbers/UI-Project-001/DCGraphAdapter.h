#pragma once
#include "stdafx.h"
#include <exception>
#include <complex>

#define GRAPHIC_DEFAULT_TOOL 0
namespace graphic {
	class GPaint {
	private:
		CPaintDC& _dc;
		LONG _left;
		LONG _top;
		LONG _right;
		LONG _bottom;
		LONG _x_axisY;
		LONG _y_axisX;
		LONG _MarkingLineStepX;
		LONG _MarkingLineStepY;

		int _AxisLabelsFreq;

		int _MarkingLinesCntX;
		int _MarkingLinesCntY;

		//Back ground style
		COLORREF _BgFillingColor;
		COLORREF _BgFrameColor;
		int _BgFrameWidth;



		//Axis style
		int _AxisWidth;
		COLORREF _AxisColor;


		//Grid style
		COLORREF _GridColor;
		int _GridNumber;


		const int WORK_SPACE_SIZE = 50;
		int GetLableFrequency(LONG number, wchar_t axis);			 

		void GetWorkSpace();
		bool DrawMarkingLinesX(LONG MarkingLineFreq = GRAPHIC_DEFAULT_TOOL);
		bool DrawMarkingLinesY(LONG MarkingLineFreq = GRAPHIC_DEFAULT_TOOL);
		void DrawAxis(int PtrSize = 5);
		void DrawLables(LONG MaxNumber, LONG scale = 10, int AxisLablesFreq = GRAPHIC_DEFAULT_TOOL);

	public:
		GPaint(CPaintDC& dc, const RECT & WorkSpace); //AxisLablesFreq - less <=> more often
		GPaint(const GPaint &) = delete;
		GPaint & operator=(const GPaint &) = delete;

		void SetBgStyle(int BevelWidth, COLORREF BgColor, COLORREF LineColor);
		void SetAxisStyle(int AxisWidth, COLORREF LineColor);
		void SetGridColor(COLORREF Color);
		void SetGridFrequency(int Freq);

		void DrawCoordinateSystem();
		void SelectPoint(CPoint point, COLORREF color = RGB(212, 53, 53));
		CPoint DrawComplex(std::complex<double> number);  //returns the position of number on Coordinate System

		class DefaulToolError : std::exception {};
	};


	int GetRoundTo(int number);
	//int GetLableStep(int number);
}