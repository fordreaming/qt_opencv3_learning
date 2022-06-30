//#include <QCoreApplication>

#include <iostream>
#include <string>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;


//vector<vector<double>> GetGaussianKernel(int ksize, double sigma) {

//}

vector<double> GetGaussianLinearKernal(int ksize, double sigma) {
    vector<double> kernal(ksize, 0);
//    int center_i = (ksize >> 1);

//    double sum{0.0f};
//    for(size_t i = 0; i < ksize; i++) {
//        kernal[i] = exp(-(1.0f)* (i - center_i)*(i - center_i) / (2.0f * sigma * sigma));
//        sum += kernal[i];
//    }

//    // normalization
//    for(size_t i = 0; i < ksize; i++) {
//        kernal[i] /= sum;
//    }

    return kernal;
}

int main()
{
//    vector<double> gaussian_kernal = GetGaussianLinearKernal(3, 1.5);
//    for(size_t i = 0; i < gaussian_kernal.size(); i++) {
//        std::cout << gaussian_kernal[i] << "   " << std::endl;
//    }

    return 0;
}
