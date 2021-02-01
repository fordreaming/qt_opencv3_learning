#include "imgproc.h"

ImgProc::ImgProc()
{

}

void ImgProc::ImageBinary(const cv::Mat &srcImg, cv::Mat& dstImg)
{
    threshold(srcImg, dstImg, 0, 255, CV_THRESH_OTSU);
}
