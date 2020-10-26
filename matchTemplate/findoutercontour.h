//#define FINDOUTERCONTOUR_H
//#include "headerall.h"
#include<opencv2/opencv.hpp>
#include<iostream>

class FindOuterContour
{
public:
    FindOuterContour();
    void PeripheralTraversa(cv::Mat srcImg,std::vector<float> &source_x, std::vector<float> &source_y);
    void ScanPoints(cv::Mat imgGray,std::vector<float> &source_x, std::vector<float> &source_y);
    void setNN(int nn);
    void findSquares( const cv::Mat& image, std::vector<std::vector<cv::Point> >& squares );
    void findAdaptiveSquares( const cv::Mat& image, std::vector<std::vector<cv::Point> >& squares );
    void drawSquares( cv::Mat& image, const std::vector<std::vector<cv::Point> >& squares );
    double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 );
    void PerspectiveTransformation(const cv::Mat &image,cv::Mat &dstImage);
    void getsrcTri(std::vector<cv::Point2f> &srcAns);
    int NN;

private:
    float th1;
    float th2;
    float th3;
    cv::Point2f srcTri[4];
    cv::Point2f dstTri[4];
};

//#endif // FINDOUTERCONTOUR_H
