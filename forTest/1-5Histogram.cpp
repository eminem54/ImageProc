#include <iostream>
#include <opencv2\opencv.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
using namespace std;
using namespace cv;
#define SIZE 256
int main() {
	FILE *f;
	fopen_s(&f, "lena256.raw", "rb");

	unsigned char input[SIZE*SIZE];
	fread(input, SIZE*SIZE, 1, f);

	unsigned char** pixels = new unsigned char*[SIZE];
	for (int i = 0; i < SIZE; i++)
		pixels[i] = new unsigned char[SIZE];

	for (int h = 0; h < SIZE; h++) {
		for (int w = 0; w < SIZE; w++) {
			pixels[h][w] = input[h*SIZE + w];
		}
	}

	srand(GetTickCount());

	int hist_ori[256] = { 0 };
	int hist_ref[256] = { 0 };
	for (int h = 0; h < SIZE; h++) {
		for (int w = 0; w < SIZE; w++) {
			hist_ori[pixels[h][w]]++;
			hist_ref[(unsigned char)rand() % 255]++;
		}
	}
	for (int i = 0; i < SIZE; i++) {
		cout << hist_ref[i] << endl;
	}
	double ori_cdf[255] = { 0.0 };
	double ref_cdf[255] = { 0.0 };

	ori_cdf[0] = (double)hist_ori[0]/SIZE*SIZE;
	ref_cdf[0] = (double)hist_ref[0]/SIZE*SIZE;

	for (int i = 1; i < SIZE; i++) {
		ori_cdf[i] = (double)(hist_ori[i] ) / SIZE*SIZE + ori_cdf[i - 1];
		ref_cdf[i] = (double)(hist_ref[i] ) / SIZE*SIZE + ref_cdf[i - 1];
	}


	unsigned char** output = new unsigned char*[SIZE];
	for (int i = 0; i < SIZE; i++)
		output[i] = new unsigned char[SIZE];

	for (int h = 0; h < SIZE; h++) {
		for (int w = 0; w < SIZE; w++) {
			int index = 0;
			for (int i = 1; i < SIZE; i++) {
				if (ori_cdf[pixels[h][w]] < ref_cdf[i] && ori_cdf[pixels[h][w]] >= ref_cdf[i - 1]) {
					index = i;
					break;
				}
			}
			output[h][w] = (unsigned char)index;
		}
	}

	Mat result = Mat(SIZE, SIZE, CV_8UC1);
	for (int h = 0; h < SIZE; h++) {
		for (int w = 0; w < SIZE; w++) {
			result.at<unsigned char>(h,w) = output[h][w];
		}
	}

	imshow("hist", result);
	waitKey(0);
	return 0;
}