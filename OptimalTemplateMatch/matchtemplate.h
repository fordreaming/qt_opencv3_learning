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

    /***********************************************************************
     *  @function     *函数功能：基于matchTemplate函数检测原图像中所有的目标
    *参数说明：
    *         image：输入原图像
    *         templ：输入的模板图像
    *         sim:   相似度，0~1之间，越接近0越相似
    *         mask： 覆盖区颜色,一般情况下直接取黑色即可Scalar(0,0,0)
    *         *all_min_loc：所有匹配到的目标的坐标
     *  @brief
     *  @return
     ***********************************************************************/
    void GetAllMinLoc(Mat image, Mat templ, double sim,Scalar mask, vector<Point> *all_min_loc);

    void multimatch(cv::Mat img,cv::Mat img_temp);
    void multimatch(cv::Mat img,cv::Mat img_temp,cv::Mat &img_matchResult);
    void matchTemplateBatch(std::string srcImgpath,cv::Mat tempImg,std::string resultpath,cv::Mat matchResult );
    /***********************************************************************
     *  @function ExtarctMatchTemplateCenter
     *  @brief    在原图像中进行模板匹配并找到圆心位置
     *            该圆心坐标是相对于原图
     *  @return
     ***********************************************************************/
    void ExtarctMatchTemplateCenter(const cv::Mat &srcImg, const cv::Mat &templateImg, vector<cv::Point> &circleCenter);

    void matchTemplateOne(cv::Mat srcImage,cv::Mat modelImage);
    void binaryImg(cv::Mat srcImg,cv::Mat &binaryResultImg);
    void matrixMinus(cv::Mat binaryImg1,cv::Mat binaryImg2,cv::Mat &resultImg);
    int twoImgsCalcNonzero(cv::Mat binaryImg1,cv::Mat binaryImg2,int &n);


    /***********************************************************************
    *  @function
    *  @brief
    *  @return
    ***********************************************************************/
    void multimatch(cv::Mat srcImg, cv::Mat templateImg, cv::Mat &matchResult, int a );
};

#endif // MATCHTEMPLATE_H

