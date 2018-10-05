//#include "opencv2\opencv.hpp"
//#include <stdio.h>
//#include <memory>
//#include <iostream>
//using namespace cv;
//using namespace std;
//#define SIZE 256
//unsigned char BilinearInterpolation(unsigned char** gray, int nHeight_Ori, int nWidth_Ori, double h_cvt, double w_cvt) {
//	int x1 = (int)w_cvt;
//	int y1 = (int)h_cvt;
//	int x2 = x1 + 1;
//	int y2 = y1 + 1;
//
//	if (y1 == nHeight_Ori - 1 && x1 == nWidth_Ori - 1) {
//		x2 = x1; y2 = y1;
//	}
//	else if (y1 == nHeight_Ori - 1 || x1 != nWidth_Ori - 1) {
//		x2 = x1; y2 = y1;
//	}
//	else if (y1 != nHeight_Ori - 1 || x1 == nWidth_Ori - 1) {
//		x2 = x1; y2 = y1;
//	}
//
//	int x = w_cvt * gray[y1][x2] + (1 - w_cvt)*gray[y1][x1];
//	int y = w_cvt * gray[y2][x2] + (1 - w_cvt)*gray[y2][x1];
//
//	return h_cvt * x + (1 - h_cvt) * y;
//}
//
//void Bilinear(unsigned char** ori, unsigned char** des, int nw, int nh, double rate) {
//	int w = SIZE;
//	int h = SIZE;
//
//	int i, j, x1, y1, x2, y2;
//	double rx, ry, p, q, value;
//
//	for (j = 0; j < nh; j++)
//		for (i = 0; i < nw; i++) {
//			rx = static_cast<double>(w - 1)*i / (nw - 1);
//			ry = static_cast<double>(h - 1)*j / (nh - 1);
//
//			x1 = (int)rx;
//			y1 = (int)ry;
//
//			x2 = x1 + 1; if (x2 == w)x2 = w - 1;
//			y2 = y1 + 1; if (y2 == h)y2 = h - 1;
//
//			p = rx - x1;
//			q = ry - y1;
//
//			value = (1.0 - p) * (1.0 - q) * ori[y1][x1]
//				+ p * (1.0 - q) * ori[y1][x2]
//				+ (1.0 - p) * q * ori[y2][x1]
//				+ p * q * ori[y2][x2];
//			des[j][i] = (unsigned char)ceil(value + 0.5);
//
//
//			/*unsigned char x = rx * ori[y1][x2] + (1.0 - rx)*ori[y1][x1];
//			unsigned char y = rx * ori[y2][x2] + (1.0 - rx)*ori[y2][x1];
//			des[j][i] = (unsigned char)(ry * x + (1.0 - ry) * y);*/
//		}
//}
//
//
//
//void main()
//{
//	char * imgpath = "lena256.raw";
//	FILE * f = fopen(imgpath, "rb");
//	if (!f)
//	{
//		printf("bad path : %s\n", imgpath);
//		return;
//	}
//
//	unsigned char pixels[SIZE * SIZE];
//	fread(pixels, SIZE * SIZE, 1, f);
//
//	double dScaleRate;
//	scanf("%lf", &dScaleRate);
//	//pixels 가 픽셀값이니까 
//
//	//스케일링 후 영상의 크기 계산
//	int nHeight_Scale = SIZE * dScaleRate;
//	int nWidth_Scale = SIZE * dScaleRate;
//
//	unsigned char** input;
//	input = new unsigned char*[SIZE];
//	for (int i = 0; i < SIZE; i++)
//		input[i] = new unsigned char[SIZE];
//
//	unsigned char** output;
//	output = new unsigned char*[nHeight_Scale];
//	for (int i = 0; i < nHeight_Scale; i++)
//		output[i] = new unsigned char[nHeight_Scale];
//
//	for (int i = 0; i < SIZE; i++) {
//		for (int j = 0; j < SIZE; j++) {
//			input[i][j] = pixels[i*SIZE + j];
//		}
//	}
//
//	Bilinear(input, output, nWidth_Scale, nHeight_Scale, dScaleRate);
//
//
//	Mat last = Mat(nHeight_Scale, nWidth_Scale, 1);
//	for (int i = 0; i < nHeight_Scale; i++) {
//		for (int j = 0; j < nWidth_Scale; j++) {
//			last.at<unsigned char>(i, j) = output[i][j];
//			cout << output[i][j];
//		}
//	}
//	imshow("lena", last);
//	waitKey(0);
//	fclose(f);
//
//}
