#ifndef COMMON_H
#define COMMON_H
//std lib
#include <iostream>
#include <vector>
using namespace std;

//#qt
#include <QString>
#include <QDir>
#include <QStringList>
#include <QMap>
#include <QDebug>
#include <QTime>

//OMP
#include "gomp/omp.h"

//#opencv
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

enum MATCHED_IMG_POSITION {
    MATCHED_IMG_POSITION_TOP_LEFT = 0,
    MATCHED_IMG_POSITION_TOP_RIGHT,
    MATCHED_IMG_POSITION_DOWN_LEFT,
    MATCHED_IMG_POSITION_DOWN_RIGHT,
};

#endif // COMMON_H
