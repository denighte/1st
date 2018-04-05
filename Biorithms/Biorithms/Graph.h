#pragma once
#pragma once
#include "stdafx.h"
#include <exception>
#include <complex>

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


		//Back ground style
		COLORREF _BgFillingColor;
		COLORREF _BgFrameColor;
		int _BgFrameWidth;

		//Axis style
		int _AxisWidth;
		COLORREF _AxisColor;


		//Grid style
		COLORREF _GridColor;
		int _GridFrequencyX;
		int _GridFrequencyY;

		//Labels style
		int _AxisLabelsFreqX;
		int _AxisLabelsFreqY;

		//Graph style
		long _LimitX;
		long _LimitY;

		const int WORK_SPACE_SIZE = 50;
		int GetLableFrequency(LONG number, wchar_t axis);

		void GetWorkSpace();
		bool DrawMarkingLinesX(LONG MarkingLineFreq);
		bool DrawMarkingLinesY(LONG MarkingLineFreq);
		void DrawAxis(int PtrSize = 5);
		void DrawLables();

	public:
		GPaint(CPaintDC& dc, const RECT & WorkSpace);
		GPaint(const GPaint &) = delete;
		GPaint & operator=(const GPaint &) = delete;

		void SetBgStyle(int BevelWidth, COLORREF BgColor, COLORREF LineColor);
		void SetAxisStyle(int AxisWidth, COLORREF LineColor);
		void SetGridColor(COLORREF Color);
		void SetLimits(long x, long y);

		void DrawCoordinateSystem();
		void SelectPoint(CPoint point, COLORREF color = RGB(212, 53, 53));
		CPoint DrawComplex(std::complex<double> number);  //returns the position of number on Coordinate System

	};


	int GetRoundTo(int number);
	//int GetLableStep(int number);





	class GPaint1 {
		CPaintDC& _dc;

		// rect for painting
		LONG _left;
		LONG _top;
		LONG _right;
		LONG _bottom;


		double minX;
		double maxX;
		double minY;
		double maxY;

		// размер сетки
		double dX;
		double dY;

		double labelStepX;
		double labelStepY;

		


		void SetLimits(double minX, double maxX, double minY, double maxY);
		void SetDeltas(double dX, double dY);
		void SetLabelsStep(double, double);


		void DrawCoordinateSytem();


		LONG toX(double v) { return v * ((_right - _left) / (maxX - minX)); }
		LONG toY(double v) { return v * ((_bottom - _top) / (maxY - minY)); }

		//Back ground style
		COLORREF _BgFillingColor;
		COLORREF _BgFrameColor;
		int _BgFrameWidth;

		//Axis style
		int _AxisWidth;
		COLORREF _AxisColor;


		//Grid style
		COLORREF _GridColor;
		int _GridFrequencyX;
		int _GridFrequencyY;

		//Labels style
		int _AxisLabelsFreqX;
		int _AxisLabelsFreqY;

		//Graph style
		long _LimitX;
		long _LimitY;

		const int WORK_SPACE_SIZE = 50;
		int GetLableFrequency(LONG number, wchar_t axis);

		void GetWorkSpace();
		bool DrawMarkingLinesX(LONG MarkingLineFreq);
		bool DrawMarkingLinesY(LONG MarkingLineFreq);
		void DrawAxis(int PtrSize = 5);
		void DrawLables();

	public:
		GPaint(CPaintDC& dc, const RECT & WorkSpace);
		GPaint(const GPaint &) = delete;
		GPaint & operator=(const GPaint &) = delete;

		void SetBgStyle(int BevelWidth, COLORREF BgColor, COLORREF LineColor);
		void SetAxisStyle(int AxisWidth, COLORREF LineColor);
		void SetGridColor(COLORREF Color);
		void SetLimits(long x, long y);

		void DrawCoordinateSystem();
		void SelectPoint(CPoint point, COLORREF color = RGB(212, 53, 53));
		CPoint DrawComplex(std::complex<double> number);  //returns the position of number on Coordinate System

	};

}