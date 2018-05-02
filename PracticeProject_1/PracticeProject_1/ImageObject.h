#pragma once
#include "stdafx.h"
class ImageObject {
private:
	CDC* dcMemory_;
	int width_;
	int height_;
	CBitmap* pOldBitmap_;
	bool empty_;
public:
	ImageObject() : empty_(true) {}
	ImageObject(CDC& dc, int width, int height);
	~ImageObject();

	bool isEmpty() { return empty_; }
	void Draw(CDC& dc, int x, int y, int xSrc, int ySrc, DWORD dwRop);
};