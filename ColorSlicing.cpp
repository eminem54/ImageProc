//#include <iostream>
//#include <opencv2\opencv.hpp>
//#include <math.h>
//using namespace std;
////390x562 2013726049	이지영
//#define WIDTH 400
//#define HEIGHT 562
//
//unsigned char* readBMP(char* filename)
//{
//	int i;
//	FILE* f = fopen(filename, "rb");
//
//	if (f == NULL)
//		throw "Argument Exception";
//
//	unsigned char info[54];
//	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
//
//											   // extract image height and width from header
//	int width = *(int*)&info[18];
//	int height = *(int*)&info[22];
//
//	cout << endl;
//	cout << "  Name: " << filename << endl;
//	cout << " Width: " << width << endl;
//	cout << "Height: " << height << endl;
//
//	int row_padded = (width * 3 + 3) & (~3);
//	unsigned char* data = new unsigned char[row_padded];
//	unsigned char tmp;
//
//	for (int i = 0; i < height; i++)
//	{
//		fread(data, sizeof(unsigned char), row_padded, f);
//		for (int j = 0; j < width * 3; j += 3)
//		{
//			// Convert (B, G, R) to (R, G, B)
//			/*tmp = data[j];
//			data[j] = data[j + 2];
//			data[j + 2] = tmp;*/
//		}
//	}
//
//	fclose(f);
//	return data;
//}
//unsigned char** allocMem() {
//	unsigned char** input_img = new unsigned char*[HEIGHT];
//	for (int i = 0; i < HEIGHT; i++) {
//		input_img[i] = new unsigned char[WIDTH * 3];
//		memset(input_img[i], 0, sizeof(unsigned char)*WIDTH * 3);
//	}
//	return input_img;
//}
//void readImage(unsigned char** input_img, const char* filename) {
//	FILE* f;
//	fopen_s(&f, filename, "rb");
//	for (int h = 0; h < HEIGHT; h++) {
//		fread(input_img[h], sizeof(unsigned char), WIDTH * 3, f);
//	}
//	fclose(f);
//}
//void saveImage(unsigned char** input_img, const char* filename) {
//	FILE *fp;
//	fopen_s(&fp, filename, "wb");
//	for (int h = 0; h < HEIGHT; h++) {
//		fwrite(input_img[h], sizeof(unsigned char), WIDTH * 3, fp);
//	}
//	fclose(fp);
//}
//void convertRGB(unsigned char** input_img) {
//	unsigned char tmp = 0;
//	for (int i = 0; i < HEIGHT; i++)
//	{
//		for (int j = 0; j < WIDTH * 3; j += 3)
//		{
//			tmp = input_img[i][j];
//			input_img[i][j] = input_img[i][j + 2];
//			input_img[i][j + 2] = tmp;
//		}
//	}
//}
//bool isInSphere(unsigned char r, unsigned char g, unsigned char b) {
//	//230 140 100  0.4893   0.2978   0.2127
//	int sumOfInputRGB = (int)r + (int)g + (int)b;
//	double rateR = (double)r / sumOfInputRGB;
//	double rateG = (double)g / sumOfInputRGB;
//	double rateB = (double)b / sumOfInputRGB;
//
//	double distanceR = rateR - 0.4893;
//	double distanceG = rateG - 0.2978;
//	double distanceB = rateB - 0.2127;
//
//	double w = 0.080 / 2;
//	//if (((distanceR*distanceR) < 0.3*0.3) && ((distanceG*distanceG) < 0.3*0.3) && ((distanceB*distanceB) < 0.3*0.3))
//	if (abs(distanceR) < w  && abs(distanceG) < w && abs(distanceB) < w)
//		return true;
//	else return false;
//}
//void copytPixelRGB(unsigned char** input, unsigned char** output) {
//	for (int h = 0; h < HEIGHT; h++) {
//		for (int w = 0; w < WIDTH * 3; w += 3) {
//			output[h][w] = input[h][w];
//			output[h][w + 1] = input[h][w + 1];
//			output[h][w + 2] = input[h][w + 2];
//		}
//	}
//}
//
//int main() {
//	unsigned char data[54];
//	unsigned char** input_img = allocMem();
//	unsigned char** rawImg = allocMem();
//
//	unsigned char **isSurvived = allocMem();
//
//	unsigned char** output_img = allocMem();
//	unsigned char** output_processd = allocMem();
//	unsigned char** output_last = allocMem();
//
//
//	readImage(input_img, "face.raw");
//	convertRGB(input_img);
//
//	for (int i = 0; i < HEIGHT; i++) {
//		rawImg[i] = input_img[HEIGHT - i - 1];
//	} //convert updown
//
//	copytPixelRGB(rawImg, output_last); //create array for overlap
//
//	for (int h = 0; h < HEIGHT; h++) {
//		for (int w = 0; w < WIDTH * 3; w += 3) {
//			if (isInSphere(rawImg[h][w], rawImg[h][w + 1], rawImg[h][w + 2])) {
//				output_img[h][w] = rawImg[h][w];
//				output_img[h][w + 1] = rawImg[h][w + 1];
//				output_img[h][w + 2] = rawImg[h][w + 2];
//				isSurvived[h][w] = 1;
//			}
//			else {
//				output_img[h][w] = 255;
//				output_img[h][w + 1] = 0;
//				output_img[h][w + 2] = 255;
//			}
//		}
//	}
//
//	//filter 생성
//	double filter[3][3] = { { 1.0 / 9.0 ,1.0 / 9.0 ,1.0 / 9.0 },{ 1.0 / 9.0 ,1.0 / 9.0 ,1.0 / 9.0 } ,{ 1.0 / 9.0 ,1.0 / 9.0 ,1.0 / 9.0 } };
//	double tempR = 0, tempG = 0, tempB = 0;
//	for (int h = 1; h < HEIGHT - 1; h++) {
//		for (int w = 3; w < WIDTH * 3 - 3; w += 3) {
//			tempR = 0, tempG = 0, tempB = 0;
//			for (int i = 0; i < 3; i++) {
//				for (int j = 0; j < 3; j++) {
//					tempR += output_img[h + i - 1][w + 3 * j - 3] * filter[i][j];
//					tempG += output_img[h + i - 1][w + 3 * j - 2] * filter[i][j];
//					tempB += output_img[h + i - 1][w + 3 * j - 1] * filter[i][j];
//				}
//			}
//			output_processd[h][w] = (unsigned char)tempR;
//			output_processd[h][w + 1] = (unsigned char)tempG;
//			output_processd[h][w + 2] = (unsigned char)tempB;
//		}
//	}
//	//스무딩결과를 원본이미지에다가 isSurvived true 한곳이라면 overlap함
//	for (int h = 0; h < HEIGHT; h++) {
//		for (int w = 0; w < WIDTH*3; w+=3) {
//			if ((int)isSurvived[h][w] == 1 && isInSphere(output_processd[h][w], output_processd[h][w+1], output_processd[h][w+2])) {
//				output_last[h][w] = output_processd[h][w];
//				output_last[h][w + 1] = output_processd[h][w + 1];
//				output_last[h][w + 2] = output_processd[h][w + 2];
//			}
//		}
//	}
//
//	saveImage(output_last, "result.raw"); //save
//	saveImage(rawImg, "result_compare.raw"); //save
//
//	return 0;
//}