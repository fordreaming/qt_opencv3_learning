#ifndef FINDCIRCLE_H
#define FINDCIRCLE_H
#include "opencv/headerall.h"

class FindCircle
{
public:
    FindCircle();
    ~FindCircle();
    void getShapeRecognition0(int &type,float circleRate,int &res);
    void getShapeRecognition(float circleRate,int &res);
    void getConcentricRoi(cv::Mat &srcImg,vector<vector<int>> &resVec);
    void getPredictResult0(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type,float &circleRate,int &res);
    void getPredictResult1(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type,float &circleRate,int &res);
    void getPredictResult2(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type,float &circleRate,int &res);

    /***********************************************************************
     *  @function getPredictResult
     *  @brief    type: 0 表示452工件           1:475工件
     *            flag: 圆孔类型, 0: 梅花孔, 1: normal 2: 下面圆孔
     *  @return
     ***********************************************************************/
    void getPredictResult(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type, int &flag,float &circleRate,int &res);

    void getInnerOuterCirclePointSet(cv::Mat &srcImg,std::vector<cv::Point> &pointVec,std::vector<cv::Point> &pointVec2);
    void getinnerouterRadiusAndcenter(cv::Mat &srcImg, float &innerRadius, float &outerRadius, cv::Point &innercenter,
                                      cv::Point &outercenter);

private:
    float m_innerRadius;
    float m_outerRadius;
    cv::Point m_center;
    cv::Point m_center2;
    std::vector<cv::Point> innerptVec;
    std::vector<cv::Point> outerptVec;
    int cnt;
    int cnt2;
    uchar m_thrend;
};

#endif // FINDCIRCLE_H
