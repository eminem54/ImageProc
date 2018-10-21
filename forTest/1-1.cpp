//#include <iostream>
//#include <opencv2\opencv.hpp>
//#include <string>
//using namespace std;
//using namespace cv;
//
//#define SIZE 256
//int main() {
//	const char* inputPath = "lena256.raw";
//	FILE* f; //= fopen(inputPath, "rb");
//	fopen_s(&f, inputPath, "rb");
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
//	Mat result = Mat(SIZE, SIZE, CV_8UC1);
//	for (int h = 0; h < SIZE; h++) {
//		for (int w = 0; w < SIZE; w++) {
//			result.at<unsigned char>(h, w) = pixels[h][w];
//		}
//	}
//	imshow("lena", result);
//
//
//	FILE* op;
//	fopen_s(&op, "abc.raw", "wb");
//	waitKey(0);
//
//	return 0;
//}