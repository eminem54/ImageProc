//#include "opencv2\opencv.hpp"
//#include <stdio.h>
//#include <memory>
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#define _USE_MATH_DEFINES
//#include <math.h>
//using namespace cv;
//using namespace std;
//#define SIZE 256
//
//
//unsigned char** Padding(unsigned char** in, int nHeight, int nWidth, int nFilterSize) {
//	int nPadSize = (int)(nFilterSize / 2);
//
//	unsigned char** Pad; //Dynamic allocate Output Image for Average Filter size7
//	Pad = new unsigned char*[SIZE+2 * nPadSize];
//	for (int i = 0; i < SIZE +2 * nPadSize; i++)
//		Pad[i] = new unsigned char[SIZE +2 * nPadSize];
//
//	for (int h = 0; h < nHeight; h++) {
//		for (int w = 0; w < nWidth; w++) {
//			Pad[h + nPadSize][w + nPadSize] = in[h][w];
//		}
//	}
//	for (int h = 0; h < nPadSize; h++) {
//		for (int w = 0; w < nWidth; w++) {
//			Pad[h][w + nPadSize] = in[0][w];
//			Pad[h + (nHeight - 1)][w + nPadSize] = in[nHeight - 1][w];
//		}
//	}
//	for (int h = 0; h < nHeight; h++) {
//		for (int w = 0; w < nPadSize; w++) {
//			Pad[h + nPadSize][w] = in[h][0];
//			Pad[h + nPadSize][w + (nWidth - 1)] = in[h][nWidth - 1];
//		}
//	}
//	for (int h = 0; h < nPadSize; h++) {
//		for (int w = 0; w < nPadSize; w++) {
//			Pad[h][w] = in[0][0];
//			Pad[h + (nHeight - 1)][w] = in[nHeight - 1][0];
//			Pad[h][w + (nWidth - 1)] = in[0][nWidth - 1];
//			Pad[h + (nHeight - 1)][w + (nWidth - 1)] = in[nHeight - 1][nWidth - 1];
//		}
//	}
//	return Pad;
//}
//
//unsigned char** allocate2DImgae(int h, int w) {
//	unsigned char** input = new unsigned char*[h];
//	for (int i = 0; i < h; i++)
//		input[i] = new unsigned char[w];
//	return input;
//}
//Mat copyPixelValue(unsigned char** ori, int h, int w) {
//	Mat last2 = Mat(h, w, CV_8UC1);
//	for (int i = 0; i < h; i++) {
//		for (int j = 0; j < w; j++) {
//			last2.at<unsigned char>(i, j) = ori[i][j];
//		}
//	}//Create and Copy pixels for Result of AverageFilter
//	return last2;
//}
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
//	fread(pixels, SIZE * SIZE, 1, f); //Read Image File
//
//	unsigned char** input = allocate2DImgae(SIZE, SIZE);
//
//	for (int i = 0; i < SIZE; i++) { //Copy pixels from File
//		for (int j = 0; j < SIZE; j++) {
//			input[i][j] = pixels[i*SIZE + j];
//		}
//	}
//
//	unsigned char** output1 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//	unsigned char** output2 = allocate2DImgae(SIZE, SIZE); //Create Value for copy pixels
//	unsigned char** output3 = allocate2DImgae(SIZE, SIZE); //Create Value for copy pixels
//	unsigned char** output4 = allocate2DImgae(SIZE, SIZE); //Create Value for copy pixels
//	unsigned char** output5 = allocate2DImgae(SIZE, SIZE); //Create Value for copy pixels
//
//	double masksize1 = 9.0;
//	double masksize2 = 49.0;
//	double filterWeight = 16.0;
//	unsigned char** pad1 = Padding(input, SIZE, SIZE, 3);
//	unsigned char** pad2 = Padding(input, SIZE, SIZE, 7);
//
//	int SmoothFilter[3][3] = { {1,2,1},{2,4,2},{1,2,1} };
//	int SharpeningFilter[3][3] = { {0,-1,0},{-1,5,-1},{0,-1,0} };
//
//
//	int sum = 0;
//	for (int h = 1; h < SIZE-1; h++)
//		for (int w = 1; w < SIZE-1; w++) {
//			sum = 0;
//			for(int i=0; i<3; i++)
//				for (int j = 0; j < 3; j++) {
//					sum += pad1[h + i - 1][w + j - 1];
//				}
//			output1[h-1][w-1] = (unsigned char)ceil(sum / masksize1 + 0.5);
//		}
//
//	sum = 0;
//	for (int h = 3; h < SIZE-3; h++)
//		for (int w = 3; w < SIZE-3; w++) {
//			sum = 0;
//			for (int i = 0; i < 7; i++)
//				for (int j = 0; j < 7; j++) {
//					sum += pad2[h + i - 3][w + j - 3];
//				}
//			output2[h][w] = (unsigned char)ceil(sum / masksize2 + 0.5);
//		}
//
//	sum = 0;
//	for (int h = 1; h < SIZE - 1; h++)
//		for (int w = 1; w < SIZE - 1; w++) {
//			sum = 0;
//			for (int i = 0; i < 3; i++)
//				for (int j = 0; j < 3; j++) {
//					sum += pad1[h + i - 1][w + j - 1]*SmoothFilter[i][j];
//				}
//			output3[h][w] = (unsigned char)ceil(sum / filterWeight + 0.5);
//		}
//
//	sum = 0;
//	for (int h = 1; h < SIZE - 1; h++)
//		for (int w = 1; w < SIZE - 1; w++) {
//			sum = 0;
//			for (int i = 0; i < 3; i++)
//				for (int j = 0; j < 3; j++) {
//					sum += pad1[h + i - 1][w + j - 1] * SharpeningFilter[i][j];
//				}
//			if (sum < 0) sum = 0;
//			if (sum > 255) sum = 255;
//			output4[h][w] = (unsigned char)ceil(sum + 0.5);
//		}
//
//	for (int h = 1; h < SIZE - 1; h++)
//		for (int w = 1; w < SIZE - 1; w++) {
//			vector<unsigned char> median;
//			for (int i = 0; i < 3; i++)
//				for (int j = 0; j < 3; j++) {
//					median.push_back(pad1[h + i - 1][w + j - 1]);
//				}
//			sort(median.begin(), median.end());
//			output5[h][w] = (unsigned char)median[4];
//		}
//
//	Mat first = copyPixelValue(input, SIZE, SIZE);
//	Mat last1 = copyPixelValue(output1, SIZE, SIZE);
//	Mat last2 = copyPixelValue(output2, SIZE, SIZE);//Create and Copy pixels for Result of AverageFilter
//	Mat last3 = copyPixelValue(output3, SIZE, SIZE);//Create and Copy pixels for Result of AverageFilter
//	Mat last4 = copyPixelValue(output4, SIZE, SIZE);//Create and Copy pixels for Result of AverageFilter
//	Mat last5 = copyPixelValue(output5, SIZE, SIZE);//Create and Copy pixels for Result of AverageFilter
//
//	imshow("lena", first);
//	imshow("Filter size 3x3", last1);
//	imshow("Filter size 9x9", last2);
//	imshow("Smooth Filter", last3);
//	imshow("Sharpening Filter", last4);
//	imshow("Median Filter", last5);
//
//	waitKey(0);
//	fclose(f);
//}
