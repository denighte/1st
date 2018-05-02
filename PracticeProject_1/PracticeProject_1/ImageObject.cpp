#include "ImageObject.h"
ImageObject::~ImageObject() {
	dcMemory_-> SelectObject(pOldBitmap_);
}

ImageObject(CDC& dc, int width, int height) : dcMemory(&dc), width_(width), height_(height)  {}