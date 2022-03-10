#include <iostream>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;

#ifndef IMG_SHOW_DEBUG
#define IMG_SHOW_DEBUG
#endif

cv::RNG rng(12345);

void ImgShow(const string &window_name, const Mat &src)
{
#ifdef IMG_SHOW_DEBUG
    cv::namedWindow(window_name, WINDOW_NORMAL);
    cv::resizeWindow(window_name, cv::Size(500, 500));
    imshow(window_name, src);
    cvWaitKey(300000);
    cv::destroyWindow(window_name);
#endif
}

int detect(cv::Mat img) {
    cv::Mat can_img, gray_img;
    cv::cvtColor(img, gray_img, CV_BGR2GRAY);
    cv::Mat input_img = gray_img.clone();
    cv::Canny(input_img, can_img, 150, 230, 3);

    ImgShow("canny image", can_img);

    std::vector<cv::Vec4i> lines_;
    cv::HoughLinesP(can_img, lines_, 1., CV_PI / 180, 50, 50, 6);

    for(size_t i = 0; i < lines_.size(); i++) {
        cv::Vec4i line_ = lines_[i];
        cv::line(img, cv::Point(line_[0], line_[1]),
                cv::Point(line_[2], line_[3]),
                cv::Scalar(0, 0,255), 1, CV_AA);
        ImgShow("draw_line", img);
    }

    return 0;
}


int main() {
    cv::Mat img = imread("/home/adt/qt/gitFordreaming/qt_opencv3_learning/HoughLineDetect/images/hough_line_detect.png",
                         IMREAD_COLOR);
    detect(img);
}
