//#include "opencv2\opencv.hpp"
//#include <stdio.h>
//#include <memory>
//#include <iostream>
//#define _USE_MATH_DEFINES
//#include <math.h>
//using namespace cv;
//using namespace std;
//#define SIZE 256
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
//	fread(pixels, SIZE * SIZE, 1, f); //Read Image File
//
//
//	unsigned char** input;
//	input = new unsigned char*[SIZE];
//	for (int i = 0; i < SIZE; i++)
//		input[i] = new unsigned char[SIZE]; //Create Value for copy pixels
//
//	unsigned char** output2; //Dynamic allocate Output Image for Histogram Equalization
//	output2 = new unsigned char*[SIZE];
//	for (int i = 0; i < SIZE; i++)
//		output2[i] = new unsigned char[SIZE];
//
//	for (int i = 0; i < SIZE; i++) { //Copy pixels from File
//		for (int j = 0; j < SIZE; j++) {
//			input[i][j] = pixels[i*SIZE + j];
//		}
//	}
//
//	int *Hist = new int[SIZE];
//	for (int h = 0; h < SIZE; h++) {
//		for (int w = 0; w < SIZE; w++) {
//			Hist[input[h][w]]++;
//		}
//	}//Create Input Histogram
//
//	double Hist_CDF[256] = { 0.0 };
//	double temp[256] = { 0.0 };
//	temp[0] = Hist[0];
//
//	for (int i = 1; i < 256; i++) {
//		temp[i] = Hist[i] + temp[i - 1];
//	}
//	for (int i = 0; i < 256; i++) {
//		Hist_CDF[i] = temp[i] / (SIZE*SIZE);
//	}//Make CDF
//
//	for (int h = 0; h < SIZE; h++) {
//		for (int w = 0; w < SIZE; w++) {
//			output2[h][w] = floor(Hist_CDF[input[h][w]] * 255 + 0.5);
//		}
//	}//Get transformed pixel value from CDF
//
//
//	Mat first = Mat(SIZE, SIZE, CV_8UC1);
//	for (int i = 0; i < SIZE; i++) {
//		for (int j = 0; j < SIZE; j++) {
//			first.at<unsigned char>(i, j) = input[i][j];
//		}
//	}//Mat for Original Image
//
//	Mat last2 = Mat(SIZE, SIZE, CV_8UC1);
//	for (int i = 0; i < SIZE; i++) {
//		for (int j = 0; j < SIZE; j++) {
//			last2.at<unsigned char>(i, j) = output2[i][j];
//		}
//	}//Create and Copy pixels for Result of Rotation
//
//	imshow("lena", first);
//	imshow("Histogram Equalization", last2);
//	waitKey(0);
//	fclose(f);
//}
