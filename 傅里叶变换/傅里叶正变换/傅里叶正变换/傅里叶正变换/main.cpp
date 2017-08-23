#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	// 1. 以灰度模式读取原始图并显示
	Mat srcImage = imread("img.jpg", 0);
	if (!srcImage.data){ printf("input image error ! \n"); return false; }
	imshow("原始图", srcImage);
	// 2. 将输入图像延展到最佳的尺寸，边界有0填充；
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols); // 以上两个是获得src图像的最佳DFT尺寸
	// 将添加的像素初始化为0；
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
	// 3. 为傅里叶变化的结果（实部和虚部）分配储存空间
	// 将planes数组组合合并成一个多通道的数组complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);
	// 4. 进行就地离散傅里叶变换
	dft(complexI, complexI);
	// 5. 将复数转换为幅值，即log (1+sqrt(Re(DFT(I)^2+IM(DFT(I)^2))
	split(complexI, planes); // 多通道分离成几个单通道数组 [0] =Re.. [1] = Im..
	magnitude(planes[0], planes[1], planes[0]);
	Mat magnitudeImage = planes[0];
	// 6. 进行尺度log 缩放
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage); // 求自然对数
	// 7. 剪切和重分布幅度象限
	// 若有奇数行或者列，进行频谱裁剪
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols&-2, magnitudeImage.rows&-2));
	// 重新排列傅里叶图像中的象限，使得原点位于图像中心
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));
	//交换象限（左上和右下交换）
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//交换象限（右上和左下）
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	// 8. 归一化 用0到1之间的浮点值将矩阵变换为可是的图像格式
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);
	// 9. 显示效果
	imshow("频谱幅值", magnitudeImage);
	waitKey(0);

	return 0;
}