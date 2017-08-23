#include <opencv.hpp>
#include <iostream>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img.jpg");
	Mat dst;

	Point2f perspectivePoints0[4] = { Point2f(100, 50), Point2f(100, 390), Point2f(600, 50), Point2f(600, 800) }; // ѡȡԭͼ���ӳ���
	Point2f perspectivePoints1[4] = { Point2f(200, 100), Point2f(200, 300), Point2f(500, 50), Point2f(600, 800) }; // ѡȡĿ��ͼ���ӳ���

	Mat trans = getPerspectiveTransform(perspectivePoints0, perspectivePoints1); // ��ñ任����

	warpPerspective(img, dst, trans, Size(img.cols, img.rows)); // ͸�ӱ任

	for (int i = 0; i < 4; ++i) // ���
	{
		circle(img, perspectivePoints0[i], 5, Scalar(0, 255, 255), -1);
		circle(dst, perspectivePoints1[i], 5, Scalar(0, 255, 255), -1);
	}

	imshow("src", img);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}