#include "opencv2\opencv.hpp"
#include <stdio.h>
#include <memory>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace cv;
using namespace std;
#define SIZE 256
unsigned char Bilinear(unsigned char** gray, int nHeight_Ori, int nWidth_Ori, double h_cvt, double w_cvt) {
	int x1 = (int)w_cvt;
	int y1 = (int)h_cvt;
	int x2 = x1 + 1;
	int y2 = y1 + 1;

	if (y1 == nHeight_Ori - 1 && x1 == nWidth_Ori - 1) {
		x2 = x1; y2 = y1;
	}
	else if (y1 == nHeight_Ori - 1 || x1 != nWidth_Ori - 1) {
		x2 = x1; y2 = y1;
	}
	else if (y1 != nHeight_Ori - 1 || x1 == nWidth_Ori - 1) {
		x2 = x1; y2 = y1;
	}

	int x = w_cvt * gray[y1][x2] + (1 - w_cvt)*gray[y1][x1];
	int y = w_cvt * gray[y2][x2] + (1 - w_cvt)*gray[y2][x1];

	return h_cvt * x + (1 - h_cvt) * y;
}

void main()
{
	char * imgpath = "lena256.raw";
	FILE * f = fopen(imgpath, "rb");
	if (!f)
	{
		printf("bad path : %s\n", imgpath);
		return;
	}

	unsigned char pixels[SIZE * SIZE];
	fread(pixels, SIZE * SIZE, 1, f); //Read Image File

	double angle;
	cout << "Input Rotation Angle" << endl;
	scanf("%lf", &angle); //Input Rate and Angle 

	unsigned char** input;
	input = new unsigned char*[SIZE];
	for (int i = 0; i < SIZE; i++)
		input[i] = new unsigned char[SIZE]; //Create Value for copy pixels

	unsigned char** output2; //Dynamic allocate Output Image for Rotation
	output2 = new unsigned char*[SIZE];
	for (int i = 0; i < SIZE; i++)
		output2[i] = new unsigned char[SIZE];

	for (int i = 0; i < SIZE; i++) { //Copy pixels from File
		for (int j = 0; j < SIZE; j++) {
			input[i][j] = pixels[i*SIZE + j];
		}
	}




	int nHeight_2 = 256 / 2;
	int nWidth_2 = 256 / 2;

	double rad = (angle * M_PI) / 180.0;

	double cos_value = cos(rad);
	double sin_value = sin(rad);

	double h_Rotate = 0;
	double w_Rotate = 0;

	for (int h = 0; h < SIZE; h++) {
		for (int w = 0; w < SIZE; w++) {

			double h_Rotate = (cos_value*(h - nHeight_2) - sin_value*(w - nHeight_2)) + nHeight_2;
			double w_Rotate = (sin_value*(h - nHeight_2) + cos_value*(w - nHeight_2)) + nHeight_2;

			if (h_Rotate >= 0 && w_Rotate >= 0 && h_Rotate < SIZE && w_Rotate < SIZE) {

				output2[h][w] = Bilinear(input, SIZE, SIZE, h_Rotate, w_Rotate);

			}
		}
	} //Rotation
	Mat first = Mat(SIZE, SIZE, CV_8UC1);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			first.at<unsigned char>(i, j) = input[i][j];
		}
	}

	Mat last2 = Mat(SIZE, SIZE, CV_8UC1);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			last2.at<unsigned char>(i, j) = output2[i][j];
		}
	}//Create and Copy pixels for Result of Rotation

	imshow("lena", first);

	imshow("Rotation", last2);
	waitKey(0);
	fclose(f);
}
