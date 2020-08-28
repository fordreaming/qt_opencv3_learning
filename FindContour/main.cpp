#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

Mat src, dst, gray_src;
char input_image[] = "input image";
char output_image[] = "output image";

int main(int argc, char ** argv){

    src = imread("case6.jpg");
    if (src.empty()){
        printf("colud not load image ..\n");
        return -1;
    }

    namedWindow(input_image, CV_WINDOW_AUTOSIZE);
    namedWindow(output_image, CV_WINDOW_AUTOSIZE);
    imshow(input_image, src);

    // 均值降噪
    Mat blurImg;
    GaussianBlur(src, blurImg, Size(15, 15), 0, 0);
    imshow("input image", src);

    // 二值化
    Mat binary;
    cvtColor(blurImg, gray_src, COLOR_BGR2GRAY);
    Threshold(gray_src, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
    imshow("binary", binary);

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
        if (rect.width < src.cols / 2) continue;
        if (rect.width > src.cols - 20) continue;

        double area = contourArea(contours[t]);
        double len = arcLength(contours[t], true);


        drawContours(connImage, contours, t, Scalar(0, 0, 255), 1, 8, hireachy);
        printf("area of star could : %f \n", area);
        printf("lenght of star could : %f \n", len);
    }
    imshow(output_image, connImage);



    waitKey(0);
    return 0;
}
