// dialting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void Dilation(int, void*);
void Erosion(int, void*);
void morphology(int, void*);
int dilate_size = 0; const int dilate_maxsize = 21;
int dilate_elem = 0; const int dilate_maxelem = 2;
int erode_size = 0; const int erode_maxsize = 21;
int erode_elem = 0; const int erode_maxelem = 2;
int mo_size = 0; const int mo_maxsize = 21;
int mo_elem = 0; const int mo_maxelem = 2;
Mat src,dsrc,esrc,graysrc,gsrc;

int main(int argc,char **argv)
{
	
	string source = "C:\\Users\\11235\\Pictures\\Camera Roll\\IMG_20170915_171544.jpg";
	if (argc > 1)
	{
		source = argv[0];
	}
	src = imread(source, IMREAD_COLOR);
	if (src.empty())
	{
		return -1;
	}
	cvtColor(src, graysrc,COLOR_BGR2GRAY );
	//用于调整实际显示图片的窗口的大小
	namedWindow("dilate demo", WINDOW_NORMAL);
	cvResizeWindow("dilate demo", 500, 500); //创建一个500*500大小的窗口
	namedWindow("erode demo", WINDOW_NORMAL);
	cvResizeWindow("erode demo", 500, 500); //创建一个500*500大小的窗口
	namedWindow("gradient demo", WINDOW_NORMAL);
	cvResizeWindow("gradient demo", 500, 500); //创建一个500*500大小的窗口
	moveWindow("dilate demo", 0, 150);
	moveWindow("erode demo", 500, 150);
	moveWindow("gradient demo", 1000, 150);
	//创建一个滑动条
	//必须要有回调函数，否则无法实现动态更新
	createTrackbar("Size:\n", "dilate demo", &dilate_size,  dilate_maxsize, Dilation);
	createTrackbar("Type:\n", "dilate demo", &dilate_elem, dilate_maxelem, Dilation);
	createTrackbar("Size:\n", "erode demo", &erode_size, erode_maxsize, Erosion);
	createTrackbar("Type:\n", "erode demo", &erode_elem, erode_maxelem, Erosion);
	createTrackbar("Size:\n", "gradient demo", &mo_size, mo_maxsize, morphology);
	createTrackbar("Elem:\n", "gradient demo", &mo_elem, mo_maxelem, morphology);
	Dilation(0, 0);
	Erosion(0, 0);
	morphology(0, 0);
	waitKey();
	return 0;
}
void Dilation(int,void*)
{
	int dilate_type = 0;
	//下面的类型决定了膨胀核的形状，有正方形、十字、圆形三种
	if (dilate_elem == 0)dilate_type = MORPH_RECT;
	else if (dilate_elem == 1)dilate_type = MORPH_CROSS;
	else if (dilate_elem == 2)dilate_type = MORPH_ELLIPSE;
	//创建一个图像数据用来存储膨胀核
	Mat element = getStructuringElement(dilate_type, Size(2 * dilate_size + 1, 2 * dilate_size + 1), Point(dilate_size, dilate_size));
	dilate(src, dsrc, element);
	imshow("dilate demo", dsrc);
}
void Erosion(int, void*)
{
	int erode_type = 0;
	if (erode_elem == 0)erode_type = MORPH_RECT;
	else if (erode_elem == 1)erode_type = MORPH_CROSS;
	else if (erode_elem == 2)erode_type = MORPH_ELLIPSE;

	Mat element = getStructuringElement(erode_type, Size(2 * erode_size + 1, 2 * erode_size + 1), Point(erode_size, erode_size));
	erode(src, esrc, element);
	imshow("erode demo", esrc);
}
//计算图像的梯度，实际上计算的是灰度图的梯度，但是实际结果来看并不能看到图像中的物体边缘
void morphology(int, void*)
{
	Mat element = getStructuringElement(mo_elem, Size(2 * mo_size + 1, 2 * mo_size + 1), Point(mo_size, mo_size));
	morphologyEx(graysrc, gsrc, 5, element);
	imshow("gradient demo", gsrc);
}
