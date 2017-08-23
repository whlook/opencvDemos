#include <opencv.hpp>
using namespace cv;
#define WINDOW_NAME "程序窗口"
// --------- 全局函数声明 ---------- // 
void on_MouseHandle(int event, int x, int y, int flags, void * param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
// ================================== //
// ---------- 全局变量声明 ----------- //
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

	// 设置鼠标操作回调函数
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);
	//程序主循环，当进行绘制的标识符为真的时候，进行绘制
	while (1)
	{
		srcImage.copyTo(tempImage); // 复制原图像到临时变量
		if (g_bDrawingBox)DrawRectangle(tempImage, g_rectangle); // 当进行绘制的标识符为真，则进行绘制
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27) break;
	}
	return 0;
}
// ----------- 子函数的定义部分 -------------- // 
// on_MouseHandle() 函数，
//描述：鼠标回调函数，根据不同的鼠标事件进行不同的操作
void on_MouseHandle(int event, int x, int y, int flags, void * param)
{
	Mat& image = *(cv::Mat*)param; // 强制类型转换
	switch (event)
	{
		// 鼠标移动消息
	case EVENT_MOUSEMOVE:
	{
							if (g_bDrawingBox) // 如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
							{
								g_rectangle.width = x - g_rectangle.x;
								g_rectangle.height = y - g_rectangle.y;
							}
	}
		break;
		// 左键按下消息
	case EVENT_LBUTTONDOWN:
	{
							  g_bDrawingBox = true;
							  g_rectangle = Rect(x, y, 0, 0); // 记录起始点
	}
		break;
	case EVENT_LBUTTONUP:
	{
							g_bDrawingBox = false; // 置标识符为false
							// 对宽和高小于0的处理
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
							//调用函数进行绘制
							DrawRectangle(image, g_rectangle);
	}
		break;
	default:
		break;
	}
}
// 自定义的矩形绘制函数
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img, Rect(box.x, box.y, box.width, box.height), Scalar(255, 200, 100), 1, 1);
}