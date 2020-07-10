####################opencv四维张量创建及索引
int sizes[] = {1, INPUT_H, INPUT_W, 3};  #NHWC
Mat input(4, sizes, CV_32F, frame.data);

for(int h=0; h<2; h++){
    for(int w=0; w<2; w++){
        for(int c=0; c<3; c++){
            float *p = (float *) input.data+h*input.step[1]+
                           w*input.step[2]+c*input.step[3];
            cout << "p:" << *p << endl;
        }
    }
}
注意四维张量的元素类型，step意味着跳过多少个字节去找该元素，float32占4个字节，所以最后一维step[3]=4， 而第三维step[2]=4*C,说明需要跳过第四维的元素数索引到第三维的下一个元素，step[1]=4*C*W, step[0]=4*C*H。

################对于直接imread读入的图片Mat，默认CV_8UC3
Mat frame=cv::Imread("*.jpg");
for(int h=0; h<frame.rows; h++){
    for(int w=0; w<frame.cols; w++){
        uchar B=frame.at<Vec3b>(h, w)[0];
        uchar G=frame.at<Vec3b>(h, w)[1];
        uchar R=frame.at<Vec3b>(h, w)[2];
        // float P=frame.at<Vec3f>(h, w)[0]; // 如果Mat为 CV_32FC3类型
    }
}
注意由图片读入的Mat，查看其step[2]为无效值，好像opencv对这类Mat默认了其step[2]，也就是通道维的step。
