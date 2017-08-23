#include <opencv.hpp>
using namespace cv;
using namespace std;
void on_change(int, void*); // trackbar �� callback
int contrastValue; // �Աȶ�
int brightValue; // ����ֵ
Mat src, dst;
int main()
{
	src = imread("img.jpg");
	dst = src.clone();

	contrastValue = 50; // init value = 50
	brightValue = 50; // init value = 50
	namedWindow("������", WINDOW_AUTOSIZE);
	createTrackbar("�Աȶȣ�", "������", &contrastValue, 100, on_change);
	createTrackbar("���ȣ�", "������", &brightValue, 100, on_change);
	on_change(contrastValue, 0);
	on_change(brightValue, 0);

	waitKey(0);
	return 0;
}
void on_change(int, void*)
{
	for (int y = 0; y < src.rows; y++)
	{
		uchar * data = dst.ptr<uchar>(y); // ���ÿ���׵�ַ
		uchar * data2 = src.ptr<uchar>(y);
		for (int x = 0; x < src.cols*src.channels(); x++)
			data[x] = saturate_cast<uchar>(data2[x] * contrastValue*0.02 + brightValue - 50);

	}
	imshow("������", dst);
}