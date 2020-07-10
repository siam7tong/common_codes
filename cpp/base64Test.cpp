/****************************************************************************
name: base64Test.cpp
date: 2020/5/23
func: opencv支持下的图片base64编解码
maintainer: zhaoliang
****************************************************************************/

#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>

#include"base64.h"

using namespace std;
using namespace cv;
 
int main()
{
	Mat img = imread("/home/zl/Pictures/hotmap.jpg");

    std::vector<unsigned char> buffer;
    cv::imencode(".jpg", img, buffer);
    string src(buffer.begin(), buffer.end());
	string imgbase64 = base64_encode((BYTE const*)src.c_str(), src.length());     //实现图片的base64编码
	cout << imgbase64 << endl;

    std::vector<unsigned char> str_decoded_byte = base64_decode(imgbase64);
    Mat mat = cv::imdecode(str_decoded_byte, CV_LOAD_IMAGE_COLOR);
    cv::imwrite("2.jpg", mat);
	
    return 0;    
}
