#include <opencv.hpp>
using namespace cv;
#define WINDOW_NAME "���򴰿�"
// --------- ȫ�ֺ������� ---------- // 
void on_MouseHandle(int event, int x, int y, int flags, void * param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
// ================================== //
// ---------- ȫ�ֱ������� ----------- //
Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);
// ================================== //
int main()
{
	g_rectangle = Rect(-1/*x*/, -1/*y*/, 0/*width*/, 0/*height*/); // Rect_<_Tp>::Rect_(_Tp _x, _Tp _y, _Tp _width, _Tp _height): x(_x), y(_y), width(_width), height(_height) {}
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	srcImage = Scalar::all(0);

	// �����������ص�����
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);
	//������ѭ���������л��Ƶı�ʶ��Ϊ���ʱ�򣬽��л���
	while (1)
	{
		srcImage.copyTo(tempImage); // ����ԭͼ����ʱ����
		if (g_bDrawingBox)DrawRectangle(tempImage, g_rectangle); // �����л��Ƶı�ʶ��Ϊ�棬����л���
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27) break;
	}
	return 0;
}
// ----------- �Ӻ����Ķ��岿�� -------------- // 
// on_MouseHandle() ������
//���������ص����������ݲ�ͬ������¼����в�ͬ�Ĳ���
void on_MouseHandle(int event, int x, int y, int flags, void * param)
{
	Mat& image = *(cv::Mat*)param; // ǿ������ת��
	switch (event)
	{
		// ����ƶ���Ϣ
	case EVENT_MOUSEMOVE:
	{
							if (g_bDrawingBox) // ����Ƿ���л��Ƶı�ʶ��Ϊ�棬���¼�³��Ϳ�RECT�ͱ�����
							{
								g_rectangle.width = x - g_rectangle.x;
								g_rectangle.height = y - g_rectangle.y;
							}
	}
		break;
		// ���������Ϣ
	case EVENT_LBUTTONDOWN:
	{
							  g_bDrawingBox = true;
							  g_rectangle = Rect(x, y, 0, 0); // ��¼��ʼ��
	}
		break;
	case EVENT_LBUTTONUP:
	{
							g_bDrawingBox = false; // �ñ�ʶ��Ϊfalse
							// �Կ�͸�С��0�Ĵ���
							if (g_rectangle.width < 0)
							{
								g_rectangle.x += g_rectangle.width;
								g_rectangle.width *= -1;
							}
							if (g_rectangle.height < 0)
							{
								g_rectangle.y += g_rectangle.height;
								g_rectangle.height *= -1;
							}
							//���ú������л���
							DrawRectangle(image, g_rectangle);
	}
		break;
	default:
		break;
	}
}
// �Զ���ľ��λ��ƺ���
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img, Rect(box.x, box.y, box.width, box.height), Scalar(255, 200, 100), 1, 1);
}