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


vector<double> GetGaussianKernal1D(int ksize, double sigma) {
    vector<double> kernal(ksize, 0);
    int center_i = (ksize >> 1);

    double sum{0.0f};
    for(size_t i = 0; i < ksize; i++) {
        kernal[i] = exp(-(1.0f)* (i - center_i)*(i - center_i) / (2.0f * sigma * sigma));
        sum += kernal[i];
    }

    // normalization
    for(size_t i = 0; i < ksize; i++) {
        kernal[i] /= sum;
    }

    return kernal;
}


vector<vector<double>> getGaussianKernel2D(int ksize, double sigmax, double sigmay) {
    vector<vector<double>> kernal(ksize, vector<double>(ksize, 0));
    int center_i = (ksize >> 1);
    int center_j = (ksize >> 1);

    double sum{0.0f};
    for(size_t i = 0; i < ksize; i++) {
        for(size_t j = 0; j < ksize; j++) {
            kernal[i][j] = exp(-(1.0f)* ((i - center_i)*(i - center_i) + (j - center_j) * (j - center_j)) / (2.0f * sigmax * sigmay));
            sum += kernal[i][j];
        }
    }

    // normalization
    for(size_t i = 0; i < ksize; i++) {
        for(size_t j = 0; j < ksize; j++) {
            kernal[i][j] /= sum;
        }
    }

    return kernal;
}

void ShowImg(const string& win_name, const cv::Mat src) {
    cv::namedWindow(win_name, WINDOW_NORMAL);
    cv::resizeWindow(win_name, cv::Size(500, 500));
    imshow(win_name, src);
    cvWaitKey(300000);
    cv::destroyWindow(win_name);
}

void GaussianBlurC(const cv::Mat& src, const vector<vector<double>>& kernal, int ksize) {
    cv::Mat dst = src.clone();

    ShowImg("dst", dst);

    for(size_t i = 0; i < src.rows; i++) {
        for(size_t j = 0; j < src.cols; j++) {

        }
    }
    getchar();
}


int main() {
    cv::Mat img = imread("/home/adt/qt/gitFordreaming/qt_opencv3_learning/HoughLineDetect/images/hough_line_detect.png",
                         IMREAD_GRAYSCALE);
    ShowImg("color", img);
//    vector<double> gaussian_kernal = GetGaussianKernal1D(3, 1.5);
    vector<vector<double>> gaussian_kernal = getGaussianKernel2D(3, 5.0, 5.0);

    for(size_t i = 0; i < gaussian_kernal.size(); i++) {
        for(size_t j = 0; j < gaussian_kernal[i].size(); j++) {
            std::cout << gaussian_kernal[i][j] << "     ";
        }
        std::cout << std::endl;
    }

    GaussianBlurC(img, gaussian_kernal, 3);

    detect(img);
}
