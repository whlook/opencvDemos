#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	// 1. �ԻҶ�ģʽ��ȡԭʼͼ����ʾ
	Mat srcImage = imread("img.jpg", 0);
	if (!srcImage.data){ printf("input image error ! \n"); return false; }
	imshow("ԭʼͼ", srcImage);
	// 2. ������ͼ����չ����ѵĳߴ磬�߽���0��䣻
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols); // ���������ǻ��srcͼ������DFT�ߴ�
	// ����ӵ����س�ʼ��Ϊ0��
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
	// 3. Ϊ����Ҷ�仯�Ľ����ʵ�����鲿�����䴢��ռ�
	// ��planes������Ϻϲ���һ����ͨ��������complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);
	// 4. ���о͵���ɢ����Ҷ�任
	dft(complexI, complexI);
	// 5. ������ת��Ϊ��ֵ����log (1+sqrt(Re(DFT(I)^2+IM(DFT(I)^2))
	split(complexI, planes); // ��ͨ������ɼ�����ͨ������ [0] =Re.. [1] = Im..
	magnitude(planes[0], planes[1], planes[0]);
	Mat magnitudeImage = planes[0];
	// 6. ���г߶�log ����
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage); // ����Ȼ����
	// 7. ���к��طֲ���������
	// ���������л����У�����Ƶ�ײü�
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols&-2, magnitudeImage.rows&-2));
	// �������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ������
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));
	//�������ޣ����Ϻ����½�����
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//�������ޣ����Ϻ����£�
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	// 8. ��һ�� ��0��1֮��ĸ���ֵ������任Ϊ���ǵ�ͼ���ʽ
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);
	// 9. ��ʾЧ��
	imshow("Ƶ�׷�ֵ", magnitudeImage);
	waitKey(0);

	return 0;
}