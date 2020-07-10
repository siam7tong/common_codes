/****************************************************************************
name: autoBrightness&Contrast.cpp
date: 2020/5/22
func: 用于自动调节图片的亮度，对比度
maintainer: zhaoliang
****************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;
using namespace cv;

vector<string> split(const string& str, const string& delim);

void fixedAdjust(Mat src, Mat& dst)
{
	int height = src.rows;
	int width = src.cols;
	dst = Mat::zeros(src.size(), src.type());
	float alpha = 1.2; 				//这里是图像的对比度
	float beta = 40; 				//这里是图像的亮度

	Mat m1;
	src.convertTo(m1, CV_32F);
	//原来图像是8位的，不能进行 Vec3f 取值，所以需要转换成32位的
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (src.channels() == 3) {
				float b = m1.at<Vec3f>(row, col)[0];
				float g = m1.at<Vec3f>(row, col)[1];
				float r = m1.at<Vec3f>(row, col)[2];
                                // mat张量索引
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);
			}
			else if (src.channels() == 1) {
				float gray = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = saturate_cast<uchar>(gray * alpha + beta);
			}
		}
	}
}

void autoAdjust(const cv::Mat &src, cv::Mat &dst, float clipHistPercent=0, int histSize = 255, int lowhist = 0)
{
    
    CV_Assert(clipHistPercent >= 0);
    CV_Assert((src.type() == CV_8UC1) || (src.type() == CV_8UC3) || (src.type() == CV_8UC4));
    
    float alpha, beta;
    double minGray = 0, maxGray = 0;
    
    //to calculate grayscale histogram
    cv::Mat gray;
    if (src.type() == CV_8UC1) gray = src;
    else if (src.type() == CV_8UC3) cvtColor(src, gray, CV_BGR2GRAY);
    else if (src.type() == CV_8UC4) cvtColor(src, gray, CV_BGRA2GRAY);
    if (clipHistPercent == 0)
    {
        // keep full available range
        cv::minMaxLoc(gray, &minGray, &maxGray);
    }
    else
    {
        cv::Mat hist; //the grayscale histogram
        
        float range[] = { 0, 256 };
        const float* histRange = { range };
        bool uniform = true;
        bool accumulate = false;
        calcHist(&gray, 1, 0, cv::Mat (), hist, 1, &histSize, &histRange, uniform, accumulate);
        
        // calculate cumulative distribution from the histogram
        std::vector<float> accumulator(histSize);
        accumulator[0] = hist.at<float>(0);
        for (int i = 1; i < histSize; i++)
        {
            accumulator[i] = accumulator[i - 1] + hist.at<float>(i);
        }
        
        // locate points that cuts at required value
        float max = accumulator.back();
        
        int clipHistPercent2;
        clipHistPercent2 = clipHistPercent * (max / 100.0); //make percent as absolute
        clipHistPercent2 /= 2.0; // left and right wings
        // locate left cut
        minGray = 0;
        while (accumulator[minGray] < clipHistPercent2)
            minGray++;
        
        // locate right cut
        maxGray = histSize - 1;
        while (accumulator[maxGray] >= (max - clipHistPercent2))
            maxGray--;
    }
    
    // current range
    float inputRange = maxGray - minGray;
    
    alpha = (histSize - 1) / inputRange;   // alpha expands current range to histsize range
    beta = -minGray * alpha + lowhist;             // beta shifts current range so that minGray will go to 0
    
    // Apply brightness and contrast normalization
    // convertTo operates with saurate_cast
    src.convertTo(dst, -1, alpha, beta);
    
    // restore alpha channel from source
    if (dst.type() == CV_8UC4)
    {
        int from_to[] = { 3, 3};
        cv::mixChannels(&src, 4, &dst,1, from_to, 1);
    }
}


int main(int argc, char** argv) 
{

    Mat src, dst1, dst2;
    src = imread("test.jpg");
    fixedAdjust(src, dst1);   // 固定调节亮度
    autoAdjust(dst1, dst2);  // 自动调节对比度，亮度
    imwrite("out.jpg", dst2);

    
    return 0;
}



