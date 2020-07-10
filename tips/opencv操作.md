继承关系：CvArr >> CvMat >>IplImage  
CvMat 是opencv面向c语言的数据结构，Mat是面向c++的数据结构
# 〇、数据类型
>https://blog.csdn.net/cindywry/article/details/81240510  
`IplImage *src1;`  
`src1 = cvLoadImage("7.jpg");`  
IplImage中ROI参数的思想是：一旦设定ROI，通常作用于整幅图像的函数便会只对ROI所表示的子图像进行操作，以下为设定函数。  
`void cvSetImageROI( IplImage* image, CvRect rect );`  
`void cvResetImageROI( IplImage* image );`  

>CvPoint        int x, y                  图像中的点  
>CvPoint2D32f   float x, y                二维空间中的点  
>CvPoint3D32f   float x, y, z             三维空间中的点  
>CvSize         int width, height         图像的尺寸  
>CvRect         int x, y, width, height   图像的部分区域  
>CvScalar       double val[4]             RGBA 值  

# 一、转换关系（CvMat，Mat）
1. CvMat之间的复制
>深拷贝 - 单独分配空间，两者相互独立
```CvMat* a;
   CvMat* b = cvCloneMat(a);
```

2. Mat之间的复制
>浅拷贝，不复制数据只创建矩阵头，数据共享（更改a,b,c的任意一个都会对另外2个产生同样的作用） 
```Mat a;
   Mat b = a;
   Mat c(a);
```
>深拷贝
``` Mat a;
    Mat b = a.clone();
    Mat c;
    a.copyTo(c); 
```
3. CvMat转Mat
>使用Mat的构造函数：Mat::Mat(const CvMat* m, bool copyData=false); 默认情况下copyData为false 
    CvMat* a;
>注意：以下三种效果一致，均为浅拷贝
``` Mat b(a);
    Mat b(a, false);
    Mat b = a;
```
>注意：当将参数copyData设为true后，则为深拷贝（复制整个图像数据）
`Mat b = Mat(a, true);`

4. Mat转CvMat
>浅拷贝
``` Mat a;
    CvMat b = a;
```
>深拷贝
``` Mat a;
    CvMat *b; 
    CvMat temp = a; //转化为CvMat类型，而不是复制数据 
    cvCopy(&temp, b); //真正复制数据 
```

# 二、矩阵和图像操作(CvMat)
>https://blog.csdn.net/zhurui_idea/article/details/28856755
1. 取出矩阵中最大最小值
```
   void cvMinMaxLoc(
	const CvArr* arr,//目标矩阵
	double* min_val,//最小值
	double* max_val,//最大值
	CvPoint* min_loc = NULL,//最小值位置
	CvPoint* max_loc = NULL,//最大值位置
	const CvArr* mask = NULL//矩阵“开关”
	);
```
2. 两个矩阵对应元素相乘
```
   void cvMul(
	const CvArr* src1,//矩阵1
	const CvArr* src2,//矩阵2
	CvArr* dst,//结果矩阵
	double scale = 1//因子系数
	);
```
3. 元素按位取反
```
    void cvNot(
    	const CvArr* src,//目标矩阵
    	CvArr* dst//结果矩阵
	);
```
4. 计算各种范式
```
   double cvNorm(
	const CvArr* arr1,//矩阵1
	const CvArr* arr2 = NULL,//矩阵2
	int norm_type = CV_L2,//选择范式标量
	const CvArr* mask = NULL//矩阵“开关”
	);
```
>https://blog.csdn.net/zhurui_idea/article/details/28668677
5. 矩阵最值操作  
   比较两个图像取最大值
```
   void cvMax(
    	const CvArr* src1,//图像1
    	const CvArr* src2,//图像2
    	CvArr* dst//结果矩阵
    );
```
   比较两个图像取最小值
```
   void cvMin(
    	const CvArr* src1,//图像1
    	const CvArr* src2,//图像2
    	CvArr* dst//结果图像
    );
```
6. 矩阵与标量的最值操作  
   比较图像与给定值取最大值
```
    void cvMaxS(
    	const CvArr* src1,//图像1
    	double value,//给定值
    	CvArr* dst//结果矩阵
    );
```
   比较图像取与给定标量最小值
```
    void cvMinS(
    	const CvArr* src1,//图像1
    	double value,//比較标量
    	CvArr* dst//结果图像
    );
```
7. 分离和合并通道(cvSplit  cvMerge)
```
    int main(int argc, char** argv)
    {
	IplImage *src1,*src2,*dst11,*dst12,*dst13;
 
	src1=cvLoadImage("5.jpg");
	src2=cvLoadImage("7.jpg");
 
	dst11 = cvCreateImage(cvSize(src1->width, src1->height), IPL_DEPTH_8U, 1);
	dst12 = cvCreateImage(cvSize(src1->width, src1->height), IPL_DEPTH_8U, 1);
	dst13 = cvCreateImage(cvSize(src1->width, src1->height), IPL_DEPTH_8U, 1);
 
	cvSplit(src1, dst11, dst12, dst13, 0);//分解
 
	cvMerge(dst11,dst12,dst13,NULL,src2);
 
	cvShowImage( "测试", src2);
 
 
	cvWaitKey();
	return 0;
    }
```
>https://blog.csdn.net/zhurui_idea/article/details/29178365
8. 计算arr各通道所有像素总和
```
   CvScalar cvSum(
    	CvArr* arr//目标矩阵
    );
```
9. 计算 A = U*W*(V的转置)
```
   void cvSVD(
	CvArr* A,
	CvArr* W,
	CvArr* U = NULL,
	CvArr* V = NULL,
	int flags = 0//标记位
    );
```
10. 计算X=V*(W伴随)*(T转置)*B
```
   void cvSVBKSb(
	const CvArr* W,
	const CvArr* U,
	const CvArr* V,
	const CvArr* B,
	CvArr* X,
	int flage = 0//标记位
    );
```
11. 求矩阵的迹
```
   CvScalar cvTrace(
	const CvArr* mat//目标矩阵
    );
```
12. 矩阵转置
```
   void cvTranspose(
    	const CvArr* src,//目标矩阵
    	CvArr* dst//结果矩阵
    );
```
13. 异或操作  
矩阵异或操作
```
   void cvXor(
	const CvArr* src1,//矩阵1
	const CvArr* src2,//矩阵2
	CvArr* dst,//结果矩阵
	const CvArr* mask = NULL//矩阵“开关”
	);
```
   矩阵与给定值进行异或操作
```
   void cvXor(
	const CvArr* src1,//矩阵1
	CvScalar value//给定值
	CvArr* dst,//结果矩阵
	const CvArr* mask = NULL//矩阵“开关”
	);
```
14. 将图像所有通道设置为零
```
   void cvZero(
	CvArr* arr//目标图像
	);
```

# 三、Mat相关操作
>https://www.cnblogs.com/cyrus-ho/p/4156015.html
```
cv::Mat a(3,2,CV_8UC1,cv::Scalar(127));
cv::Mat b(3,2,CV_8UC1,cv::Scalar(128));
```
## 修改mask获得指定掩模
```
cv::Mat mask(3,2,CV_8UC1,255);//默认全体操作
```
## 算术运算
```
double alpha;
double beta;
cv::Mat c;
cv::add(a,b,c,mask); // a+b元素级相加,结果放到c，下面的类似
cv::scaleAdd(a, alpha, b, c, mask); // a*alpha+b, 元素级相加，其中一个矩阵带缩放
cv::addWeighted(a, alpha, b beta, c, mask); // a*alpha+b*beta, 元素级相加，两个矩阵分别带缩放系数 （还可以带偏移gamma）
cv::subtract(a,b,c,mask); // 元素级相减
cv::abs(a,c); // 取绝对值
cv::absdiff(a,b,c); // 元素级相减取绝对值 （个人很好奇为何不是absDiff而是全小写）
cv::multiply(a,b,c,mask); // 元素级乘法
cv::divide(a,b,c,mask); // 元素级除法, 类似的操作还有log，sqrt，exp，pow，min，max
```
cv::compare(a,b,c, cv::CMP_GT); 
>元素级比较大小，结果存放在c中，条件满足则为255，否则为0，就是说c是一个元素类型CV_8UC1的矩阵
>条件关系 CMP_GT 大于 --- CMP_GE 大于等于 --- CMP_LT 小于 --- CMP_LE 小于等于 --- CMP_EQ 等于 --- CMP_NE 不等于
## 逻辑运算
`cv::bitwise_or(a,b,c,mask); `// 元素级或运算
>类似的还有bitwise_and等，注意这个不仅仅是元素级，还是位运算，例如a某个元素是128，b对应位置的元素是0，则它们进行bitwise_or的结果，对应位置是128，如果b对应位置的元素是1，那么结果对应位置就是129（因为128最后一位是0，和1的最后一位（也就是1）相或后得到1，128的前边的位数都保留了，得到129），同理如果a的元素是129，b对应元素是1，那么结果该位置还是129

# 五、四维张量的创建及索引
>注意四维张量的元素类型，step意味着跳过多少个字节去找该元素，float32占4个字节，所以最后一维step[3]=4， 而第三维step[2]=4*C,说明需要跳过第四维的元素数索引到第三维的下一个元素，step[1]=4*C*W, step[0]=4*C*H。
```
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
```  
# 六、图片索引
>注意由图片读入的Mat，查看其step[2]为无效值，好像opencv对这类Mat默认了其step[2]，也就是通道维的step。
```
Mat frame=cv::Imread("*.jpg");
for(int h=0; h<frame.rows; h++){
    for(int w=0; w<frame.cols; w++){
        uchar B=frame.at<Vec3b>(h, w)[0];
        uchar G=frame.at<Vec3b>(h, w)[1];
        uchar R=frame.at<Vec3b>(h, w)[2];
        // float P=frame.at<Vec3f>(h, w)[0]; // 如果Mat为 CV_32FC3类型
    }
}
```
