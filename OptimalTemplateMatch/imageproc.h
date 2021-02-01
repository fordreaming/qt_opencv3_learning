#ifndef IMAGEPROC_H
#define IMAGEPROC_H

#include "common.h"

class ImageProc
{
public:
    ImageProc();

    /***********************************************************************
     *  @function
     *  @brief  image binary
     *  @return
     ***********************************************************************/
    void ImageBinary(const cv::Mat &srcImg, cv::Mat& dstImg);

    /***********************************************************************
     *  @function
     *  @brief
     *  @return
     ***********************************************************************/
    cv::Mat GetOptimalTemplate(const cv::Mat& imgTemplateWhole, const QString& imgDirectory, int templateIndex);

    /***********************************************************************
     *  @function
     *  @brief    get template image compare to image directory's each image
     *            diff, expect^2 + sigma^2
     *  @return
     ***********************************************************************/
    double GetTemplateFeatureCompareToDirectory(const cv::Mat& imgTemplate, const QString& imgDirectory);

    void CaptureImgPiece(cv::Mat& optimalTemplate, const QString& imgDirectory, const QString& imgSavePath);

    /***********************************************************************
    *函数功能：基于matchTemplate函数检测原图像中所有的目标
    *参数说明：
    *         image：输入原图像
    *         templ：输入的模板图像
    *         sim:   相似度，0~1之间，越接近0越相似
     ***********************************************************************/
    cv::Mat GetTemplateImg(cv::Mat& image, cv::Mat& templ, double sim);

    /***********************************************************************
     *  @function GetTemplateImg
     *  @brief    get template image self implement
     *  @retur
     ***********************************************************************/
    void GetTemplateImg(const cv::Mat& image, const cv::Mat& templateImg, int matchedImgPos, cv::Mat& matchedImg);




private:
    void InitTmeplateBoxRange();
    QStringList LoadFiles(const QString &path, QString ext);
    bool IsImageValid(const cv::Mat& img, int posX, int posY, int width, int height);

    /***********************************************************************
     *  @function
     *  @brief
     *  @return
     ***********************************************************************/
    double ClacMinMeanAndSigma(const std::vector<int>& dataVec);

    void GetAllMinLoc(Mat image, Mat templ, double sim,Scalar mask, vector<Point> *all_min_loc);




private:
    struct TemplateBoxRange
    {
        int TopLeftXMin;
        int TopLeftXMax;
        int TopLeftYMin;
        int TopLeftYMax;
        int widthMin;
        int widthMax;
        int heightMin;
        int heightMax;

        TemplateBoxRange(){}
        TemplateBoxRange(int topLeftXMin_, int topLeftXMax_, int topLeftYMin_, int topLeftYMax_,
                         int widthMin_, int widthMax_, int heightMin_, int heightMax_):
            TopLeftXMin(topLeftXMin_),
            TopLeftXMax(topLeftXMax_),
            TopLeftYMin(topLeftYMin_),
            TopLeftYMax(topLeftYMax_),
            widthMin(widthMin_),
            widthMax(widthMax_),
            heightMin(heightMin_),
            heightMax(heightMax_)
        {}
    };

    vector<TemplateBoxRange>        m_templateBoxRangeVec;
    vector<cv::Mat>                 m_templatMatPiece;
    vector<double>                  m_minMeanSigma;
    QStringList                     m_fileNameWithPath;
};

#endif // IMAGEPROC_H
