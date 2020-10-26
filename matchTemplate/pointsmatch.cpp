#include "pointsmatch.h"

PointsMatch::PointsMatch()
{

}

// algorithm ICP
// source_x,source_y: points need to trans
// standard_x,standard_y: points are target
// trans_x,trans_y: points that are source points after transform
void PointsMatch::ICP(std::vector<float> source_x, std::vector<float> source_y,
                      std::vector<float> standard_x, std::vector<float> standard_y,
                      std::vector<float> &trans_x, std::vector<float> &trans_y, double &stheta)
{
    std::vector<float> A_x = standard_x;
    std::vector<float> A_y = standard_y;
    std::vector<float> B_x = source_x;
    std::vector<float> B_y = source_y;
    stheta = 0.0;
    int iter_times = 0;
    double loss_now;
    double loss_improve = 1000;
    double loss_before = getLossShapeMatch(source_x, source_y, standard_x, standard_y) / standard_x.size();

    double A_x_sum = std::accumulate(std::begin(A_x), std::end(A_x), 0.0);
    double A_x_mean = A_x_sum / A_x.size();
    double A_y_sum = std::accumulate(std::begin(A_y), std::end(A_y), 0.0);
    double A_y_mean = A_y_sum / A_y.size();

    std::vector<float> A_x_;
    std::vector<float> A_y_;
    A_x_.resize(A_x.size());
    A_y_.resize(A_x.size());
    for (int i = 0; i < A_x.size(); i++)
    {
        A_x_[i] = A_x[i] - A_x_mean;
        A_y_[i] = A_y[i] - A_y_mean;
    }

    //while (iter_times < 2000 && loss_improve > 0.0005)
    while (iter_times < 20)
    {
        double B_x_sum = std::accumulate(std::begin(B_x), std::end(B_x), 0.0);
        double B_x_mean = B_x_sum / B_x.size();
        double B_y_sum = std::accumulate(std::begin(B_y), std::end(B_y), 0.0);
        double B_y_mean = B_y_sum / B_y.size();

        std::vector<float> B_x_;
        std::vector<float> B_y_;
        B_x_.resize(B_x.size());
        B_y_.resize(B_x.size());
        for (int i = 0; i < B_x.size(); i++)
        {
            B_x_[i] = B_x[i] - B_x_mean;
            B_y_[i] = B_y[i] - B_y_mean;
        }

        double w_up = 0;
        double w_down = 0;
        for (int i = 0; i < A_x_.size(); i++)
        {
            int id = getClosestPointID(A_x_[i], A_y_[i], B_x_, B_y_);
            double w_up_i = A_x_[i] * B_y_[id] - A_y_[i] * B_x_[id];
            double w_down_i = A_x_[i] * B_x_[id] + A_y_[i] * B_y_[id];
            w_up = w_up + w_up_i;
            w_down = w_down + w_down_i;
        }

        double theta = atan2(w_up, w_down);
        double x = A_x_mean - cos(theta)*B_x_mean - sin(theta)*B_y_mean;
        double y = A_y_mean + sin(theta)*B_x_mean - cos(theta)*B_y_mean;
        stheta += theta;
        for (int i = 0; i < B_x.size(); i++)
        {
            double xx = B_x[i];
            double yy = B_y[i];
            B_x[i] = cos(theta)*xx + sin(theta)*yy + x;
            B_y[i] = -sin(theta)*xx + cos(theta)*yy + y;
        }

        iter_times++;
        double loss_now = getLossShapeMatch(B_x, B_y, A_x, A_y )/ A_x.size();
        loss_improve = loss_before - loss_now;
        //std::cout<<"itertime: "<<iter_times<<", loss now: "<<loss_now<<", improve: "<<loss_improve<<std::endl;
        loss_before = loss_now;
        if (loss_now < 5e-4)break;

    }

    trans_x = B_x;
    trans_y = B_y;
}

// get all points distance of {[test_x, test_y]} and {[standard_x,standard_y]} as loss
double PointsMatch::getLossShapeMatch(std::vector<float> test_x, std::vector<float> test_y, std::vector<float> standard_x, std::vector<float> standard_y)
{
    double loss_sum = 0;
    for (int i = 0; i < standard_x.size(); i++)
    {
        double closest_x, closest_y;
        getClosestPoint(standard_x[i], standard_y[i], test_x, test_y, closest_x, closest_y);
        double loss = getDistanceOfTwoPoints(standard_x[i], standard_y[i], closest_x, closest_y);
        loss_sum = loss_sum + loss;
    }
    return loss_sum;
}

// get closet point of [x,y] in {[sourcePoints_x, sourcePoints_y]}
void PointsMatch::getClosestPoint(float x, float y, std::vector<float> sourcePoints_x, std::vector<float> sourcePoints_y, double& find_x, double& find_y)
{
    double dist_min = 10000000;
    for (int i = 0; i < sourcePoints_x.size(); i++)
    {
        double dist = getDistanceOfTwoPoints(x, y, sourcePoints_x[i], sourcePoints_y[i]);
        if (dist < dist_min)
        {
            dist_min = dist;
            find_x = sourcePoints_x[i];
            find_y = sourcePoints_y[i];
        }
    }
}

int PointsMatch::getClosestPointID(double x, double y, std::vector<float> sourcePoints_x, std::vector<float> sourcePoints_y)
{
    int id = 0;
    double dist_min = 1000000;
    for (int i = 0; i < sourcePoints_x.size(); i++)
    {
        double dist = getDistanceOfTwoPoints(x, y, sourcePoints_x[i], sourcePoints_y[i]);
        if (dist < dist_min)
        {
            dist_min = dist;
            id = i;
        }
    }
    return id;
}

// distance of two points (x1, y1) and (x2, y2)
double PointsMatch::getDistanceOfTwoPoints(double x1, double y1, double x2, double y2)
{
    //return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return sqrt((x1 - x2)*(x1-x2) + (y1 - y2)*(y1-y2));
}

void PointsMatch::getTranslationVector(std::vector<float> source_x, std::vector<float> source_y,
                                       std::vector<float> standard_x, std::vector<float> standard_y,
                                       double &tx, double &ty, double &sxc, double &syc)
{
    std::vector<float> A_x = standard_x;
    std::vector<float> A_y = standard_y;
    std::vector<float> B_x = source_x;
    std::vector<float> B_y = source_y;
    double A_x_sum  = std::accumulate(std::begin(A_x), std::end(A_x), 0.0);
    double A_x_mean = A_x_sum / A_x.size();
    double A_y_sum  = std::accumulate(std::begin(A_y), std::end(A_y), 0.0);
    double A_y_mean = A_y_sum / A_y.size();
    double B_x_sum  = std::accumulate(std::begin(B_x), std::end(B_x), 0.0);
    double B_x_mean = B_x_sum / B_x.size();
    double B_y_sum  = std::accumulate(std::begin(B_y), std::end(B_y), 0.0);
    double B_y_mean = B_y_sum / B_y.size();

    tx = B_x_mean - A_x_mean;
    ty = B_y_mean - A_y_mean;
    sxc=A_x_mean;
    syc=A_y_mean;

}

