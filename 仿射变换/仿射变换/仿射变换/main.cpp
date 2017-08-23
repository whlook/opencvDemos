#include <opencv.hpp>
#include <iostream>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img.jpg");
	Mat dst;

	Point2f affinePoints0[3] = { Point2f(100, 50), Point2f(100, 390), Point2f(600, 50) }; // ѡȡԭͼ���ӳ���
	Point2f affinePoints1[3] = { Point2f(200, 100), Point2f(200, 300), Point2f(500, 50) }; // ѡȡĿ��ͼ���ӳ���

	Mat trans = getAffineTransform(affinePoints0, affinePoints1); // ��ñ任����

	warpAffine(img, dst, trans, Size(img.cols, img.rows)); // ����任

	for (int i = 0; i < 3; ++i) // ���
	{
		circle(img, affinePoints0[i], 5, Scalar(0, 255, 255), -1);
		circle(dst, affinePoints1[i], 5, Scalar(0, 255, 255), -1);
	}

	imshow("src", img);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}