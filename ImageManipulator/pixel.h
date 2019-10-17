#pragma once
class pixel
{
private:
	int r=0, g=0, b=0;
	double lum;
public:
	pixel();
	pixel(int r, int g, int b);
	void setValues(int r, int g, int b);
	int getLum();
	~pixel();
};

