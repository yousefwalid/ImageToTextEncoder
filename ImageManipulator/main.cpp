#include <iostream>
#include <fstream>
#include <string>
#include "pixel.h"
#include <locale>
#include <codecvt>
#include <cstdio>  // for _fileno
#include <io.h>    // for _setmode
#include <fcntl.h> // for _O_U16TEXT
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

pixel** ReadImage(int& width, int& height, int& maxRGB, string& s); //responsible for reading the image and transferring it into an array of pixels
void PrintImage(const int& width, const int& height,const int& maxRGB, pixel** grid,const string& fileName); //responsible for printing the image


int main()
{
	int w, h, maxRGB;
	string filename;
	pixel** ImageGrid = ReadImage(w,h,maxRGB,filename);

	PrintImage(w, h, maxRGB, ImageGrid,filename);
	

	cout << "Completed!\nSet your font to Arial, size 2" << endl <<endl;
	system("pause");

}

pixel** ReadImage(int& width, int& height, int& maxRGB, string& s)
{

	wcout << "Enter the image name" << endl;
	maxRGB = 255;
	cin >> s;
	Mat inputImg = imread(s);

	while (!inputImg.data)
	{
		wcout << "Image not found, please enter a valid input\nmake sure the image is in the same directory\n\n";
		cin >> s;
		inputImg = imread(s);
	}

	height = inputImg.rows;
	width = inputImg.cols;

	if (width > 300)
	{
		double ratio = 300.0/width;
		resize(inputImg, inputImg, Size(), ratio, ratio);
	}

	height = inputImg.rows;
	width = inputImg.cols;


	pixel** pixelGrid; 
	pixelGrid = new pixel*[height];
	for (int i = 0; i < height; i++)
		pixelGrid[i] = new pixel[width];

	int r, g, b;

	for(int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			b = inputImg.at<Vec3b>(i, j)[0];
			g = inputImg.at<Vec3b>(i, j)[1];
			r = inputImg.at<Vec3b>(i, j)[2];
			pixelGrid[i][j].setValues(r, g, b);
		}

	return pixelGrid;
}

void PrintImage(const int& width, const int& height, const int& maxRGB, pixel** grid, const string& fileName)
{
	double ratio = maxRGB / 5.0;

	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
	string temp = fileName;
	temp.pop_back(); 	temp.pop_back(); 	temp.pop_back(); 	temp.pop_back();
	wofstream op(temp + ".txt");
	op.imbue(utf8_locale);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (grid[i][j].getLum() < 1 * ratio)
				op << L"\x2588\x2588";
			else if (grid[i][j].getLum() < 2 * ratio)
				op << L"\x2593\x2593";
			else if (grid[i][j].getLum() < 3 * ratio)
				op << L"\x2592\x2592";
			else if (grid[i][j].getLum() < 4 * ratio)
				op << L"\x2591\x2591";
			else
				op << L"    ";
		}
		op << endl;
	}
}