#ifndef IMGPROC_H
#define IMGPROC_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class ImgProc
{
public:
    ImgProc();
    /***********************************************************************
     *  @function
     *  @brief  image binary
     *  @return
     ***********************************************************************/
    void ImageBinary(const cv::Mat &srcImg, cv::Mat& dstImg);

};

#endif // IMGPROC_H
