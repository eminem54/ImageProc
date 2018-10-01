#include "opencv2\opencv.hpp"
#include <stdio.h>
#include <memory>
using namespace cv;


void main()
{
	char * imgpath = "lena256.raw";
	FILE * f = fopen(imgpath, "rb");
	if (!f)
	{
		printf("bad path : %s\n", imgpath);
		return;
	}
	char pixels[256 * 256];
	fread(pixels, 256 * 256, 1, f);

	double dScaleRate;
	scanf("%lf", &dScaleRate);
	//pixels 가 픽셀값이니까 

	//스케일링 후 영상의 크기 계산
	int nHeight_Scale = 256 * dScaleRate;
	int nWidth_Scale = 256 * dScaleRate;

	unsigned char** Out = MemAlloc2D(nHeight_Scale, nWidth_Scale, 0);  //스케일링 결과를 담을 2차원 unsigned char 형 배열

	for (int h = 0; h < nHeight_Scale; h++) {
		for (int w = 0; w < nWidth_Scale; w++) {
			double h_Ori = h / dScaleRate;
			double w_Ori = w / dScaleRate;
			if (nInterpolationType == BILINEAR) {
				Out[h][w] = BilinearInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Ori, w_Ori);
			}
			else {
				Out[h][w] = BicubicInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Ori, w_Ori);
			}
		}
	}
	Ori_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
	Proc_Img = Mat(nHeight_Scale, nWidth_Scale, CV_8UC1);

	for (int h = 0; h < nHeight_in; h++) {
		for (int w = 0; w < nWidth_in; w++) {
			Ori_Img.at<unsigned char>(h, w) = ch_in_gray[h][w];
		}
	}
	for (int h = 0; h < nHeight_Scale; h++) {
		for (int w = 0; w < nWidth_Scale; w++) {
			Proc_Img.at<unsigned char>(h, w) = Out[h][w];
		}
	}







	//요기에 작성하면되나?
	
	Mat img(256, 256, CV_8UC1, pixels);
	imshow("Original Image", img); //원본

	imshow("Scaled Image", Proc_Img); //결과

	waitKey(0);
	fclose(f);

}
