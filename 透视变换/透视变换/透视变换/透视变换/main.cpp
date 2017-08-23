#include <opencv.hpp>
#include <iostream>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img.jpg");
	Mat dst;

	Point2f perspectivePoints0[4] = { Point2f(100, 50), Point2f(100, 390), Point2f(600, 50), Point2f(600, 800) }; // 选取原图像的映射点
	Point2f perspectivePoints1[4] = { Point2f(200, 100), Point2f(200, 300), Point2f(500, 50), Point2f(600, 800) }; // 选取目标图像的映射点

	Mat trans = getPerspectiveTransform(perspectivePoints0, perspectivePoints1); // 获得变换矩阵

	warpPerspective(img, dst, trans, Size(img.cols, img.rows)); // 透视变换

	for (int i = 0; i < 4; ++i) // 描点
	{
		circle(img, perspectivePoints0[i], 5, Scalar(0, 255, 255), -1);
		circle(dst, perspectivePoints1[i], 5, Scalar(0, 255, 255), -1);
	}

	imshow("src", img);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}