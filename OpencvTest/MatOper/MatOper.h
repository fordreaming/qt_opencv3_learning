#ifndef MATOPER_H
#define MATOPER_H

#include <iostream>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;


class MatOper
{
public:
    MatOper();

    /***********************************************************************
     *  @function
     *  @brief
     *  @param
     *  @return
    ***********************************************************************/
    void CreateMat();


private:
    cv::Mat                      m_mat;
};

#endif // MATOPER_H
