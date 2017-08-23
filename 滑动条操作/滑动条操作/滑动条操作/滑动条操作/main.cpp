#include <opencv.hpp>
using namespace cv;
using namespace std;
void on_change(int, void*); // trackbar 的 callback
int contrastValue; // 对比度
int brightValue; // 亮度值
Mat src, dst;
int main()
{
	src = imread("img.jpg");
	dst = src.clone();

	contrastValue = 50; // init value = 50
	brightValue = 50; // init value = 50
	namedWindow("调节器", WINDOW_AUTOSIZE);
	createTrackbar("对比度：", "调节器", &contrastValue, 100, on_change);
	createTrackbar("亮度：", "调节器", &brightValue, 100, on_change);
	on_change(contrastValue, 0);
	on_change(brightValue, 0);

	waitKey(0);
	return 0;
}
void on_change(int, void*)
{
	for (int y = 0; y < src.rows; y++)
	{
		uchar * data = dst.ptr<uchar>(y); // 获得每行首地址
		uchar * data2 = src.ptr<uchar>(y);
		for (int x = 0; x < src.cols*src.channels(); x++)
			data[x] = saturate_cast<uchar>(data2[x] * contrastValue*0.02 + brightValue - 50);

	}
	imshow("调节器", dst);
}