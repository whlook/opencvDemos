#include <opencv.hpp>
#include <iostream>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lines.jpg");

	Mat mid;

	Canny(img, mid, 50, 200);


	vector<Vec2f> lines;

	HoughLines(mid, lines, 1, CV_PI / 180, 150, 0, 0);

	for (size_t i = 0; i < lines.size(); ++i)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(img, pt1, pt2, Scalar(55, 255, 255), 1, CV_AA);
	}

	cv::imshow("test", img);
	waitKey(0);

	return 0;
}

