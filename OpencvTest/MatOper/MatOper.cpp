#include "MatOper.h"

MatOper::MatOper()
{

}

void MatOper::CreateMat()
{
    cv::Mat m;
    m.create(3, 10, CV_32FC3);
    m.setTo(cv::Scalar(1.0f, 0.0f, 1.0f));

    cout << m.at<float>(0, 0) << endl;
    cout << m.at<float>(0, 1) << endl;

    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
//            cout << m.at<cv::Vec2f>(0, 0)[0]
//                    << "   "
//                    << m.at<cv::Vec2f>(0, 0)[1]
//                    << endl;
        float *data = m.ptr<float>(i, j);
        cout << data << " " << (data + 1) << endl;
        }
    }


//    cout << "pointer access" << endl;
//    cout << m.ptr<Vec3f>(3) << endl;
//    cout << *(m.ptr<Vec3f>(3))<< endl;
//    cout << (m.ptr<Vec3f>(3)[1])<< endl;
}
