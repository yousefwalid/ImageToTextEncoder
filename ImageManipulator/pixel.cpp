#include "pixel.h"



pixel::pixel()
{
}

pixel::pixel(int r, int g, int b)
{
	setValues(r, g, b);
}

void pixel::setValues(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->lum = 0.299*r + 0.587*g + 0.114*b;
}

int pixel::getLum()
{
	return lum;
}



pixel::~pixel()
{
}
