#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/****************倾斜校正子程序*****************/
//函数名称：IplImage *Rotate(IplImage *RowImage）
//功能：对每行数字进行倾斜校正
//入口参数：行图像RowImage
//出口参数：旋转后的图像RotateRow
/********************************************/
IplImage *Rotate(IplImage *RowImage)
{
    //建立储存边缘检测结果图像canImage
    IplImage *canImage=cvCreateImage(cvGetSize(RowImage),IPL_DEPTH_8U,1);
    //进行边缘检测
    cvCanny(RowImage,canImage,30,200,3);
    //进行hough变换
    CvMemStorage *storage=cvCreateMemStorage();
    CvSeq *lines=NULL;
    lines=cvHoughLines2(canImage,storage,CV_HOUGH_STANDARD,1,CV_PI/180,20,0,0);
    //统计与竖直夹角<30度的直线个数以及其夹角和
    int numLine=0;
    float sumAng=0.0;
    for(int i=0;i<lines->total;i++)
    {
        float *line=(float *)cvGetSeqElem(lines,i);
        float theta=line[1];  //获取角度 为弧度制
        if(theta<30*CV_PI/180 || (CV_PI-theta)<30*CV_PI/180 )
        {
            numLine++;
            sumAng=sumAng+theta;
        }
    }
    //计算出平均倾斜角，anAng为角度制
    float avAng=(sumAng/numLine)*180/CV_PI;

    //获取二维旋转的仿射变换矩阵
    CvPoint2D32f center;
    center.x=float (RowImage->width/2.0);
    center.y=float (RowImage->height/2.0);
    float m[6];
    CvMat M = cvMat( 2, 3, CV_32F, m );
    cv2DRotationMatrix( center,avAng,1, &M);
    //建立输出图像RotateRow
    double a=sin(sumAng/numLine);
    double b=cos(sumAng/numLine);
    int width_rotate=int (RowImage->height*fabs(a)+RowImage->width*fabs(b));
    int height_rotate=int (RowImage->width*fabs(a)+RowImage->height*fabs(b));
    IplImage *RotateRow=cvCreateImage(cvSize(width_rotate,height_rotate),IPL_DEPTH_8U,1);
    //变换图像，并用黑色填充其余值
    m[2]+=(width_rotate-RowImage->width)/2;
    m[5]+=(height_rotate-RowImage->height)/2;
    cvWarpAffine(RowImage,RotateRow, &M,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS,cvScalarAll(0));
    //释放
    cvReleaseImage(&canImage);
    cvReleaseMemStorage(&storage);
    return RotateRow;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
