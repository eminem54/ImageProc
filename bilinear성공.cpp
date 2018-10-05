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
//	for (int h = 0; h < nHeight_Scale; h++) {
//		for (int w = 0; w < nWidth_Scale; w++) {
//			double h_Ori = h / dScaleRate;
//			double w_Ori = w / dScaleRate;
//			output[h][w] = BilinearInterpolation(input, SIZE, SIZE, h_Ori, w_Ori);
//		}
//	}
//
//	Mat last = Mat(nHeight_Scale, nWidth_Scale, CV_8UC1);
//	for (int i = 0; i < nHeight_Scale; i++) {
//		for (int j = 0; j < nWidth_Scale; j++) {
//			last.at<unsigned char>(i, j) = output[i][j];
//		}
//	}
//	imshow("lena", last);
//	waitKey(0);
//	fclose(f);
//
//}
