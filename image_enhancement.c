# 直方图均衡化
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
 
using namespace cv;
 
int main(int argc, char *argv[])
{
	Mat image = imread("Test.jpg", 1);
	if (image.empty())
	{
		std::cout << "打开图片失败,请检查" << std::endl;
		return -1;
	}
	imshow("原图像", image);
	Mat imageRGB[3];
	split(image, imageRGB);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(imageRGB[i], imageRGB[i]);
	}
	merge(imageRGB, 3, image);
	imshow("直方图均衡化图像增强效果", image);
	waitKey();
	return 0;
}

# 拉普拉斯算子增强局部的图像对比度
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
 
using namespace cv;
 
int main(int argc, char *argv[])
{
	Mat image = imread("Test.jpg", 1);
	if (image.empty())
	{
		std::cout << "打开图片失败,请检查" << std::endl;
		return -1;
	}
	imshow("原图像", image);
	Mat imageEnhance;
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
	filter2D(image, imageEnhance, CV_8UC3, kernel);
	imshow("拉普拉斯算子图像增强效果", imageEnhance);
	waitKey();
	return 0;
}


# 对数变换增强
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>
 
using namespace cv;
 
int main(int argc, char *argv[])
{
	Mat image = imread("Test.jpg");
	Mat imageLog(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
			imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
			imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
		}
	}
	//归一化到0~255  
	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
	//转换成8bit图像显示  
	convertScaleAbs(imageLog, imageLog);
	imshow("Soure", image);
	imshow("after", imageLog);
	waitKey();	
	return 0;
}

# 伽马变换增强
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>
 
using namespace cv;
 
int main(int argc, char *argv[])
{
	Mat image = imread("Test.jpg");
	Mat imageGamma(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			imageGamma.at<Vec3f>(i, j)[0] = (image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0]);
			imageGamma.at<Vec3f>(i, j)[1] = (image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1]);
			imageGamma.at<Vec3f>(i, j)[2] = (image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2]);
		}
	}
	//归一化到0~255  
	normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
	//转换成8bit图像显示  
	convertScaleAbs(imageGamma, imageGamma);
	imshow("原图", image);
	imshow("伽马变换图像增强效果", imageGamma);
	waitKey();
	return 0;
}
