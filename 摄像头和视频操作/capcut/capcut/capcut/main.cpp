#include <iostream>
#include <opencv.hpp>
#include <io.h>
#include <fstream>
#include <string>
#include <direct.h>
#include <conio.h>
#include <Windows.h>

using namespace std;
using namespace cv;


class capcut
{
public:
	explicit capcut(string filePath) :filePath(filePath)
	{
		cap.open(filePath);
	}


	/*
		画ROI
	*/
	void drawROI()
	{
		namedWindow("capcut");
		Mat tempImg1, tempImg2;
		
		bool drawFlag = false;

		while (1)
		{

			

			setMouseCallback("capcut", on_MouseHandle, (void*)&tempImg1);
		
			cap >> tempImg1; // raw frame

			tempImg1.copyTo(tempImg2);

			DrawRectangle(tempImg2, Rect(pos[0], pos[1], pos[2], pos[3]));

			if (drawingBox)
			{
				DrawRectangle(tempImg2, grectangle);
				drawFlag = true;

			}
			else
			{
				if (drawFlag&&grectangle.width > 5 && grectangle.height > 5)
				{
					drawFlag = false;
					system("cls");

					pos[0] = grectangle.x;
					pos[1] = grectangle.y;
					pos[2] = grectangle.width;
					pos[3] = grectangle.height;

					cout << pos[0] << "," << pos[1] << "," << pos[2] << "," << pos[3] << endl;

					cout << "确定保存？(y/n):";
					char q;
					cin >> q;
					if (q == 'y' || q == 'Y')
					{
						cout << "正在保存..." << endl;

						cap.release();
						cap.open(filePath);

						long nFrame = static_cast<long>(cap.get(CV_CAP_PROP_FRAME_COUNT));
						
						double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
						double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
						int fps = cap.get(CV_CAP_PROP_FPS);


						Size frameSize(static_cast<int>(pos[2]), static_cast<int>(pos[3]));
						VideoWriter writer("test.avi", CV_FOURCC('M', 'P', 'E', 'G'), fps, frameSize, true);

						Mat saveROI;
						
						for (int i = 0; i < nFrame; ++i)
						{
						
							system("cls");
							cap >> tempImg1;
							
							cout << i <<" of "<<nFrame<< endl;

							tempImg1(Rect(pos[0], pos[1], pos[2], pos[3])).copyTo(saveROI);

							writer.write(saveROI);

						}
					
						cout << "保存完成" << endl;
						waitKey(200);
						exit(0);
					}
					else
					{
						cout << "取消" << endl;
						pos[0] = 0;
						pos[1] = 0;
						pos[2] = 0;
						pos[3] = 0;
					}
					
				}
			}

			imshow("capcut", tempImg2);

			waitKey(20);
	
		}

	} // end drawROI

	
public:

	//画框
	static void DrawRectangle(cv::Mat& img, cv::Rect box)
	{
		cv::rectangle(img, Rect(box.x, box.y, box.width, box.height), Scalar(255, 200, 100), 1, 1);
	}

	//鼠标的事件响应
	static void on_MouseHandle(int event, int x, int y, int flags, void* param)
	{
		Mat& image = *(cv::Mat*)param;

		switch (event)
		{
		case EVENT_MOUSEMOVE:
		{

								if (drawingBox)
								{
									grectangle.width = x - grectangle.x;
									grectangle.height = y - grectangle.y;
								}

		}break;
		case EVENT_LBUTTONDOWN:
		{

								  drawingBox = true;
								  grectangle = Rect(x, y, 0, 0);

		}break;
		case EVENT_LBUTTONUP:
		{

								drawingBox = false;
								if (grectangle.width < 0)
								{
									grectangle.x += grectangle.width;
									grectangle.width *= -1;
								}
								if (grectangle.height < 0)
								{
									grectangle.y += grectangle.height;
									grectangle.height *= -1;
								}


								DrawRectangle(image, grectangle);

		}break;
		default:break;

		}
	}
private:

	string filePath = nullptr;

	int pos[4];

	VideoCapture cap;

	vector<Mat> cache;

	static cv::Rect grectangle;

	static bool drawingBox;
};

bool capcut::drawingBox = false;
Rect capcut::grectangle = Rect(-1, -1, 0, 0);

int main(int argc, char** argv)
{
	capcut test("video.mp4");
	test.drawROI();

	return 0;
}