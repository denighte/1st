#pragma once
#include "stdafx.h"
#include <exception>

namespace graphic {
	class GPaint {
	private:
		CPaintDC& _dc;
		LONG _left;
		LONG _top;
		LONG _right;
		LONG _bottom;

		//Graph limits
		double _LimitMaxX;
		double _LimitMaxY;
		double _LimitMinX;
		double _LimitMinY;


		// размер сетки
		double dX;
		double dY;

		double labelStepX;
		double labelStepY;

		//Labels frequency
		int _AxisLabelsFreqX;
		int _AxisLabelsFreqY;
		int GetAxisLabelsFrequency(char axis);


		//void SetLimits(double minX, double maxX, double minY, double maxY);
		//void SetDeltas(double dX, double dY);
		//void SetLabelsStep(double, double);

		LONG toX(double vx) { return v * ((_right - _left) / (_LimitMaxX - _LimitMinX)); }
		LONG toY(double vy) { return v * ((_bottom - _top) / (_LimitMaxY - _LimitMinY)); }


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

		const int WORK_SPACE_SIZE = 50;
		int GetLableFrequency(LONG number, wchar_t axis);

		void GetWorkSpace();
		bool DrawMarkingLinesX(LONG MarkingLineFreq);
		bool DrawMarkingLinesY(LONG MarkingLineFreq);
		void DrawAxis(int PtrSize = 5);

	public:
		GPaint(CPaintDC& dc, const RECT & WorkSpace);
		GPaint(const GPaint &) = delete;
		GPaint & operator=(const GPaint &) = delete;

		void SetBgStyle(int BevelWidth, COLORREF BgColor, COLORREF LineColor);
		void SetAxisStyle(int AxisWidth, COLORREF LineColor);
		void SetGridColor(COLORREF Color);
		void SetLimits(double minX, double maxX, double minY, double maxY);

		void DrawCoordinateSystem();
	};


	double GetRound(double number);

}