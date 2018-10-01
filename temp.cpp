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
//double reversedMatrix[4][4] = { { -1.0 / 6.0, 0.5, -0.5, 1.0 / 6.0 },
//{ 0.5, -1.0, 0.5, 0.0 },
//{ -1.0 / 3.0, -0.5, 1.0, -1.0 / 6.0 },
//{ 0.0, 1.0, 0.0, 0.0 } };
//
//unsigned char BicubicInterpolation(unsigned char** In, int nHeight_Ori, int nWidth_Ori, double h_cvt, double w_cvt) {
//	int x1, x2, x3, x4, y1, y2, y3, y4;
//
//	x1 = (int)w_cvt - 1; if ((int)w_cvt == 0) x1 = 0;
//	y1 = (int)h_cvt - 1; if ((int)h_cvt == 0) y1 = 0;
//	x2 = (int)w_cvt;
//	y2 = (int)h_cvt;
//	x3 = (int)w_cvt + 1; if (x3 >= nWidth_Ori) x3 = x2;
//	y3 = (int)h_cvt + 1; if (y3 >= nHeight_Ori) y3 = y2;
//	x4 = (int)w_cvt + 2; if (x4 >= nWidth_Ori) x4 = x2;
//	y4 = (int)h_cvt + 2; if (y4 >= nHeight_Ori) y4 = y2;
//
//
//	double value[4][4] = { { In[y1][x1], In[y1][x2], In[y1][x3] ,In[y1][x4] },
//	{ In[y2][x1], In[y2][x2], In[y2][x3], In[y2][x4] },
//	{ In[y3][x1], In[y3][x2], In[y3][x3], In[y3][x4] },
//	{ In[y4][x1], In[y4][x2], In[y4][x3], In[y4][x4] } };
//
//	double v1, v2, v3, v4;
//	v1 = BicubicCalculation(In[y1][x1], In[y1][x2], In[y1][x3], In[y1][x4], w_cvt - x2);
//	v2 = BicubicCalculation(In[y2][x1], In[y2][x2], In[y2][x3], In[y2][x4], w_cvt - x2);
//	v3 = BicubicCalculation(In[y3][x1], In[y3][x2], In[y3][x3], In[y3][x4], w_cvt - x2);
//	v4 = BicubicCalculation(In[y4][x1], In[y4][x2], In[y4][x3], In[y4][x4], w_cvt - x2);
//
//	return (unsigned char)BicubicCalculation(v1, v2, v3, v4, h_cvt - y2);
//}
//
//double BicubicCalculation(unsigned char v1, unsigned char v2, unsigned char v3, unsigned char v4, double val) {
//	double n[4];
//	double last[4] = { 0,0,0,0 };
//
//
//	for (int i = 0; i < 4; i++) {
//		last[i] = reversedMatrix[i][0] * v1 + reversedMatrix[i][1] * v2 + reversedMatrix[i][2] * v3 + reversedMatrix[i][3] * v4;
//	}
//
//	n[3] = 1;
//	n[2] = val;
//	n[1] = (double)pow(val, 2);
//	n[0] = (double)pow(val, 3);
//
//	double ret = n[0] * last[0] + n[1] * last[1] + n[2] * last[2] + n[3] * last[3];
//
//	return ret;
//}
//
//void CViewerDlg::OnEditRotation()
//{
//	if (isImageOpened && nFormat == FORMAT_GRAY) { //영상이 열려있을때 & 영상포멧이 Gray(channel 1) 일때만 실행
//		if (RotationDlg.DoModal() == IDOK) { //회전 정보를 받아옴
//			int nInterpolationType = RotationDlg.GetInterpolationType(); // 보간 타입
//			int nAngle = RotationDlg.GetAngle(); // 회전 각도
//
//			if (nAngle < 0 || nAngle > 360) {
//				MessageBox("회전 범위가 잘못되었습니다.");
//				return;
//			}
//
//			unsigned char** Out = MemAlloc2D(nHeight_in, nWidth_in, 0); //회전 결과를 담은 2차원 배열
//
//			int nHeight_2 = nHeight_in / 2;
//			int nWidth_2 = nWidth_in / 2;
//
//			double rad = (nAngle * M_PI) / 180.0;
//
//			double cos_value = cos(rad);
//			double sin_value = sin(rad);
//
//			double h_Rotate = 0;
//			double w_Rotate = 0;
//
//			for (int h = 0; h < nHeight_in; h++) {
//				for (int w = 0; w < nWidth_in; w++) {
//					//회전한 좌표 계산///////////////////////////////////////////////
//
//					double h_Rotate = (cos_value*(h - nHeight_2) - sin_value*(w - nHeight_2)) + nHeight_2;
//					double w_Rotate = (sin_value*(h - nHeight_2) + cos_value*(w - nHeight_2)) + nHeight_2;
//
//					//////////////////////////////////////////////////////////
//					if (isInsideBoundary(nHeight_in, nWidth_in, h_Rotate, w_Rotate)) {
//						if (nInterpolationType == BILINEAR) {
//							Out[h][w] = BilinearInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Rotate, w_Rotate);
//						}
//						else {
//							Out[h][w] = BicubicInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Rotate, w_Rotate);
//						}
//					}
//				}
//			}
//
//			Proc_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
//
//			for (int h = 0; h < nHeight_in; h++) {
//				for (int w = 0; w < nWidth_in; w++) {
//					Proc_Img.at<unsigned char>(h, w) = Out[h][w];
//				}
//			}
//
//			DisplayImage(Proc_Img, false);
//			MemFree2D(Out, nHeight_in);
//		}
//	}
//	else {
//		MessageBox("불러온 영상이 없거나 영상 포멧이 회색조 영상이 아닙니다.");
//	}
//}