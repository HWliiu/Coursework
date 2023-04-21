// Opencv_homework.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <vector>
#include <cmath>
#define DILATE 0
#define ERODE 1
#define PI 3.1415926

using namespace std;
using namespace cv;

Mat getRedness(Mat src)
{
	Mat redness = Mat::zeros(src.rows, src.cols, CV_8UC1);
	uchar *pSrc = src.data;
	uchar *pDst = redness.data;
	short temp;
	while (pSrc <= src.dataend)
	{
		temp = *(pSrc + 2) * 3 - *(pSrc + 1) - *pSrc;
		if (temp < 0)
		{
			temp = 0;
		};
		*pDst = temp / 3;
		pSrc += 3;
		pDst++;
	}
	return redness;
}

// uchar sort(uchar* kernel, int n) {	//希尔排序
//	char temp;
//	for (int gap = n / 2; gap > 0; gap /= 2) {
//		for (int i = gap; i < n; i++) {
//			for (int j = i - gap; j >= 0 && kernel[j] > kernel[j + gap]; j -= gap) {
//				temp = kernel[j];
//				kernel[j] = kernel[j + 1];
//				kernel[j + 1] = temp;
//			}
//		}
//	}
//	return kernel[n/2];
// }

void quickSort(uchar *kernel, int l, int r)
{ // 快速排序
	if (l < r)
	{
		int i = l, j = r, x = kernel[l];
		while (i < j)
		{
			while (i < j && kernel[j] >= x)
			{
				j--;
			}
			if (i < j)
			{
				kernel[i++] = kernel[j];
			}
			while (i < j && kernel[i] < x)
			{
				i++;
			}
			if (i < j)
			{
				kernel[j--] = kernel[i];
			}
		}
		kernel[i] = x;
		quickSort(kernel, l, i - 1);
		quickSort(kernel, i + 1, r);
	}
}

void medianFlitering(Mat src, Mat dst, int kRadius)
{ // 单通道中值过滤
	int kSize = (kRadius * 2 + 1) * (kRadius * 2 + 1);
	uchar *kernel = new uchar[kSize];
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if ((i - kRadius) > 0 && (i + kRadius) < src.rows && (j - kRadius) > 0 && (j + kRadius) < src.cols)
			{
				short k = 0;
				for (int m = -kRadius; m <= kRadius; m++)
				{
					for (int n = -kRadius; n <= kRadius; n++)
					{
						kernel[k] = src.at<uchar>(i + m, j + n);
						k++;
					}
				}
				// dst.at<uchar>(i, j) = sort(kernel, (kRadius * 2 + 1)*(kRadius * 2 + 1));
				quickSort(kernel, 0, kSize - 1);
				dst.at<uchar>(i, j) = kernel[kSize / 2];
			}
			else
			{
				dst.at<uchar>(i, j) = src.at<uchar>(i, j);
			}
		}
	}
	delete[] kernel;
}

void mySobel(Mat src, Mat dst)
{ // 单通道sobel算子边缘检测
	uchar *pSrc = src.data, *pDst = dst.data;
	while (pSrc < src.data + src.cols + 1)
	{ // 图像边缘像素处理
		*pDst = 0;
		pSrc++;
		pDst++;
	}
	const uchar *pEnd = src.dataend - src.cols - 1;
	int result;
	while (pSrc < pEnd)
	{
		result = abs(*(pSrc - src.cols - 1) + *(pSrc - src.cols) * 2 + *(pSrc - src.cols + 1) - *(pSrc + src.cols - 1) - *(pSrc + src.cols) * 2 - *(pSrc + src.cols + 1)) + abs(*(pSrc - src.cols - 1) + *(pSrc - 1) * 2 + *(pSrc + src.cols - 1) - *(pSrc - src.cols + 1) - *(pSrc + 1) * 2 - *(pSrc + src.cols + 1));
		if (result > 255)
		{
			result = 255;
		}
		*pDst = result;
		pSrc++;
		pDst++;
	}
	while (pSrc < src.dataend)
	{ // 图像边缘像素处理
		*pDst = 0;
		pSrc++;
		pDst++;
	}
}

void myGaussBlur(Mat src, Mat dst)
{ // 单通道3x3高斯模糊
	double kernel[3][3], sum = 0, sigma = 1.5;
	for (int i = 0; i < 3; i++)
	{ // 生成3x3高斯核
		for (int j = 0; j < 3; j++)
		{
			sum += kernel[i][j] = exp(-((i - 1) * (i - 1) + (j - 1) * (j - 1)) / (sigma * sigma * 2));
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			kernel[i][j] /= sum;
		}
	}
	uchar *pSrc = src.data + src.cols + 1, *pDst = dst.data + dst.cols + 1;
	const uchar *pEnd = src.dataend - src.cols - 1;
	int result;
	while (pSrc < pEnd)
	{
		result = *(pSrc - src.cols - 1) * kernel[0][0] + *(pSrc - src.cols) * kernel[0][1] + *(pSrc - src.cols + 1) * kernel[0][2] + *(pSrc - 1) * kernel[1][0] + *pSrc * kernel[1][1] + *(pSrc + 1) * kernel[1][2] + *(pSrc + src.cols - 1) * kernel[2][0] + *(pSrc + src.cols) * kernel[2][1] + *(pSrc + src.cols + 1) * kernel[2][2];
		if (result > 255)
		{
			result = 255;
		}
		*pDst = result;
		pSrc++;
		pDst++;
	}
}

void myThresh(Mat src, Mat dst, int thresh)
{
	uchar *pSrc = src.data, *pDst = dst.data;
	while (pSrc < src.dataend)
	{
		if (*pSrc < thresh)
		{
			*pDst = 0;
		}
		else
		{
			*pDst = 255;
		}
		pSrc++;
		pDst++;
	}
}

void baseMorphology(Mat src, Mat dst, int flag = 0)
{ // 简单的膨胀与腐蚀算法
	uchar *pSrc = src.data + src.cols + 1, *pDst = dst.data + dst.cols + 1;
	const uchar *pEnd = src.dataend - src.cols - 1;
	uchar kernel[9];
	uchar result;
	while (pSrc < pEnd)
	{
		kernel[0] = *(pSrc - src.cols - 1);
		kernel[1] = *(pSrc - src.cols);
		kernel[2] = *(pSrc - src.cols + 1);
		kernel[3] = *(pSrc - 1);
		kernel[4] = *pSrc;
		kernel[5] = *(pSrc + 1);
		kernel[6] = *(pSrc + src.cols - 1);
		kernel[7] = *(pSrc + src.cols);
		kernel[8] = *(pSrc + src.cols + 1);
		result = kernel[0];
		if (flag)
		{
			for (int i = 1; i < 9; i++)
			{
				if (kernel[i] < result)
				{
					result = kernel[i];
				}
			}
		}
		else
		{
			for (int i = 1; i < 9; i++)
			{
				if (kernel[i] > result)
				{
					result = kernel[i];
				}
			}
		}
		*pDst = result;
		pSrc++;
		pDst++;
	}
}

void myHoughCircle(Mat src, vector<Vec3i> &circles, int minDist, int thresh, int minRadius, int maxRadius)
{
	int radiusRange = maxRadius - minRadius; // 自定义houghCircle，实现了最小圆心距离，累加器阈值，圆的最大最小半径参数的输入
	// 定义并初始化累加器
	int ***count;
	count = new int **[radiusRange];
	for (int i = 0; i < radiusRange; i++)
	{
		count[i] = new int *[src.rows];
	}
	for (int i = 0; i < radiusRange; i++)
	{
		for (int j = 0; j < src.rows; j++)
		{
			count[i][j] = new int[src.cols];
		}
	}
	for (int k = 0; k < radiusRange; k++)
	{
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				count[k][i][j] = 0;
			}
		}
	}
	// 遍历
	int x0 = 0, y0 = 0; // 圆心坐标
	for (int k = 0; k < radiusRange; k++)
	{
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				if (src.at<uchar>(i, j) > 0)
				{ // 判断是否为检测点
					// cout << "x:" << j << "\ty:" << i << endl;
					for (int theta = 0; theta <= 360; theta++)
					{
						double t = (theta * PI) / 180;
						x0 = (int)(j - (k + minRadius) * cos(t));
						y0 = (int)(i - (k + minRadius) * sin(t));
						if (x0 > 0 && x0 < src.cols && y0 > 0 && y0 < src.rows)
						{
							count[k][y0][x0]++;
						}
					}
				}
			}
		}
	}
	// 将超过阈值的累加器存入circles向量
	for (int k = 0; k < radiusRange; k++)
	{
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				if (count[k][i][j] > thresh)
				{
					Vec3i c;
					c[0] = j;
					c[1] = i;
					c[2] = k + minRadius;
					if (circles.size() > 0)
					{
						bool pass = false; // 用于去除距离过近的圆
						for (int s = 0; s < circles.size(); s++)
						{
							Vec3i d = circles[s];
							int dist = (int)sqrt((float)(pow((j - d[0]), 2) + pow((i - d[1]), 2)));
							// cout << "j:" << j << "\td[0]:" << d[0] << "\ti:" << i << "\td[1]:" << d[1] << endl;
							// cout << "dist:"<< dist << endl;
							if (dist < minDist)
							{
								pass = true;
								break; // 存在距离过近的圆即跳出循环
							}
						}
						if (!pass)
						{ // 不存在距离过近的圆即加入circles
							circles.push_back(c);
						}
					}
					else
					{
						circles.push_back(c);
					}
				}
			}
		}
	}
	// cout << "circles nums:" <<circles.size() << endl;
	for (int i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		cout << "x0:" << c[0] << "\ty0:" << c[1] << "\tr:" << c[2] << endl;
	}

	// 释放内存，防止内存泄漏
	for (int i = 0; i < radiusRange; i++)
	{
		for (int j = 0; j < src.rows; j++)
		{
			delete[] count[i][j];
			count[i][j] = NULL;
		}
	}
	for (int i = 0; i < radiusRange; i++)
	{
		delete[] count[i];
		count[i] = NULL;
	}
	delete[] count;
	count = NULL;
}

int main()
{
	Mat src = imread("apple1.jpg");
	imshow("src", src);
	Mat temp1(src.rows, src.cols, CV_8UC1, Scalar(0));
	Mat temp2(src.rows, src.cols, CV_8UC1, Scalar(0));
	temp1 = getRedness(src);
	myGaussBlur(temp1, temp1);
	medianFlitering(temp1, temp1, 3);
	// imshow("median", temp1);
	mySobel(temp1, temp2);
	// imshow("sobel",temp2);
	myThresh(temp2, temp1, 80);
	// imshow("thresh", temp1);
	baseMorphology(temp1, temp2, ERODE); //
	// imshow("erode", temp2);				//
	baseMorphology(temp2, temp1, DILATE); // 开运算
	// imshow("mop_open", temp1);
	vector<Vec3i> circles;
	// HoughCircles(sobel, circles, HOUGH_GRADIENT, 1, 30, 100, 15, 5, 50);
	myHoughCircle(temp1, circles, 15, 215, 10, 80);
	cout << "circles nums:" << circles.size() << endl;
	for (int i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		circle(src, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), 1, LINE_AA);
	}
	imshow("result", src);
	waitKey(0);
	return 0;
}
