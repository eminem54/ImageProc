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
//FILE* getImage(const char* path) {
//	FILE * f = fopen(path, "rb");
//	if (!f)
//	{
//		printf("bad path : %s\n", path);
//		return NULL;
//	}
//	return f;
//}
//void main()
//{
//	double masksize1 = 9.0;
//	double masksize2 = 49.0;
//	double filterWeight = 16.0;
//
//	int SmoothFilter[3][3] = { { 1,2,1 },{ 2,4,2 },{ 1,2,1 } };
//	int SharpeningFilter[3][3] = { { 0,-1,0 },{ -1,5,-1 },{ 0,-1,0 } };
//
//	int flag = 1;
//	while (flag) {
//		int filter;
//
//		cout << "원하는 필터를 선택하세요(숫자+엔터)\n";
//		cout << "1. Average Filter 3x3\n";
//		cout << "2. Average Filter 7x7\n";
//		cout << "3. Smooth Filter\n";
//		cout << "4. Sharpening Filter\n";
//		cout << "5. Median Filter\n";
//		cout << "6. exit\n";
//
//		cin >> filter;
//		switch (filter) {
//		case 1: {
//			char * imgpath = "lena256.raw";
//			FILE *f = getImage(imgpath);
//
//			unsigned char pixels[SIZE * SIZE];
//			fread(pixels, SIZE * SIZE, 1, f); //Read Image File
//
//			unsigned char** input = allocate2DImgae(SIZE, SIZE);
//
//			for (int i = 0; i < SIZE; i++) { //Copy pixels from File
//				for (int j = 0; j < SIZE; j++) {
//					input[i][j] = pixels[i*SIZE + j];
//				}
//			}
//			unsigned char** pad1 = Padding(input, SIZE, SIZE, 3);
//
//			unsigned char** output1 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//
//			int sum = 0;
//			for (int h = 1; h < SIZE - 1; h++)
//				for (int w = 1; w < SIZE - 1; w++) {
//					sum = 0;
//					for (int i = 0; i < 3; i++)
//						for (int j = 0; j < 3; j++) {
//							sum += pad1[h + i - 1][w + j - 1];
//						}
//					output1[h - 1][w - 1] = (unsigned char)ceil(sum / masksize1 + 0.5);
//				}
//
//
//			Mat first = copyPixelValue(input, SIZE, SIZE);
//			Mat last1 = copyPixelValue(output1, SIZE, SIZE);
//			/*
//			FILE* fp;
//			char *outname = "lena3x3.raw";
//			fopen_s(&fp,outname, "wb");
//			for (int h = 0; h < SIZE; h++) {
//				fwrite(output1[h], sizeof(unsigned char), SIZE, fp);
//			}*/
//			imshow("lena", first);
//			imshow("Filter size 3x3", last1);
//
//			waitKey(0);
//			fclose(f);
//			break;
//		}
//		case 2: {
//			char * imgpath = "lena256.raw";
//			FILE *f = getImage(imgpath);
//
//			unsigned char pixels[SIZE * SIZE];
//			fread(pixels, SIZE * SIZE, 1, f); //Read Image File
//
//			unsigned char** input = allocate2DImgae(SIZE, SIZE);
//
//			for (int i = 0; i < SIZE; i++) { //Copy pixels from File
//				for (int j = 0; j < SIZE; j++) {
//					input[i][j] = pixels[i*SIZE + j];
//				}
//			}
//			unsigned char** pad2 = Padding(input, SIZE, SIZE, 7);
//
//			unsigned char** output2 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//			int sum = 0;
//			for (int h = 3; h < SIZE - 3; h++)
//				for (int w = 3; w < SIZE - 3; w++) {
//					sum = 0;
//					for (int i = 0; i < 7; i++)
//						for (int j = 0; j < 7; j++) {
//							sum += pad2[h + i - 3][w + j - 3];
//						}
//					output2[h][w] = (unsigned char)ceil(sum / masksize2 + 0.5);
//				}
//			Mat last2 = copyPixelValue(output2, SIZE, SIZE);
//			Mat first = copyPixelValue(input, SIZE, SIZE);
//			/*FILE* fp;
//			char *outname = "lena7x7.raw";
//			fopen_s(&fp, outname, "wb");
//			for (int h = 0; h < SIZE; h++) {
//				fwrite(output2[h], sizeof(unsigned char), SIZE, fp);
//			}*/
//			imshow("lena", first);
//
//			imshow("Filter size 9x9", last2);
//			waitKey(0);
//			fclose(f);
//			break;
//		}
//		case 3: {
//			char * imgpath = "lena256.raw";
//			FILE *f = getImage(imgpath);
//
//			unsigned char pixels[SIZE * SIZE];
//			fread(pixels, SIZE * SIZE, 1, f); //Read Image File
//
//			unsigned char** input = allocate2DImgae(SIZE, SIZE);
//
//			for (int i = 0; i < SIZE; i++) { //Copy pixels from File
//				for (int j = 0; j < SIZE; j++) {
//					input[i][j] = pixels[i*SIZE + j];
//				}
//			}
//			unsigned char** pad1 = Padding(input, SIZE, SIZE, 3);
//
//			unsigned char** output3 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//			int sum = 0;
//			for (int h = 1; h < SIZE - 1; h++)
//				for (int w = 1; w < SIZE - 1; w++) {
//					sum = 0;
//					for (int i = 0; i < 3; i++)
//						for (int j = 0; j < 3; j++) {
//							sum += pad1[h + i - 1][w + j - 1] * SmoothFilter[i][j];
//						}
//					output3[h][w] = (unsigned char)ceil(sum / filterWeight + 0.5);
//				}
//			Mat last3 = copyPixelValue(output3, SIZE, SIZE);
//			Mat first = copyPixelValue(input, SIZE, SIZE);
//			imshow("lena", first);
//
//			imshow("Smooth Filter", last3);
//			waitKey(0);
//			fclose(f);
//			break;
//		}
//		case 4: {
//			char * imgpath = "lena3x3.raw";
//			FILE *f = getImage(imgpath);
//
//			unsigned char pixels[SIZE * SIZE];
//			fread(pixels, SIZE * SIZE, 1, f); //Read Image File
//
//			unsigned char** input = allocate2DImgae(SIZE, SIZE);
//
//			for (int i = 0; i < SIZE; i++) { //Copy pixels from File
//				for (int j = 0; j < SIZE; j++) {
//					input[i][j] = pixels[i*SIZE + j];
//				}
//			}
//			unsigned char** pad1 = Padding(input, SIZE, SIZE, 3);
//
//			unsigned char** output4 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//			int sum = 0;
//				for (int h = 1; h < SIZE-1; h++)
//					for (int w = 1; w < SIZE-1; w++) {
//						sum = 0;
//						for(int i=0; i<3; i++)
//							for (int j = 0; j < 3; j++) {
//								sum += pad1[h + i - 1][w + j - 1]*SharpeningFilter[i][j];
//							}
//						if (sum < 0)sum = 0;
//						if (sum >255)sum = 255;
//
//						output4[h-1][w-1] = (unsigned char)ceil(sum + 0.5);
//					}
//
//			Mat last4 = copyPixelValue(output4, SIZE, SIZE);
//			Mat first = copyPixelValue(input, SIZE, SIZE);
//			imshow("lena", first);
//
//			imshow("Sharpening Filter", last4);
//			waitKey(0);
//			fclose(f);
//			break;
//		}
//		case 5: {
//			FILE *f1 = getImage("lena256_n5.raw");
//			FILE *f2 = getImage("lena256_n10.raw");
//			FILE *f3 = getImage("lena256_n25.raw");
//
//			unsigned char pixels1[SIZE * SIZE];
//			fread(pixels1, SIZE * SIZE, 1, f1); //Read Image File
//			unsigned char pixels2[SIZE * SIZE];
//			fread(pixels2, SIZE * SIZE, 1, f2); //Read Image File
//			unsigned char pixels3[SIZE * SIZE];
//			fread(pixels3, SIZE * SIZE, 1, f3); //Read Image File
//
//			unsigned char** input1 = allocate2DImgae(SIZE, SIZE);
//			unsigned char** input2 = allocate2DImgae(SIZE, SIZE);
//			unsigned char** input3 = allocate2DImgae(SIZE, SIZE);
//
//			for (int i = 0; i < SIZE; i++) { //Copy pixels from File
//				for (int j = 0; j < SIZE; j++) {
//					input1[i][j] = pixels1[i*SIZE + j];
//					input2[i][j] = pixels2[i*SIZE + j];
//					input3[i][j] = pixels3[i*SIZE + j];
//
//				}
//			}
//			unsigned char** pad1 = Padding(input1, SIZE, SIZE, 3);
//			unsigned char** pad2 = Padding(input2, SIZE, SIZE, 3);
//			unsigned char** pad3 = Padding(input3, SIZE, SIZE, 3);
//
//			unsigned char** output5 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//			unsigned char** output6 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//			unsigned char** output7 = allocate2DImgae(SIZE, SIZE);//Create Value for copy pixels
//
//			for (int h = 1; h < SIZE - 1; h++)
//				for (int w = 1; w < SIZE - 1; w++) {
//					vector<unsigned char> median1;
//					vector<unsigned char> median2;
//					vector<unsigned char> median3;
//
//					for (int i = 0; i < 3; i++)
//						for (int j = 0; j < 3; j++) {
//							median1.push_back(pad1[h + i - 1][w + j - 1]);
//							median2.push_back(pad2[h + i - 1][w + j - 1]);
//							median3.push_back(pad3[h + i - 1][w + j - 1]);
//						}
//					sort(median1.begin(), median1.end());
//					sort(median2.begin(), median2.end());
//					sort(median3.begin(), median3.end());
//					output5[h][w] = (unsigned char)median1[4];
//					output6[h][w] = (unsigned char)median2[4];
//					output7[h][w] = (unsigned char)median3[4];
//
//				}
//			Mat first1 = copyPixelValue(input1, SIZE, SIZE);
//			Mat first2 = copyPixelValue(input2, SIZE, SIZE);
//			Mat first3 = copyPixelValue(input3, SIZE, SIZE);
//
//			Mat last5 = copyPixelValue(output5, SIZE, SIZE);//Create and Copy pixels for Result of AverageFilter
//			Mat last6 = copyPixelValue(output6, SIZE, SIZE);//Create and Copy pixels for Result of AverageFilter
//			Mat last7 = copyPixelValue(output7, SIZE, SIZE);//Create and Copy pixels for Result of AverageFilter
//
//			imshow("lena_n5", first1);
//			imshow("lena_n10", first2);
//			imshow("lena_n25", first3);
//
//			imshow("Median n5", last5);
//			imshow("Median n10", last6);
//			imshow("Median n25", last7);
//
//			waitKey(0);
//			fclose(f1);
//			fclose(f2);
//			fclose(f3);
//
//			break;
//		}
//		case 6: {
//			flag = 0;
//			break;
//		}
//		}
//	}
//}