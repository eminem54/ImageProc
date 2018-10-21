#include <iostream>
#include <opencv2\opencv.hpp>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace cv;

#define SIZE 256

unsigned char** padding(unsigned char** in, int height, int width, int filtersize) {
	int padSize = (int)(filtersize / 2);

	unsigned char** ret = new unsigned char*[SIZE+2*padSize];
	for (int i = 0; i < SIZE+2*padSize; i++)
		ret[i] = new unsigned char[SIZE+2*padSize];

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < height; w++) {
			ret[h + padSize][w + padSize] = in[h][w];
		}
	}

	for (int h = 0; h < padSize; h++) {
		for (int w = 0; w < width; w++) {
			ret[h][w+padSize] = in[0][w];
			ret[h + height - 1][w + padSize] = in[height - 1][w];
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < padSize; w++) {
			ret[h+padSize][w] = in[h][0];
			ret[h+padSize][w+width-1] = in[h][width-1];
		}
	}
	for (int h = 0; h < padSize; h++) {
		for (int w = 0; w < padSize; w++) {
			ret[h][w] = in[0][0];
			ret[h][w + width - 1] = in[0][width-1];
			ret[h + height - 1][w] = in[height-1][0];
			ret[h + height - 1][w + width - 1] = in[height-1][width-1];
		}
	}
	return ret;
}

int main() {
	const char* inputPath = "lena256.raw";
	FILE* f; //= fopen(inputPath, "rb");
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

	int filter[3][3] = { {0,-1,0}, {-1,5,-1}, {0,-1,0} };

	unsigned char** pad = padding(pixels, SIZE, SIZE, 3);
	unsigned char** output = new unsigned char*[SIZE];
	for (int i = 0; i < SIZE; i++) {
		output[i] = new unsigned char[SIZE];
	}
	for (int h = 1; h < SIZE+1; h++) {
		for (int w = 1; w < SIZE+1; w++) {
			int sum = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					sum += pad[h + i - 1][w + j - 1] * filter[i][j];
				}
			}
			if (sum < 0)sum = 0;
			if (sum > 255)sum = 255;
			output[h - 1][w - 1] = sum;
		}
	}

	Mat result = Mat(SIZE, SIZE, CV_8UC1);
	for (int h = 0; h < SIZE; h++) {
		for (int w = 0; w < SIZE; w++) {
			result.at<unsigned char>(h, w) = output[h][w];
		}
	}
	imshow("lena", result);
	waitKey(0);

	return 0;
}
