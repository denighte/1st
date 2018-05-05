#pragma once
#include "stdafx.h"
#include <string>
class ImageObject {
private:
	CDC dcMemory_;
	BITMAP bmpInfo_;
	CBitmap* pOldBitmap_;
	bool init_;

	void shift_(int &x, int &y) {
		x -= bmpInfo_.bmWidth/2;
	}
public:
	ImageObject() : init_(false) {}
	~ImageObject() {
		if(init_)
			dcMemory_.SelectObject(pOldBitmap_);
	}

	bool LoadFromFile(CDC& dc,const std::wstring& path) {
		CBitmap bmp_;
		CImage image;
		if (!image.Load(path.c_str())) {
			init_ = true;

			bmp_.Attach(image.Detach());
			bmp_.GetBitmap(&bmpInfo_);
			dcMemory_.CreateCompatibleDC(&dc);
			pOldBitmap_ = dcMemory_.SelectObject(&bmp_);

			return true;
		}
		else {
			init_ = false;
			return false;
		}
	}

	void Rotate() {
		if (!init_)
			throw std::logic_error("ImageObject initialization error");
		for (int y = 0; y < bmpInfo_.bmHeight / 2; y++)
		{
			for (int x = 0; x < bmpInfo_.bmWidth; x++)
			{
				COLORREF rgb1 = dcMemory_.GetPixel(x, y);
				COLORREF rgb2 = dcMemory_.GetPixel(x, bmpInfo_.bmHeight - y - 1);

				BYTE r = GetRValue(rgb2);
				BYTE g = GetGValue(rgb2);
				BYTE b = GetBValue(rgb2);
				dcMemory_.SetPixel(x, y, RGB(r, g, b));

				r = GetRValue(rgb1);
				g = GetGValue(rgb1);
				b = GetBValue(rgb1);
				dcMemory_.SetPixel(x, bmpInfo_.bmHeight - y - 1, RGB(r, g, b));

			}
		}
	}

	bool isInit() { return init_; }

	void Draw(CDC& dc, int x, int y, int xSrc, int ySrc, DWORD dwRop) {
		if (!init_)
			throw std::logic_error("ImageObject initialization error");
		shift_(x, y);
		dc.BitBlt(x, y, bmpInfo_.bmWidth, bmpInfo_.bmHeight, &dcMemory_,
			0, 0, SRCCOPY | NOMIRRORBITMAP);
	}
};