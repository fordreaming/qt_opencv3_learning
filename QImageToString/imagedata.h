#ifndef CIMAGEDATA_H
#define CIMAGEDATA_H
#include <QString>
#include <QImage>
#include <vector>
#include <QColor>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>

namespace image_proc {
using std::vector;
using namespace cv;

class CImageData
{
public:
    CImageData();
    ~CImageData();

public:
    /***********************************************************************
     *  @function LoadFile
     *  @brief    Loads an image from the file with the given fileName
     *  @return   Returns true if the image was successfully loaded;
     *            otherwise invalidates the image and returns false;
    ***********************************************************************/
    static bool LoadFile(QString fileName, QImage &img);

    /***********************************************************************
     *  @function LoadFile
     *  @brief    Loads an image mat unchanged from the file with the given fileName
     *  @return   Returns true if the image was successfully loaded;
     *            otherwise invalidates the image mat and returns false;
     ***********************************************************************/
    static bool LoadFile(QString fileName, cv::Mat &img);

    /***********************************************************************
     *  @function ImageToGray8
     *  @brief    convert QImage to gray value with 8 bit
     *  @return   Returns true if the image was successfully converted and
     *            the rows, cols of the image;
     *            otherwise return false
     *            NOTE!!!!!!!!!:accurately returns the blue component of the RGB;
     ***********************************************************************/
    static bool ImageToGray8(const QImage &img, std::vector<unsigned char> &v_gray, int &rows, int &cols);

    /***********************************************************************
     *  @function
     *  @brief
     *  @return
     ***********************************************************************/
    static bool ImageToColor(QImage &img, std::vector<unsigned char> &v_gray, int &rows, int &cols);


    /***********************************************************************
     *  @function ImageToString
     *  @brief    Encodes an QImage object into a memory buffer
     *            img: QImage object to be written
     *            ext: File extension that defines the output format
     *  @return   the string of specific image format
     ***********************************************************************/
    static bool ImageToString(const QImage &img, const std::string &ext, std::string imgString);

    /***********************************************************************
     *  @function ImageToCvMat
     *  @brief    convert QImage to Mat of opencv
     *  @return   the struct of Mat of opencv
     ***********************************************************************/
    static void ImageToCvMat(const QImage &img, cv::Mat &mat);


    /***********************************************************************
     *  @function
     *  @brief
     *  @return
     ***********************************************************************/
    static QImage CvmatToQImage(const cv::Mat mat);

    /***********************************************************************
     *  @function
     *  @brief
     *  @return
     ***********************************************************************/
    static void SaveImg(const cv::Mat img);

};
}

#endif // CIMAGEDATA_H
