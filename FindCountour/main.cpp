#include <iostream>
#include <math.h>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

cv::Mat src, dst, gray_src;
char input_image[] = "input image";
char output_image[] = "output image";

#define CALC_AVER_BOX_WIDTH 10

int calculateAver(const cv::Mat &img, int x, int y, int width, int height)
{
    int sum = 0;
    for(int i = y; i < height + y; ++i){
        const uchar *data = img.ptr<uchar>(i);
        for(int j = x; j < width + x; ++j){
            sum += data[j];
        }
    }
    return sum/(width*height);
}

int imgThreshold(const Mat &src, Mat &dst, int percision)
{
    cvtColor(src, dst, COLOR_RGB2GRAY);
    int topLeft  = calculateAver(dst, 0, 0, CALC_AVER_BOX_WIDTH, CALC_AVER_BOX_WIDTH);
    int topRight = calculateAver(dst, dst.cols - CALC_AVER_BOX_WIDTH, 0, CALC_AVER_BOX_WIDTH, CALC_AVER_BOX_WIDTH);
    int bottomLeft = calculateAver(dst, 0, dst.rows - CALC_AVER_BOX_WIDTH, CALC_AVER_BOX_WIDTH, CALC_AVER_BOX_WIDTH);
    int bottomRight = calculateAver(dst, dst.cols - CALC_AVER_BOX_WIDTH, dst.rows - CALC_AVER_BOX_WIDTH, CALC_AVER_BOX_WIDTH, CALC_AVER_BOX_WIDTH);
    int backGroundColor = (topLeft + topRight + bottomLeft + bottomRight)/4;
    for(int i = 0; i < dst.rows; ++i){
        for(int j = 0; j < dst.cols; ++j){
            if(dst.at<uchar>(i, j) - backGroundColor > percision || backGroundColor - dst.at<uchar>(i, j) > percision){
                dst.at<uchar>(i, j) = 255;
            }else{
                dst.at<uchar>(i, j) = 0;
            }
        }
    }
    return backGroundColor;
}

int main(int argc, char ** argv)
{

    cv::Mat src0 = imread("0571/0571-0001-06.jpg");
    src = cv::imread("0571/0571-0001-06.jpg");
    if (src.empty()){
        printf("colud not load image ..\n");
        return -1;
    }
    double percision = (mean(src))[0];
    std::cout << "percison: " << percision << std::endl;
//    namedWindow(input_image, CV_WINDOW_AUTOSIZE);
//    namedWindow(output_image, CV_WINDOW_AUTOSIZE);
//    imshow(input_image, src);

    Mat blurImg;
    GaussianBlur(src, blurImg, Size(5, 5), 0, 0);
    imshow("input image", src);

    Mat binary;
//    cvtColor(blurImg, gray_src, COLOR_BGR2GRAY);
//    threshold(gray_src, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);

    int bkColor = imgThreshold(blurImg, binary, percision/2);
    cout << "back color: " << bkColor << endl;
    imshow("binary", binary);

    // change my own


    // 闭操作进行联通物体内部
    Mat morphImage;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    morphologyEx(binary, morphImage, MORPH_CLOSE, kernel, Point(-1, -1), 2);
    imshow("morphology", morphImage);

    // 获取最大轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hireachy;
    findContours(morphImage, contours, hireachy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
    Mat connImage = Mat::zeros(src.size(), CV_8UC3);
    for (size_t t = 0; t < contours.size(); t++){
        Rect rect = boundingRect(contours[t]);
        if (rect.height < src.rows / 2) continue;
        if (rect.height > src.rows - 20) continue;

        vector<Point> approx;
        approxPolyDP(contours[t], approx, 5, true);
        double area = contourArea(approx);
        double len = arcLength(contours[t], true);
        double vertices = approx.size();

        //contour Moments
        Moments mu = moments(contours[t], false );
        Point2f mc = Point2d( mu.m10/mu.m00 , mu.m01/mu.m00 );

        drawContours(src0, contours, t, Scalar(0, 0, 255), 1, 8, hireachy);
        circle(src0, mc, 5, Scalar( 0, 0, 255), -1, 8, 0 );
        rectangle(src0, boundingRect(contours.at(t)), cvScalar(0,255,0));
        char tam[100];
        sprintf(tam, "(%0.0f,%0.0f)",mc.x,mc.y);
        putText(src0, tam, Point(mc.x, mc.y), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255,0,255),1);


        printf("area of star could : %f \n", area);
        printf("lenght of star could : %f \n", len);
        printf("approx poly vertices: %f \n", vertices);
    }



    imshow(output_image, src0);
    imwrite("biggest.jpg", src0);

    waitKey(0);
    return 0;
}
