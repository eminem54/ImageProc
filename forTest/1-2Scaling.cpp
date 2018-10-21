#include <opencv2\opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
#define SIZE 256
unsigned char bilinear(unsigned char** ori, double hrotate, double wrotate) {
	int x1, x2, y1, y2;
	x1 = (int)wrotate;
	x2 = x1 + 1; if (x2 >= SIZE)x2 = x1;
	y1 = (int)hrotate;
	y2 = y1 + 1; if (y2 >= SIZE)y2 = y1;

	int p = (wrotate - x1)*ori[y1][x2] + (1 - (wrotate - x1))*ori[y1][x1];
	int q = (wrotate - x1)*ori[y2][x2] + (1 - (wrotate - x1))*ori[y2][x2];

	int r = ((hrotate - y1)*q + (1 - (hrotate - y1))*p);
	return r;
}
int main() {
	FILE* f;
	const char* inputPath = "lena256.raw";
	fopen_s(&f, inputPath, "rb");

	unsigned char input[SIZE*SIZE];
	fread(input, SIZE*SIZE, 1, f);

	unsigned char** pixels = new unsigned char*[SIZE];
	for (int i = 0; i < SIZE; i++) {
		pixels[i] = new unsigned char[SIZE];
	}
	
	for (int h = 0; h < SIZE; h++) {
		for (int w = 0; w < SIZE; w++) {
			pixels[h][w] = input[h*SIZE + w];
		}
	}

	double scaleRate = 0;
	scanf("%lf", &scaleRate);
	int scaleHeight = SIZE*scaleRate;
	int scaleWidth= SIZE*scaleRate;

	unsigned char** bigImage = new unsigned char*[scaleHeight];
	for (int i = 0; i < scaleHeight; i++) {
		bigImage[i] = new unsigned char[scaleWidth];
	}

	for (int h = 0; h < scaleHeight; h++) {
		for (int w = 0; w < scaleWidth; w++) {
			double wconvert = w / scaleRate;
			double hconvert = h / scaleRate;

			
			bigImage[h][w] = bilinear(pixels, hconvert, wconvert);
		}
	}

	//for (int h = 0; h < scaleHeight; h++) {
	//	for (int w = 0; w < scaleWidth; w++) {
	//		double wconvert = w / scaleRate;
	//		double hconvert = h / scaleRate;

	//		int x1, x2, y1, y2;
	//		x1 = (int)wconvert;
	//		x2 = x1 + 1; if (x2 >= SIZE)x2 = x1;
	//		y1 = (int)hconvert;
	//		y2 = y1 + 1; if (y2 >= SIZE)y2 = y1;

	//		int p = (wconvert - x1)*pixels[y1][x2] + (1 - (wconvert - x1))*pixels[y1][x1];
	//		int q = (wconvert - x1)*pixels[y2][x2] + (1 - (wconvert - x1))*pixels[y2][x2];

	//		int r = ((hconvert - y1)*q + (1 - (hconvert - y1))*p);
	//		bigImage[h][w] = (unsigned char)r;
	//	}
	//}

	Mat result = Mat(scaleHeight, scaleWidth, CV_8UC1);
	for (int h = 0; h < scaleHeight; h++) {
		for (int w = 0; w < scaleWidth; w++) {
			result.at<unsigned char>(h,w) = bigImage[h][w];
		}
	}

	imshow("scaled", result);
	waitKey(0);
	return 0;
}