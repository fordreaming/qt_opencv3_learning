#include "imageproc.h"

ImageProc::ImageProc()
{
    InitTmeplateBoxRange();
}

void ImageProc::ImageBinary(const cv::Mat &srcImg, cv::Mat& dstImg)
{
    threshold(srcImg, dstImg, 0, 255, CV_THRESH_OTSU);
}

cv::Mat ImageProc::GetOptimalTemplate(const cv::Mat& imgTemplateWhole, const QString& imgDirectory, int templateIndex)
{
    // load binaray image files
    QStringList fileNameList = LoadFiles(imgDirectory, "*.jpg");
    // change image template positon
    for(int posX = m_templateBoxRangeVec[templateIndex].TopLeftXMin; posX < m_templateBoxRangeVec[templateIndex].TopLeftXMax; posX++) {
        for(int posY = m_templateBoxRangeVec[templateIndex].TopLeftYMin; posY < m_templateBoxRangeVec[templateIndex].TopLeftYMax; posY++) {
            for(int width = m_templateBoxRangeVec[templateIndex].widthMin; width < m_templateBoxRangeVec[templateIndex].widthMax; width++) {
                for(int height = m_templateBoxRangeVec[templateIndex].heightMin; height < m_templateBoxRangeVec[templateIndex].heightMax; height++) {
                    // judge template box is valid
                    if(IsImageValid(imgTemplateWhole, posX, posY, width, height)) {
                        qDebug() << "posX:" << posX << "posY:" << posY << "width:" << width << "height:" << height << endl;
                        Rect rect(posX, posY, width, height);
                        cv::Mat templateImgPiece = imgTemplateWhole(rect).clone();

                        vector<int> noneZeroVec;
                        foreach (QString fileName, fileNameList) {
                            std::string fileNameWithPath = (imgDirectory + fileName).toStdString();
                            cv::Mat comparedImg = imread(fileNameWithPath, 0);
                            threshold(comparedImg, comparedImg, 0, 255, CV_THRESH_OTSU);
                            // find compared image piece
                            cv::Mat matchedImg;
                            GetTemplateImg(comparedImg, templateImgPiece, MATCHED_IMG_POSITION_TOP_LEFT, matchedImg);
                            // calculate diff
                            cv::Mat diffImg;
                            cv::absdiff(templateImgPiece, matchedImg, diffImg);
                            std::vector<cv::Point> locations;
                            cv::findNonZero(diffImg, locations);
                            int noneZeroNum = locations.size();
                            noneZeroVec.push_back(noneZeroNum);
                        }
                        double minMeanAndSigma = ClacMinMeanAndSigma(noneZeroVec);
                        m_templatMatPiece.push_back(templateImgPiece);
                        m_minMeanSigma.push_back(minMeanAndSigma);
                    }
                }
            }
        }
    }
    // find min mean and sigma correspond to template mat
    auto minMeanSigma = std::min_element(std::begin(m_minMeanSigma), std::end(m_minMeanSigma));
    int minMeanSigmaIndex = std::distance(std::begin(m_minMeanSigma), minMeanSigma);
    cv::Mat optimalTemplateMat = m_templatMatPiece[minMeanSigmaIndex];
    return optimalTemplateMat;
}

double ImageProc::GetTemplateFeatureCompareToDirectory(const Mat &imgTemplate, const QString &imgDirectory)
{
    return 0.0;
}

void ImageProc::CaptureImgPiece(Mat &optimalTemplate, const QString &imgDirectory, const QString &imgSavePath)
{
    QStringList fileNameList = LoadFiles(imgDirectory, "*.jpg");
    // capture image accord to optimal image template
    foreach (QString fileName, fileNameList) {
        std::string fileNameWithPath = (imgDirectory + fileName).toStdString();
        cv::Mat imgSrc = imread(fileNameWithPath, 0);
        cv::Mat matchedImg;
//        matchedImg = GetTemplateImg(imgSrc, optimalTemplate, 0.01);
        GetTemplateImg(imgSrc, optimalTemplate, MATCHED_IMG_POSITION_TOP_LEFT, matchedImg);
        // save image
        imwrite(imgSavePath.toStdString(), matchedImg);
    }
}

Mat ImageProc::GetTemplateImg(Mat& image, Mat& templ, double sim)
{
    vector<Point> P;
    if(image.empty()) {
        std::cout << "image empty" << std::endl;
    }
    qDebug() << "image type:" << image.channels() << endl;
    GetAllMinLoc(image, templ, sim, Scalar(0, 0, 0), &P);

    cv::Mat img_matchResult;
    for (int k = 0; k < P.size(); k++)
    {
        Point loc = P[k];
        Rect rect = Rect(loc.x, loc.y, templ.cols, templ.rows);
        //获取匹配部分的roi图像
        cv::Mat result_image = image.clone();
        rectangle(image, Rect(loc.x, loc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2, 8);
        cv::Mat result_imageROI = result_image(rect);

        img_matchResult = result_imageROI.clone();
    }
    return img_matchResult.clone();
}

void ImageProc::GetTemplateImg(const cv::Mat& image, const cv::Mat& templateImg, int matchedImgPos, cv::Mat& matchedImg)
{
    // find i, j range accord to matched image position
    int minCol = 0;
    int maxCol = 0;
    int minRow = 0;
    int maxRow = 0;
    switch(matchedImgPos) {
    case MATCHED_IMG_POSITION_TOP_LEFT:
        minCol = 0;
        maxCol = image.cols/2;
        minRow = 0;
        maxRow = image.rows/2;
        break;
    case MATCHED_IMG_POSITION_TOP_RIGHT:
        minCol = image.cols/2;;
        maxCol = image.cols/2 - templateImg.cols;
        minRow = 0;
        maxRow = image.rows/2;
        break;
    case MATCHED_IMG_POSITION_DOWN_LEFT:
        minCol = 0;;
        maxCol = image.cols/2;
        minRow = image.rows/2;
        maxRow = image.rows - templateImg.rows;
        break;
    case MATCHED_IMG_POSITION_DOWN_RIGHT:
        minCol = image.cols/2;;
        maxCol = image.cols/2 - templateImg.cols;
        minRow = image.rows/2;
        maxRow = image.rows - templateImg.rows;
        break;
    default:
        break;
    }
    int height = image.rows;
    int width = image.cols;


    int noneZeroNumMax = templateImg.rows * templateImg.cols;
    QTime startTime = QTime::currentTime();
#pragma omp parallel for num_threads(4)
    for(int i = minCol; i < maxCol; i += 2) {
        for(int j = minRow; j < maxRow; j += 2) {
            cv::Rect cutImgRect(i, j, templateImg.cols, templateImg.rows);

            cv::Mat cutImg = image(cutImgRect).clone();
            cv::Mat diffImg;
            cv::absdiff(cutImg, templateImg, diffImg);
            std::vector<cv::Point> locations;
            cv::findNonZero(diffImg, locations);
            int noneZeroNum = locations.size();
            if(noneZeroNumMax > noneZeroNum) {
                noneZeroNumMax = noneZeroNum;
                matchedImg = cutImg.clone();
            }
        }
    }
    QTime stopTime = QTime::currentTime();
    qDebug() << "time elpased: " << startTime.msecsTo(stopTime) << endl;
}

void ImageProc::InitTmeplateBoxRange()
{
    TemplateBoxRange L1TemplateBoxRange = TemplateBoxRange(987, 1008, 609, 633, 183, 222, 112, 144);
    m_templateBoxRangeVec.push_back(L1TemplateBoxRange);
}

QStringList ImageProc::LoadFiles(const QString &path, QString ext)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << ext;
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    return files;
}

bool ImageProc::IsImageValid(const Mat &img, int posX, int posY, int width, int height)
{
    if(posX + width > img.cols || posY + height > img.rows) {
        return false;
    }
    return true;
}

double ImageProc::ClacMinMeanAndSigma(const std::vector<int> &dataVec)
{
    double sum = std::accumulate(std::begin(dataVec), std::end(dataVec), 0.0);
    double mean =  sum / dataVec.size(); //均值

    double accum  = 0.0;
    std::for_each (std::begin(dataVec), std::end(dataVec), [&](const double d) {
        accum  += (d-mean)*(d-mean);
    });

    double dev = accum;
    return mean*mean + dev;
}

void ImageProc::GetAllMinLoc(Mat image, Mat templ, double sim, Scalar mask, vector<Point> *all_min_loc)
{
    bool test = true;
    int i=0;
    int src_Width = image.cols, src_Height=image.rows;
    int templ_Width=templ.cols, templ_Height=templ.rows;
    double min_value, max_value;
    Point min_Loc, max_Loc;
    Mat img_result(image.size(), CV_32FC1);
    Mat img_clon = image.clone();
    if (templ_Width > src_Width || templ_Height > src_Height)
    {
        printf("模板尺寸大于原图像，请选择正确的模板\n");
        exit;
    }

    while(1)
    {
        matchTemplate(img_clon, templ, img_result, TM_SQDIFF_NORMED);
        minMaxLoc(img_result, &min_value, &max_value, &min_Loc, &max_Loc);
        if (min_value < sim)//检测结果符合预期范围
        {
            all_min_loc->push_back(min_Loc);
            rectangle(img_clon, Rect(min_Loc.x, min_Loc.y, templ_Width, templ_Height), mask, -1);
        }
        else
            break;
    }
}
