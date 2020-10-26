#ifndef POINTSMATCH_H
#define POINTSMATCH_H

//#include "headerall.h"

#include <cmath>
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
class PointsMatch
{
public:
    PointsMatch();
    double getLossShapeMatch(std::vector<float> test_x, std::vector<float> test_y, std::vector<float> standard_x, std::vector<float> standard_y);
    void getClosestPoint(float x, float y, std::vector<float> sourcePoints_x, std::vector<float> sourcePoints_y, double& find_x, double& find_y);
    int getClosestPointID(double x, double y, std::vector<float> sourcePoints_x, std::vector<float> sourcePoints_y);
    double getDistanceOfTwoPoints(double x1, double y1, double x2, double y2);
    void getTranslationVector(std::vector<float> source_x, std::vector<float> source_y,std::vector<float> standard_x, std::vector<float> standard_y, double &tx, double &ty,double &sxc, double &syc);
    void ICP(std::vector<float> source_x, std::vector<float> source_y,
        std::vector<float> standard_x, std::vector<float> standard_y,
        std::vector<float> &trans_x, std::vector<float> &trans_y, double &stheta);
};
#endif // POINTSMATCH_H
