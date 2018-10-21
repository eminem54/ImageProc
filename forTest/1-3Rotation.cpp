//#include <opencv2\opencv.hpp>
//#include <iostream>
//#define _USE_MATH_DEFINES
//#include <math.h>
//using namespace std;
//using namespace cv;
//#define SIZE 256
//
//
//unsigned char bilinear(unsigned char** ori, double hrotate, double wrotate) {
//	int x1, x2, y1, y2;
//	x1 = (int)wrotate;
//	x2 = x1 + 1; if (x2 >= SIZE)x2 = x1;
//	y1 = (int)hrotate;
//	y2 = y1 + 1; if (y2 >= SIZE)y2 = y1;
//
//	int p = (wrotate - x1)*ori[y1][x2] + (1 - (wrotate - x1))*ori[y1][x1];
//	int q = (wrotate - x1)*ori[y2][x2] + (1 - (wrotate - x1))*ori[y2][x2];
//
//	int r = ((hrotate - y1)*q + (1 - (hrotate - y1))*p);
//	return r;
//}
//
//int main() {
//	FILE *f;
//	fopen_s(&f, "lena256.raw", "rb");
//
//	unsigned char input[SIZE*SIZE];
//	fread(input, SIZE*SIZE, 1, f);
//
//	unsigned char** pixels = new unsigned char*[SIZE];
//	for (int i = 0; i < SIZE; i++) {
//		pixels[i] = new unsigned char[SIZE];
//	}
//
//	for (int h = 0; h < SIZE; h++) {
//		for (int w = 0; w < SIZE; w++) {
//			pixels[h][w] = input[h*SIZE + w];
//		}
//	}
//
//	unsigned char** rotation = new unsigned char*[SIZE];
//	for (int i = 0; i < SIZE; i++) {
//		rotation[i] = new unsigned char[SIZE];
//	}
//
//
//	int angle = 0;
//	scanf("%d", &angle);
//
//	int halfSIZE = SIZE / 2;
//	double rad = (angle*M_PI) / 180.0;
//
//	double cos_value = cos(rad);
//	double sin_value = sin(rad);
//
//	for (int h = 0; h < SIZE; h++) {
//		for (int w = 0; w < SIZE; w++) {
//			double h_rotate = cos_value*(h - halfSIZE) - sin_value*(w - halfSIZE) + halfSIZE;
//			double w_rotate = sin_value*(h - halfSIZE) + cos_value*(w - halfSIZE) + halfSIZE;
//
//			if (h_rotate > 0 && w_rotate > 0 && h_rotate < SIZE && w_rotate < SIZE) {
//				rotation[h][w] = bilinear(pixels, h_rotate, w_rotate);
//			}
//		}
//	}
//
//	Mat result = Mat(SIZE, SIZE, CV_8UC1);
//	for (int h = 0; h < SIZE; h++) {
//		for (int w = 0; w < SIZE; w++) {
//			result.at<unsigned char>(h,w) = rotation[h][w];
//		}
//	}
//
//	imshow("rotate", result);
//	waitKey(0);
//	return 0;
//}