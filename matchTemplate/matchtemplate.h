#ifndef MATCHTEMPLATE_H
#define MATCHTEMPLATE_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
class MatchTemplate
{
public:
    MatchTemplate();
    void GetAllMinLoc(Mat image, Mat templ, double sim,Scalar mask, vector<Point> *all_min_loc);
    void multimatch(cv::Mat img,cv::Mat img_temp);
    void multimatch(cv::Mat img,cv::Mat img_temp,cv::Mat &img_matchResult);
    void matchTemplateBatch(std::string srcImgpath,cv::Mat tempImg,std::string resultpath,cv::Mat matchResult );
    void matchTemplateOne(cv::Mat srcImage,cv::Mat modelImage);
    void binaryImg(cv::Mat srcImg,cv::Mat &binaryResultImg);
    void matrixMinus(cv::Mat binaryImg1,cv::Mat binaryImg2,cv::Mat &resultImg);
    int twoImgsCalcNonzero(cv::Mat binaryImg1,cv::Mat binaryImg2,int &n);
};

#endif // MATCHTEMPLATE_H

